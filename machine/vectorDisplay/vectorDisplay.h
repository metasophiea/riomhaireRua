#ifndef _INCL_GUARD_HEX_UINT_vectorDisplay
#define _INCL_GUARD_HEX_UINT_vectorDisplay

#include <iostream>
#include <vector>
#include <math.h>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include "metal.h"

typedef boost::interprocess::allocator<unsigned int, boost::interprocess::managed_shared_memory::segment_manager> vectorDisplay_ShmemAllocator;
typedef boost::interprocess::vector   <unsigned int, vectorDisplay_ShmemAllocator> DataVector;

//shared vector memory:
    #define vectorMemorySize 65536
    #define vectorDisplay_sharedMemorySpaceName "vectorDisplay_memorySpace"
    //object names
        #define vectorDisplay_vectorMemory "vectorDisplay_data"
        #define vectorDisplay_control      "vectorDisplay_control"
        #define vectorDisplay_windowHeight "vectorDisplay_windowHeight"
        #define vectorDisplay_windowWidth  "vectorDisplay_windowWidth"

class vectorDisplay: public metal
{
    //flags
    public:
        bool isStarted;
    //inner components
    private:
        bool debugMode;
        static DataVector *dataMemory; //shared vector memory
            //vector of unsigned int data. graphical language commands are written here
        static unsigned int *control; //shared control memory
            //unsigned int for communicating status and commands
            // 0 : waiting on displayUnit to say all is good
            // 1 : all is good
            // 2 : shut down your side of the system
        static unsigned int *windowHeight, *windowWidth;
        unsigned int selectedByte;
        std::vector<unsigned int> selectedByte_vector;

    //construction/destruction
    public:
        vectorDisplay(unsigned int bitSize, unsigned int dataVector_size, unsigned int windowWidth, unsigned int windowHeight);
        virtual ~vectorDisplay();

    // readers and writers
    public:
        //address
            virtual void         setAddressByte(unsigned int byte, unsigned int value);
            virtual unsigned int getAddressByte(unsigned int byte);
            virtual void         setAddressBit(unsigned int byte, unsigned int bit, bool value);
            virtual bool         getAddressBit(unsigned int byte, unsigned int bit);
        //pixel
            virtual void         setMemoryByte(unsigned int value);
            virtual unsigned int getMemoryByte();
            virtual void         setMemoryBit(unsigned int bit, bool value);
            virtual bool         getMemoryBit(unsigned int bit);

    //display unit functions
    public:
        virtual void start();
        virtual void stop();

    //printers and debug
    public:
        virtual void printMemory();
        virtual void debug(bool onOff);
        virtual void debug(bool onOff, unsigned int depth);

};

#endif