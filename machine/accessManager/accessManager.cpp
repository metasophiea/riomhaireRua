#include <iostream>

#include "accessManager.h"

//construction/destruction
    accessManager::accessManager(unsigned int bitSize, unsigned int worktopSize):
        metal(bitSize),
        worktopBase(bitSize, worktopSize),
        console(bitSize),
        pixelDisplay(bitSize,2,256,256,1000,1000)
        {}
    accessManager::~accessManager(){}

//getters and setters
    unsigned int accessManager::getByte(unsigned int byte){if(debugMode){ std::cout << "accessManager - getting byte: " << byte << std::endl; } 
        switch(byte){
            case console_port:               return console.read();                 break;
            case pixelDisplay_AccessPort:    return pixelDisplay.getPixelByte();    break;
            case pixelDisplay_AddressPort_y: return pixelDisplay.getAddressByte(1); break;
            case pixelDisplay_AddressPort_x: return pixelDisplay.getAddressByte(0); break;
        }

        return worktopBase.getByte(byte);
    }
    void accessManager::setByte(unsigned int byte, unsigned int value){if(debugMode){ std::cout << "accessManager - setting byte: " << byte << " to the value " << value << std::endl; } 
        switch(byte){
            case console_port:               console.write(value);                 break;
            case pixelDisplay_AccessPort:    pixelDisplay.setPixelByte(value);     break;
            case pixelDisplay_AddressPort_y: pixelDisplay.setAddressByte(1,value); break;
            case pixelDisplay_AddressPort_x: pixelDisplay.setAddressByte(0,value); break;
        }

        worktopBase.setByte(byte,value);
    }
    bool accessManager::getBit(unsigned int byte, unsigned int bit){if(debugMode){ std::cout << "accessManager - getting bit: " << bit << " of byte " << byte << std::endl; } 
        switch(byte){
            case console_port:               return console.readBit(bit);              break;
            case pixelDisplay_AccessPort:    return pixelDisplay.getPixelBit(bit);     break;
            case pixelDisplay_AddressPort_y: return pixelDisplay.getAddressBit(1,bit); break;
            case pixelDisplay_AddressPort_x: return pixelDisplay.getAddressBit(0,bit); break;
        }

        return worktopBase.getBit(byte,bit);
    }
    void accessManager::setBit(unsigned int byte, unsigned int bit, bool value){if(debugMode){ std::cout << "accessManager - setting bit: " << bit << " of byte " << byte << " to the value " << value << std::endl; } 
        switch(byte){
            case console_port:               console.writeBit(bit,value);             break;
            case pixelDisplay_AccessPort:    pixelDisplay.setPixelBit(bit,value);     break;
            case pixelDisplay_AddressPort_y: pixelDisplay.setAddressBit(bit,1,value); break;
            case pixelDisplay_AddressPort_x: pixelDisplay.setAddressBit(bit,0,value); break;
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
            pixelDisplay.printMemory();
            std::cout << std::endl;
    }
    void accessManager::debug(bool onOff){ 
        debugMode = onOff;
        worktopBase.debug(onOff);
        console.debug(onOff);
    }