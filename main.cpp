#include <iostream>

#include "executer.h"

/*
|----executer-------------------------------------------|
| |--logicUnit--| |--accessManager--------------------| |
| |             | | |-memoryBlock-| |-consoleAccess-| | |
| |             | | |             | |               | | |
| |-------------| | |-------------| |---------------| | |
|                 |                                   | |
|                 |-----------------------------------| |
|                                                       |
|-------------------------------------------------------|
*/

int main(int argumentCount, char *arguments[]){

    std::cout << "Hello" << std::endl;

    executer a = executer(8,256);
    a.runCommand("11000");
    a.runCommand("40220");

    a.printMemory();
        
    return 0;
}