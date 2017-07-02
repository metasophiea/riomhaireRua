#include <iostream>

#include "vectorDisplay.h"

int main(){
    std::cout << "Hello" << std::endl;

    vectorDisplay obj = vectorDisplay(8,256,500,500);
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

    std::cout << "- obj.setMemoryByte(100)" << std::endl;
        obj.setMemoryByte(100);
        std::cout << std::endl;
    std::cout << "- obj.getMemoryByte()" << std::endl;
        std::cout << obj.getMemoryByte() << std::endl;
        std::cout << std::endl;
    std::cout << "- obj.setMemoryBit(7,true)" << std::endl;
        obj.setMemoryBit(7,true);
        std::cout << std::endl;
    std::cout << "- obj.getMemoryBit(0)" << std::endl;
        std::cout << obj.getMemoryBit(0) << std::endl;
        std::cout << std::endl;

    obj.printMemory();

    return 0;
}