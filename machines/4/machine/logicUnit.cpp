#include <iostream>

#include "logicUnit.h"

//construction/destruction
    logicUnit::logicUnit(unsigned int bitSize):
        metal(bitSize),
        resultIsZero(false),
        resultSign(false),
        resultOverflowed(false),
        resultUnderflowed(false)
        {}
    logicUnit::~logicUnit(){}

//logical functions
    unsigned int logicUnit::check( int value ){
        //check if value is zero
            resultIsZero = (value == 0);

        //check sign of result
            resultSign = value < 0;

        //check if value overflowed
            resultOverflowed = (value >= getMaxPossibleValue());

        //check if value underflowed
            


        //correct value size to suit system bit size, and return
        return HEXtoUINT( UINTtoHEX_systemSize(value) );
    }
    //logical
        //lone byte
        unsigned int logicUnit::flip( unsigned int value ){
            std::string temp = UINTtoBIN_systemSize(value);

            for(unsigned int a = 0; a < temp.length(); a++){
                temp[a] == '0' ? temp[a] = '1' : temp[a] = '0';
            }

            return check(BINtoUINT(temp));
        }
        unsigned int logicUnit::lRotate( unsigned int value ){
            std::string b = UINTtoBIN_systemSize(value);

            char temp = b[0];
            for(unsigned int a = 1; a < b.length(); a++){ b[a-1] = b[a]; }
            b[ b.length()-1 ] = temp;

            return check(BINtoUINT(b));
        }
        unsigned int logicUnit::rRotate( unsigned int value ){
            std::string b = UINTtoBIN_systemSize(value);

            char temp = b[b.length()-1];
            for(unsigned int a = b.length() - 2; a > 0; a--){ b[a+1] = b[a]; }
            b[0] = temp;

            return check(BINtoUINT(b));
        }
        //multi byte
        unsigned int logicUnit::AND( unsigned int value_a, unsigned int value_1 ){
            std::string b_a = UINTtoBIN_systemSize(value_a);
            std::string b_1 = UINTtoBIN_systemSize(value_1);

            for(unsigned int a = 0; a < b_a.length(); a++){
                ((b_a[a] == b_1[a]) && b_a[a] != '0') ?  b_1[a] = '1' : b_1[a] = '0';
            }

            return check(BINtoUINT(b_1));
        }
        unsigned int logicUnit::NAND( unsigned int value_a, unsigned int value_1 ){
            std::string b_a = UINTtoBIN_systemSize(value_a);
            std::string b_1 = UINTtoBIN_systemSize(value_1);

            for(unsigned int a = 0; a < b_a.length(); a++){
                !((b_a[a] == b_1[a]) && b_a[a] != '0') ?  b_1[a] = '1' : b_1[a] = '0';
            }

            return check(BINtoUINT(b_1));
        }
        unsigned int logicUnit::OR( unsigned int value_a, unsigned int value_1 ){
            std::string b_a = UINTtoBIN_systemSize(value_a);
            std::string b_1 = UINTtoBIN_systemSize(value_1);

            for(unsigned int a = 0; a < b_a.length(); a++){
                ((b_a[a] == '1') || (b_1[a] == '1')) ?  b_1[a] = '1' : b_1[a] = '0';
            }

            return check(BINtoUINT(b_1));
        }
        unsigned int logicUnit::NOR( unsigned int value_a, unsigned int value_1 ){
            std::string b_a = UINTtoBIN_systemSize(value_a);
            std::string b_1 = UINTtoBIN_systemSize(value_1);

            for(unsigned int a = 0; a < b_a.length(); a++){
                !((b_a[a] == '1') || (b_1[a] == '1')) ?  b_1[a] = '1' : b_1[a] = '0';
            }

            return check(BINtoUINT(b_1));
        }
        unsigned int logicUnit::XOR( unsigned int value_a, unsigned int value_1 ){
            std::string b_a = UINTtoBIN_systemSize(value_a);
            std::string b_1 = UINTtoBIN_systemSize(value_1);

            for(unsigned int a = 0; a < b_a.length(); a++){
                ( (b_a[a] == '1') ^ (b_1[a] == '1') ) ?  b_1[a] = '1' : b_1[a] = '0';
            }

            return check(BINtoUINT(b_1));
        }

    //math
        //lone byte
        unsigned int logicUnit::inc( unsigned int value ){
            return check(value + 1);
        }
        unsigned int logicUnit::dec( unsigned int value ){
            return check(value - 1);
        }
        unsigned int logicUnit::neg( unsigned int value ){}

        //multi byte
        unsigned int logicUnit::add( unsigned int value_a, unsigned int value_1 ){}
        unsigned int logicUnit::sub( unsigned int value_a, unsigned int value_1 ){}

//printers and debug
    void logicUnit::printMemory(){}
    void logicUnit::debug(bool onOff){}