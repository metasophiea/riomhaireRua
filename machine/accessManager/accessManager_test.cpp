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

    // // testing storage device A
    //     accessManager obj = accessManager(8,256);
    //     obj.debug(true);

    //     obj.setByte(13,0);
    //     obj.setByte(14,100);
    //     obj.setByte(12,255);
    //     std::cout << obj.getByte(12) << std::endl;
    //     std::cout << std::endl;

    //     obj.setBit(12,0,false);
    //     std::cout << obj.getByte(12) << std::endl;
    //     std::cout << std::endl;

    //     obj.setByte(13,200);
    //     obj.setByte(14,47);
    //     obj.setBit(12,1,true);
    //     std::cout << std::endl;
    //     std::cout << obj.getByte(12) << std::endl;
    //     std::cout << obj.getBit(12,1) << std::endl;

    //     std::cout << std::endl;

    //     obj.printMemory();

    // testing removable storage device A
        accessManager obj = accessManager(8,256);

        // obj.setByte(15,2);
        // std::cout << obj.getByte(16) << std::endl;
        
        // obj.setByte(15,2);
        // obj.setByte(16,100);

        // obj.setByte(15,3);
        // std::cout   << obj.getByte(16) << std::endl;
        // std::cout   << obj.getBit(16, 7)
        //             << obj.getBit(16, 6)
        //             << obj.getBit(16, 5)
        //             << obj.getBit(16, 4)
        //             << obj.getBit(16, 3)
        //             << obj.getBit(16, 2)
        //             << obj.getBit(16, 1)
        //             << obj.getBit(16, 0) 
        //             << std::endl;

        // obj.setBit(16, 0, true);

        // std::cout   << obj.getByte(16) << std::endl;
        // std::cout   << obj.getBit(16, 7)
        //             << obj.getBit(16, 6)
        //             << obj.getBit(16, 5)
        //             << obj.getBit(16, 4)
        //             << obj.getBit(16, 3)
        //             << obj.getBit(16, 2)
        //             << obj.getBit(16, 1)
        //             << obj.getBit(16, 0) 
        //             << std::endl;

        obj.printMemory();


    return 0;
}