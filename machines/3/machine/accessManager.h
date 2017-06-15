#ifndef _INCL_GUARD_HEX_UINT_accessManager
#define _INCL_GUARD_HEX_UINT_accessManager

#include "bareMetal.h"
#include "memoryBlock.h"
#include "consoleAccess.h"
#include "visualDisplay.h"

class accessManager: public bareMetal
{
    private:
        memoryBlock memoryBlock;
        consoleAccess console; static const unsigned int console_port = 3;
        visualDisplay visual; static const unsigned int visual_PixelPort = 4, visual_AddressPort_y = 5, visual_AddressPort_x = 6;

    public:
        accessManager(unsigned int bitCount, unsigned int memorySize);
        virtual ~accessManager();

        virtual unsigned int size();
        virtual bool getBit(std::string byte, unsigned int bit);
        virtual bool getBit(unsigned int byte, unsigned int bit);
        virtual void setBit(std::string byte, unsigned int bit, bool value);
        virtual void setBit(unsigned int byte, unsigned int bit, bool value);
        virtual std::string getByte(std::string byte);
        virtual std::string getByte(unsigned int byte);
        virtual void clearByte(std::string byte);
        virtual void clearByte(unsigned int byte);
        virtual void setByte(std::string byte, std::string value);
        virtual void setByte(unsigned int byte, std::string value);
        virtual void setByte(unsigned int byte, unsigned int value);
        virtual void display();

};

#endif