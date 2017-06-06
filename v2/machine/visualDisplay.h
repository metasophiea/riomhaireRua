#ifndef _INCL_GUARD_HEX_UINT_visualDisplay
#define _INCL_GUARD_HEX_UINT_visualDisplay

#include "bareMetal.h"

class visualDisplay: public bareMetal
{
    private:
        unsigned int width, height;
        static std::vector<std::string>  pixelArray;
        std::string selectedPixel;

    public:
        visualDisplay(unsigned int bitCount, unsigned int width, unsigned int height);
        virtual ~visualDisplay();

        virtual void setAddressBit(unsigned int bit, bool value);
        virtual void setPixelBit(unsigned int bit,  bool value);
        virtual bool getAddressBit(unsigned int bit);
        virtual bool getPixelBit(unsigned int bit);    

        virtual void setAddressByte(std::string value);
        virtual void setPixelByte(std::string value);
        virtual std::string getAddressByte();
        virtual std::string getPixelByte();    

        virtual void display();

    //openGL functions
    public:
        static void setUp();
    private:
        static void render();

};

#endif