#include "console.h"

//construction/destruction
    console::console(unsigned int bitSize):
        metal(bitSize),
        printingMode(0),
        buffer( std::vector<unsigned int>() ),
        prePrintBuffer_stageCode(0),
        prePrintBuffer_selectedCode(0)
        {
            //populate prePrint buffer
                for(unsigned int a = 0; a < (pow(2,8)/2)-4; a++){ prePrintBuffer.push_back( std::vector<unsigned int>() ); }
        }
    console::~console(){}

//readers and writers
    bool console::readBit(unsigned int bit){
    //reads bit from the front value on the buffer. This does not pop the value.
        if(debugMode){ std::cout << "console - readBit - reading bit: " << bit << std::endl; } 
        if(buffer.size() == 0){
            if(debugMode){ std::cout << "console - readBit - buffer is empty, returning 0" << bit << std::endl; } 
            return false;
        }

        if(debugMode){ std::cout << "console - readBit - value found: " << getBitFromUINT(buffer[0], bit) << std::endl; } 
        return getBitFromUINT(buffer[0], bit);
    }

    void console::writeBit(unsigned int bit, bool value){ 
    //creates byte with this single bit adjusted, sending byte to write method
    //If result is larger than the bitSize can support; the resulting byte will be zero.
        if(debugMode){ 
            std::cout << "console - writeBit - writing bit: " << value << " to the bit " << bit << " creating the number: " << BINtoUINT( resize(adjustBIN("0",bit,value),getBitSize())) << std::endl;
            if( BINtoUINT( resize(adjustBIN("0",bit,value),getBitSize()) ) == 0 ){ std::cout << "console - writeBit - result is zero; will prompt for input" << std::endl; }
        } 

        write(BINtoUINT( resize(adjustBIN("0",bit,value),getBitSize())) );
    }

    unsigned int console::read(){
    //popping off value from buffer. If there are no values, return zero
        if(debugMode){ std::cout << "console - reading value" << std::endl; } 
        if( buffer.size() == 0 ){ if(debugMode){ std::cout << "console - end of input, returing 0" << std::endl; } return 0; }

        //popping
            unsigned int temp = buffer[0];
            buffer.erase(buffer.begin());

        if(debugMode){ std::cout << "console - returning value: " << temp << std::endl; } 
        return temp;
    }

    void console::write(unsigned int value){ 
    //selection of printing mode
        if(value == 128){ 
            if(debugMode){ std::cout << "console - entering preprint buffer writing mode" << std::endl; } 
            printingMode = 1;
        }

    //clear all prePrints
        if(value == 130){ 
            if(debugMode){ std::cout << "console - clearing all preprint buffers" << std::endl; } 
            for(unsigned int a = 0; a < prePrintBuffer.size(); a++){ prePrintBuffer[a].clear(); }
        }

    //enter correct mode
        switch(printingMode){
            default: standard_write(value); break;
            case 1:  prePrintBuffer_write(value); break;
        }
    }


//internal writing protocols    
    void console::writeToOutput(unsigned int value){
    //regular print mode
        if(debugMode){ std::cout << "console - writing value: " << value << std::endl; } 

        if( value < 128 ){ /*direct convert value to char*/ std::cout << (char)value; }
        else{//this is a buffer; run through each code in the buffer, pushing them through the writeToOutput function
            unsigned int actualBufferNumber = prePrintBuffer_selectedCode - ((pow(2,8)/2)+4);
            for(unsigned int a = 0; a < prePrintBuffer[actualBufferNumber].size(); a++){
                writeToOutput( prePrintBuffer[actualBufferNumber][a] );
            }
        }
    }

    void console::standard_write(unsigned int value){
    //writes value to console
    //if value is zero, console will be prompted for input which will be placed in the buffer.
    //otherwise, the value will be converted to a char and printed
        //prompt mode
            if( value == 0 ){ 
                //prompt for input
                    if(debugMode){ std::cout << "console - prompting for input" << std::endl; }
                    std::string input;
                    std::getline(std::cin, input);
                //convert input to unsigned int values and append to the buffer
                    if(debugMode){ std::cout << "console - received: " << input << std::endl; }

                    for(unsigned int a = 0; a < input.length(); a++){
                        if(debugMode){ std::cout << "console - converting and pushing to buffer: " << input[a] << " = " << (unsigned int)input[a] << std::endl; }
                        buffer.push_back( (unsigned int)input[a] );
                    }

                    if(debugMode){ std::cout << "console - buffer size: " << buffer.size() << std::endl; }
                    return;
            }

    //actually print value
        writeToOutput(value);
    }

    void console::prePrintBuffer_write(unsigned int value){
        unsigned int actualBufferNumber;

        switch(prePrintBuffer_stageCode){
            default: /*record unknown error and reset state values*/ if(debugMode){ std::cout << "console - preprint buffer - unknown error" << std::endl << "value: " << value << std::endl << "stage: " << prePrintBuffer_stageCode << std::endl << "selected code: " << prePrintBuffer_selectedCode << std::endl; prePrintBuffer_stageCode = 0; prePrintBuffer_selectedCode = 0; printingMode = 0; } break;
            case 0:  /*initial command*/ if(debugMode){ std::cout << "console - preprint buffer - stage 0" << std::endl; }  prePrintBuffer_stageCode++; break;
            case 1:  /*selection of code*/
                if(value <= 131){//attempt to select an uneditable code: record error and reset state values
                    if(debugMode){ std::cout << "console - preprint buffer - writing mode error: invalid code entered for stage 1: " << value << std::endl; } 
                    prePrintBuffer_stageCode = 0; prePrintBuffer_selectedCode = 0; printingMode = 0;
                    return; 
                }

                if(debugMode){ std::cout << "console - preprint buffer - writing stage 1: selected code: " << value << std::endl; } 

                //record selected code and progress to the next stage
                prePrintBuffer_selectedCode = value;
                prePrintBuffer_stageCode++;
            break;
            case 2: /*control of selected buffer*/
                if(debugMode){ std::cout << "console - preprint buffer - stage 2: entered code: " << value << std::endl; } 
                switch(value){
                    default: //add this code to the buffer
                        if(debugMode){ std::cout << "console - preprint buffer - stage 2: pushing value " << value << " to code: " << prePrintBuffer_selectedCode << " (actual buffer number: " << (prePrintBuffer_selectedCode - ((pow(2,8)/2)+4)) << ")" << std::endl; }
                        prePrintBuffer[ prePrintBuffer_selectedCode - ((pow(2,8)/2)+4) ].push_back(value);
                    break;
                    case 129: //clear command
                        if(debugMode){ std::cout << "console - preprint buffer - stage 2: clearing code: " << value << std::endl; }
                        prePrintBuffer[ prePrintBuffer_selectedCode - ((pow(2,8)/2)+4) ].clear();
                    break;
                    case 131: //exit command
                        if(debugMode){ std::cout << "console - preprint buffer - stage 2: exiting preprint buffer writing mode" << std::endl; } 
                        prePrintBuffer_stageCode = 0;
                        printingMode = 0;
                    break;
                }
            break;
        }

    }  

//printers and debug
    void console::printMemory(){
        if(buffer.size() == 0){ std::cout << "-empty-" << std::endl; }

        for(unsigned int a = 0; a < buffer.size(); a++){
            std::cout << buffer[a] << " | " << (char)buffer[a] << std::endl;
        }
    }
    void console::debug(bool onOff){ debugMode = onOff; }