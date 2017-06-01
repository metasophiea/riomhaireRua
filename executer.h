#ifndef _INCL_GUARD_HEX_UINT_executer
#define _INCL_GUARD_HEX_UINT_executer

#include "logicUnit.h"
#include "accessManager.h"

class executer{
    private:
        logicUnit logicUnit;
        accessManager memory;

        unsigned int programCounter;
        virtual void update();

    public:
        executer(unsigned int bitCount, unsigned int memorySize);
        virtual ~executer();

        virtual void runCommand(std::string command);
        // clear  f   | 0nnxx
        // flip   f   | 1nnxx
        // inc    f   | 2nnxx
        // lShift f   | 3nnxx
        // copy   f f | 4nnnn
        // nand   f f | 5nnnn
        // add    f f | 6nnnn

        virtual void printMemory();

};

#endif