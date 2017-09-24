#include <iostream>

#include "memoryBlock.h"

//construction/destruction
    memoryBlock::memoryBlock(unsigned int bitSize, unsigned int memorySize):
        metal(bitSize),
        memorySize(memorySize),
        debugMode(false)
        {
            memory = new unsigned int[memorySize];
            for(unsigned int a = 0; a < memorySize; a++){ memory[a] = 0; }
        }
    memoryBlock::~memoryBlock(){}

//getters and setters
    unsigned int memoryBlock::getByte(unsigned int byte){ 
        if(debugMode){ std::cout << "memoryBlock - getting byte: " << byte << " which has the value " << memory[byte] << std::endl;}
        if( byte >= memorySize ){ std::cout << "memoryBlock error - attempting to access unavailable byte: " << byte << " - action will be ignored" << std::endl; return 0;}
        return memory[byte];
    }
    void memoryBlock::setByte(unsigned int byte, unsigned int value){ 
        if(debugMode){ std::cout << "memoryBlock - setting byte: " << byte << " to the value " << value << std::endl;}
        if( byte >= memorySize ){ std::cout << "memoryBlock error - attempting to access unavailable byte: " << byte << " - action will be ignored" << std::endl; return;}
        memory[byte] = value;
    }
    bool memoryBlock::getBit(unsigned int byte, unsigned int bit){
        if(debugMode){ std::cout << "memoryBlock - getting bit: " << bit << " of the byte " << byte << " which has the value " << memory[byte] << " the bit being: " << getBitFromUINT(memory[byte],bit) << std::endl;}
        if( byte >= memorySize ){ std::cout << "memoryBlock error - attempting to access unavailable byte: " << byte << " - action will be ignored" << std::endl; return false;}
        if( bit >= getBitSize() ){ std::cout << "memoryBlock error - attempting to access unavailable bit: " << bit << " - action will be ignored" << std::endl; return false;}
        return getBitFromUINT(memory[byte],bit);
    }
    void memoryBlock::setBit(unsigned int byte, unsigned int bit, bool value){
        if(debugMode){ std::cout << "memoryBlock - setting bit: " << bit << " of the byte " << byte << " to the value " << value << std::endl;}
        if( byte >= memorySize ){ std::cout << "memoryBlock error - attempting to access unavailable byte: " << byte << " - action will be ignored" << std::endl; return;}
        if( bit >= getBitSize() ){ std::cout << "memoryBlock error - attempting to access unavailable bit: " << bit << " - action will be ignored" << std::endl; return;}

        memory[byte] = BINtoUINT(adjustBIN(UINTtoBIN(memory[byte]),bit,value));
        if(debugMode){ std::cout << "memoryBlock - setting bit - result byte value: " << memory[byte] << std::endl; }
    }

//printers and debug
    void memoryBlock::printMemory(){
        if(debugMode){ std::cout << "memoryBlock - printing memory" << std::endl; }
        unsigned int bytePerLine = 50;

        //y axis numbering, divider and data
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
    void memoryBlock::debug(bool onOff){ debugMode = onOff; }
    void memoryBlock::debug(bool onOff, unsigned int depth){
        debugMode = onOff;
        if(depth > 0){}
    }