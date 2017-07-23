#include <iostream>

#include "memoryBlock.h"

int main(){
    std::cout << "Hello" << std::endl;

    // //byte setting and getting
    //     memoryBlock obj = memoryBlock(8,2048);
    //     obj.debug(false);

    //     obj.setByte(2047,255);
    //     std::cout << obj.getByte(2047) << std::endl; 

    //     obj.printMemory();

    //bit setting and getting 
        memoryBlock obj = memoryBlock(8,256);
        obj.debug(true);

        obj.setBit(0,1,true);
        std::cout << obj.getBit(0,0) << std::endl;

        obj.printMemory();

    return 0;
}