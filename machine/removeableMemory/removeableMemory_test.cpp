#include <iostream>

#include "removeableMemory.h"

int main(){
    std::cout << "Hello" << std::endl;

    //byte setting and getting
        removeableMemory obj = removeableMemory(8,16);
        obj.debug(true);

        // obj.setBit(1, 0, false);

        // std::cout << obj.getBit(1, 0) << std::endl;
        // std::cout << obj.getBit(1, 1) << std::endl;
        // std::cout << obj.getBit(1, 2) << std::endl;
        // std::cout << obj.getBit(1, 3) << std::endl;
        // std::cout << obj.getBit(1, 4) << std::endl;
        // std::cout << obj.getBit(1, 5) << std::endl;
        // std::cout << obj.getBit(1, 6) << std::endl;
        // std::cout << obj.getBit(1, 7) << std::endl;

        // std::cout << obj.getByte(0) << std::endl; 
        // std::cout << obj.getByte(1) << std::endl; 
        // std::cout << obj.getByte(2) << std::endl; 

        obj.setByte(10,100);

        // std::cout << std::endl;

        // std::cout << obj.getByte(0) << std::endl; 
        // std::cout << obj.getByte(1) << std::endl; 
        // std::cout << obj.getByte(2) << std::endl; 

        obj.printMemory();

    return 0;
}