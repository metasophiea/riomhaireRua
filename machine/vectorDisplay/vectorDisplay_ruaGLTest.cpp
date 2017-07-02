#include <iostream>

#include "vectorDisplay.h"

int main(){
    std::cout << "Hello" << std::endl;

    vectorDisplay obj = vectorDisplay(8,256,500,500);
    obj.debug(true);
    std::cout << std::endl;

    //drawing square
    // 1 100 100 100 0 0 100 100 0
    obj.setAddressByte(0,0); obj.setMemoryByte(1);
    obj.setAddressByte(0,1); obj.setMemoryByte(255);
    obj.setAddressByte(0,2); obj.setMemoryByte(255);
    obj.setAddressByte(0,3); obj.setMemoryByte(255);

        obj.setAddressByte(0,4); obj.setMemoryByte(0);
        obj.setAddressByte(0,5); obj.setMemoryByte(0);

        obj.setAddressByte(0,6); obj.setMemoryByte(100);
        obj.setAddressByte(0,7); obj.setMemoryByte(100);

        obj.setAddressByte(0,8); obj.setMemoryByte(100);
        obj.setAddressByte(0,9); obj.setMemoryByte(0);

        obj.setAddressByte(0,10); obj.setMemoryByte(0);
        obj.setAddressByte(0,11); obj.setMemoryByte(0);

    obj.setAddressByte(0,12); obj.setMemoryByte(0);





    obj.printMemory();

    return 0;
}