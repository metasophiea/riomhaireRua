#include <iostream>

#include "accessManager.h"

accessManager::accessManager(unsigned int bitCount, unsigned int memorySize):
bareMetal(bitCount),memoryBlock(bitCount, memorySize),console(bitCount){}
accessManager::~accessManager(){}

unsigned int accessManager::size()                                          { return memoryBlock.size(); }
void accessManager::display(){ memoryBlock.display(); }

bool accessManager::getBit(std::string byte, unsigned int bit)              { return getBit(HEXtoUINT(byte),bit); }
void accessManager::setBit(std::string byte, unsigned int bit, bool value)  { setBit(HEXtoUINT(byte),bit,value); }
std::string accessManager::getByte(std::string byte)                        { return getByte(HEXtoUINT(byte)); }
void accessManager::clearByte(std::string byte)                             { clearByte(HEXtoUINT(byte)); }
void accessManager::setByte(std::string byte, std::string value)            { setByte(HEXtoUINT(byte),value); }

bool accessManager::getBit(unsigned int byte, unsigned int bit){ 
    if( byte == console_port ){ return console.getBit(); }
    else{ return memoryBlock.getBit(byte,bit); }
}
void accessManager::setBit(unsigned int byte, unsigned int bit, bool value){ 
    if( byte == console_port ){ console.writeBit(value); }
    else{ memoryBlock.setBit(byte,bit,value); }
}
std::string accessManager::getByte(unsigned int byte){ 
    if( byte == console_port ){ return console.getByte(); }
    else{ return memoryBlock.getByte(byte); }
}
void accessManager::clearByte(unsigned int byte){ 
    if( byte == console_port ){ console.writeByte(localSizeHex("0")); }
    else{ memoryBlock.clearByte(byte); }
}
void accessManager::setByte(unsigned int byte, std::string value){ 
    if( byte == console_port ){ console.writeByte(value); }
    else{ memoryBlock.setByte(byte,value);  }
}