#include <iostream>

#include "consoleAccess.h"

consoleAccess::consoleAccess(unsigned int bitCount):
bareMetal(bitCount){}
consoleAccess::~consoleAccess(){}

bool consoleAccess::getBit(){
    std::string input;
    
    do{ std::cout << "single bit input: "; std::cin >> input; }
    while(input.length() != 1);

    return input != "0" ? true : false;
}

void consoleAccess::writeBit(bool value){
    std::cout << value << std::endl;
}

std::string consoleAccess::getByte(){
    std::string input;
    
    do{ std::cout << "byte input: "; std::cin >> input; }
    while(input.length() > 2 || input.length() == 0);

    if(input.length() == 1){ input = "0" + input; }

    return input;
}

void consoleAccess::writeByte(std::string value){std::cout << value << std::endl;}