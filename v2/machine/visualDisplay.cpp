#include <iostream>

#include "visualDisplay.h"

visualDisplay::visualDisplay(unsigned int bitCount, unsigned int width, unsigned int height):
    bareMetal(bitCount)
    {}
visualDisplay::~visualDisplay(){}

void visualDisplay::setAddressBit       (unsigned int bit, bool value){ std::cout << "setting visual address port bit: " << bit << " to: " << value << std::endl; }
void visualDisplay::setPixelBit         (unsigned int bit, bool value){ std::cout << "setting visual pixel port bit: " << bit << " to: " << value << std::endl; }
bool visualDisplay::getAddressBit       (unsigned int bit){return false;}
bool visualDisplay::getPixelBit         (unsigned int bit){return false;}

void visualDisplay::setAddressByte          (std::string value){ std::cout << "setting visual address port to: " << value << std::endl; }
void visualDisplay::setPixelByte            (std::string value){ std::cout << "setting visual pixel port to: " << value << std::endl; }
std::string visualDisplay::getAddressByte   (){return "string";}
std::string visualDisplay::getPixelByte     (){return "string";}