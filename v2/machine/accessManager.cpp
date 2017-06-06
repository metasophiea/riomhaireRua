#include <iostream>

#include "accessManager.h"

accessManager::accessManager(unsigned int bitCount, unsigned int memorySize):
    bareMetal(bitCount),
    memoryBlock(bitCount, memorySize),
    console(bitCount),
    visual(bitCount,16,16)
    {}
accessManager::~accessManager(){}

unsigned int accessManager::size()                                          { return memoryBlock.size(); }
void accessManager::display(){ 
    std::cout << "Internal Memory" << std::endl;
    memoryBlock.display(); 
    std::cout << std::endl << "Visual Display Memory" << std::endl;
    visual.display();
}

bool accessManager::getBit(std::string byte, unsigned int bit)              { return getBit(HEXtoUINT(byte),bit); }
void accessManager::setBit(std::string byte, unsigned int bit, bool value)  { setBit(HEXtoUINT(byte),bit,value); }
std::string accessManager::getByte(std::string byte)                        { return getByte(HEXtoUINT(byte)); }
void accessManager::clearByte(std::string byte)                             { clearByte(HEXtoUINT(byte)); }
void accessManager::setByte(std::string byte, std::string value)            { setByte(HEXtoUINT(byte),value); }
void accessManager::setByte(unsigned int byte, unsigned int value)          { setByte(byte,localSizeHex(UINTtoHEX(value))); }

bool accessManager::getBit(unsigned int byte, unsigned int bit){
    switch(byte){
        case console_port: return console.getBit(); break;
        case visual_AddressPort: return visual.getAddressBit(bit); break;
        case visual_PixelPort: return visual.getPixelBit(bit); break;
        default: return memoryBlock.getBit(byte,bit); break;
    }
}
void accessManager::setBit(unsigned int byte, unsigned int bit, bool value){
    switch(byte){
        case console_port: console.writeBit(value); break;
        case visual_AddressPort: visual.setAddressBit(bit,value); break;
        case visual_PixelPort: visual.setPixelBit(bit,value); break;
        default: memoryBlock.setBit(byte,bit,value); break;
    }
}
std::string accessManager::getByte(unsigned int byte){
    switch(byte){
        case console_port: return console.getByte(); break;
        case visual_AddressPort: return visual.getAddressByte(); break;
        case visual_PixelPort: return visual.getPixelByte(); break;
        default: return memoryBlock.getByte(byte); break;
    }
}
void accessManager::clearByte(unsigned int byte){
    switch(byte){
        case console_port: console.writeByte(localSizeHex("0")); break;
        case visual_AddressPort: visual.setAddressByte(localSizeHex("0")); break;
        case visual_PixelPort: visual.setPixelByte(localSizeHex("0")); break;
        default: memoryBlock.clearByte(byte); break;
    }
}
void accessManager::setByte(unsigned int byte, std::string value){
    switch(byte){
        case console_port: console.writeByte(value); break;
        case visual_AddressPort: visual.setAddressByte(value); break;
        case visual_PixelPort: visual.setPixelByte(value); break;
        default: memoryBlock.setByte(byte,value); break;
    }
}