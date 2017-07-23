#include <iostream>

#include "accessManager.h"

int main(){
    std::cout << "Hello" << std::endl;

    // //testing indirect access
    //     accessManager obj = accessManager(8,256);
    //     obj.debug(true);

    //     obj.setByte(5,30);
    //     obj.setByte(4,30);
    //     obj.setByte(5,60);
    //     obj.setByte(4,200);

    //     std::cout << std::endl;
    //     obj.printMemory();

    // testing storage device 0 
        accessManager obj = accessManager(8,256);
        obj.debug(true);

        obj.setByte(13,0);
        obj.setByte(14,100);
        obj.setByte(12,255);
        std::cout << obj.getByte(12) << std::endl;
        std::cout << std::endl;

        obj.setBit(12,0,false);
        std::cout << obj.getByte(12) << std::endl;
        std::cout << std::endl;

        obj.setByte(13,200);
        obj.setByte(14,47);
        obj.setBit(12,1,true);
        std::cout << std::endl;
        std::cout << obj.getByte(12) << std::endl;
        std::cout << obj.getBit(12,1) << std::endl;

        std::cout << std::endl;

        obj.printMemory();

    return 0;
}