#ifndef _INCL_GUARD_HEX_UINT_console
#define _INCL_GUARD_HEX_UINT_console

#include <iostream>
#include <vector>
#include <math.h>

#include "metal.h"

class console: public metal
{
    //inner components
    private:
        bool debugMode;
        std::vector<unsigned int> buffer;
        int printingMode;

        std::vector< std::vector<unsigned int> > prePrintBuffer;
        int prePrintBuffer_stageCode;
        int prePrintBuffer_selectedCode;

    //construction/destruction
    public:
        console(unsigned int bitSize);
        virtual ~console();

    //readers and writers
        virtual bool readBit(unsigned int bit);
        virtual void writeBit(unsigned int bit, bool value);
        virtual unsigned int read();
        virtual void write(unsigned int value);

    //internal writing protocols
        private: virtual void writeToOutput(unsigned int value);
        private: virtual void standard_write(unsigned int value);
        private: virtual void prePrintBuffer_write(unsigned int value);

    //printers and debug
    public:
        virtual void printMemory();
        virtual void debug(bool onOff);
        virtual void debug(bool onOff, unsigned int depth);
};

#endif