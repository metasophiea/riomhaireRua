#ifndef _INCL_GUARD_HEX_UINT_programManager
#define _INCL_GUARD_HEX_UINT_programManager

#include "executer.h"

class programManager
{
    private:
        bool debugMode;
        unsigned int programLength;
        unsigned int programCounterByteCount;
        unsigned int maxProgramLength;
        std::string* program;
        executer executer;

    public:
        //construction/destruction
            programManager(unsigned int bitSize, unsigned int worktopSize, unsigned int programCounterByteCount);
            virtual ~programManager();

        //program manipulation
            virtual void clearProgram();
            virtual void load(std::string program[], unsigned int programLength);
            virtual void appendInstruction(std::string command);
            virtual void run();

        //printers and debug
            virtual void printProgram();
            virtual void printMemory();
            virtual void debug(bool onOff);

};

#endif