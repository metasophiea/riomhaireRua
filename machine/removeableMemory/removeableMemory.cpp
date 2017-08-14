#include "removeableMemory.h"

//construction/destruction
    removeableMemory::removeableMemory(unsigned int bitSize, unsigned int memorySize):
        metal(bitSize),
        memorySize(memorySize),
        debugMode(false),
        fileName("loadedMemory.txt")
        {}
    removeableMemory::~removeableMemory(){}

//getters and setters
    unsigned int removeableMemory::getByte(unsigned int byte){
        loadedMemory = fopen("loadedMemory.txt","r");
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
            currentByte++;
        }

        fclose(loadedMemory);
        return DECtoUINT(tempString);
    }
    void removeableMemory::setByte(unsigned int byte, unsigned int value){
        //rename original file, then set it up for reading and create a new file with the old name for writing
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

                //writing to second file
                    //if this is the byte, change the string to the new value
                    if( currentByte == byte ){ tempString = UINTtoDEC(value); }

                    //if there's nothing but empty space from here on out and we're past the byte of interest; bail on loop
                    if( tempString.length() == 0 && currentByte > byte ){ break; }

                    //if the string is still empty, set it to zero
                    if( tempString.length() == 0 ){ tempString = "0"; }

                    //next-line before printing (unless this is the very first printing)
                    if( firstPrint ){ firstPrint = false; }
                    else{ fwrite("\n" , sizeof(char), 1, loadedMemory_out); }

                    //print the string to file
                    fwrite(tempString.c_str() , sizeof(char), tempString.length(), loadedMemory_out);

                currentByte++;

            }

        //close files and delete the input file
            fclose(loadedMemory_in);
            fclose(loadedMemory_out);
            remove((fileName+".ruaDisk").c_str());
    }
    bool removeableMemory::getBit(unsigned int byte, unsigned int bit){ return getBitFromUINT(getByte(byte),bit); }
    void removeableMemory::setBit(unsigned int byte, unsigned int bit, bool value){ setByte(byte,BINtoUINT(adjustBIN(UINTtoBIN(getByte(byte)),bit,value))); }

//printers and debug
    void removeableMemory::printMemory(){
        std::cout << "removeableMemory - printing memory" << std::endl;
        std::cout << "memory size: " << memorySize << " bytes" << std::endl;
        std::cout << "bits per byte: " << getBitSize() << std::endl;
        std::cout << std::endl;

        loadedMemory = fopen("loadedMemory.txt","r");
        rewind(loadedMemory);

        //load memory into a temporary array
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
    void removeableMemory::debug(bool onOff){ debugMode = onOff; }