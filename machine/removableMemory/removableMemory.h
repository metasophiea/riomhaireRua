#ifndef _INCL_GUARD_HEX_UINT_removableMemory
#define _INCL_GUARD_HEX_UINT_removableMemory

#include <iostream>
#include "metal.h"

class removableMemory: public metal
{
    private:
        bool debugMode;
        FILE* loadedMemory;
        unsigned int memorySize;
        std::string fileName;

    public:
    //construction/destruction
        removableMemory(unsigned int bitSize, unsigned int memorySize, std::string fileName);
        virtual ~removableMemory();

    //getters and setters
        virtual unsigned int getByte(unsigned int byte);
        virtual void setByte(unsigned int byte, unsigned int value);
        virtual bool getBit(unsigned int byte, unsigned int bit);
        virtual void setBit(unsigned int byte, unsigned int bit, bool value);

    //printers and debug
        virtual void printMemory();
        virtual void debug(bool onOff);
        virtual void debug(bool onOff, unsigned int depth);
};

#endif