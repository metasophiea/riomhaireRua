#include <iostream>

#include "removableMemory.h"

int main(){
    std::cout << "Hello" << std::endl;

    //byte setting and getting
        removableMemory obj = removableMemory(8,16,"loadedMemory_2.txt");

        //debuggin'
            obj.debug(true);
            obj.getByte(10);
            obj.setByte(10,100);

            obj.getBit(1, 0);
            obj.setBit(1, 0, false);

            obj.printMemory();

        // breakin' stuff
            //obj.getByte(1000);
            //obj.setByte(0,10000);
            //obj.getBit(1000, 10);
            //obj.setBit(1, 10, false);

        // //gettin' and settin'
        //     std::cout << obj.getByte(1) << std::endl; 
        //     obj.setByte(1,100);
        //     std::cout << obj.getByte(1) << std::endl; 

        // //bit work
        //     std::cout   << obj.getByte(1) << std::endl;
        //     std::cout   << obj.getBit(1, 7)
        //                 << obj.getBit(1, 6)
        //                 << obj.getBit(1, 5)
        //                 << obj.getBit(1, 4)
        //                 << obj.getBit(1, 3)
        //                 << obj.getBit(1, 2)
        //                 << obj.getBit(1, 1)
        //                 << obj.getBit(1, 0) 
        //                 << std::endl;

        //     obj.setBit(1, 0, true);

        //     std::cout   << obj.getByte(1) << std::endl;
        //     std::cout   << obj.getBit(1, 7)
        //                 << obj.getBit(1, 6)
        //                 << obj.getBit(1, 5)
        //                 << obj.getBit(1, 4)
        //                 << obj.getBit(1, 3)
        //                 << obj.getBit(1, 2)
        //                 << obj.getBit(1, 1)
        //                 << obj.getBit(1, 0) 
        //                 << std::endl;

    return 0;
}