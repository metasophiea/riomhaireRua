#ifndef _INCL_GUARD_HEX_UINT_accessManager
#define _INCL_GUARD_HEX_UINT_accessManager

#include "metal.h"
#include "memoryBlock.h"
#include "console.h"

class accessManager: public metal
{
    //inner components
    private:
        bool debugMode;
        memoryBlock worktopBase;
        console console;
        //pixelDisplay_8bit pixelDisplay_8bit;

    //ports
        /* 0: program counter high byte           */
        /* 1: program counter low byte            */
        /* 2: console                             */ private: static const unsigned int console_port = 2;
        /* 3: pixelDisplay_8bit pixel byte access */ private: static const unsigned int pixelDisplay_8bit_AccessPort = 3;
        /* 4: pixelDisplay_8bit address Y         */ private: static const unsigned int pixelDisplay_8bit_AddressPort_y = 4;
        /* 5: pixelDisplay_8bit address X         */ private: static const unsigned int pixelDisplay_8bit_AddressPort_x = 5;

    //construction/destruction
        public: accessManager(unsigned int bitSize, unsigned int worktopSize);
        public: virtual ~accessManager();

    //getters and setters
        public: virtual unsigned int getByte(unsigned int byte);
        public: virtual void setByte(unsigned int byte, unsigned int value);
        public: virtual bool getBit(unsigned int byte, unsigned int bit);
        public: virtual void setBit(unsigned int byte, unsigned int bit, bool value);

    //printers and debug
        public: virtual void printMemory();
        public: virtual void debug(bool onOff);

};

#endif