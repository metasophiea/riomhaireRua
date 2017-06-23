#include <iostream>
#include <fstream>

#include "programManager.h"

// sign and magnitude (-0 is zero, 0 is null)
// calculations are capped (with flags to indicate clipping)

/*
|----programManager-------------------------------------------------------------------| |-displayUnit---|
| program  |----executer------------------------------------------------------------| | |               |
|    -     | |--logicUnit--| |--accessManager-------------------------------------| | | |               |
|    -     | |             | | |-memoryBlock-| |-console-------| |-visualDisplay-|| | | |------|--------|
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
        unsigned int bitSize = 8;
        unsigned int worktopSize = 256;
        unsigned int programCounterByteCount = 2;
        programManager machine = programManager(bitSize,worktopSize,programCounterByteCount);
        //machine.debug(true);

    //load in program
        std::ifstream inputFile(arguments[1]); 
        if( !inputFile.good() ){ std::cout << "machine failed to start - provided file does not exist" << std::endl; return 3;}
        std::string line;
        while(getline( inputFile, line )){ machine.appendInstruction(line); }

    //run, and print memory when all is done
        machine.run();
        std::cout << std::endl << std::endl << "program done - printing memory" << std::endl << std::endl;
        machine.printMemory();
        
    return 0;
}