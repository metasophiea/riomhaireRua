#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>

#include "executer.h"

//construction/destruction
    executer::executer(unsigned int bitSize, unsigned int worktopSize, unsigned int programCounterByteCount):
        metal(bitSize),
        debugMode(false),
        programCounterByteCount(programCounterByteCount),
        programCounterStack(std::vector<unsigned int>()),
        logicUnit(bitSize),
        accessManager(bitSize,worktopSize)
        {}
    executer::~executer(){}

//process controls
    void executer::runInstruction(std::string instruction){
        if(debugMode){ std::cout << std::endl << "executer - performing instruction: " << instruction << std::endl; } 
        setProgramCounter(getProgramCounter() + 1);

        //split instruction up, and convert each to unsigned ints
        std::vector<std::string> instructionSegments_temp = splitString(instruction,':');
        std::vector<unsigned int> instructionSegments = std::vector<unsigned int>();
        for(unsigned int a = 0; a < instructionSegments_temp.size(); a++){  instructionSegments.push_back( std::atoi( instructionSegments_temp[a].c_str() ) ); }

        //match instruction number to the action
        if(debugMode){ std::cout << "executer - instruction number: " << instructionSegments[0] << std::endl; } 
        switch( instructionSegments[0] ){
            /* nop               */ case  0: if(debugMode){ std::cout << std::endl << "executer::nop" << std::endl; } break;
            /* goto              */ case  1: if(debugMode){ std::cout << std::endl << "executer::goto - going to instruction number " << instructionSegments[1] << std::endl; } setProgramCounter(instructionSegments[1]); break;
            /* jump              */ case  2: 
                if(debugMode){ std::cout << "executer::jump: high byte: " << accessManager.getByte(2) << std::endl; std::cout << "executer::jump: low byte: "  << accessManager.getByte(3) << std::endl; }
                setProgramCounter( accessManager.getByte(2)*10 + accessManager.getByte(3) );
            break;
            /* wait              */ case  3: if(debugMode){ std::cout << std::endl << "executer - wait - waiting for " << instructionSegments[1] << " milliseconds" << std::endl; } usleep(1000*instructionSegments[1]); break;
            /* ifBitSet          */ case  4: 
                if(debugMode){ std::cout << std::endl << "executer - ifBitSet - testing bit " << instructionSegments[2] << " in byte " << instructionSegments[1] << std::endl; }  
                if( accessManager.getBit(instructionSegments[1],instructionSegments[2]) ){
                    setProgramCounter(instructionSegments[3]);
                    if(debugMode){ std::cout << "executer::ifBitSet - bit set; going to location: " << instructionSegments[3] << std::endl; }
                }else{ if(debugMode){ std::cout << "executer::ifBitSet - bit not set" << std::endl; } }
            break;
            /* ifResultZero      */ case  5: 
                if(debugMode){ std::cout << std::endl << "executer::ifResultZero - testing if result is zero" << std::endl; }  
                if( logicUnit.getIsZero() ){
                    setProgramCounter(instructionSegments[1]);
                    if(debugMode){ std::cout << "executer::ifResultZero - result is zero; going to location: " << instructionSegments[1] << std::endl; }
                }else{ if(debugMode){ std::cout << "executer::ifResultZero - continuing as normal" << std::endl; } }
            break;
            /* ifResultOverflow  */ case  6: 
                if(debugMode){ std::cout << std::endl << "executer::ifResultOverflow - testing if result more than the maximum value" << std::endl; }  
                if( logicUnit.getOverflowed() ){
                    setProgramCounter(instructionSegments[1]);
                    if(debugMode){ std::cout << "executer::ifResultOverflow - result overflowed; going to location: " << instructionSegments[1] << std::endl; }
                }else{ if(debugMode){ std::cout << "executer::ifResultOverflow - continuing as normal" << std::endl; } }
            break;
            /* ifResultUnderflow */ case  7: 
                if(debugMode){ std::cout << std::endl << "executer::ifResultUnderflow - testing if result less than the minumum value" << std::endl; }  
                if( logicUnit.getUnderflowed() ){
                    setProgramCounter(instructionSegments[1]);
                    if(debugMode){ std::cout << "executer::ifResultUnderflow - result underflowed; going to location: " << instructionSegments[1] << std::endl; }
                }else{ if(debugMode){ std::cout << "executer::ifResultUnderflow - continuing as normal" << std::endl; } }
            break;
            /* ifResultNegative  */ case  8: 
                if(debugMode){ std::cout << std::endl << "executer::ifResultNegative - testing if result is negative" << std::endl; }  
                if( logicUnit.getSign() ){
                    setProgramCounter(instructionSegments[1]);
                    if(debugMode){ std::cout << "executer::ifResultNegative - result is negative; going to location: " << instructionSegments[1] << std::endl;}
                }else{ if(debugMode){ std::cout << "executer::ifResultNegative - continuing as normal" << std::endl; } }
            break;
            /* ifSAMmode         */ case  9: 
                if(debugMode){ std::cout << std::endl << "executer::ifSAMmode - testing if SAM mode is active " << std::endl; }  
                if( logicUnit.SAMmode() ){ 
                    setProgramCounter(instructionSegments[1]);
                    if(debugMode){ std::cout << "executer::ifSAMmode - SAM mode active; going to location: " << instructionSegments[1] << std::endl;}
                }else{ if(debugMode){ std::cout << "executer::ifSAMmode - continuing as normal" << std::endl; } }
            break;
            /* setBit            */ case  10: 
                if(debugMode){ std::cout << std::endl << "executer::setBit - setting the bit: " << instructionSegments[2] << " of the byte " << instructionSegments[1] << " to the value " << instructionSegments[3] << std::endl; }  
                accessManager.setBit(
                    instructionSegments[1],
                    instructionSegments[2],
                    (instructionSegments[3] != 0)
                ); 
            break;
            /* clear             */ case 11: accessManager.setByte(instructionSegments[1],0); break;
            /* flip              */ case 12: accessManager.setByte(instructionSegments[1], logicUnit.flip      ( accessManager.getByte(instructionSegments[1]) )); break;
            /* lrotate           */ case 13: accessManager.setByte(instructionSegments[1], logicUnit.lRotate   ( accessManager.getByte(instructionSegments[1]) )); break;
            /* rrotate           */ case 14: accessManager.setByte(instructionSegments[1], logicUnit.rRotate   ( accessManager.getByte(instructionSegments[1]) )); break;
            /* copy              */ case 15: accessManager.setByte(instructionSegments[2], logicUnit.logicCheck( accessManager.getByte(instructionSegments[1]) )); break;
            /* and               */ case 16: accessManager.setByte(instructionSegments[2], logicUnit.AND ( accessManager.getByte(instructionSegments[1]),accessManager.getByte(instructionSegments[2]) )); break;
            /* nand              */ case 17: accessManager.setByte(instructionSegments[2], logicUnit.NAND( accessManager.getByte(instructionSegments[1]),accessManager.getByte(instructionSegments[2]) )); break;
            /* or                */ case 18: accessManager.setByte(instructionSegments[2], logicUnit.OR  ( accessManager.getByte(instructionSegments[1]),accessManager.getByte(instructionSegments[2]) )); break;
            /* nor               */ case 19: accessManager.setByte(instructionSegments[2], logicUnit.NOR ( accessManager.getByte(instructionSegments[1]),accessManager.getByte(instructionSegments[2]) )); break;
            /* xor               */ case 20: accessManager.setByte(instructionSegments[2], logicUnit.XOR ( accessManager.getByte(instructionSegments[1]),accessManager.getByte(instructionSegments[2]) )); break;
            /* mode              */ case 21: logicUnit.setCalculationMode( instructionSegments[1] ); break;
            /* convert           */ case 22: accessManager.setByte(instructionSegments[1], logicUnit.convert( accessManager.getByte(instructionSegments[1]),instructionSegments[2],instructionSegments[3]) ); break;
            /* set               */ case 23: accessManager.setByte(instructionSegments[1], logicUnit.logicCheck(instructionSegments[2]) ); break;
            /* inc               */ case 24: accessManager.setByte(instructionSegments[1], logicUnit.inc( accessManager.getByte(instructionSegments[1]) )); break;
            /* dec               */ case 25: accessManager.setByte(instructionSegments[1], logicUnit.dec( accessManager.getByte(instructionSegments[1]) )); break;
            /* neg               */ case 26: accessManager.setByte(instructionSegments[1], logicUnit.neg( accessManager.getByte(instructionSegments[1]) )); break;
            /* add               */ case 27: accessManager.setByte(instructionSegments[3], logicUnit.add( accessManager.getByte(instructionSegments[1]),accessManager.getByte(instructionSegments[2]) )); break;
            /* sub               */ case 28: accessManager.setByte(instructionSegments[3], logicUnit.sub( accessManager.getByte(instructionSegments[1]),accessManager.getByte(instructionSegments[2]) )); break;
            /* routine           */ case 29: std::cout << "executer error - rutine definition command found: " << instruction << std::endl; break;
            /* end:routName      */ case 30: pullProgramPositionFromStack(); break;
            /* run:routName      */ case 31: pushCurrentProgramPositionToStack(instructionSegments[1]); break;
            default: std::cout << "executer error - unknown instruction: " << instructionSegments[0] << std::endl; break;
        }

        if(debugMode){ std::cout << "executer - end of instruction action" << std::endl << std::endl; }
    }

    unsigned int executer::getProgramCounter(){
        if(debugMode){ std::cout << "executer - getting instruction number" << std::endl; }

        std::string counterValue_str;
        for(unsigned int a = 0; a < programCounterByteCount; a++){
            counterValue_str += UINTtoHEX_systemSize( accessManager.getByte(a) );
        }

        if(debugMode){ std::cout << "executer - current program counter value: " << HEXtoUINT(counterValue_str) << std::endl; }
        return HEXtoUINT(counterValue_str);
    }
    void executer::setProgramCounter(unsigned int newValue){ 
        if(debugMode){ std::cout << "executer - setting program counter value to: " << newValue << std::endl; }

        //updating program counter bytes
            std::string fullLengthHex = resize(UINTtoHEX(newValue), programCounterByteCount*getBitSize()/4 ); std::string temp; if(debugMode){ std::cout << "executer - new program location number: " << fullLengthHex << std::endl; } 
            for(unsigned int a = 0; a < fullLengthHex.length(); a+=(getBitSize()/4)){ temp = "";
                for(unsigned int b = 0; b < (getBitSize()/4); b++){ temp = fullLengthHex[ fullLengthHex.length()-1-a-b ] + temp; }
                if(debugMode){ std::cout << "executer - setting byte: " << programCounterByteCount-1-( a/(getBitSize()/4) ) << " to " << temp << std::endl; } 
                accessManager.setByte( programCounterByteCount-1-( a/(getBitSize()/4) ) , HEXtoUINT(temp) );
            }
    }

    void executer::pushCurrentProgramPositionToStack(unsigned int newValue){
        if(debugMode){ unsigned int programCounterNumber = getProgramCounter(); std::cout << "executer - pushing current program position (which is: " << programCounterNumber << ") to the stack (position "<< programCounterStack.size() <<" on the stack)" << " to be replaced by: " << newValue << std::endl; }
        programCounterStack.push_back( getProgramCounter() ); if(debugMode){ std::cout << "executer - old program counter position added to stack" << std::endl; }
        setProgramCounter(newValue); if(debugMode){ std::cout << "executer - new program counter position added" << std::endl; }
    }
    void executer::pullProgramPositionFromStack(){
        if(debugMode){ std::cout << "executer - pulling program position from stack, position: " << programCounterStack.size() -1 << " which refers to location " << programCounterStack.back() << std::endl; }
        setProgramCounter( programCounterStack.back() ); if(debugMode){ std::cout << "executer - top program counter position from stack inserted into current program counter position" << std::endl; }
        programCounterStack.pop_back(); if(debugMode){ std::cout << "executer - top stack position removed" << std::endl; }
    }

//utilities
    std::vector<std::string> executer::splitString(std::string string, char splitChar){
        std::vector<std::string> output; std::string temp = "";

        for(unsigned int a = 0; a < string.length(); a++){
            if(string[a] == splitChar){ output.push_back(temp); temp = ""; }
            else{ temp += string[a]; }
        }

        output.push_back(temp);
        return output;
    }

//printers and debug
    void executer::printMemory(){
        std::cout << "Executer" << std::endl;
        std::cout << "- current program counter position: " << getProgramCounter() << std::endl;
        std::cout << "- program counter stack" << std::endl;
        for(int a = programCounterStack.size()-1; a >= 0; a--){ std::cout << a << " | " << programCounterStack[a] << std::endl; }
        std::cout << std::endl;
        accessManager.printMemory();
    }
    void executer::debug(bool onOff){
        debugMode = onOff;
        accessManager.debug(onOff);
        logicUnit.debug(onOff);
    }
    void executer::debug(bool onOff, unsigned int depth){
        debugMode = onOff;
        if(depth > 0){ 
            accessManager.debug(onOff,depth-1);
            logicUnit.debug(onOff,depth-1);
        }
    }