#ifndef _INCL_GUARD_HEX_UINT_removeableMemory
#define _INCL_GUARD_HEX_UINT_removeableMemory

#include <iostream>
#include "metal.h"

class removeableMemory: public metal
{
    private:
        bool debugMode;
        FILE* loadedMemory;
        unsigned int memorySize;
        std::string fileName;

    public:
    //construction/destruction
        removeableMemory(unsigned int bitSize, unsigned int memorySize);
        virtual ~removeableMemory();

    //getters and setters
        virtual unsigned int getByte(unsigned int byte);
        virtual void setByte(unsigned int byte, unsigned int value);
        virtual bool getBit(unsigned int byte, unsigned int bit);
        virtual void setBit(unsigned int byte, unsigned int bit, bool value);

    //printers and debug
        virtual void printMemory();
        virtual void debug(bool onOff);
};

#endif