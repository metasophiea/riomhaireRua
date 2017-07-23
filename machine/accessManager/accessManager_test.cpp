#include <iostream>

#include "accessManager.h"

int main(){
    std::cout << "Hello" << std::endl;

    accessManager obj = accessManager(8,256);
    obj.debug(true);

    obj.setByte(5,30);
    obj.setByte(4,30);
    obj.setByte(5,60);
    obj.setByte(4,200);

    std::cout << std::endl;

    obj.printMemory();

    return 0;
}