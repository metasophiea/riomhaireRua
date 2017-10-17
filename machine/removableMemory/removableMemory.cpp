#include "removableMemory.h"

//construction/destruction
    removableMemory::removableMemory(unsigned int bitSize, unsigned int memorySize, std::string fileName):
        metal(bitSize),
        memorySize(memorySize),
        debugMode(false),
        fileName(fileName)
        {}
    removableMemory::~removableMemory(){}

//getters and setters
    unsigned int removableMemory::getByte(unsigned int byte){
        if(debugMode){ std::cout << "removableMemory::getByte - getting byte: " << byte << std::endl;}
        if( byte >= memorySize ){std::cout << "removableMemory error - attempting to access unavailable byte: " << byte << " - action will be ignored" << std::endl; return 0;}

        loadedMemory = fopen(fileName.c_str(), "r");
        if( loadedMemory == 0 ){ std::cout << "- no removable storage device attached" << std::endl; return 0; }
        unsigned int currentByte = 0;
        unsigned int tempData = 0;
        std::string tempString;

        //run through memory to to find the correct byte, then break off
        while( currentByte <= byte ){
            tempString = "";
            tempData = fgetc(loadedMemory);
            while( tempData != -1 && tempData != 10 ){
                tempString += (char)tempData;
                tempData = fgetc(loadedMemory);
            }
            if(debugMode){ std::cout << "removableMemory::getByte - currentByte: " << currentByte << " value: " << tempString << std::endl;}

            currentByte++;
        }

        fclose(loadedMemory);
        if(debugMode){ std::cout << "removableMemory::getByte - returning value: " << DECtoUINT(tempString) << std::endl;}
        return DECtoUINT(tempString);
    }
    void removableMemory::setByte(unsigned int byte, unsigned int value){
        if(debugMode){ std::cout << "removableMemory::setByte - setting byte: " << byte << " to the value " << value << std::endl;}
        if( byte >= memorySize ){std::cout << "removableMemory error - attempting to access unavailable byte: " << byte << " - action will be ignored" << std::endl; return;}

        //check if file exists first
            if( fopen(fileName.c_str(), "r") == 0 ){ std::cout << "- no removable storage device attached" << std::endl; return; }

        //rename original file, then set it up for reading and create a new file with the old name for writing
            if(debugMode){ std::cout << "removableMemory::setByte - renaming input file and opening a fresh file" << std::endl;}
            rename(fileName.c_str(), (fileName+".ruaDisk").c_str());
            FILE* loadedMemory_in  = fopen((fileName+".ruaDisk").c_str(),"r");
            FILE* loadedMemory_out = fopen(fileName.c_str(),"w");

        //main work loop
            unsigned int currentByte = 0;
            unsigned int tempData = 0; std::string tempString;
            bool firstPrint = true;
            while( currentByte < memorySize ){

                //reading in byte from first file
                    tempData = fgetc(loadedMemory_in);
                    tempString = "";
                    while( tempData != -1 && tempData != 10 ){
                        tempString += (char)tempData;
                        tempData = fgetc(loadedMemory_in);
                    }
                    if(debugMode){ std::cout << "removableMemory::setByte - currentByte: " << currentByte << " value: " << tempString << std::endl;}

                //writing to second file
                    //if this is the byte, change the string to the new value
                    if( currentByte == byte ){
                        if(debugMode){ std::cout << "removableMemory::setByte - found byte: " << byte << " which has the value " << tempString << std::endl;}
                        tempString = UINTtoDEC_systemSize(value);
                    }

                    //if there's nothing but empty space from here on out and we're past the byte of interest; bail on loop
                    if( tempString.length() == 0 && currentByte > byte ){ 
                        if(debugMode){ std::cout << "removableMemory::setByte - current byte: " << currentByte << " there's nothing but empty space from here on out and we're past the byte of interest: bailing on loop" << tempString << std::endl << std::endl;}
                        break;
                    }

                    //if the string is still empty, set it to zero
                    if( tempString.length() == 0 ){ 
                        if(debugMode){ std::cout << "removableMemory::setByte - byte " << currentByte << " is empty: setting to zero" << std::endl;}
                        tempString = "0";
                    }

                    //next-line before printing (unless this is the very first printing)
                    if( firstPrint ){ firstPrint = false; }
                    else{ fwrite("\n" , sizeof(char), 1, loadedMemory_out); }

                    //print the string to file
                    if(debugMode){ std::cout << "removableMemory::setByte - printing the string " << tempString << " to the output file" << std::endl;}
                    fwrite(tempString.c_str() , sizeof(char), tempString.length(), loadedMemory_out);

                currentByte++;

                if(debugMode){ std::cout << "removableMemory::setByte - end of loop" << std::endl << std::endl;}
            }

        //close files and delete the input file
            if(debugMode){ std::cout << "removableMemory::setByte - closing files and deleting the old file" << std::endl;}
            fclose(loadedMemory_in);
            fclose(loadedMemory_out);
            remove((fileName+".ruaDisk").c_str());
    }
    bool removableMemory::getBit(unsigned int byte, unsigned int bit){
        if(debugMode){ std::cout << "removableMemory::getBit - getting bit: " << bit << " of byte: " << byte << std::endl;}
        if( bit >= getBitSize() ){ std::cout << "removableMemory error - attempting to access unavailable bit: " << bit << " - action will be ignored" << std::endl; return false;}
        return getBitFromUINT(getByte(byte),bit);
    }
    void removableMemory::setBit(unsigned int byte, unsigned int bit, bool value){
        if(debugMode){ std::cout << "removableMemory::setBit - setting bit: " << bit << " of byte: " << byte << " to the value " << value << std::endl;}
        if( byte >= memorySize ){std::cout << "removableMemory error - attempting to access unavailable byte: " << byte << " - action will be ignored" << std::endl; return;}
        if( bit >= getBitSize() ){ std::cout << "removableMemory error - attempting to access unavailable bit: " << bit << " - action will be ignored" << std::endl; return;}
        setByte(byte,BINtoUINT(adjustBIN(UINTtoBIN(getByte(byte)),bit,value)));
    }

//printers and debug
    void removableMemory::printMemory(){
        if(debugMode){ std::cout << "removableMemory::printMemory - printing memory" << std::endl;}
        std::cout << "- memory size: " << memorySize << " bytes" << std::endl;
        std::cout << "- bits per byte: " << getBitSize() << std::endl;
        loadedMemory = fopen(fileName.c_str(), "r");
        if( loadedMemory == 0 ){ std::cout << "- no removable storage device attached" << std::endl; return; }
        std::cout << std::endl;

        //load memory into a temporary array
            rewind(loadedMemory);
            unsigned int memory[memorySize]; 
            unsigned int memoryCounter = 0;
            unsigned int tempData = 0;
            std::string tempString;
            while( memoryCounter < memorySize ){ 
                tempData = fgetc(loadedMemory);
                if( tempData == -1 ){ memory[memoryCounter++] = DECtoUINT(tempString); break; }
                else if( tempData == 10 ){ memory[memoryCounter++] = DECtoUINT(tempString); tempString = ""; }
                else{ tempString += (char)tempData; }
            }
            fclose(loadedMemory);

        //fill in leftover space
            while( memoryCounter < memorySize ){ memory[memoryCounter++] = 0; }

        //print the temporary array
            unsigned int bytePerLine = 50;
            for(unsigned int a = 0; a < memorySize; a++){
                //write y column stuff
                    if( a%bytePerLine == 0 ){ std::cout << resize(std::to_string(a),std::to_string(memorySize).length()) << "|"; }
                
                //write data
                    std::cout << resize(UINTtoHEX(memory[a]),(getBitSize()/4)) << " ";

                //next line
                    if( (a+1)%bytePerLine == 0 ){ std::cout << std::endl; }            
            }
            std::cout << std::endl;
    }
    void removableMemory::debug(bool onOff){ debugMode = onOff; }
    void removableMemory::debug(bool onOff, unsigned int depth){
        debugMode = onOff;
        if(depth > 0){}
    }