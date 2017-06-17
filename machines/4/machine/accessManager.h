#ifndef _INCL_GUARD_HEX_UINT_accessManager
#define _INCL_GUARD_HEX_UINT_accessManager

#include "metal.h"

class accessManager: public metal
{
    private:
        bool debugMode;
        //memoryBlock memoryBlock;
        //consoleAccess console; static const unsigned int console_port = 3;
        //visualDisplay visual; static const unsigned int visual_PixelPort = 4, visual_AddressPort_y = 5, visual_AddressPort_x = 6;

    //construction/destruction
        public: accessManager(unsigned int bitSize, unsigned int worktopSize);
        public: virtual ~accessManager();

    //getters and setters
        public: virtual bool getBit(unsigned int byte, unsigned int bit);
        public: virtual void setBit(unsigned int byte, unsigned int bit, bool value);
        public: virtual unsigned int getByte(unsigned int byte);
        public: virtual void setByte(unsigned int byte, unsigned int value);

    //printers and debug
        public: virtual void printMemory();
        public: virtual void debug(bool onOff);

};

#endif