#include <iostream>

#include "memoryBlock.h"

//construction/destruction
    memoryBlock::memoryBlock(unsigned int bitSize, unsigned int memorySize):
        metal(bitSize),
        memorySize(memorySize)
        {
            memory = new unsigned int[memorySize];
            for(unsigned int a = 0; a < memorySize; a++){ memory[a] = 0; }
        }
    memoryBlock::~memoryBlock(){}

//getters and setters
    unsigned int memoryBlock::getByte(unsigned int byte){ 
        if(debugMode){ std::cout << "memoryBlock - getting byte: " << byte << " which has the value " << memory[byte] << std::endl;}
        if( byte >= memorySize ){ std::cout << "memoryBlock error - attempting to access unavailable byte: " << byte << std::endl; return 0;}
        return memory[byte];
    }
    void memoryBlock::setByte(unsigned int byte, unsigned int value){ 
        if(debugMode){ std::cout << "memoryBlock - setting byte: " << byte << " to the value " << memory[byte] << std::endl;}
        if( byte >= memorySize ){ std::cout << "memoryBlock error - attempting to access unavailable byte: " << byte << std::endl; return;}
        memory[byte] = value;
    }
    bool memoryBlock::getBit(unsigned int byte, unsigned int bit){
        if(debugMode){ std::cout << "memoryBlock - getting bit: " << bit << " of the byte " << byte << " which has the value " << memory[byte] << std::endl;}
        if( byte >= memorySize ){ std::cout << "memoryBlock error - attempting to access unavailable byte: " << byte << std::endl; return false;}
        if( bit >= getBitSize() ){ std::cout << "memoryBlock error - attempting to access unavailable bit: " << bit << std::endl; return false;}
        return getBitFromUINT(memory[byte],bit);
    }
    void memoryBlock::setBit(unsigned int byte, unsigned int bit, bool value){
        if(debugMode){ std::cout << "memoryBlock - setting bit: " << bit << " of the byte " << byte << " to the value " << value << std::endl;}
        if( byte >= memorySize ){ std::cout << "memoryBlock error - attempting to access unavailable byte: " << byte << std::endl; return;}
        if( bit >= getBitSize() ){ std::cout << "memoryBlock error - attempting to access unavailable bit: " << bit << std::endl; return;}

        memory[byte] = BINtoUINT(adjustBIN(UINTtoBIN(memory[byte]),bit,value));
        if(debugMode){ std::cout << "memoryBlock - setting bit - result byte value: " << memory[byte] << std::endl; }
    }

//printers and debug
    void memoryBlock::printMemory(){
        if(debugMode){ std::cout << "memoryBlock - printing memory" << std::endl; }
        //y axis numbering, divider and data
            for(unsigned int a = 0; a < memorySize; a+=16){
                std::cout << resize(UINTtoHEX(a),UINTtoHEX(memorySize-1).length()) << " | ";
                for(unsigned int b = 0; b < 16; b++){ std::cout << resize(UINTtoHEX(memory[a+b]),(getBitSize()/4)) << " ";}
                std::cout << std::endl;
            }
    }
    void memoryBlock::debug(bool onOff){ debugMode = onOff; }