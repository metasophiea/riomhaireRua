#ifndef _INCL_GUARD_HEX_UINT_executer
#define _INCL_GUARD_HEX_UINT_executer

#include "metal.h"
#include "logicUnit.h"
#include "accessManager.h"

class executer: public metal
{
    private:
        bool debugMode;
        unsigned int programCounterByteCount;
        std::vector<unsigned int> programCounterStack;
        logicUnit logicUnit;
        accessManager accessManager;

    //construction/destruction
        public: executer(unsigned int bitSize, unsigned int worktopSize, unsigned int programCounterByteCount);
        public: virtual ~executer();

    //process controls
        public:  virtual void runInstruction(std::string instruction);
        public:  virtual unsigned int getProgramCounter();
        private: virtual void setProgramCounter(unsigned int newValue);
        public:  virtual void pushCurrentProgramPositionToStack(unsigned int newValue);
        public:  virtual void pullProgramPositionFromStack();

    //utilities
        private: virtual std::vector<std::string> splitString(std::string string, char splitChar);

    //printers and debug
        public: virtual void printMemory();
        public: virtual void debug(bool onOff);
        public: virtual void debug(bool onOff, unsigned int depth);
};

#endif