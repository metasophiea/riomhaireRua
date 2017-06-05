#include <iostream>

#include "memoryBlock.h"

memoryBlock::memoryBlock(unsigned int bitCount, unsigned int memorySize):
bareMetal(bitCount),memorySize(memorySize)
{
    memory = new unsigned int[memorySize];
    for(unsigned int a = 0; a < memorySize; a++){ memory[a] = 0; }
}
memoryBlock::~memoryBlock(){}

unsigned int memoryBlock::size(){ return memorySize; }

bool memoryBlock::getBit(std::string byte, unsigned int bit){ return getBit(HEXtoUINT(byte),bit); }
bool memoryBlock::getBit(unsigned int byte, unsigned int bit){
    if( byte >= memorySize){ std::cout << "bad byte selected - " << UINTtoHEX(byte) << "/" << UINTtoHEX(memorySize) << std::endl; return false; }
    if( bit >= getBitCount() ){ std::cout << "bad bit provided - " << UINTtoHEX(bit) << "/" << UINTtoHEX(getBitCount()) << std::endl; return false; }
    if( UINTtoBIN(memory[byte])[getBitCount()-bit-1] == '1' ){ return true; }else{ return false; }
}
void memoryBlock::setBit(std::string byte, unsigned int bit, bool value){ setBit(HEXtoUINT(byte),bit,value); }
void memoryBlock::setBit(unsigned int byte, unsigned int bit, bool value){
    if( byte >= memorySize){ std::cout << "bad byte selected - " << UINTtoHEX(byte) << "/" << UINTtoHEX(memorySize) << std::endl; return; }
    if( bit >= getBitCount() ){ std::cout << "bad bit provided - " << UINTtoHEX(bit) << "/" << UINTtoHEX(getBitCount()) << std::endl; return; }
    
    std::string temp = UINTtoBIN(memory[byte]);
    temp[getBitCount()-bit-1] = value ? '1' : '0'; 
    memory[byte] = BINtoUINT(temp);
}

std::string memoryBlock::getByte(std::string byte){ return getByte(HEXtoUINT(byte)); }
std::string memoryBlock::getByte(unsigned int byte){
    if( byte >= memorySize){ std::cout << "bad byte selected - " << UINTtoHEX(byte) << "/" << UINTtoHEX(memorySize) << std::endl; return "0"; }
    return localSizeHex(UINTtoHEX(memory[byte]));
}

void memoryBlock::clearByte(std::string byte){ clearByte(HEXtoUINT(byte)); }
void memoryBlock::clearByte(unsigned int  byte){
    if( byte >= memorySize){ std::cout << "bad byte selected - " << UINTtoHEX(byte) << "/" << UINTtoHEX(memorySize) << std::endl; return; }
    memory[byte] = 0;
}

void memoryBlock::setByte(std::string byte, std::string value){ setByte(HEXtoUINT(byte),value); }
void memoryBlock::setByte(unsigned int byte, std::string value){
    if( byte >= memorySize ){ std::cout << "bad byte selected - " << UINTtoHEX(byte) << "/" << UINTtoHEX(memorySize) << std::endl; return; }
    if( checkForComplyingLength(value) != 0 ){ std::cout << "bad byte value provided - " << value << std::endl; return; } 
    memory[byte] = HEXtoUINT(value);
}

void memoryBlock::display(){
    //x axis numbering
        for(unsigned int b = 0; b < getBitCount()/4; b++){ std::cout << " "; }
        std::cout << " | ";
        for(unsigned int a = 0; a < 16; a++){
            std::cout << localSizeHex(UINTtoHEX(a)) << " ";
        }std::cout << std::endl;

    //x axis divider
        for(unsigned int b = 0; b < getBitCount()/4; b++){ std::cout << "-"; }
        std::cout << "--";
        for(unsigned int a = 0; a < 16; a++){
            std::cout << "-";
            for(unsigned int b = 0; b < getBitCount()/4; b++){ std::cout << "-"; }
        }std::cout << std::endl;

    //y axis numbering, divider and data
        for(unsigned int a = 0; a < memorySize; a+=16){
            std::cout << localSizeHex(UINTtoHEX(a)) << " | ";
            for(unsigned int b = 0; b < 16; b++){
                std::cout << localSizeHex(UINTtoHEX(memory[a+b])) << " ";
            }
            std::cout << std::endl;
        }
}