#include <iostream>

#include "vectorDisplay.h"

int main(){
    std::cout << "Hello" << std::endl;

    vectorDisplay obj = vectorDisplay(8,256,500,500);
    obj.debug(true);
    std::cout << std::endl;

    //drawing poly
    // 1 RGB points . . . first-point
    unsigned int counter = 0;
    obj.setAddressByte(0,(counter++)); obj.setMemoryByte(1);
    obj.setAddressByte(0,(counter++)); obj.setMemoryByte(28);

        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(128);
        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(55);

        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(55);
        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(200);

        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(200);
        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(200);

        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(128);
        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(55);

    //drawing a rectangle
    // 2 RGB x y width height angle
    obj.setAddressByte(0,(counter++)); obj.setMemoryByte(2);
    obj.setAddressByte(0,(counter++)); obj.setMemoryByte(3);

        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(30);
        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(30);

        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(30);
        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(30);

        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(10);

    //drawing a central rectangle
    // 3 RGB x y width height angle
    obj.setAddressByte(0,(counter++)); obj.setMemoryByte(3);
    obj.setAddressByte(0,(counter++)); obj.setMemoryByte(44);

        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(30);
        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(30);

        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(30);
        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(30);

        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(20);

    //drawing a circle
    // 4 RGB x y radius
    obj.setAddressByte(0,(counter++)); obj.setMemoryByte(4);
    obj.setAddressByte(0,(counter++)); obj.setMemoryByte(100);

        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(40);
        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(40);

        obj.setAddressByte(0,(counter++)); obj.setMemoryByte(50);


    obj.printMemory();

    return 0;
}