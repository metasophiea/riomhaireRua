#include <iostream>

#include "accessManager.h"

//construction/destruction
    accessManager::accessManager(unsigned int bitSize, unsigned int worktopSize):
        metal(bitSize)
        {
        }
    accessManager::~accessManager(){}

//getters and setters
    bool accessManager::getBit(unsigned int byte, unsigned int bit){}
    void accessManager::setBit(unsigned int byte, unsigned int bit, bool value){}
    unsigned int accessManager::getByte(unsigned int byte){}
    void accessManager::setByte(unsigned int byte, unsigned int value){}

//printers and debug
    void accessManager::printMemory(){}
    void accessManager::debug(bool onOff){ debugMode = onOff; }