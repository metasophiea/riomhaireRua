#include <iostream>
#include <vector>

#include "visualDisplay.h"
#include <Cocoa/Cocoa.h>

visualDisplay::visualDisplay(unsigned int bitCount, unsigned int width, unsigned int height):
    bareMetal(bitCount),
    width(width),
    height(height)
    {
        for(unsigned int a = 0; a < width*height; a++){ pixelArray.push_back(localSizeHex("0")); }
        selectedPixel = localSizeHex("0");
        setUp();
    }

std::vector<std::string> visualDisplay::pixelArray = std::vector<std::string>();

visualDisplay::~visualDisplay(){}

void visualDisplay::setAddressBit       (unsigned int bit, bool value){ 
    std::string temp = HEXtoBIN(selectedPixel);
    if(value){ temp[bit] = '1'; }else{ temp[bit] = '0'; }
    selectedPixel = BINtoHEX(temp); 
}
void visualDisplay::setPixelBit         (unsigned int bit, bool value){ 
    std::string temp = HEXtoBIN(pixelArray[HEXtoUINT(selectedPixel)]);
    if(value){ temp[bit] = '1'; }else{ temp[bit] = '0'; }
    pixelArray[HEXtoUINT(selectedPixel)] = BINtoHEX(temp); 
}
bool visualDisplay::getAddressBit       (unsigned int bit){return HEXtoBIN(selectedPixel)[bit];}
bool visualDisplay::getPixelBit         (unsigned int bit){return HEXtoBIN(pixelArray[HEXtoUINT(selectedPixel)])[bit]; render();}

void visualDisplay::setAddressByte          (std::string value){ selectedPixel = value;}
void visualDisplay::setPixelByte            (std::string value){ pixelArray[HEXtoUINT(selectedPixel)] = value; render();}
std::string visualDisplay::getAddressByte   (){return selectedPixel;}
std::string visualDisplay::getPixelByte     (){return pixelArray[HEXtoUINT(selectedPixel)];}

void visualDisplay::display(){
    //x axis numbering
        for(unsigned int b = 0; b < getBitCount()/4; b++){ std::cout << " "; }
        std::cout << " | ";
        for(unsigned int a = 0; a < width; a++){
            std::cout << localSizeHex(UINTtoHEX(a)) << " ";
        }std::cout << std::endl;

    //x axis divider
        for(unsigned int b = 0; b < getBitCount()/4; b++){ std::cout << "-"; }
        std::cout << "--";
        for(unsigned int a = 0; a < width; a++){
            std::cout << "-";
            for(unsigned int b = 0; b < getBitCount()/4; b++){ std::cout << "-"; }
        }std::cout << std::endl;

    //y axis numbering, divider and data
        for(unsigned int a = 0; a < height*width; a+=16){
            std::cout << localSizeHex(UINTtoHEX(a)) << " | ";
            for(unsigned int b = 0; b < width; b++){
                std::cout << localSizeHex(pixelArray[a+b]) << " ";
            }
            std::cout << std::endl;
        }
}

    //openGL functions
    void visualDisplay::setUp(){}
    void visualDisplay::render(){}