#include <iostream>

#include "pixelDisplay.h"

int main(){
    std::cout << "Hello" << std::endl;

    pixelDisplay obj = pixelDisplay(8,2,500,500,500,500);
    obj.debug(true);
    std::cout << std::endl;

    std::cout << "- obj.setAddressByte(0,10)" << std::endl;
        obj.setAddressByte(0,10); 
        std::cout << std::endl;
    std::cout << "- obj.getAddressByte(0)" << std::endl;
        std::cout << obj.getAddressByte(0) << std::endl;
        std::cout << std::endl;
    std::cout << "- obj.setAddressBit(0,1,true)" << std::endl;
        obj.setAddressBit(0,1,true); 
        std::cout << std::endl;
    std::cout << "- obj.getAddressBit(0,1)" << std::endl;
        std::cout << obj.getAddressBit(0,1) << std::endl;
        std::cout << std::endl;

    std::cout << "- obj.setPixelByte(100)" << std::endl;
        obj.setPixelByte(100);
        std::cout << std::endl;
    std::cout << "- obj.getPixelByte()" << std::endl;
        std::cout << obj.getPixelByte() << std::endl;
        std::cout << std::endl;
    std::cout << "- obj.setPixelBit(100)" << std::endl;
        obj.setPixelBit(7,true);
        std::cout << std::endl;
    std::cout << "- obj.getPixelBit(0)" << std::endl;
        std::cout << obj.getPixelBit(0) << std::endl;
        std::cout << std::endl;


        
    return 0;
}