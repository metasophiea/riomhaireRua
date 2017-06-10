#ifndef _INCL_GUARD_HEX_UINT_visualDisplay
#define _INCL_GUARD_HEX_UINT_visualDisplay
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>

#include "bareMetal.h"

class visualDisplay: public bareMetal
{
    private:
        unsigned int pixelCountX, pixelCountY, windowWidth, windowHeight;
        float pixelWidth, pixelHeight;
        std::vector<std::string> pixelArray;
        std::string selectedPixel;
        GLFWwindow* window;

    public:
        visualDisplay(unsigned int bitCount, unsigned int pixelCountX, unsigned int pixelCountY, unsigned int windowWidth, unsigned int windowHeight);
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

    //graphical functions
    public:
        virtual void setUp();
        virtual void shutDown();
    private:
        virtual void render();
        virtual float eightBitColour_extractRed(std::string colourHEX);
        virtual float eightBitColour_extractGreen(std::string colourHEX);
        virtual float eightBitColour_extractBlue(std::string colourHEX);

};

#endif