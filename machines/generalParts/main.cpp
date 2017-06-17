#include <iostream>
#include <fstream>
#include <unistd.h>

#include "programManager.h"

/*
|----programManager-------------------------------------------------------------------| |-displayUnit---|
| program  |----executer------------------------------------------------------------| | |               |
|    -     | |--logicUnit--| |--accessManager-------------------------------------| | | |               |
|    -     | |             | | |-memoryBlock-| |-consoleAccess-| |-visualDisplay-|| | | |------|--------|
|    -     | |             | | |             | |               | |               || | |        |
|    -     | |             | | |             | |               | |       ----------------------|
|    -     | |             | | |             | |               | |               || | |
|    -     | |             | | |-------------| |---------------| |---------------|| | |
|    -     | |-------------| |----------------------------------------------------| | |
|    -     |------------------------------------------------------------------------| |
|-------------------------------------------------------------------------------------|
*/

int main(int argumentCount, char *arguments[]){    
    //input checking
        if(argumentCount < 2){ std::cout << "machine failed to start - elements missing from arguments" << std::endl; return 1;}
        if(argumentCount > 2){ std::cout << "machine failed to start - more arguments than allowed" << std::endl; return 2;}

    //create machine
        unsigned int bitCount = 8;
        unsigned int memorySize = 256;
        unsigned int programSize = 65536;
        programManager machine = programManager(bitCount,memorySize,programSize);

    //load in program
        std::ifstream inputFile(arguments[1]); 
        if( !inputFile.good() ){ std::cout << "machine failed to start - provided file does not exist" << std::endl; return 3;}
        std::string line;
        while(getline( inputFile, line )){ machine.appendCommand(line); }

    //run, and print memory when all is done
        machine.run();
        std::cout << std::endl << "program done - printing memory" << std::endl << std::endl;
        machine.printMemory();
        
    return 0;
}