#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>

#include "executer.h"

//construction/destruction
    executer::executer(unsigned int bitSize, unsigned int worktopSize, unsigned int programCounterByteCount):
        metal(bitSize),
        programCounter(0),
        debugMode(false),
        SAMmode(false),
        programCounterByteCount(programCounterByteCount),
        logicUnit(bitSize),
        accessManager(bitSize,worktopSize)
        {}
    executer::~executer(){}

//process controls
    void executer::runInstruction(std::string instruction){
        if(debugMode){ std::cout << "executer - performing instruction: " << instruction << std::endl; } 
        programCounter++;

        std::vector<std::string> instructionSegments = splitString(instruction,':');
        switch( std::atoi( instructionSegments[0].c_str() ) ){
            /* nop             */ case  0: break;
            /* goto            */ case  1: programCounter = std::atoi(instructionSegments[1].c_str()); break;
            /* wait            */ case  2: usleep(1000*std::atoi(instructionSegments[1].c_str())); break;
            /* ifbitflow       */ case  3: break;
            /* ifbitskip       */ case  4: break;
            /* ifbytezeroflow  */ case  5: break;
            /* ifbytezeroskip  */ case  6: break;
            /* ifclippingflow  */ case  7: break;
            /* ifclippingskip  */ case  8: break;
            /* ifsammodeonflow */ case  9: break;
            /* ifsammodeonskip */ case 10: break;
            /* setBit          */ case 11: 
                accessManager.setBit(
                    std::atoi(instructionSegments[1].c_str()),
                    std::atoi(instructionSegments[2].c_str()),
                    (std::atoi(instructionSegments[3].c_str()) != 0)
                ); 
            break;
            /* clear           */ case 12: accessManager.setByte(std::atoi(instructionSegments[1].c_str()),0); break;
            /* flip            */ case 13: break;
            /* lrotate         */ case 14: break;
            /* rrotate         */ case 15: break;
            /* copy            */ case 16: break;
            /* and             */ case 17: break;
            /* nand            */ case 18: break;
            /* or              */ case 19: break;
            /* nor             */ case 20: break;
            /* xor             */ case 21: break;
            /* sammode         */ case 22: if(std::atoi(instructionSegments[1].c_str()) != 0){SAMmode = true;}else{SAMmode = false;} break;
            /* convert         */ case 23: break;
            /* set             */ case 24: break;
            /* int             */ case 25: break;
            /* dec             */ case 26: break;
            /* neg             */ case 27: break;
            /* add             */ case 28: break;
            /* sub             */ case 29: break;
        }

        update();
    }
    unsigned int executer::nextInstructionNumber(){ return programCounter; }
    void executer::update(){if(debugMode){ std::cout << "executer - updating program counter" << std::endl; } 
        //updating program counter bytes
            std::string fullLengthHex = resize(UINTtoHEX(programCounter), programCounterByteCount*getBitSize()/4 ); std::string temp; if(debugMode){ std::cout << "executer - new program location number: " << fullLengthHex << std::endl; } 
            for(unsigned int a = 0; a < fullLengthHex.length(); a+=(getBitSize()/4)){ temp = "";
                for(unsigned int b = 0; b < (getBitSize()/4); b++){ temp = fullLengthHex[ fullLengthHex.length()-1-a-b ] + temp; }
                accessManager.setByte( programCounterByteCount-1-( a/(getBitSize()/4) ) , HEXtoUINT(temp) );
                if(debugMode){ std::cout << "executer - setting byte: " << programCounterByteCount-1-( a/(getBitSize()/4) ) << " to " << temp << std::endl; } 
            }
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
    void executer::printMemory(){if(debugMode){ std::cout << "executer - printing memory" << std::endl; } 
        accessManager.printMemory();
    }
    void executer::debug(bool onOff){ 
        debugMode = onOff; 
        accessManager.debug(onOff);
    }