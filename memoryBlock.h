#ifndef _INCL_GUARD_HEX_UINT_memoryBlock
#define _INCL_GUARD_HEX_UINT_memoryBlock

#include "bareMetal.h"

class memoryBlock: public bareMetal
{
    private:
        unsigned int* memory;
        unsigned int memorySize;

    public:
        memoryBlock(unsigned int bitCount, unsigned int memorySize);
        virtual ~memoryBlock();

        virtual unsigned int size();

        virtual bool getBit(std::string byte, unsigned int bit);
        virtual bool getBit(unsigned int byte, unsigned int bit);
        virtual void setBit(std::string byte, unsigned int bit, bool value);
        virtual void setBit(unsigned int byte, unsigned int bit, bool value);

        virtual std::string getByte(std::string byte);
        virtual std::string getByte(unsigned int byte);
        virtual void clearByte(std::string byte);
        virtual void clearByte(unsigned int byte);
        virtual void setByte(std::string byte, std::string value);
        virtual void setByte(unsigned int byte, std::string value);

        virtual void display();
};

#endif