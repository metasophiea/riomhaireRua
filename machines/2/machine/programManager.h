#ifndef _INCL_GUARD_HEX_UINT_programManager
#define _INCL_GUARD_HEX_UINT_programManager

#include "executer.h"

class programManager
{
    private:
        executer executer;
        std::string* program;
        unsigned int programLength;
        unsigned int maxProgramLength;

    public:
        programManager(unsigned int bitCount, unsigned int memorySize, unsigned int maxProgramLength);
        virtual ~programManager();

        virtual void load(std::string program[], unsigned int programLength);
        virtual void appendCommand(std::string command);
        virtual void run();
        virtual void stop();
        virtual void printMemory();

};

#endif