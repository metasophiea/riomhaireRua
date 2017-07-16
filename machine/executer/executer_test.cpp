#include <iostream>

#include "executer.h"

int main(){
    std::cout << "Hello" << std::endl;

    executer obj = executer(8,256,2);
    obj.debug(true);

    obj.runInstruction("0");
    obj.runInstruction("1:10");
    obj.runInstruction("0");

    return 0;
}