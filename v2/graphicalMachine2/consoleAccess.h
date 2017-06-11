#ifndef _INCL_GUARD_HEX_UINT_consoleAccess
#define _INCL_GUARD_HEX_UINT_consoleAccess

#include "bareMetal.h"

class consoleAccess: public bareMetal
{
    private:
    public:
        consoleAccess(unsigned int bitCount);
        virtual ~consoleAccess();

        virtual bool getBit();
        virtual void writeBit(bool value);
        virtual std::string getByte();
        virtual void writeByte(std::string value);

};

#endif