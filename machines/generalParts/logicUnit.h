#ifndef _INCL_GUARD_HEX_UINT_logicUnit
#define _INCL_GUARD_HEX_UINT_logicUnit

#include "bareMetal.h"

class logicUnit: public bareMetal
{
    private:
        bool zero;
        bool overflow;
        bool underflow;
        virtual std::string analyseAndReturn(std::string result);
        virtual std::string analyseAndReturn(int value);

    public:
        logicUnit(unsigned int bitCount);
        virtual ~logicUnit();

        virtual bool isZero();
        virtual bool isOverflow();
        virtual bool isUnderflow();

        virtual std::string pass( std::string value );

        virtual std::string neg( std::string value );
        virtual std::string flip( std::string value );
        virtual std::string inc( std::string value );
        virtual std::string dec( std::string value );
        virtual std::string lRotate( std::string value );
        virtual std::string rRotate( std::string value );

        virtual std::string And( std::string value_1, std::string value_2 );
        virtual std::string nand( std::string value_1, std::string value_2 );
        virtual std::string Or( std::string value_1, std::string value_2 );
        virtual std::string nor( std::string value_1, std::string value_2 );
        virtual std::string Xor( std::string value_1, std::string value_2 );
        virtual std::string add( std::string value_1, std::string value_2 );
        virtual std::string sub( std::string value_1, std::string value_2 );
};

#endif