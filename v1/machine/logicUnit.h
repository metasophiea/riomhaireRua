#ifndef _INCL_GUARD_HEX_UINT_logicUnit
#define _INCL_GUARD_HEX_UINT_logicUnit

#include "bareMetal.h"

class logicUnit: public bareMetal
{
    private:
        bool zero;
        bool overflow;
        virtual std::string analyseAndReturn(std::string result);

    public:
        logicUnit(unsigned int bitCount);
        virtual ~logicUnit();

        virtual bool isZero();
        virtual bool isOverflow();

        virtual std::string pass( std::string value );

        virtual std::string flip( std::string value );
        virtual std::string inc( std::string value );
        virtual std::string lShift( std::string value );

        virtual std::string nand( std::string value_1, std::string value_2 );
        virtual std::string add( std::string value_1, std::string value_2 );
};

#endif