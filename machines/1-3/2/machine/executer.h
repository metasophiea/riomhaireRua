#ifndef _INCL_GUARD_HEX_UINT_executer
#define _INCL_GUARD_HEX_UINT_executer

#include "logicUnit.h"
#include "accessManager.h"

class executer: public bareMetal
{
    private:
        logicUnit logicUnit;
        accessManager memory;

        unsigned int programCounter;
        unsigned int LogicUnitFlagsByte;
        virtual void update();
        virtual void incrementProgramCounter();

    public:
        executer(unsigned int bitCount, unsigned int memorySize);
        virtual ~executer();

        virtual unsigned int nextCommandNumber();
        virtual void runCommand(std::string command);

        virtual void printMemory();

};

#endif