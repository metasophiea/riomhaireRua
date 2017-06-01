#include <iostream>

#include "executer.h"

executer::executer(unsigned int bitCount, unsigned int memorySize):
bareMetal(bitCount),logicUnit(bitCount),memory(bitCount,memorySize)
{programCounter = 0;}
executer::~executer(){}

void executer::update(){
    memory.setBit( 1, 0, logicUnit.isZero() );
    memory.setBit( 1, 1, logicUnit.isCarry() );
}

unsigned int executer::nextCommandNumber(){return programCounter;}
void executer::runCommand(std::string command){
    memory.setByte(0,logicUnit.inc( memory.getByte(0) ));

    std::string arg_1 = std::string(1,command[1]) + std::string(1,command[2]);
    std::string arg_2 = std::string(1,command[3]) + std::string(1,command[4]);

    switch(command[0]){
        /* nop           */ case '0': break;
        /* goto l        */ case '1': memory.setByte(0,arg_1); break;
        /* ifBitFlow f b */ case '2': if( !memory.getBit(arg_1, HEXtoUINT(arg_2)) ){ memory.setByte(0,logicUnit.inc( memory.getByte(0) )); } break;
        /* clear f       */ case '3': memory.clearByte(arg_1); break;
        /* flip f        */ case '4': memory.setByte( arg_1 , logicUnit.flip   ( memory.getByte(arg_1) ) ); break;
        /* inc f         */ case '5': memory.setByte( arg_1 , logicUnit.inc    ( memory.getByte(arg_1) ) ); break;
        /* lShift f      */ case '6': memory.setByte( arg_1 , logicUnit.lShift ( memory.getByte(arg_1) ) ); break;
        /* copy f f      */ case '7': memory.setByte( arg_2 , logicUnit.pass   ( memory.getByte(arg_1) ) ); break;
        /* nand f f      */ case '8': memory.setByte( arg_2 , logicUnit.nand   ( memory.getByte(arg_1),memory.getByte(arg_2)) ); break;
        /* add f f       */ case '9': memory.setByte( arg_2 , logicUnit.add    ( memory.getByte(arg_1),memory.getByte(arg_2)) ); break;
    }

    programCounter = HEXtoUINT(memory.getByte(0));
    update();
}

void executer::printMemory(){memory.display();}