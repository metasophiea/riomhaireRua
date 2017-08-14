#include <iostream>
#include <math.h>

#include "metal.h"
//construction/destruction
    metal::metal(unsigned int bitSize):
        debugMode(false),
        bitSize(bitSize),
        maxPossibleValue_abs( pow(2,bitSize) -1 ),
        maxPossibleValue_sam( pow(2,bitSize-1) -1 )
        {}
    metal::~metal(){}

    unsigned int metal::getBitSize(){return bitSize;}
    unsigned int metal::getMaxPossibleValue(int mode){
        if(mode == 0){      return maxPossibleValue_abs; }
        else if(mode == 1){ return maxPossibleValue_sam; }
        else{ return 0; }
    }

//converters
    std::string metal::UINTtoANYTHING(unsigned int UINT, char outputChars[], unsigned int numerationLength){
        std::string output = "";
        if(UINT == 0){ output += outputChars[0]; return output; }

        //find biggest pow
            unsigned int biggestPow = 0;
            while( (unsigned int)(UINT/pow(numerationLength,(biggestPow))) != 0 ){
                biggestPow++;
            }

        //do conversion
            do{
                biggestPow--;
                output += outputChars[ (unsigned int)(UINT/pow(numerationLength,biggestPow)) ]; 
                UINT = UINT - (unsigned int)(UINT/pow(numerationLength,biggestPow)) * pow(numerationLength,biggestPow);
            }while( biggestPow != 0 && UINT > 0 );

        //add in remaining zeros
            while(biggestPow > 0){ biggestPow--; output += outputChars[0]; }

        return output;
    }
    unsigned int metal::ANYTHINGtoUINT(std::string ANYTHING, char outputChars[], unsigned int numerationLength){
        unsigned int UINT = 0;

        for(unsigned int a = 0; a < ANYTHING.length(); a++){
            for(unsigned int b = 0; b < numerationLength; b++){
                if( ANYTHING[a] == outputChars[b] ){ UINT += pow(numerationLength, (ANYTHING.length()-a-1) ) * b ; }
            }
        }

        return UINT;
    }

    std::string metal::UINTtoHEX(unsigned int UINT){
        char charArray[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
        return UINTtoANYTHING(UINT,charArray,16);
    }
    std::string metal::UINTtoHEX_systemSize(unsigned int UINT){ return resize(UINTtoHEX(UINT),bitSize/4); }
    
    unsigned int metal::HEXtoUINT(std::string HEX){
        char charArray[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
        return ANYTHINGtoUINT(HEX,charArray,16);
    }

    std::string metal::UINTtoBIN(unsigned int UINT){
        char charArray[] = {'0','1'};
        return UINTtoANYTHING(UINT,charArray,2);
    }
    std::string metal::UINTtoBIN_systemSize(unsigned int UINT){ return resize(UINTtoBIN(UINT),bitSize); }

    unsigned int metal::BINtoUINT(std::string BIN){
        char charArray[] = {'0','1'};
        return ANYTHINGtoUINT(BIN,charArray,2);
    }

    std::string metal::UINTtoDEC(unsigned int UINT){
        char charArray[] = {'0','1','2','3','4','5','6','7','8','9'};
        return UINTtoANYTHING(UINT,charArray,10);
    }
    std::string metal::UINTtoDEC_systemSize(unsigned int UINT){ 
        if( UINT > getMaxPossibleValue(0) ){UINT = getMaxPossibleValue(0); }
        return UINTtoDEC(UINT);
    }
    unsigned int metal::DECtoUINT(std::string DEC){
        char charArray[] = {'0','1','2','3','4','5','6','7','8','9'};
        return ANYTHINGtoUINT(DEC,charArray,10);
    }

//adjusters/getters
    bool metal::getBitFromUINT(unsigned int UINT, unsigned int bit){
        std::string bin = UINTtoBIN(UINT);
        if(bin.length() <= bit){return false;}
        else{ return (bin[ bin.length()-1-bit ] == '0') ? false : true; }
    }
    std::string metal::adjustBIN(std::string BIN, unsigned int bit, bool value){
        if( BIN.length() > bit ){ value ? BIN[BIN.length()-1-bit] = '1' : BIN[BIN.length()-1-bit] = '0'; }
        else{ for(unsigned int a = BIN.length()-1; a < bit-1; a++){ BIN = BIN + '0'; } BIN = ( value ? '1' : '0') + BIN; }
        return BIN;
    }
    unsigned int metal::bitAdjustUINT_systemSize(unsigned int UINT, unsigned int bit, bool value){
        return BINtoUINT(adjustBIN(UINTtoBIN_systemSize(UINT),bit,value));
    }

std::string metal::resize(std::string val, unsigned int byteSize){
    if(val.length() == byteSize){return val;}
    else if( val.length() < byteSize ){
        for(unsigned int a = val.length(); a < byteSize; a++){ val = "0" + val; }
        return val;
    }
    else{
        std::string returnVal;
        for(unsigned int a = 0; a < byteSize; a++){ returnVal = val[ val.length()-a-1  ] + returnVal; }
        return returnVal;
    }
}

//printers and debug
    void metal::printMemory(){}
    void metal::debug(bool onOff){ debugMode = onOff; }