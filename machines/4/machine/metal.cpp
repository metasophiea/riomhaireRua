#include <iostream>
#include <math.h>

#include "metal.h"
//construction/destruction
    metal::metal(unsigned int bitSize):
        bitSize(bitSize),
        maxPossibleValue( pow(2,bitSize) )
        {}
    metal::~metal(){}

    unsigned int metal::getBitSize(){return bitSize;}
    unsigned int metal::getMaxPossibleValue(){return maxPossibleValue;}

//converters
    std::string metal::UINTtoHEX(unsigned int UINT){
        if(UINT == 0){ return "0";}

        std::string hexArray[] = {"0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f"};
        std::string HEX = "";

        //find biggest pow
            unsigned int biggestPow = 0;
            while( biggestPow < 100 ){
                if( (unsigned int)(UINT/pow(16,(biggestPow))) == 0 ){break;} 
                biggestPow++;
            }
            
        //do conversion
            do{
                biggestPow--;
                HEX += hexArray[ (unsigned int)(UINT/pow(16,biggestPow)) ]; 
                UINT = UINT - (unsigned int)(UINT/pow(16,biggestPow)) * pow(16,biggestPow);
            }while( biggestPow != 0 && UINT > 0 );

        //add in remaining zeros
            while(biggestPow > 0){ biggestPow--; HEX += "0"; }

        return HEX;
    }

    std::string metal::UINTtoHEX_systemSize(unsigned int UINT){ return resize(UINTtoHEX(UINT),bitSize/4); }

    unsigned int metal::HEXtoUINT(std::string HEX){
        unsigned int UINT = 0;
            
        for(unsigned int a = 0; a < HEX.length(); a++){
            switch(HEX[a]){
                case '0': 			 UINT += pow(16, (HEX.length()-a-1) ) * 0 ; break;
                case '1': 			 UINT += pow(16, (HEX.length()-a-1) ) * 1 ; break;
                case '2': 			 UINT += pow(16, (HEX.length()-a-1) ) * 2 ; break;
                case '3': 			 UINT += pow(16, (HEX.length()-a-1) ) * 3 ; break;
                case '4': 			 UINT += pow(16, (HEX.length()-a-1) ) * 4 ; break;
                case '5': 			 UINT += pow(16, (HEX.length()-a-1) ) * 5 ; break;
                case '6': 			 UINT += pow(16, (HEX.length()-a-1) ) * 6 ; break;
                case '7': 			 UINT += pow(16, (HEX.length()-a-1) ) * 7 ; break;
                case '8': 			 UINT += pow(16, (HEX.length()-a-1) ) * 8 ; break;
                case '9': 			 UINT += pow(16, (HEX.length()-a-1) ) * 9 ; break;
                case 'a': case 'A':  UINT += pow(16, (HEX.length()-a-1) ) * 10; break;
                case 'b': case 'B':  UINT += pow(16, (HEX.length()-a-1) ) * 11; break;
                case 'c': case 'C':  UINT += pow(16, (HEX.length()-a-1) ) * 12; break;
                case 'd': case 'D':  UINT += pow(16, (HEX.length()-a-1) ) * 13; break;
                case 'e': case 'E':  UINT += pow(16, (HEX.length()-a-1) ) * 14; break;
                case 'f': case 'F':  UINT += pow(16, (HEX.length()-a-1) ) * 15; break;
            }
        }

        return UINT;
    }

    std::string metal::UINTtoBIN_systemSize(unsigned int UINT){ return resize(UINTtoBIN(UINT),bitSize); }

    unsigned int metal::BINtoUINT(std::string BIN){
        unsigned int output = 0;
        for(unsigned int a = 0; a < BIN.length(); a++){ if( BIN[ BIN.length()-1-a ] == '1' ){ output += pow(2,a); } }
        return output;
    }
    std::string metal::UINTtoBIN(unsigned int UINT){
	    if(UINT == 0){ return "0"; }
        std::string binArray[] = {"0","1"};
        std::string outputBin = "";

        //find biggest pow
            unsigned int biggestPow = 0;
            while( biggestPow < 100 ){
                if( (unsigned int)(UINT/pow(2,(biggestPow))) == 0 ){break;} 
                biggestPow++;
            }
            
        //do conversion
            do{
                biggestPow--;
                outputBin += binArray[ (unsigned int)(UINT/pow(2,biggestPow)) ]; 
                UINT = UINT - (unsigned int)(UINT/pow(2,biggestPow)) * pow(2,biggestPow);
            }while( biggestPow != 0 && UINT > 0 );

        //add in remaining zeros
            while(biggestPow > 0){ biggestPow--; outputBin += "0"; }

        return outputBin;
    }

//adjusters
    bool metal::getBitFromUINT(unsigned int UINT, unsigned int bit){
        std::string bin = UINTtoBIN(UINT);
        if(bin.length() <= bit){return false;}
        else{ return (bin[ bin.length()-1-bit ] == '0') ? false : true; }
    }
    std::string metal::adjustBIN(std::string BIN, unsigned int bit, bool value){
        if( BIN.length() > bit ){ value ? BIN[bit] = '1' : BIN[bit] = '0'; }
        else{ for(unsigned int a = BIN.length()-1; a < bit-1; a++){ BIN = '0' + BIN; } BIN = '1' + BIN; }
        return BIN;
    }

std::string metal::resize(std::string val, unsigned int byteSize){
    if(val.length() == byteSize){return val;}
    else if( val.length() < byteSize ){
        for(unsigned int a = val.length(); a < byteSize; a++){ val = "0" + val; }
        return val;
    }
    else{
        std::string returnVal;
        for(unsigned int a = 0; a < byteSize; a++){ returnVal += val[ val.length()-a-1  ]; }
        return returnVal;
    }
}