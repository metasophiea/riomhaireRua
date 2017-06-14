#include <iostream>

#include "logicUnit.h"

logicUnit::logicUnit(unsigned int bitCount):
bareMetal(bitCount)
{
    zero = false;
    overflow = false;
}
logicUnit::~logicUnit(){}

std::string logicUnit::analyseAndReturn(std::string result){
    if( checkForComplyingLength(result) == 1 ){ overflow = true; }else{ overflow = false; } 
    result = localSizeHex(result);
    if( HEXtoUINT(result) == 0 ){ zero = true; }else{ zero = false; }
    return result;
}

bool logicUnit::isZero(){return zero;}
bool logicUnit::isOverflow(){return overflow;}


std::string logicUnit::pass( std::string value ){ return analyseAndReturn(value); }

std::string logicUnit::flip( std::string value ){
    std::string b = HEXtoBIN(value);

    for(unsigned int a = 0; a < b.length(); a++){
        if( b[a] == '0' ){ b[a] = '1'; }else{ b[a] = '0'; }
    }

    return analyseAndReturn(BINtoHEX(b));
}

std::string logicUnit::inc( std::string value ){ return analyseAndReturn(UINTtoHEX(HEXtoUINT(value) + 1)); }

std::string logicUnit::lShift( std::string value ){
    std::string b = HEXtoBIN(value);

    char temp = b[0];
    for(unsigned int a = 1; a < b.length(); a++){ b[a-1] = b[a]; }
    b[ b.length()-1 ] = temp;

    return analyseAndReturn(BINtoHEX(b));
}

std::string logicUnit::nand( std::string value_1, std::string value_2 ){
    std::string b_1 = HEXtoBIN(value_1);
    std::string b_2 = HEXtoBIN(value_2);

    for(unsigned int a = 0; a < b_1.length(); a++){
        if( !(b_1[a] == b_2[a]) || (b_1[a] == '0' && b_2[a] == '0') ){ b_2[a] = '1'; }else{ b_2[a] = '0'; }
    }

    return analyseAndReturn(BINtoHEX(b_2));
}

std::string logicUnit::add( std::string value_1, std::string value_2 ){ return analyseAndReturn(UINTtoHEX(HEXtoUINT(value_1)+HEXtoUINT(value_2))); }