#ifndef _INCL_GUARD_HEX_UINT_visualDisplay
#define _INCL_GUARD_HEX_UINT_visualDisplay

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <iostream>
#include "bareMetal.h"

typedef boost::interprocess::allocator<float, boost::interprocess::managed_shared_memory::segment_manager>  ShmemAllocator;
typedef boost::interprocess::vector   <float, ShmemAllocator> PixelVector;

//pixel memory:
    #define pixelMemorySize 65535
    #define visualDisplay_sharedMemorySpaceName "visualDisplay_memorySpace"
    //object names
        #define visualDisplay_pixelMemory  "pixels"
        #define visualDisplay_control      "control"     
        #define visualDisplay_pixelHeight  "pixelHeight" 
        #define visualDisplay_pixelWidth   "pixelWidth"  
        #define visualDisplay_windowHeight "windowHeight"
        #define visualDisplay_windowWidth  "windowWidth" 
        #define visualDisplay_pixelCountY  "pixelCountY" 
        #define visualDisplay_pixelCountX  "pixelCountX" 

class visualDisplay: public bareMetal
{
    private:
        static PixelVector *pixels; //shared pixel memory
            //vector of floats, three times larger than the number of pixels
            //each number represents a colour value, with a batch of three for
            //each pixel; RGBRGBRGBRGBRGB, etc.
        static unsigned int *control; //shared control memory
            //unsigned int for communicating status and commands
            // 0 : all is good
            // 1 : shut down your side of the system
        static float *pixelHeight, *pixelWidth;
        static unsigned int *windowHeight, *windowWidth;
        static unsigned int *pixelCountY, *pixelCountX;
        std::string selectedPixel;

    public:
        visualDisplay(unsigned int bitCount, unsigned int pixelCountX, unsigned int pixelCountY, unsigned int windowWidth, unsigned int windowHeight);
        virtual ~visualDisplay();

        virtual void setAddressByte(std::string value);
        virtual void setAddressBit(unsigned int bit, bool value);
        virtual void setPixelByte(std::string value);
        virtual void setPixelBit(unsigned int bit,  bool value);

        virtual std::string getAddressByte();
        virtual bool getAddressBit(unsigned int bit);
        virtual std::string getPixelByte();    
        virtual bool getPixelBit(unsigned int bit);    

        virtual void display();

    //graphical functions
    public:
        virtual void start();
        virtual void stop();
    private:
        virtual std::string produceEightBitColourBin(float R, float G, float B);
        virtual float eightBitColour_extractRed(std::string colourHEX);
        virtual float eightBitColour_extractGreen(std::string colourHEX);
        virtual float eightBitColour_extractBlue(std::string colourHEX);

};

#endif