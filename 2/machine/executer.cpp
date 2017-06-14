#include <iostream>

#include "executer.h"

executer::executer(unsigned int bitCount, unsigned int memorySize):
bareMetal(bitCount),logicUnit(bitCount),memory(bitCount,memorySize)
{ programCounter = 0; LogicUnitFlagsByte = 2; }
executer::~executer(){}

void executer::update(){
    memory.setBit( LogicUnitFlagsByte, 0, logicUnit.isZero() );
    memory.setBit( LogicUnitFlagsByte, 1, logicUnit.isOverflow() );
    memory.setBit( LogicUnitFlagsByte, 2, logicUnit.isUnderflow() );
}

void executer::incrementProgramCounter(){
    unsigned int temp = HEXtoUINT(memory.getByte(1)) + 1;
    if( isUINTbeyondBitCount(temp) ){
        memory.setByte(1,0);
        temp = HEXtoUINT(memory.getByte(0)) + 1;
        if( isUINTbeyondBitCount(temp) ){ memory.setByte(0,0); }else{ memory.setByte(0,temp); }
    }else{ memory.setByte(1,temp); }
}

unsigned int executer::nextCommandNumber(){return programCounter;}
void executer::runCommand(std::string command){
    incrementProgramCounter();

    std::string arg_1 = std::string(1,command[1]) + std::string(1,command[2]);
    std::string arg_2 = std::string(1,command[3]) + std::string(1,command[4]);

    switch(command[0]){
        /* nop           */ case '0': break;
        /* goto l        */ case '1': memory.setByte(0,arg_1); memory.setByte(1,arg_2); break;
        /* ifBitFlow f b */ case '2': if( !memory.getBit(arg_1, HEXtoUINT(arg_2)) ){ incrementProgramCounter(); } break;
        /* ifBitSkip f b */ case '3': if( memory.getBit(arg_1, HEXtoUINT(arg_2)) ){ incrementProgramCounter(); } break;
        /* clear f       */ case '4': memory.clearByte(arg_1); break;
        /* set f         */ case '5': memory.setByte(arg_1,arg_2); break;
        /* flip f        */ case '6': memory.setByte( arg_1 , logicUnit.flip    ( memory.getByte(arg_1) ) ); break;
        /* inc f         */ case '7': memory.setByte( arg_1 , logicUnit.inc     ( memory.getByte(arg_1) ) ); break;
        /* dec f         */ case '8': memory.setByte( arg_1 , logicUnit.dec     ( memory.getByte(arg_1) ) ); break;
        /* lRotate f     */ case '9': memory.setByte( arg_1 , logicUnit.lRotate ( memory.getByte(arg_1) ) ); break;
        /* rRotate f     */ case 'a': memory.setByte( arg_1 , logicUnit.lRotate ( memory.getByte(arg_1) ) ); break;
        /* copy f f      */ case 'b': memory.setByte( arg_2 , logicUnit.pass    ( memory.getByte(arg_1) ) ); break;
        /* nand f f      */ case 'c': memory.setByte( arg_2 , logicUnit.nand    ( memory.getByte(arg_1),memory.getByte(arg_2)) ); break;
        /* add f f       */ case 'd': memory.setByte( arg_2 , logicUnit.add     ( memory.getByte(arg_1),memory.getByte(arg_2)) ); break;
    }

    programCounter = HEXtoUINT(memory.getByte(0))*256 + HEXtoUINT(memory.getByte(1));
    update();
}

void executer::printMemory(){memory.display();}