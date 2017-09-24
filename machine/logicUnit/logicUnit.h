#ifndef _INCL_GUARD_HEX_UINT_logicUnit
#define _INCL_GUARD_HEX_UINT_logicUnit

#include "metal.h"

class logicUnit: public metal
{
    private:
        bool debugMode;
        bool resultIsZero;
        bool resultSign;
        bool resultOverflowed;
        bool resultUnderflowed;
        unsigned int calculationMode;
        unsigned int calculationModeCount;

    //construction/destruction
    public: 
        logicUnit(unsigned int bitSize);
        virtual ~logicUnit();

    //indicators
    public:
        virtual bool getIsZero();
        virtual bool getSign();
        virtual bool getOverflowed();
        virtual bool getUnderflowed();
        virtual bool SAMmode();

    //functions
    public: 
        //checks
            virtual unsigned int logicCheck( int value );
            virtual unsigned int mathCheck( int value,unsigned int calculationMode );

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
            //control
            virtual void setCalculationMode(unsigned int mode);
            //lone byte
            virtual unsigned int convert( unsigned int value,unsigned int inputMode,unsigned int outputMode );
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
        virtual void debug(bool onOff, unsigned int depth);
};

#endif