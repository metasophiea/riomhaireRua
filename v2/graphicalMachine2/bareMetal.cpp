#include <iostream>
#include <math.h>

#include "bareMetal.h"

bareMetal::bareMetal(unsigned int bitCount){
	unsigned int a = 0;
	while( bitCount/pow(2,a) > 1 ){a++;}

	if( pow(2,a)!=bitCount ){
		std::cout << "bareMetal - bit count value " << bitCount << " is not on the 2^n scale" << std::endl;
		std::cout << "          - using closest larger value " << pow(2,a) << std::endl; 
	}  

	this->bitCount = pow(2,a);
}
bareMetal::~bareMetal(){}

std::string bareMetal::UINTtoHEX(unsigned int UINT){
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

unsigned int bareMetal::HEXtoUINT(std::string HEX){
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

std::string bareMetal::BINtoHEX(std::string binIn){
	//check if string can't be split into chunks of 4
	if(binIn.length() % 4 != 0){
		std::cout << "cannot turn bin string into hex string" << std::endl;
		std::cout << "bin string is: " << binIn.length() << std::endl;
		std::cout << "will only convert the first " << (unsigned int)(binIn.length()/4)*4 << " characters" << std::endl;
	}
	
	int value; 	std::string returnHex;
	for(unsigned int a = 0; a < (unsigned int)(binIn.length()/4)*4; a+=4){
		value = 0;
		if( binIn[a] == '1' ){value += 8;}
		if( binIn[a+1] == '1' ){value += 4;}
		if( binIn[a+2] == '1' ){value += 2;}
		if( binIn[a+3] == '1' ){value += 1;}
		
		switch(value){
			case 0:  returnHex += '0'; break;
			case 1:  returnHex += '1'; break;
			case 2:  returnHex += '2'; break;
			case 3:  returnHex += '3'; break;
			case 4:  returnHex += '4'; break;
			case 5:  returnHex += '5'; break;
			case 6:  returnHex += '6'; break;
			case 7:  returnHex += '7'; break;
			case 8:  returnHex += '8'; break;
			case 9:  returnHex += '9'; break;
			case 10: returnHex += 'a'; break;
			case 11: returnHex += 'b'; break;
			case 12: returnHex += 'c'; break;
			case 13: returnHex += 'd'; break;
			case 14: returnHex += 'e'; break;
			case 15: returnHex += 'f'; break;
		}
	}
	
	return returnHex;
}

std::string bareMetal::HEXtoBIN(std::string hexIn){
	std::string returnBin;
		
	for(unsigned int a = 0; a < hexIn.length(); a++){				
		switch(hexIn[a]){
			case '0': 			 returnBin += "0000"; break;
			case '1': 			 returnBin += "0001"; break;
			case '2': 			 returnBin += "0010"; break;
			case '3': 			 returnBin += "0011"; break;
			case '4': 			 returnBin += "0100"; break;
			case '5': 			 returnBin += "0101"; break;
			case '6': 			 returnBin += "0110"; break;
			case '7': 			 returnBin += "0111"; break;
			case '8': 			 returnBin += "1000"; break;
			case '9': 			 returnBin += "1001"; break;
			case 'a': case 'A':  returnBin += "1010"; break;
			case 'b': case 'B':  returnBin += "1011"; break;
			case 'c': case 'C':  returnBin += "1100"; break;
			case 'd': case 'D':  returnBin += "1101"; break;
			case 'e': case 'E':  returnBin += "1110"; break;
			case 'f': case 'F':  returnBin += "1111"; break;
			default: 
				std::cout << "unknown hex character: '" << hexIn[a] << "' inserting zero" << std::endl;
				returnBin += "0000";
			break;
		}
	}
	
	return returnBin;
}

unsigned int bareMetal::BINtoUINT(std::string BIN){ return HEXtoUINT(localSizeHex(BINtoHEX(BIN))); }
std::string bareMetal::UINTtoBIN(unsigned int UINT){ return HEXtoBIN(localSizeHex(UINTtoHEX(UINT))); }

std::string bareMetal::localSizeHex(std::string HEX){
    if(HEX.length() == bitCount/4){return HEX;}
    else if( HEX.length() < bitCount/4 ){
        for(unsigned int a = HEX.length(); a < bitCount/4; a++){ HEX = "0" + HEX; }
        return HEX;
    }
    else{
        std::string returnHEX;
        for(unsigned int a = 0; a < bitCount/4; a++){ returnHEX += HEX[ HEX.length()-a-1  ]; }
        return returnHEX;
    }
}
std::string bareMetal::localSizeBIN(std::string BIN){
    if(BIN.length() == bitCount){return BIN;}
    else if( BIN.length() < bitCount ){
        for(unsigned int a = BIN.length(); a < bitCount; a++){ BIN = "0" + BIN; }
        return BIN;
    }
    else{
        std::string returnBIN;
        for(unsigned int a = 0; a < bitCount; a++){ returnBIN += BIN[a]; }
        return returnBIN;
    }
}

int bareMetal::checkForComplyingLength(std::string HEX){
	return HEX.length() - bitCount/4;
}

bool bareMetal::isUINTbeyondBitCount(unsigned int UINT){
	return UINT > pow(2,bitCount);
}

unsigned int bareMetal::getBitCount(){return bitCount;}