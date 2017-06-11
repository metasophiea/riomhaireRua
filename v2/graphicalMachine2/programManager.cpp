#include <iostream>

#include "programManager.h"

programManager::programManager(unsigned int bitCount, unsigned int memorySize, unsigned int maxProgramLength):
    executer(bitCount,memorySize),
    maxProgramLength(maxProgramLength)
    { 
        program = new std::string[maxProgramLength];
    }
programManager::~programManager(){}

void programManager::load(std::string newProgram[], unsigned int newProgramLength){ 
    if( newProgramLength > maxProgramLength ){ std::cout << "programManager::load error - provided program too large : " << newProgramLength << "/" << maxProgramLength << std::endl; return;}
    programLength = newProgramLength;
    for(unsigned int a = 0; a < newProgramLength; a++){ program[a] = newProgram[a]; }
}

void programManager::appendCommand(std::string command){
    if( programLength + 1 > maxProgramLength ){ std::cout << "programManager::appendCommand error - no more command space left" << std::endl; return;}
    program[programLength] = command;
    programLength++; 
}

void programManager::run(){
    unsigned int nextCommand;
    while(true){
        nextCommand = executer.nextCommandNumber();
        if( nextCommand >= programLength || nextCommand >= maxProgramLength ){ break; }
        executer.runCommand(program[nextCommand]); 
    }
    stop();
}

void programManager::stop(){}

void programManager::printMemory(){executer.printMemory();}