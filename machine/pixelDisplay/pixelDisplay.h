#ifndef _INCL_GUARD_HEX_UINT_pixelDisplay
#define _INCL_GUARD_HEX_UINT_pixelDisplay

#include <iostream>
#include <vector>
#include <math.h>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include "metal.h"

typedef boost::interprocess::allocator<float, boost::interprocess::managed_shared_memory::segment_manager> pixelDisplay_ShmemAllocator;
typedef boost::interprocess::vector   <float, pixelDisplay_ShmemAllocator> PixelVector;

//shared pixel memory:
    #define pixelMemorySize 16777215
    #define pixelDisplay_sharedMemorySpaceName "pixelDisplay_memorySpace"
    //object names
        #define pixelDisplay_pixelMemory  "pixelDisplay_pixels"
        #define pixelDisplay_control      "pixelDisplay_control"     
        #define pixelDisplay_pixelHeight  "pixelDisplay_pixelHeight" 
        #define pixelDisplay_pixelWidth   "pixelDisplay_pixelWidth"  
        #define pixelDisplay_windowHeight "pixelDisplay_windowHeight"
        #define pixelDisplay_windowWidth  "pixelDisplay_windowWidth" 
        #define pixelDisplay_pixelCountY  "pixelDisplay_pixelCountY" 
        #define pixelDisplay_pixelCountX  "pixelDisplay_pixelCountX" 

class pixelDisplay: public metal
{
    //flags
    public:
        bool isStarted;    
    //inner components
    private:
        bool debugMode;
        static PixelVector *pixels; //shared pixel memory
            //vector of floats, three times larger than the number of pixels
            //each number represents a colour value, with a batch of three for
            //each pixel; RGBRGBRGBRGBRGB, etc.
        static unsigned int *control; //shared control memory
            //unsigned int for communicating status and commands
            // 0 : waiting on displayUnit to say all is good
            // 1 : all is good
            // 2 : shut down your side of the system
        static float *pixelHeight, *pixelWidth;
        static unsigned int *windowHeight, *windowWidth;
        static unsigned int *pixelCountY, *pixelCountX;
        unsigned int selectedPixel;
        std::vector<unsigned int> selectedPixel_vector;

    //construction/destruction
    public:
        pixelDisplay(unsigned int bitSize, unsigned int selectedPixel_byteCount, unsigned int pixelCountX, unsigned int pixelCountY, unsigned int windowWidth, unsigned int windowHeight);
        virtual ~pixelDisplay();

    //readers and writers
    public:
        //address
            virtual void         setAddressByte(unsigned int byte, unsigned int value);
            virtual unsigned int getAddressByte(unsigned int byte);
            virtual void         setAddressBit(unsigned int byte, unsigned int bit, bool value);
            virtual bool         getAddressBit(unsigned int byte, unsigned int bit);
        //pixel
            virtual void         setPixelByte(unsigned int value);
            virtual unsigned int getPixelByte();
            virtual void         setPixelBit(unsigned int bit, bool value);
            virtual bool         getPixelBit(unsigned int bit);

    //display unit functions
    public:
        virtual void start();
        virtual void stop();
    private:
        virtual unsigned int produceEightBitColourBin(float R, float G, float B);
        virtual float eightBitColour_extractRed  (unsigned int colourUINT);
        virtual float eightBitColour_extractGreen(unsigned int colourUINT);
        virtual float eightBitColour_extractBlue (unsigned int colourUINT);

    //printers and debug
    public:
        virtual void printMemory();
        virtual void debug(bool onOff);
        virtual void debug(bool onOff, unsigned int depth);

};

#endif