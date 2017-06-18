#include <iostream>
#include <math.h>

#include "programManager.h"

//construction/destruction
    programManager::programManager(unsigned int bitSize, unsigned int worktopSize, unsigned int programCounterByteCount):
        executer(bitSize,worktopSize,programCounterByteCount),
        programCounterByteCount(programCounterByteCount)
        {
            debugMode = false;
            programLength = 0;
            maxProgramLength = pow(2,(bitSize*programCounterByteCount));
            program = new std::string[maxProgramLength];
        }
    programManager::~programManager(){}

//program manipulation
    void programManager::clearProgram(){ if(debugMode){ std::cout << "programManager - clearing program" << std::endl; } program = new std::string[maxProgramLength]; }
    void programManager::load(std::string newProgram[], unsigned int newProgramLength){ if(debugMode){ std::cout << "loading in new program" << std::endl; } 
        clearProgram();
        if( newProgramLength > maxProgramLength ){ std::cout << "programManager::load error - provided program too large : " << newProgramLength << "/" << maxProgramLength << std::endl; return;}
        programLength = newProgramLength; if(debugMode){ std::cout << "programManager - newProgramLength: " << newProgramLength << std::endl; } 
        for(unsigned int a = 0; a < newProgramLength; a++){ if(debugMode){std::cout << a << "\t" << newProgram[a] << std::endl;} program[a] = newProgram[a]; }
        if(debugMode){ std::cout << "programManager - program loaded" << std::endl; } 
    }

    void programManager::appendInstruction(std::string instruction){ if(debugMode){ std::cout << "programManager - appending command" << std::endl; } 
        if( programLength + 1 > maxProgramLength ){ std::cout << "programManager::appendCommand error - no more command space left" << std::endl; return;}
        program[programLength] = instruction; if(debugMode){ std::cout << "programManager - new instruction: " << instruction << " at position " << programLength << std::endl; } 
        programLength++; 
    }

    void programManager::run(){if(debugMode){ std::cout << "programManager - running program" << std::endl; }
        unsigned int nextCommand = 0;
        while(true){
            nextCommand = executer.nextInstructionNumber();
            if( nextCommand >= programLength || nextCommand >= maxProgramLength ){ break; }
            if(debugMode){ std::cout << "programManager - next command number: " << nextCommand << " | " << program[nextCommand] << std::endl; }
            executer.runInstruction(program[nextCommand]); 
        }

        executer.runInstruction("");
    }

//printers and debug
    void programManager::printProgram(){
        std::cout << "- Loaded Program -" << std::endl;
        for(unsigned int a = 0; a < programLength; a++){ std::cout << a << "\t" << program[a] << std::endl; }
    }
    void programManager::printMemory(){ executer.printMemory(); }
    void programManager::debug(bool onOff){ 
        debugMode = onOff;
        executer.debug(onOff);
    }