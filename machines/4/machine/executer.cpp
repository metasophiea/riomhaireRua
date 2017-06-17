#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>

#include "executer.h"

//construction/destruction
    executer::executer(unsigned int bitSize, unsigned int worktopSize, unsigned int programCounterByteCount):
        metal(bitSize),
        programCounterByteCount(programCounterByteCount),
        //logicUnit(bitSize),
        accessManager(bitSize,worktopSize)
        {
            programCounter = 0;
        }
    executer::~executer(){}

//process controls
    void executer::runInstruction(std::string instruction){
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
            /* clear           */ case 11: break;
            /* flip            */ case 12: break;
            /* lrotate         */ case 13: break;
            /* rrotate         */ case 14: break;
            /* copy            */ case 15: break;
            /* and             */ case 16: break;
            /* nand            */ case 17: break;
            /* or              */ case 18: break;
            /* nor             */ case 19: break;
            /* xor             */ case 20: break;
            /* sammode         */ case 21: break;
            /* convert         */ case 22: break;
            /* set             */ case 23: break;
            /* int             */ case 24: break;
            /* dec             */ case 25: break;
            /* neg             */ case 26: break;
            /* add             */ case 27: break;
            /* sub             */ case 28: break;
        }

        update();
    }
    unsigned int executer::nextInstructionNumber(){ return programCounter; }
    void executer::update(){
        //updating program counter bytes
            std::string fullLengthHex = resizeHex(UINTtoHEX(programCounter), programCounterByteCount*getBitSize()/4 ); std::string temp;
            for(unsigned int a = 0; a < fullLengthHex.length(); a+=(getBitSize()/4)){ temp = "";
                for(unsigned int b = 0; b < (getBitSize()/4); b++){ temp = fullLengthHex[ fullLengthHex.length()-1-a-b ] + temp; }
                accessManager.setByte( programCounterByteCount-1-( a/(getBitSize()/4) ) , HEXtoUINT(temp) );
            }
    }

//utilities
    std::vector<std::string> executer::splitString(std::string string, char splitChar){
        std::vector<std::string> output; std::string temp = "empty";

        for(unsigned int a = 0; a < string.length(); a++){
            if(string[a] == splitChar){ output.push_back(temp); temp = ""; }
            else{ temp += string[a]; }
        }

        output.push_back(temp);
        return output;
    }

//printers and debug
    void executer::printMemory(){}
    void executer::debug(bool onOff){ debugMode = onOff; }