#include <iostream>

#include "accessManager.h"

//construction/destruction
    accessManager::accessManager(unsigned int bitSize, unsigned int worktopSize):
        metal(bitSize),
        worktopBase(bitSize, worktopSize),
        console(bitSize)
        {}
    accessManager::~accessManager(){}

//getters and setters
    unsigned int accessManager::getByte(unsigned int byte){if(debugMode){ std::cout << "accessManager - getting byte: " << byte << std::endl; } 
        switch(byte){
            case console_port:                       return console.read();                  break;
        //     case pixelDisplay_8bit_AccessPort:       return pixelDisplay_8bit.getPixel();    break;
        //     case pixelDisplay_8bit_AddressPort_y:    return pixelDisplay_8bit.getAddress(1); break;
        //     case pixelDisplay_8bit_AddressPort_x:    return pixelDisplay_8bit.getAddress(0); break;
        }

        return worktopBase.getByte(byte);
    }
    void accessManager::setByte(unsigned int byte, unsigned int value){if(debugMode){ std::cout << "accessManager - setting byte: " << byte << " to the value " << value << std::endl; } 
        switch(byte){
            case console_port:                       console.write(value);                  break;
        //     case pixelDisplay_8bit_AccessPort:       pixelDisplay_8bit.setPixel(value);     break;
        //     case pixelDisplay_8bit_AddressPort_y:    pixelDisplay_8bit.setAddress(1,value); break;
        //     case pixelDisplay_8bit_AddressPort_x:    pixelDisplay_8bit.setAddress(0,value); break;
        }

        worktopBase.setByte(byte,value);
    }
    bool accessManager::getBit(unsigned int byte, unsigned int bit){if(debugMode){ std::cout << "accessManager - getting bit: " << bit << " of byte " << byte << std::endl; } 
        switch(byte){
            case console_port:                       return console.readBit(bit);                      break;
        //     case pixelDisplay_8bit_AccessPort:       return pixelDisplay_8bit.getPixelBit(bit);     break;
        //     case pixelDisplay_8bit_AddressPort_y:    return pixelDisplay_8bit.getAddressBit(1,bit); break;
        //     case pixelDisplay_8bit_AddressPort_x:    return pixelDisplay_8bit.getAddressBit(0,bit); break;
        }

        return worktopBase.getBit(byte,bit);
    }
    void accessManager::setBit(unsigned int byte, unsigned int bit, bool value){if(debugMode){ std::cout << "accessManager - setting bit: " << bit << " of byte " << byte << " to the value " << value << std::endl; } 
        switch(byte){
            case console_port:                       console.writeBit(bit,value);                      break;
        //     case pixelDisplay_8bit_AccessPort:       pixelDisplay_8bit.setPixelBit(bit,value);     break;
        //     case pixelDisplay_8bit_AddressPort_y:    pixelDisplay_8bit.setAddressBit(bit,1,value); break;
        //     case pixelDisplay_8bit_AddressPort_x:    pixelDisplay_8bit.setAddressBit(bit,0,value); break;
        }

        worktopBase.setBit(byte,bit,value); 
    }

//printers and debug
    void accessManager::printMemory(){if(debugMode){ std::cout << "accessManager - printing memory" << std::endl; } 
        std::cout << "Worktop" << std::endl;
            worktopBase.printMemory();
            std::cout << std::endl;

        std::cout << "Console" << std::endl;
            console.printMemory();
            std::cout << std::endl;

        std::cout << "Pixel Display" << std::endl;
            //pixelDisplay_8bit.printMemory();
            std::cout << std::endl;
    }
    void accessManager::debug(bool onOff){ 
        debugMode = onOff;
        worktopBase.debug(onOff);
        console.debug(onOff);
    }