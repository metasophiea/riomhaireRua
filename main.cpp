#include <iostream>
#include <fstream>

#include "programManager.h"

/*
|----programManager--------------------------------------------------|
| program  |----executer-------------------------------------------| |
|    -     | |--logicUnit--| |--accessManager--------------------| | |
|    -     | |             | | |-memoryBlock-| |-consoleAccess-| | | |
|    -     | |             | | |             | |               | | | |
|    -     | |             | | |-------------| |---------------| | | |
|    -     | |-------------| |-----------------------------------| | |
|    -     |-------------------------------------------------------| |
|--------------------------------------------------------------------|
*/

int main(int argumentCount, char *arguments[]){    
    //input checking
        if(argumentCount < 2){ std::cout << "machine failed to start - elements missing from arguments" << std::endl; return 1;}
        if(argumentCount > 2){ std::cout << "machine failed to start - more arguments than allowed" << std::endl; return 2;}

    //create machine
        unsigned int bitCount = 8;
        unsigned int memorySize = 256;
        unsigned int programSize = 256;
        programManager machine = programManager(bitCount,memorySize,bitCount);

    //load in program
        std::ifstream inputFile(arguments[1]); std::string line;
        while(getline( inputFile, line )){ machine.appendCommand(line); }

    //run, and print memory when all is done
        machine.run();
        std::cout << std::endl << "program done - printing memory" << std::endl << std::endl;
        machine.printMemory();
        
    return 0;
}