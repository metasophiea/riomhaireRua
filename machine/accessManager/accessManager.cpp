#include <iostream>

#include "accessManager.h"

//construction/destruction
    accessManager::accessManager(unsigned int bitSize, unsigned int worktopSize):
        metal(bitSize),
        worktopBase(bitSize, worktopSize),
        console(bitSize),
        pixelDisplay(bitSize,2,256,256,1000,1000),
        vectorDisplay(bitSize,256,1000,1000),
        internalStorageDevice_A(bitSize,65536),
        removableStorageDevice_A(8,256,"removableDisk")
        {}
    accessManager::~accessManager(){}

//getters and setters
    unsigned int accessManager::getByte(unsigned int byte){if(debugMode){ std::cout << "accessManager - getting byte: " << byte << std::endl; } 
        switch(byte){
            case indirect_access: if( getByte(indirect_address) == indirect_access ){ return 0; /*to guard against an access loop*/ } return getByte(indirect_address); break;
            case console_port:                        return console.read();                  break;
            case pixelDisplay_AccessPort:             return pixelDisplay.getPixelByte();     break;
            case pixelDisplay_AddressPort_y:          return pixelDisplay.getAddressByte(1);  break;
            case pixelDisplay_AddressPort_x:          return pixelDisplay.getAddressByte(0);  break;
            case vectorDisplay_AccessPort:            return vectorDisplay.getMemoryByte();   break;
            case vectorDisplay_AddressPort:           return vectorDisplay.getAddressByte(0); break;
            case internalStorageDevice_A_accessPort:  return internalStorageDevice_A.getByte( getByte(internalStorageDevice_A_address_1)*10 + getByte(internalStorageDevice_A_address_0) ); break;
            case removableStorageDevice_A_AccessPort:  break;
            case removableStorageDevice_A_AddressPort: return removableStorageDevice_A.getByte( getByte(removableStorageDevice_A_AccessPort) ); break;
        }

        return worktopBase.getByte(byte);
    }
    void accessManager::setByte(unsigned int byte, unsigned int value){if(debugMode){ std::cout << "accessManager - setting byte: " << byte << " to the value " << value << std::endl; } 
        switch(byte){
            case indirect_access:            if( getByte(indirect_address) != indirect_access ){ setByte(getByte(indirect_address),value); } break;
            case console_port:               console.write(value);                  break;
            case pixelDisplay_AccessPort:    pixelDisplay.setPixelByte(value);      break;
            case pixelDisplay_AddressPort_y: pixelDisplay.setAddressByte(1,value);  break;
            case pixelDisplay_AddressPort_x: pixelDisplay.setAddressByte(0,value);  break;
            case vectorDisplay_AccessPort:   vectorDisplay.setMemoryByte(value);    break;
            case vectorDisplay_AddressPort:  vectorDisplay.setAddressByte(0,value); break;
            case internalStorageDevice_A_accessPort:   return internalStorageDevice_A.setByte( getByte(internalStorageDevice_A_address_1)*10 + getByte(internalStorageDevice_A_address_0), value ); break;
            case removableStorageDevice_A_AccessPort:  break;
            case removableStorageDevice_A_AddressPort: removableStorageDevice_A.setByte( getByte(removableStorageDevice_A_AccessPort),value ); break;
        }

        worktopBase.setByte(byte,value);
    }
    bool accessManager::getBit(unsigned int byte, unsigned int bit){if(debugMode){ std::cout << "accessManager - getting bit: " << bit << " of byte " << byte << std::endl; } 
        switch(byte){
            case indirect_access:            if( getByte(indirect_address) == indirect_access ){ return false; /*to guard against an access loop*/ } return getBit(getByte(indirect_address),bit); break;
            case console_port:               return console.readBit(bit);               break;
            case pixelDisplay_AccessPort:    return pixelDisplay.getPixelBit(bit);      break;
            case pixelDisplay_AddressPort_y: return pixelDisplay.getAddressBit(1,bit);  break;
            case pixelDisplay_AddressPort_x: return pixelDisplay.getAddressBit(0,bit);  break;
            case vectorDisplay_AccessPort:   return vectorDisplay.getMemoryBit(bit);    break;
            case vectorDisplay_AddressPort:  return vectorDisplay.getAddressBit(0,bit); break;
            case internalStorageDevice_A_accessPort: return internalStorageDevice_A.getBit( getByte(internalStorageDevice_A_address_1)*10 + getByte(internalStorageDevice_A_address_0), bit ); break;
            case removableStorageDevice_A_AccessPort:  break;
            case removableStorageDevice_A_AddressPort: return removableStorageDevice_A.getBit( getByte(removableStorageDevice_A_AccessPort),bit ); break;
        }

        return worktopBase.getBit(byte,bit);
    }
    void accessManager::setBit(unsigned int byte, unsigned int bit, bool value){if(debugMode){ std::cout << "accessManager - setting bit: " << bit << " of byte " << byte << " to the value " << value << std::endl; } 
        switch(byte){
            case indirect_access:            if(getByte(indirect_address) != indirect_access ){ setBit(getByte(indirect_address),bit,value); } break;
            case console_port:               console.writeBit(bit,value);              break;
            case pixelDisplay_AccessPort:    pixelDisplay.setPixelBit(bit,value);      break;
            case pixelDisplay_AddressPort_y: pixelDisplay.setAddressBit(1,bit,value);  break;
            case pixelDisplay_AddressPort_x: pixelDisplay.setAddressBit(0,bit,value);  break;
            case vectorDisplay_AccessPort:   vectorDisplay.setMemoryBit(bit,value);    break;
            case vectorDisplay_AddressPort:  vectorDisplay.setAddressBit(0,bit,value); break;
            case internalStorageDevice_A_accessPort: return internalStorageDevice_A.setBit( getByte(internalStorageDevice_A_address_1)*10 + getByte(internalStorageDevice_A_address_0), bit, value ); break;
            case removableStorageDevice_A_AccessPort:  break;
            case removableStorageDevice_A_AddressPort: removableStorageDevice_A.setBit( getByte(removableStorageDevice_A_AccessPort),bit,value ); break;
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
            if( pixelDisplay.isStarted ){ pixelDisplay.printMemory(); }
            else{ std::cout << "- pixel display was never started" << std::endl; }
            std::cout << std::endl;

        std::cout << "Vector Display" << std::endl;
            if( vectorDisplay.isStarted ){ vectorDisplay.printMemory(); }
            else{ std::cout << "- vector display was never started" << std::endl; }
            std::cout << std::endl;

        std::cout << "Internal Storage Device A" << std::endl;
            //internalStorageDevice_A.printMemory();
            std::cout << std::endl;

        std::cout << "Removable Storage Device A" << std::endl;
            removableStorageDevice_A.printMemory();
            std::cout << std::endl;    

    }
    void accessManager::debug(bool onOff){ 
        debugMode = onOff;
        worktopBase.debug(onOff);
        console.debug(onOff);
        pixelDisplay.debug(onOff);
        vectorDisplay.debug(onOff);
        internalStorageDevice_A.debug(onOff);
    }
    void accessManager::debug(bool onOff, unsigned int depth){
        debugMode = onOff;
        if(depth > 0){ 
            worktopBase.debug(onOff,depth-1);
            console.debug(onOff,depth-1);
            pixelDisplay.debug(onOff,depth-1);
            vectorDisplay.debug(onOff,depth-1);
            internalStorageDevice_A.debug(onOff,depth-1);
        }
    }