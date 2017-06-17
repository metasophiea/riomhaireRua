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
void executer::runCommand(std::string instruction){
    incrementProgramCounter();

    std::string command = std::string(1,instruction[0]) + std::string(1,instruction[1]);
    std::string arg_1   = std::string(1,instruction[2]) + std::string(1,instruction[3]);
    std::string arg_2   = std::string(1,instruction[4]) + std::string(1,instruction[5]);

    /* nop           */ if      ( command.compare("00") == 0 ){  }
    /* goto l        */ else if ( command.compare("01") == 0 ){ memory.setByte(0,arg_1); memory.setByte(1,arg_2);}
    /* ifBitFlow f b */ else if ( command.compare("02") == 0 ){ if( !memory.getBit(arg_1, HEXtoUINT(arg_2)) ){ incrementProgramCounter(); } }
    /* ifBitSkip f b */ else if ( command.compare("03") == 0 ){ if( memory.getBit(arg_1, HEXtoUINT(arg_2)) ){ incrementProgramCounter(); } }
    /* wait t        */ else if ( command.compare("04") == 0 ){ usleep(1000*HEXtoUINT(arg_1+arg_2)); }
    /* clear f       */ else if ( command.compare("05") == 0 ){ memory.clearByte(arg_1); }
    /* set f         */ else if ( command.compare("06") == 0 ){ memory.setByte(arg_1,arg_2); }
    /* neg f         */ else if ( command.compare("07") == 0 ){ memory.setByte( arg_1 , logicUnit.neg     ( memory.getByte(arg_1) ) ); }
    /* flip f        */ else if ( command.compare("08") == 0 ){ memory.setByte( arg_1 , logicUnit.flip    ( memory.getByte(arg_1) ) ); }
    /* inc f         */ else if ( command.compare("09") == 0 ){ memory.setByte( arg_1 , logicUnit.inc     ( memory.getByte(arg_1) ) ); }
    /* dec f         */ else if ( command.compare("0a") == 0 ){ memory.setByte( arg_1 , logicUnit.dec     ( memory.getByte(arg_1) ) ); }
    /* lRotate f     */ else if ( command.compare("0b") == 0 ){ memory.setByte( arg_1 , logicUnit.lRotate ( memory.getByte(arg_1) ) ); }
    /* rRotate f     */ else if ( command.compare("0c") == 0 ){ memory.setByte( arg_1 , logicUnit.lRotate ( memory.getByte(arg_1) ) ); }
    /* copy f f      */ else if ( command.compare("0d") == 0 ){ memory.setByte( arg_2 , logicUnit.pass    ( memory.getByte(arg_1) ) ); }
    /* and f f       */ else if ( command.compare("0e") == 0 ){ memory.setByte( arg_2 , logicUnit.And     ( memory.getByte(arg_1),memory.getByte(arg_2)) ); }
    /* nand f f      */ else if ( command.compare("0f") == 0 ){ memory.setByte( arg_2 , logicUnit.nand    ( memory.getByte(arg_1),memory.getByte(arg_2)) ); }
    /* or f f        */ else if ( command.compare("10") == 0 ){ memory.setByte( arg_2 , logicUnit.Or      ( memory.getByte(arg_1),memory.getByte(arg_2)) ); }
    /* nor f f       */ else if ( command.compare("11") == 0 ){ memory.setByte( arg_2 , logicUnit.nor     ( memory.getByte(arg_1),memory.getByte(arg_2)) ); }
    /* xor f f       */ else if ( command.compare("12") == 0 ){ memory.setByte( arg_2 , logicUnit.Xor     ( memory.getByte(arg_1),memory.getByte(arg_2)) ); }
    /* add f f       */ else if ( command.compare("13") == 0 ){ memory.setByte( arg_2 , logicUnit.add     ( memory.getByte(arg_1),memory.getByte(arg_2)) ); }
    /* sub f f       */ else if ( command.compare("14") == 0 ){ memory.setByte( arg_2 , logicUnit.sub     ( memory.getByte(arg_1),memory.getByte(arg_2)) ); }

    programCounter = HEXtoUINT(memory.getByte(0))*256 + HEXtoUINT(memory.getByte(1));
    update();
}

void executer::printMemory(){memory.display();}