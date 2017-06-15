#include <iostream>

#include "accessManager.h"

accessManager::accessManager(unsigned int bitCount, unsigned int memorySize):
    bareMetal(bitCount),
    memoryBlock(bitCount, memorySize),
    console(bitCount)
    {}
accessManager::~accessManager(){}

unsigned int accessManager::size()                                          { return memoryBlock.size(); }
void accessManager::display(){ 
    memoryBlock.display(); 
}

bool accessManager::getBit(std::string byte, unsigned int bit)              { return getBit(HEXtoUINT(byte),bit); }
void accessManager::setBit(std::string byte, unsigned int bit, bool value)  { setBit(HEXtoUINT(byte),bit,value); }
std::string accessManager::getByte(std::string byte)                        { return getByte(HEXtoUINT(byte)); }
void accessManager::clearByte(std::string byte)                             { clearByte(HEXtoUINT(byte)); }
void accessManager::setByte(std::string byte, std::string value)            { setByte(HEXtoUINT(byte),value); }

bool accessManager::getBit(unsigned int byte, unsigned int bit){ 
    switch(byte){
        case console_port: return console.getBit(); break;
        default: return memoryBlock.getBit(byte,bit); break;
    }
}
void accessManager::setBit(unsigned int byte, unsigned int bit, bool value){ 
    switch(byte){
        case console_port: console.writeBit(value); break;
    }
    memoryBlock.setBit(byte,bit,value);
}
std::string accessManager::getByte(unsigned int byte){ 
    switch(byte){
        case console_port: return console.getByte(); break;
        default: return memoryBlock.getByte(byte); break;
    }
}
void accessManager::clearByte(unsigned int byte){ 
    switch(byte){
        case console_port: console.writeByte(localSizeHex("0")); break;
    }
    memoryBlock.clearByte(byte);
}
void accessManager::setByte(unsigned int byte, std::string value){ 
    switch(byte){
        case console_port: console.writeByte(value); break;
    }
    memoryBlock.setByte(byte,value);
}