#include <iostream>

#include "logicUnit.h"

//construction/destruction
    logicUnit::logicUnit(unsigned int bitSize):
        metal(bitSize),
        debugMode(false),
        resultIsZero(false),
        resultSign(false),
        resultOverflowed(false),
        resultUnderflowed(false),
        calculationMode(0),
        calculationModeCount(2)
        {}
    logicUnit::~logicUnit(){}

//indicators
    bool logicUnit::getIsZero()     { return resultIsZero; }
    bool logicUnit::getSign()       { return resultSign; }
    bool logicUnit::getOverflowed() { return resultOverflowed; }
    bool logicUnit::getUnderflowed(){ return resultUnderflowed; }
    bool logicUnit::SAMmode()       { return calculationMode==1; }

//logical functions
    unsigned int logicUnit::logicCheck( int value ){
        if(debugMode){ std::cout << "logicUnit - logicCheck" << std::endl; } 
        //check if value is zero, if so, you can just return now
            if(debugMode){ std::cout << "logicUnit - checking if value: " << value << " is zero: " << ((value == 0)?"yes":"no") << std::endl; } 
            resultIsZero = (value == 0);
            if(resultIsZero){ return value; }

        //correct value size to suit system bit size, and return
        if(debugMode){ std::cout << "logicUnit - correcting value size to suit system bit size - value: " << value << " result: " << HEXtoUINT( UINTtoHEX_systemSize(value) ) << std::endl; } 
        return HEXtoUINT( UINTtoHEX_systemSize(value) );
    }
    unsigned int logicUnit::mathCheck( int value,unsigned int calculationMode ){
        if(debugMode){ std::cout << "logicUnit - mathCheck" << std::endl; } 
        //detect invalid calculationMode
            if( calculationMode >= calculationModeCount ){ std::cout << "logicUnit error - mathCheck - unknown calculationMode: " << calculationMode << " setting to 0" << std::endl; calculationMode = 0; }

        //check if value is zero
            if(debugMode){ std::cout << "logicUnit - mathCheck - checking if value: " << value << " is zero: " << ((value == 0)?"yes":"no") << std::endl; } 
            resultIsZero = (value == 0);

        //check sign of result
            if(debugMode){ std::cout << "logicUnit - mathCheck - checking sign: " << ((value < 0)?"negative":"positive") << std::endl; } 
            resultSign = value < 0;

        //split into modes
            if(debugMode){ std::cout << "logicUnit - mathCheck - calculation mode: " << calculationMode << std::endl; } 
            if( calculationMode == 0 ){
                //check if value overflowed
                    if(debugMode){ std::cout << "logicUnit - mathCheck - checking for overflow: " << ((value >= (int)getMaxPossibleValue(calculationMode))?"yes":"no") << std::endl; } 
                    resultOverflowed = value > (int)getMaxPossibleValue(calculationMode);

                //check if value underflowed, if so wrap around
                    if(debugMode){ std::cout << "logicUnit - mathCheck - checking for underflow: " << ((value < 0)?"yes - wrap":"no") << std::endl; } 
                    resultUnderflowed = value < 0; 
                    if(resultUnderflowed){ value = value + (unsigned int)getMaxPossibleValue(calculationMode)+1; }

                //correct value size to suit system bit size, and return
                    return HEXtoUINT( UINTtoHEX_systemSize(value) );
            }
            else if( calculationMode == 1 ){ 
                //check if value overflowed
                    if(debugMode){ std::cout << "logicUnit - mathCheck - checking for overflow: " << ((value >= (int)getMaxPossibleValue(calculationMode))?"yes - set to maximum value":"no") << std::endl; } 
                    resultOverflowed = value > (int)getMaxPossibleValue(calculationMode);
                    if(resultOverflowed){ value = getMaxPossibleValue(calculationMode); }
                    if(debugMode){ std::cout << "logicUnit - mathCheck - after overflow correction: " << value << std::endl; } 
                
                //check if value underflowed (if so, switch the value to a positive number)
                    if(debugMode){ std::cout << "logicUnit - mathCheck - checking for underflow: " << ((value < -(int)getMaxPossibleValue(calculationMode))?"yes - set to minimum value":"no") << std::endl; } 
                    if( value < -(int)getMaxPossibleValue(calculationMode) ){ resultUnderflowed = true; value = getMaxPossibleValue(calculationMode); }
                    else{ resultUnderflowed = false; }
                    if(debugMode){ std::cout << "logicUnit - mathCheck - after underflow correction: " << value << std::endl; } 

                //get absolute value, correct value size to suit system bit size, set sign bit and return
                    if(value < 0){value = -value;}
                    std::string temp = UINTtoBIN_systemSize(value);
                    resultSign ? temp[0] = '1' : temp[0] = '0';
                    if(debugMode){ std::cout << "logicUnit - mathCheck - conversion to binary: " << temp << std::endl; } 
                    return BINtoUINT(temp);
            }else{std::cout << "logicUnit - mathCheck - unreachable code" << std::endl; return 0;}
    }

    //logical
        //lone byte
        unsigned int logicUnit::convert( unsigned int value,unsigned int inputMode,unsigned int outputMode ){
            if(debugMode){ std::cout << "logicUnit - convert: " << value << " | from mode: " << inputMode << " to mode: " << outputMode << std::endl; } 
            //detect pointless job
                if( inputMode == outputMode ){ if(debugMode){ std::cout << "logicUnit - convert - input and output mode are the same" << std::endl; return value; } }
            //detect invalid calculationModes
                if( inputMode >= calculationModeCount ){ std::cout << "logicUnit error - convert - unknown inputMode: " << inputMode << " setting to 0" << std::endl; inputMode = 0; }
                if( outputMode >= calculationModeCount ){ std::cout << "logicUnit error - convert - unknown outputMode: " << outputMode << " setting to 0" << std::endl; outputMode = 0; }

            //convert to int
                int returnValue = 0;
                std::string bin = UINTtoBIN_systemSize(value);
                if(debugMode){ std::cout << "logicUnit - convert - gathered binary: " << bin << std::endl; } 
                if( inputMode == 0 ){ returnValue = value; }
                else if( inputMode == 1 ){
                    bool sign = bin[0] == '1';
                    bin[0] = '0';
                    returnValue = BINtoUINT(bin);
                    if(sign){returnValue = -returnValue;}
                }else{std::cout << "logicUnit - convert - unreachable code" << std::endl; return 0;}
            if(debugMode){ std::cout << "logicUnit - convert - gathered value: " << returnValue << std::endl; } 

            //push int into mathCheck to finish conversion
                return mathCheck(returnValue,outputMode);
        }
        unsigned int logicUnit::flip( unsigned int value ){
            if(debugMode){ std::cout << "logicUnit - flip: " << value << std::endl; } 

            //convert to binary string
            std::string b = UINTtoBIN_systemSize(value);
            if(debugMode){ std::cout << "logicUnit - flip - binary input:  " << b << std::endl; } 

            //actual flip
            for(unsigned int a = 0; a < b.length(); a++){ b[a] == '0' ? b[a] = '1' : b[a] = '0'; }

            if(debugMode){ std::cout << "logicUnit - flip - binary output: " << b << std::endl; } 
            if(debugMode){ std::cout << "logicUnit - flip - result: " << BINtoUINT(b) << std::endl; } 
            return logicCheck(BINtoUINT(b));
        }
        unsigned int logicUnit::lRotate( unsigned int value ){
            if(debugMode){ std::cout << "logicUnit - lRotate: " << value << std::endl; } 

            //convert to binary string
            std::string b = UINTtoBIN_systemSize(value);
            if(debugMode){ std::cout << "logicUnit - lRotate - binary input:  " << b << std::endl; } 

            //actual rotation
            char temp = b[0];
            for(unsigned int a = 1; a < b.length(); a++){ b[a-1] = b[a]; }
            b[ b.length()-1 ] = temp;

            if(debugMode){ std::cout << "logicUnit - lRotate - binary output: " << b << std::endl; } 
            if(debugMode){ std::cout << "logicUnit - lRotate - result: " << BINtoUINT(b) << std::endl; } 
            return logicCheck(BINtoUINT(b));
        }
        unsigned int logicUnit::rRotate( unsigned int value ){
            if(debugMode){ std::cout << "logicUnit - rRotate: " << value << std::endl; } 

            //convert to binary string
            std::string b = UINTtoBIN_systemSize(value);
            if(debugMode){ std::cout << "logicUnit - rRotate - binary input:  " << b << std::endl; } 

            //actual rotation
            char temp = b[b.length()-1];
            for(unsigned int a = b.length() - 2; a > 0; a--){ b[a+1] = b[a]; }
            b[0] = temp;

            if(debugMode){ std::cout << "logicUnit - rRotate - binary output: " << b << std::endl; } 
            if(debugMode){ std::cout << "logicUnit - rRotate - result: " << BINtoUINT(b) << std::endl; } 
            return logicCheck(BINtoUINT(b));
        }
        //multi byte
        unsigned int logicUnit::AND( unsigned int value_a, unsigned int value_1 ){
            if(debugMode){ std::cout << "logicUnit - AND: " << value_a << " | " << value_1 << std::endl; } 

            //convert to binary strings
            std::string b_a = UINTtoBIN_systemSize(value_a);
            std::string b_1 = UINTtoBIN_systemSize(value_1);
            if(debugMode){ std::cout << "logicUnit - AND - binary input:  " << b_a << " | " << b_1 << std::endl; } 

            //actual logic
            for(unsigned int a = 0; a < b_a.length(); a++){
                ((b_a[a] == b_1[a]) && b_a[a] != '0') ?  b_1[a] = '1' : b_1[a] = '0';
            }

            if(debugMode){ std::cout << "logicUnit - AND - binary output: " << b_1 << std::endl; } 
            if(debugMode){ std::cout << "logicUnit - AND - result: " << BINtoUINT(b_1) << std::endl; } 
            return logicCheck(BINtoUINT(b_1));
        }
        unsigned int logicUnit::NAND( unsigned int value_a, unsigned int value_1 ){
            if(debugMode){ std::cout << "logicUnit - NAND: " << value_a << " | " << value_1 << std::endl; } 

            //convert to binary strings
            std::string b_a = UINTtoBIN_systemSize(value_a);
            std::string b_1 = UINTtoBIN_systemSize(value_1);
            if(debugMode){ std::cout << "logicUnit - NAND - binary input:  " << b_a << " | " << b_1 << std::endl; } 

            //actual logic
            for(unsigned int a = 0; a < b_a.length(); a++){
                !((b_a[a] == b_1[a]) && b_a[a] != '0') ?  b_1[a] = '1' : b_1[a] = '0';
            }

            if(debugMode){ std::cout << "logicUnit - NAND - binary output: " << b_1 << std::endl; } 
            if(debugMode){ std::cout << "logicUnit - NAND - result: " << BINtoUINT(b_1) << std::endl; } 
            return logicCheck(BINtoUINT(b_1));
        }
        unsigned int logicUnit::OR( unsigned int value_a, unsigned int value_1 ){
            if(debugMode){ std::cout << "logicUnit - OR: " << value_a << " | " << value_1 << std::endl; } 

            //convert to binary strings
            std::string b_a = UINTtoBIN_systemSize(value_a);
            std::string b_1 = UINTtoBIN_systemSize(value_1);
            if(debugMode){ std::cout << "logicUnit - OR - binary input:  " << b_a << " | " << b_1 << std::endl; } 

            //actual logic
            for(unsigned int a = 0; a < b_a.length(); a++){
                ((b_a[a] == '1') || (b_1[a] == '1')) ?  b_1[a] = '1' : b_1[a] = '0';
            }

            if(debugMode){ std::cout << "logicUnit - OR - binary output: " << b_1 << std::endl; } 
            if(debugMode){ std::cout << "logicUnit - OR - result: " << BINtoUINT(b_1) << std::endl; } 
            return logicCheck(BINtoUINT(b_1));
        }
        unsigned int logicUnit::NOR( unsigned int value_a, unsigned int value_1 ){
            if(debugMode){ std::cout << "logicUnit - NOR: " << value_a << " | " << value_1 << std::endl; } 

            //convert to binary strings
            std::string b_a = UINTtoBIN_systemSize(value_a);
            std::string b_1 = UINTtoBIN_systemSize(value_1);
            if(debugMode){ std::cout << "logicUnit - NOR - binary input:  " << b_a << " | " << b_1 << std::endl; } 

            //actual logic
            for(unsigned int a = 0; a < b_a.length(); a++){
                !((b_a[a] == '1') || (b_1[a] == '1')) ?  b_1[a] = '1' : b_1[a] = '0';
            }

            if(debugMode){ std::cout << "logicUnit - NOR - binary output: " << b_1 << std::endl; } 
            if(debugMode){ std::cout << "logicUnit - NOR - result: " << BINtoUINT(b_1) << std::endl; } 
            return logicCheck(BINtoUINT(b_1));
        }
        unsigned int logicUnit::XOR( unsigned int value_a, unsigned int value_1 ){
            if(debugMode){ std::cout << "logicUnit - XOR: " << value_a << " | " << value_1 << std::endl; } 

            //convert to binary strings
            std::string b_a = UINTtoBIN_systemSize(value_a);
            std::string b_1 = UINTtoBIN_systemSize(value_1);
            if(debugMode){ std::cout << "logicUnit - XOR - binary input:  " << b_a << " | " << b_1 << std::endl; } 

            //actual logic
            for(unsigned int a = 0; a < b_a.length(); a++){
                ( (b_a[a] == '1') ^ (b_1[a] == '1') ) ?  b_1[a] = '1' : b_1[a] = '0';
            }

            if(debugMode){ std::cout << "logicUnit - XOR - binary output: " << b_1 << std::endl; } 
            if(debugMode){ std::cout << "logicUnit - XOR - result: " << BINtoUINT(b_1) << std::endl; } 
            return logicCheck(BINtoUINT(b_1));
        }

    //math
        //control
        void logicUnit::setCalculationMode(unsigned int mode){
            if(debugMode){ std::cout << "logicUnit - setCalculationMode: " << mode << std::endl; }
            calculationMode = mode;
        }
        //lone byte
        unsigned int logicUnit::inc( unsigned int value ){
            if(debugMode){ std::cout << "logicUnit - inc - incrementing value: " << value << std::endl; }
            if(debugMode){ std::cout << "logicUnit - inc - calculationMode: " << calculationMode << std::endl; }

            //split into modes
                if( calculationMode == 0 ){ return mathCheck(value + 1,calculationMode); }
                else if( calculationMode == 1 ){
                    if(debugMode){ std::cout << "logicUnit - inc - sign = " << getBitFromUINT(value,getBitSize()-1) << std::endl; }
                    if( getBitFromUINT(value,getBitSize()-1) ){ return mathCheck(getMaxPossibleValue(1)-value+2,calculationMode); }
                    else{ return mathCheck(value + 1,calculationMode); }
                }
                
            std::cout << "logicUnit - inc - calculation error - calculationMode = " << calculationMode << std::endl;
            return 0;
        }
        unsigned int logicUnit::dec( unsigned int value ){
            if(debugMode){ std::cout << "logicUnit - dec - decrementing value: " << value << std::endl; }
            if(debugMode){ std::cout << "logicUnit - dec - calculationMode: " << calculationMode << std::endl; }

            //split into modes
                if( calculationMode == 0 ){ return mathCheck(value - 1,calculationMode); }
                else if( calculationMode == 1 ){
                    if(debugMode){ std::cout << "logicUnit - dec - sign = " << getBitFromUINT(value,getBitSize()-1) << std::endl; }
                    if( getBitFromUINT(value,getBitSize()-1) ){ return mathCheck(getMaxPossibleValue(1)-value,calculationMode); }
                    else{ return mathCheck(value - 1,calculationMode); }
                }
                
            std::cout << "logicUnit - dec - calculation error - calculationMode = " << calculationMode << std::endl;
            return 0;
        }
        unsigned int logicUnit::neg( unsigned int value ){
            if(debugMode){ std::cout << "logicUnit - neg - flipping value:" << value << std::endl; }
            return mathCheck(-value,calculationMode);
        }

        //multi byte
        unsigned int logicUnit::add( unsigned int value_a, unsigned int value_1 ){
            if(debugMode){ std::cout << "logicUnit - add - adding the value:" << value_a << " to " << value_1 << std::endl; } 
            if(debugMode){ std::cout << "logicUnit - add - calculationMode: " << calculationMode << std::endl; }

            //split into modes
                if( calculationMode == 0 ){ return mathCheck(value_a+value_1,calculationMode); }
                else{
                    if(debugMode){ std::cout << "logicUnit - add - sign = " << getBitFromUINT(value_a,getBitSize()-1) << " | sign = " << getBitFromUINT(value_1,getBitSize()-1) << std::endl; }
                    int newValue_a = value_a; int newValue_1 = value_1;
                    if( getBitFromUINT(value_a,getBitSize()-1) ){ newValue_a = getMaxPossibleValue(1) - newValue_a +1; }
                    if( getBitFromUINT(value_1,getBitSize()-1) ){ newValue_1 = getMaxPossibleValue(1) - newValue_1 +1; }
                    if(debugMode){ std::cout << "logicUnit - add - newValue_a: " << newValue_a << " | newValue_1: " << newValue_1 << std::endl; }
                    return mathCheck(newValue_a+newValue_1,calculationMode);
                }
                
            std::cout << "logicUnit - add - calculation error - calculationMode = " << calculationMode << std::endl;
            return 0;
        }
        unsigned int logicUnit::sub( unsigned int value_a, unsigned int value_1 ){
            if(debugMode){ std::cout << "logicUnit - sub - subtracting the value:" << value_1 << " from " << value_a << std::endl; } 
            if(debugMode){ std::cout << "logicUnit - sub - calculationMode: " << calculationMode << std::endl; }

            //split into modes
                if( calculationMode == 0 ){ return mathCheck(value_a-value_1,calculationMode); }
                else{
                    if(debugMode){ std::cout << "logicUnit - sub - sign = " << getBitFromUINT(value_a,getBitSize()-1) << " | sign = " << getBitFromUINT(value_1,getBitSize()-1) << std::endl; }
                    int newValue_a = value_a; int newValue_1 = value_1;
                    if( getBitFromUINT(value_a,getBitSize()-1) ){ newValue_a = getMaxPossibleValue(1) - newValue_a +1; }
                    if( getBitFromUINT(value_1,getBitSize()-1) ){ newValue_1 = getMaxPossibleValue(1) - newValue_1 +1; }
                    if(debugMode){ std::cout << "logicUnit - sub - newValue_a: " << newValue_a << " | newValue_1: " << newValue_1 << std::endl; std::cout << "logicUnit - sub: " << newValue_a << " - " << newValue_1 << " = " << (newValue_a-newValue_1) << std::endl; }
                    return mathCheck(newValue_a-newValue_1,calculationMode);
                }

            std::cout << "logicUnit - add - calculation error - calculationMode = " << calculationMode << std::endl;
            return 0;
        }

//printers and debug
    void logicUnit::printMemory(){}
    void logicUnit::debug(bool onOff){debugMode = onOff;}