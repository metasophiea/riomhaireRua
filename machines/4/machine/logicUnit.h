#ifndef _INCL_GUARD_HEX_UINT_logicUnit
#define _INCL_GUARD_HEX_UINT_logicUnit

#include "metal.h"

class logicUnit: public metal
{
    private:
        bool resultIsZero;
        bool resultSign;
        bool resultOverflowed;
        bool resultUnderflowed;

    //construction/destruction
    public: 
        logicUnit(unsigned int bitSize);
        virtual ~logicUnit();

    //logical functions
    public: 
        virtual unsigned int check( int value );

        //logical
            //lone byte
            virtual unsigned int flip( unsigned int value );
            virtual unsigned int lRotate( unsigned int value );
            virtual unsigned int rRotate( unsigned int value );
            //multi byte
            virtual unsigned int AND( unsigned int value_a, unsigned int value_1 );
            virtual unsigned int NAND( unsigned int value_a, unsigned int value_1 );
            virtual unsigned int OR( unsigned int value_a, unsigned int value_1 );
            virtual unsigned int NOR( unsigned int value_a, unsigned int value_1 );
            virtual unsigned int XOR( unsigned int value_a, unsigned int value_1 );

        //math
            //lone byte
            virtual unsigned int inc( unsigned int value );
            virtual unsigned int dec( unsigned int value );
            virtual unsigned int neg( unsigned int value );
            //multi byte
            virtual unsigned int add( unsigned int value_a, unsigned int value_1 );
            virtual unsigned int sub( unsigned int value_a, unsigned int value_1 );

    //printers and debug
    public:
        virtual void printMemory();
        virtual void debug(bool onOff);
};

#endif