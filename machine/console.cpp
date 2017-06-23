#include "console.h"

//construction/destruction
    console::console(unsigned int bitSize):
        metal(bitSize),
        buffer( std::vector<unsigned int>() )
        {}
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
        //regular print mode
            if(debugMode){ std::cout << "console - writing value: " << value << std::endl; } 
            if( value < 128 ){ std::cout << (char)value; return; }
            switch(value){
                case 128: std::cout << "riomhaireRua"; return; break;
                default: std::cout << " -unknown character: " + std::to_string(value) + "- "; return; break;
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