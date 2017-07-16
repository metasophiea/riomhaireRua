#ifndef _INCL_GUARD_HEX_UINT_accessManager
#define _INCL_GUARD_HEX_UINT_accessManager

#include "metal.h"
#include "memoryBlock.h"
#include "console.h"
#include "pixelDisplay.h"
#include "vectorDisplay.h"

class accessManager: public metal
{
    //inner components
    private:
        bool debugMode;
        memoryBlock worktopBase;
        console console;
        pixelDisplay pixelDisplay;
        vectorDisplay vectorDisplay;

    //ports
        /* 0: program counter high byte           */
        /* 1: program counter low byte            */
        /* x: program counter buffer high byte    */     
        /* x: program counter buffer low byte     */
        /* x: indirect access                     */
        /* x: indirect address                    */
        /* 2: console                             */ private: static const unsigned int console_port = 2;
        /* 3: pixelDisplay pixel byte access      */ private: static const unsigned int pixelDisplay_AccessPort = 3;
        /* 4: pixelDisplay address Y              */ private: static const unsigned int pixelDisplay_AddressPort_y = 4;
        /* 5: pixelDisplay address X              */ private: static const unsigned int pixelDisplay_AddressPort_x = 5;
        /* 6: vectorDisplay memory byte access    */ private: static const unsigned int vectorDisplay_AccessPort = 6;
        /* 7: vectorDisplay memory byte address   */ private: static const unsigned int vectorDisplay_AddressPort = 7;

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