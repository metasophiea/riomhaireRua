#include <iostream>
#include <math.h>

#include "metal.h"

metal::metal(unsigned int bitSize){
	this->bitSize = bitSize;
}
metal::~metal(){}

unsigned int metal::getBitSize(){return bitSize;}

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

std::string metal::resizeHex(std::string HEX, unsigned int byteSize){
    if(HEX.length() == byteSize){return HEX;}
    else if( HEX.length() < byteSize ){
        for(unsigned int a = HEX.length(); a < byteSize; a++){ HEX = "0" + HEX; }
        return HEX;
    }
    else{
        std::string returnHEX;
        for(unsigned int a = 0; a < byteSize; a++){ returnHEX += HEX[ HEX.length()-a-1  ]; }
        return returnHEX;
    }
}