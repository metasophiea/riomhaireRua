#ifndef _INCL_GUARD_HEX_UINT_memoryBlock
#define _INCL_GUARD_HEX_UINT_memoryBlock

#include "metal.h"

class memoryBlock: public metal
{
    private:
        bool debugMode;
        unsigned int* memory;
        unsigned int memorySize;

    public:
    //construction/destruction
        memoryBlock(unsigned int bitCount, unsigned int memorySize);
        virtual ~memoryBlock();

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