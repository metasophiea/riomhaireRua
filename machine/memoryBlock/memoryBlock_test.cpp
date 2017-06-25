#include <iostream>

#include "memoryBlock.h"

int main(){    
    std::cout << "Hello" << std::endl;

    memoryBlock mb = memoryBlock(8,256);
    mb.debug(true);

    //Memory printing
        std::cout << "Memory printing test" << std::endl;
        mb.printMemory();
        std::cout << std::endl << std::endl;

    //Setting bytes
        std::cout << "Memory byte setting test" << std::endl;
        mb.setByte(0,10);
        mb.printMemory();
        std::cout << std::endl << std::endl;

    //Getting bytes
        std::cout << "Memory byte getting test" << std::endl;
        std::cout << mb.getByte(0) << std::endl;
        std::cout << std::endl << std::endl;

    //Setting bits
        std::cout << "Memory bit setting test" << std::endl;
        mb.setBit(1,0,true);
        mb.printMemory();
        std::cout << std::endl << std::endl;

    //Getting bits
        std::cout << "Memory bit getting test" << std::endl;
        std::cout << mb.getBit(1,0) << std::endl;
        std::cout << std::endl << std::endl;

    return 0;
}