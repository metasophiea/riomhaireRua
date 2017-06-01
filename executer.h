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
        virtual void update();

    public:
        executer(unsigned int bitCount, unsigned int memorySize);
        virtual ~executer();

        virtual unsigned int nextCommandNumber();
        virtual void runCommand(std::string command);

        virtual void printMemory();

};

#endif