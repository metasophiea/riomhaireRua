#include <iostream>

#include "metal.h"


int main(){    
    std::cout << "Hello" << std::endl;

    metal m = metal(8);
    unsigned int tempUINT;
    std::string tempString;
    char tempCharArray_hex[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    unsigned int tempCharArray_hex_length = 16;
    char tempCharArray_bin[] = {'0','1'};
    unsigned int tempCharArray_bin_length = 2;

    //get bit size
        std::cout << "getBitSize()" << std::endl;
        std::cout << m.getBitSize() << std::endl;
        std::cout << std::endl << std::endl;

    //get maximum possible value
        std::cout << "getMaxPossibleValue(0)" << std::endl;
        std::cout << m.getMaxPossibleValue(0) << std::endl;
        std::cout << std::endl;
        std::cout << "getMaxPossibleValue(1)" << std::endl;
        std::cout << m.getMaxPossibleValue(1) << std::endl;
        std::cout << std::endl;

    //testing UINTtoANYTHINGto do hex stuff
    tempUINT = 0;     std::cout << "m.UINTtoANYTHING("<<tempUINT<<",tempCharArray_hex,tempCharArray_hex_length) -> " << m.UINTtoANYTHING(tempUINT,tempCharArray_hex,tempCharArray_hex_length) << std::endl;
    tempUINT = 10;    std::cout << "m.UINTtoANYTHING("<<tempUINT<<",tempCharArray_hex,tempCharArray_hex_length) -> " << m.UINTtoANYTHING(tempUINT,tempCharArray_hex,tempCharArray_hex_length) << std::endl;
    tempUINT = 15;    std::cout << "m.UINTtoANYTHING("<<tempUINT<<",tempCharArray_hex,tempCharArray_hex_length) -> " << m.UINTtoANYTHING(tempUINT,tempCharArray_hex,tempCharArray_hex_length) << std::endl;
    tempUINT = 16;    std::cout << "m.UINTtoANYTHING("<<tempUINT<<",tempCharArray_hex,tempCharArray_hex_length) -> " << m.UINTtoANYTHING(tempUINT,tempCharArray_hex,tempCharArray_hex_length) << std::endl;
    tempUINT = 100;   std::cout << "m.UINTtoANYTHING("<<tempUINT<<",tempCharArray_hex,tempCharArray_hex_length) -> " << m.UINTtoANYTHING(tempUINT,tempCharArray_hex,tempCharArray_hex_length) << std::endl;
    tempUINT = 255;   std::cout << "m.UINTtoANYTHING("<<tempUINT<<",tempCharArray_hex,tempCharArray_hex_length) -> " << m.UINTtoANYTHING(tempUINT,tempCharArray_hex,tempCharArray_hex_length) << std::endl;
    std::cout << std::endl;

    //testing ANYTHINGtoUINT do hex stuff
    tempString = "0";    std::cout << "m.ANYTHINGtoUINT("<<tempString<<",tempCharArray_hex,tempCharArray_hex_length) -> " << m.ANYTHINGtoUINT(tempString,tempCharArray_hex,tempCharArray_hex_length) << std::endl;
    tempString = "a";    std::cout << "m.ANYTHINGtoUINT("<<tempString<<",tempCharArray_hex,tempCharArray_hex_length) -> " << m.ANYTHINGtoUINT(tempString,tempCharArray_hex,tempCharArray_hex_length) << std::endl;
    tempString = "10";   std::cout << "m.ANYTHINGtoUINT("<<tempString<<",tempCharArray_hex,tempCharArray_hex_length) -> " << m.ANYTHINGtoUINT(tempString,tempCharArray_hex,tempCharArray_hex_length) << std::endl;
    tempString = "64";   std::cout << "m.ANYTHINGtoUINT("<<tempString<<",tempCharArray_hex,tempCharArray_hex_length) -> " << m.ANYTHINGtoUINT(tempString,tempCharArray_hex,tempCharArray_hex_length) << std::endl;
    tempString = "ff";   std::cout << "m.ANYTHINGtoUINT("<<tempString<<",tempCharArray_hex,tempCharArray_hex_length) -> " << m.ANYTHINGtoUINT(tempString,tempCharArray_hex,tempCharArray_hex_length) << std::endl;
    std::cout << std::endl;

    //testing UINTtoANYTHING to do binary stuff
    tempUINT = 0;     std::cout << "m.UINTtoANYTHING("<<tempUINT<<",tempCharArray_bin,tempCharArray_bin_length) -> " << m.UINTtoANYTHING(tempUINT,tempCharArray_bin,tempCharArray_bin_length) << std::endl;
    tempUINT = 10;    std::cout << "m.UINTtoANYTHING("<<tempUINT<<",tempCharArray_bin,tempCharArray_bin_length) -> " << m.UINTtoANYTHING(tempUINT,tempCharArray_bin,tempCharArray_bin_length) << std::endl;
    tempUINT = 15;    std::cout << "m.UINTtoANYTHING("<<tempUINT<<",tempCharArray_bin,tempCharArray_bin_length) -> " << m.UINTtoANYTHING(tempUINT,tempCharArray_bin,tempCharArray_bin_length) << std::endl;
    tempUINT = 16;    std::cout << "m.UINTtoANYTHING("<<tempUINT<<",tempCharArray_bin,tempCharArray_bin_length) -> " << m.UINTtoANYTHING(tempUINT,tempCharArray_bin,tempCharArray_bin_length) << std::endl;
    tempUINT = 100;   std::cout << "m.UINTtoANYTHING("<<tempUINT<<",tempCharArray_bin,tempCharArray_bin_length) -> " << m.UINTtoANYTHING(tempUINT,tempCharArray_bin,tempCharArray_bin_length) << std::endl;
    tempUINT = 255;   std::cout << "m.UINTtoANYTHING("<<tempUINT<<",tempCharArray_bin,tempCharArray_bin_length) -> " << m.UINTtoANYTHING(tempUINT,tempCharArray_bin,tempCharArray_bin_length) << std::endl;
    std::cout << std::endl;

    //testing ANYTHINGtoUINT do binary stuff
    tempString = "0";        std::cout << "m.ANYTHINGtoUINT("<<tempString<<",tempCharArray_bin,tempCharArray_bin_length) -> " << m.ANYTHINGtoUINT(tempString,tempCharArray_bin,tempCharArray_bin_length) << std::endl;
    tempString = "1010";     std::cout << "m.ANYTHINGtoUINT("<<tempString<<",tempCharArray_bin,tempCharArray_bin_length) -> " << m.ANYTHINGtoUINT(tempString,tempCharArray_bin,tempCharArray_bin_length) << std::endl;
    tempString = "1111";     std::cout << "m.ANYTHINGtoUINT("<<tempString<<",tempCharArray_bin,tempCharArray_bin_length) -> " << m.ANYTHINGtoUINT(tempString,tempCharArray_bin,tempCharArray_bin_length) << std::endl;
    tempString = "10000";    std::cout << "m.ANYTHINGtoUINT("<<tempString<<",tempCharArray_bin,tempCharArray_bin_length) -> " << m.ANYTHINGtoUINT(tempString,tempCharArray_bin,tempCharArray_bin_length) << std::endl;
    tempString = "1100100";  std::cout << "m.ANYTHINGtoUINT("<<tempString<<",tempCharArray_bin,tempCharArray_bin_length) -> " << m.ANYTHINGtoUINT(tempString,tempCharArray_bin,tempCharArray_bin_length) << std::endl;
    tempString = "11111111"; std::cout << "m.ANYTHINGtoUINT("<<tempString<<",tempCharArray_bin,tempCharArray_bin_length) -> " << m.ANYTHINGtoUINT(tempString,tempCharArray_bin,tempCharArray_bin_length) << std::endl;
    std::cout << std::endl;


    //testing UINTtoHEX
    tempUINT = 0;     std::cout << "m.UINTtoHEX("<<tempUINT<<") -> " << m.UINTtoHEX(tempUINT) << std::endl;
    tempUINT = 10;    std::cout << "m.UINTtoHEX("<<tempUINT<<") -> " << m.UINTtoHEX(tempUINT) << std::endl;
    tempUINT = 16;    std::cout << "m.UINTtoHEX("<<tempUINT<<") -> " << m.UINTtoHEX(tempUINT) << std::endl;
    tempUINT = 100;   std::cout << "m.UINTtoHEX("<<tempUINT<<") -> " << m.UINTtoHEX(tempUINT) << std::endl;
    tempUINT = 255;   std::cout << "m.UINTtoHEX("<<tempUINT<<") -> " << m.UINTtoHEX(tempUINT) << std::endl;
    tempUINT = 300;   std::cout << "m.UINTtoHEX("<<tempUINT<<") -> " << m.UINTtoHEX(tempUINT) << std::endl;
    std::cout << std::endl;

    //testing UINTtoHEX_systemSize
    tempUINT = 0;     std::cout << "m.UINTtoHEX_systemSize("<<tempUINT<<") -> " << m.UINTtoHEX_systemSize(tempUINT) << std::endl;
    tempUINT = 10;    std::cout << "m.UINTtoHEX_systemSize("<<tempUINT<<") -> " << m.UINTtoHEX_systemSize(tempUINT) << std::endl;
    tempUINT = 15;    std::cout << "m.UINTtoHEX_systemSize("<<tempUINT<<") -> " << m.UINTtoHEX_systemSize(tempUINT) << std::endl;
    tempUINT = 16;    std::cout << "m.UINTtoHEX_systemSize("<<tempUINT<<") -> " << m.UINTtoHEX_systemSize(tempUINT) << std::endl;
    tempUINT = 100;   std::cout << "m.UINTtoHEX_systemSize("<<tempUINT<<") -> " << m.UINTtoHEX_systemSize(tempUINT) << std::endl;
    tempUINT = 255;   std::cout << "m.UINTtoHEX_systemSize("<<tempUINT<<") -> " << m.UINTtoHEX_systemSize(tempUINT) << std::endl;
    tempUINT = 300;   std::cout << "m.UINTtoHEX_systemSize("<<tempUINT<<") -> " << m.UINTtoHEX_systemSize(tempUINT) << std::endl;
    std::cout << std::endl;

    //testing HEXtoUINT
    tempString = "0";    std::cout << "m.HEXtoUINT("<<tempString<<") -> " << m.HEXtoUINT(tempString) << std::endl;
    tempString = "a";    std::cout << "m.HEXtoUINT("<<tempString<<") -> " << m.HEXtoUINT(tempString) << std::endl;
    tempString = "10";   std::cout << "m.HEXtoUINT("<<tempString<<") -> " << m.HEXtoUINT(tempString) << std::endl;
    tempString = "64";   std::cout << "m.HEXtoUINT("<<tempString<<") -> " << m.HEXtoUINT(tempString) << std::endl;
    tempString = "ff";   std::cout << "m.HEXtoUINT("<<tempString<<") -> " << m.HEXtoUINT(tempString) << std::endl;
    std::cout << std::endl;

    //testing UINTtoBIN
    tempUINT = 0;     std::cout << "m.UINTtoBIN("<<tempUINT<<") -> " << m.UINTtoBIN(tempUINT) << std::endl;
    tempUINT = 10;    std::cout << "m.UINTtoBIN("<<tempUINT<<") -> " << m.UINTtoBIN(tempUINT) << std::endl;
    tempUINT = 15;    std::cout << "m.UINTtoBIN("<<tempUINT<<") -> " << m.UINTtoBIN(tempUINT) << std::endl;
    tempUINT = 16;    std::cout << "m.UINTtoBIN("<<tempUINT<<") -> " << m.UINTtoBIN(tempUINT) << std::endl;
    tempUINT = 100;   std::cout << "m.UINTtoBIN("<<tempUINT<<") -> " << m.UINTtoBIN(tempUINT) << std::endl;
    tempUINT = 255;   std::cout << "m.UINTtoBIN("<<tempUINT<<") -> " << m.UINTtoBIN(tempUINT) << std::endl;
    tempUINT = 300;   std::cout << "m.UINTtoBIN("<<tempUINT<<") -> " << m.UINTtoBIN(tempUINT) << std::endl;
    std::cout << std::endl;

    //testing BINtoUINT
    tempString = "0";        std::cout << "m.BINtoUINT("<<tempString<<") -> " << m.BINtoUINT(tempString) << std::endl;
    tempString = "1010";     std::cout << "m.BINtoUINT("<<tempString<<") -> " << m.BINtoUINT(tempString) << std::endl;
    tempString = "1111";     std::cout << "m.BINtoUINT("<<tempString<<") -> " << m.BINtoUINT(tempString) << std::endl;
    tempString = "10000";    std::cout << "m.BINtoUINT("<<tempString<<") -> " << m.BINtoUINT(tempString) << std::endl;
    tempString = "1100100";  std::cout << "m.BINtoUINT("<<tempString<<") -> " << m.BINtoUINT(tempString) << std::endl;
    tempString = "11111111"; std::cout << "m.BINtoUINT("<<tempString<<") -> " << m.BINtoUINT(tempString) << std::endl;
    std::cout << std::endl;

    //testing BINtoUINT_systemSize
    tempUINT = 0;     std::cout << "m.UINTtoBIN_systemSize("<<tempUINT<<") -> " << m.UINTtoBIN_systemSize(tempUINT) << std::endl;
    tempUINT = 10;    std::cout << "m.UINTtoBIN_systemSize("<<tempUINT<<") -> " << m.UINTtoBIN_systemSize(tempUINT) << std::endl;
    tempUINT = 15;    std::cout << "m.UINTtoBIN_systemSize("<<tempUINT<<") -> " << m.UINTtoBIN_systemSize(tempUINT) << std::endl;
    tempUINT = 16;    std::cout << "m.UINTtoBIN_systemSize("<<tempUINT<<") -> " << m.UINTtoBIN_systemSize(tempUINT) << std::endl;
    tempUINT = 100;   std::cout << "m.UINTtoBIN_systemSize("<<tempUINT<<") -> " << m.UINTtoBIN_systemSize(tempUINT) << std::endl;
    tempUINT = 255;   std::cout << "m.UINTtoBIN_systemSize("<<tempUINT<<") -> " << m.UINTtoBIN_systemSize(tempUINT) << std::endl;
    tempUINT = 300;   std::cout << "m.UINTtoBIN_systemSize("<<tempUINT<<") -> " << m.UINTtoBIN_systemSize(tempUINT) << std::endl;
    std::cout << std::endl;


        
    return 0;
}