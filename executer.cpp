#include <iostream>

#include "executer.h"

executer::executer(unsigned int bitCount, unsigned int memorySize):
logicUnit(bitCount),memory(bitCount,memorySize)
{programCounter = 0;}
executer::~executer(){}

void executer::update(){
    memory.setBit( 1, 0, logicUnit.isZero() );
    memory.setBit( 1, 1, logicUnit.isCarry() );

    memory.setByte(0,logicUnit.inc( memory.getByte(0) ));
}

void executer::runCommand(std::string command){
    std::string arg_1 = std::string(1,command[1]) + std::string(1,command[2]);
    std::string arg_2 = std::string(1,command[3]) + std::string(1,command[4]);

    switch(command[0]){
        /* clear  f   | 0nnxx */ case '0': memory.clearByte(arg_1); break;
        /* flip   f   | 1nnxx */ case '1': memory.setByte( arg_1 , logicUnit.flip   ( memory.getByte(arg_1) ) ); break;
        /* inc    f   | 2nnxx */ case '2': memory.setByte( arg_1 , logicUnit.inc    ( memory.getByte(arg_1) ) ); break;
        /* lShift f   | 3nnxx */ case '3': memory.setByte( arg_1 , logicUnit.lShift ( memory.getByte(arg_1) ) ); break;
        /* copy   f f | 4nnnn */ case '4': memory.setByte( arg_2 , logicUnit.pass   ( memory.getByte(arg_1) ) ); break;
        /* nand   f f | 5nnnn */ case '5': memory.setByte( arg_2 , logicUnit.nand   ( memory.getByte(arg_1),memory.getByte(arg_2)) ); break;
        /* add    f f | 6nnnn */ case '6': memory.setByte( arg_2 , logicUnit.add    ( memory.getByte(arg_1),memory.getByte(arg_2)) ); break;
    }

    update();
}

void executer::printMemory(){memory.display();}