#include <iostream>

#include "executer.h"

int main(){
    std::cout << "Hello" << std::endl;

    executer obj = executer(8,256,2);
    //obj.debug(true);

    std::cout << obj.getProgramCounter() << std::endl;
    obj.runInstruction("0");
    std::cout << obj.getProgramCounter() << std::endl;
    obj.runInstruction("1:10");
    std::cout << obj.getProgramCounter() << std::endl;
    obj.runInstruction("0");
    std::cout << obj.getProgramCounter() << std::endl;

    obj.runInstruction("23:2:10");
    std::cout << obj.getProgramCounter() << std::endl;
    obj.runInstruction("23:3:0");
    std::cout << obj.getProgramCounter() << std::endl;
    obj.runInstruction("2");
    std::cout << obj.getProgramCounter() << std::endl;

    std::cout << std::endl;

    obj.printMemory();

    return 0;
}