#include "pixelDisplay.h"

//construction/destruction
    pixelDisplay::pixelDisplay(unsigned int bitSize, unsigned int selectedPixel_byteCount, unsigned int pixelCountX, unsigned int pixelCountY, unsigned int windowWidth, unsigned int windowHeight):
        metal(bitSize),
        selectedPixel(0),
        selectedPixel_vector( std::vector<unsigned int>() ),
        debugMode(false),isStarted(false)
        {
            //populate shared pixel vector
                for(unsigned int a = 0; a < 3*pixelCountX*pixelCountY; a++){ this->pixels->push_back(0); }

            *this->control      = 0; 
            *this->pixelCountY  = pixelCountY; 
            *this->pixelCountX  = pixelCountX; 
            *this->windowHeight = windowHeight; 
            *this->windowWidth  = windowWidth; 
            *this->pixelHeight  = 2*(((float)windowHeight/(float)pixelCountY)/(float)windowHeight);
            *this->pixelWidth   = 2*(((float)windowWidth/(float)pixelCountX)/(float)windowWidth);

            //setup address access values
                for(unsigned int a = 0; a < selectedPixel_byteCount; a++){ selectedPixel_vector.push_back(0); }

        }
    pixelDisplay::~pixelDisplay(){
        stop();
    }

//shared memory setup
    struct pixelMemory_shm_remove{
        pixelMemory_shm_remove() { boost::interprocess::shared_memory_object::remove(pixelDisplay_sharedMemorySpaceName); }
        ~pixelMemory_shm_remove(){ boost::interprocess::shared_memory_object::remove(pixelDisplay_sharedMemorySpaceName); }
    } pixelMemory_remover;
    boost::interprocess::managed_shared_memory pixelMemory_segment(boost::interprocess::create_only, pixelDisplay_sharedMemorySpaceName, pixelMemorySize);
    pixelDisplay_ShmemAllocator pixelMemory_alloc_inst(pixelMemory_segment.get_segment_manager());
    //now the objects
         PixelVector  *pixelDisplay::pixels       = pixelMemory_segment.construct<PixelVector> (pixelDisplay_pixelMemory )(pixelMemory_alloc_inst);
         unsigned int *pixelDisplay::control      = pixelMemory_segment.construct<unsigned int>(pixelDisplay_control     )(0);
         float        *pixelDisplay::pixelHeight  = pixelMemory_segment.construct<float>       (pixelDisplay_pixelHeight )(0);
         float        *pixelDisplay::pixelWidth   = pixelMemory_segment.construct<float>       (pixelDisplay_pixelWidth  )(0);
         unsigned int *pixelDisplay::windowHeight = pixelMemory_segment.construct<unsigned int>(pixelDisplay_windowHeight)(0);
         unsigned int *pixelDisplay::windowWidth  = pixelMemory_segment.construct<unsigned int>(pixelDisplay_windowWidth )(0);
         unsigned int *pixelDisplay::pixelCountY  = pixelMemory_segment.construct<unsigned int>(pixelDisplay_pixelCountY )(0);
         unsigned int *pixelDisplay::pixelCountX  = pixelMemory_segment.construct<unsigned int>(pixelDisplay_pixelCountX )(0);

//readers and writers
     //address
        void pixelDisplay::setAddressByte(unsigned int byte, unsigned int value){
            if(debugMode){ std::cout << "pixelDisplay::setAddressByte("<<byte<<","<<value<<")"<< std::endl; }
            //input checking
                if( byte > selectedPixel_vector.size() ){ std::cout << "pixelDisplay::setAddressByte - error: selected address byte out of range: " << byte << std::endl; return;}
                if( value > getMaxPossibleValue(0) ){ std::cout << "pixelDisplay::setAddressByte - error: value out of range: " << value << std::endl; return;}

            //add value to selectedPixel_vector
                selectedPixel_vector[ byte ] = value;
            //consolidate vector into the selectedPixel unsigned int
                selectedPixel = 0; for(unsigned int a = 0; a < selectedPixel_vector.size(); a++){ selectedPixel += pow(2,getBitSize()*a)*selectedPixel_vector[a]; }

            if(debugMode){ 
                std::cout << "pixelDisplay::setAddressByte - new selectedPixel_vector:" << std::endl;
                for(unsigned int a = 0; a < selectedPixel_vector.size(); a++){ std::cout << a << " | " << selectedPixel_vector[a] << std::endl; }
                std::cout << "pixelDisplay::setAddressByte - new selectedPixel: " << selectedPixel << std::endl;
            }
        }
        unsigned int pixelDisplay::getAddressByte(unsigned int byte){
            if(debugMode){ 
                std::cout << "pixelDisplay::getAddressByte("<<byte<<")"<< std::endl;
                std::cout << "pixelDisplay::getAddressByte - selectedPixel_vector:" << std::endl;
                for(unsigned int a = 0; a < selectedPixel_vector.size(); a++){ std::cout << a << " | " << selectedPixel_vector[a] << std::endl; }
            }
            //input checking
                if( byte > selectedPixel_vector.size() ){ std::cout << "pixelDisplay::getAddressByte - error: selected address byte out of range: " << byte << std::endl; return 0;}
                if(debugMode){ std::cout << "pixelDisplay::getAddressByte - gathered value: " << selectedPixel_vector[ byte ] << std::endl; }

            //reverse gather this value
            return selectedPixel_vector[ byte ];
        }
        void pixelDisplay::setAddressBit(unsigned int byte, unsigned int bit, bool value){
            if(debugMode){ std::cout << "pixelDisplay::setAddressBit("<<byte<<","<<bit<<","<<value<<")"<< std::endl; }
            //input checking
                if( bit >= getBitSize() ){ std::cout << "pixelDisplay::setAddressBit - error: selected bit out of range: " << bit << std::endl; return;}

            //get byte, convert to bin, set the bit, convert back and set that byte to this new value
                setAddressByte(byte,bitAdjustUINT_systemSize(getAddressByte(byte),bit,value));
        }

        bool pixelDisplay::getAddressBit(unsigned int byte, unsigned int bit){
            if(debugMode){ std::cout << "pixelDisplay::getAddressBit("<<byte<<","<<bit<<")"<< std::endl; }
            //input checking
                if( bit > getBitSize() ){ std::cout << "pixelDisplay::setAddressBit - error: selected bit out of range: " << bit << std::endl; return false;}

            //get address byte, then extract the bit and return it
            return UINTtoBIN_systemSize(getAddressByte(byte))[bit] == '1' ? true : false;
        }
    //pixel
        void pixelDisplay::setPixelByte(unsigned int value){start();
            if(debugMode){ std::cout << "pixelDisplay::setPixelByte("<<value<<")"<< std::endl; }
            //input checking
                if( value > getMaxPossibleValue(0) ){ std::cout << "pixelDisplay::setPixelByte - error: value out of range: " << value << std::endl; }

            //multiply the selectedPixel by 3 to approach the red component of the pixel wanted in the vector
                unsigned int pixelNumberByThree = selectedPixel*3;
                if(debugMode){ std::cout << "pixelDisplay::setPixelByte - setting pixel: " << selectedPixel << " red component at: " << pixelNumberByThree << std::endl; }
            //get colour values from the value and set the pixel colours
                try{
                    pixels->at( pixelNumberByThree+0 ) = eightBitColour_extractRed(value);   if(debugMode){ std::cout << "pixelDisplay::setPixelByte - eightBitColour_extractRed: "   << eightBitColour_extractRed(value) << std::endl; }
                    pixels->at( pixelNumberByThree+1 ) = eightBitColour_extractGreen(value); if(debugMode){ std::cout << "pixelDisplay::setPixelByte - eightBitColour_extractGreen: " << eightBitColour_extractGreen(value) << std::endl; }
                    pixels->at( pixelNumberByThree+2 ) = eightBitColour_extractBlue(value);  if(debugMode){ std::cout << "pixelDisplay::setPixelByte - eightBitColour_extractBlue: "  << eightBitColour_extractBlue(value) << std::endl; }
                }catch(std::out_of_range e){ std::cout << "pixelDisplay::setPixelByte - error - attempting to reach non-existant pixel: " << selectedPixel << std::endl; return;}
        }
        unsigned int pixelDisplay::getPixelByte(){
            if(debugMode){ std::cout << "pixelDisplay::getPixelByte()"<< std::endl; }

            //multiply the selectedPixel by 3 to approach the red component of the pixel wanted in the vector
                unsigned int pixelNumberByThree = selectedPixel*3;
                if(debugMode){ std::cout << "pixelDisplay::getPixelByte - setting pixel: " << selectedPixel << " red component at: " << pixelNumberByThree << std::endl;
                               std::cout << "pixelDisplay::getPixelByte - eightBitColour_extractRed: "   << pixels->at( pixelNumberByThree+0 ) << std::endl;
                               std::cout << "pixelDisplay::getPixelByte - eightBitColour_extractGreen: " << pixels->at( pixelNumberByThree+1 ) << std::endl;
                               std::cout << "pixelDisplay::getPixelByte - eightBitColour_extractBlue: "  << pixels->at( pixelNumberByThree+2 ) << std::endl; }
            //gather the colours and convert them to a single unsigned int
                return produceEightBitColourBin( pixels->at( pixelNumberByThree+0 ),pixels->at( pixelNumberByThree+1 ),pixels->at( pixelNumberByThree+2 ) );
        }
        void pixelDisplay::setPixelBit(unsigned int bit, bool value){
            if(debugMode){ std::cout << "pixelDisplay::setPixelBit("<<bit<<","<<value<<")"<< std::endl; }
            //input checking
                if( bit > getBitSize() ){ std::cout << "pixelDisplay::setPixelBit - error: selected bit out of range: " << bit << std::endl; return;}

            //get byte, convert to bin, set the bit, convert back and set the byte to this new value
                setPixelByte(bitAdjustUINT_systemSize(getPixelByte(),bit,value));
        }
        bool pixelDisplay::getPixelBit(unsigned int bit){
            if(debugMode){ std::cout << "pixelDisplay::getPixelBit("<<bit<<")"<< std::endl; }
            //input checking
                if( bit > getBitSize() ){ std::cout << "pixelDisplay::getPixelBit - error: selected bit out of range: " << bit << std::endl; return false;}

            //get address byte, then extract the bit and return it
                return UINTtoBIN_systemSize(getPixelByte())[bit] == '1' ? true : false;
        }

//display unit functions
    void pixelDisplay::start(){
        if(debugMode){ std::cout << "pixelDisplay::start - attempting to start the external pixel display module"<< std::endl; }
        if(isStarted){ if(debugMode){ std::cout << "pixelDisplay::start - display module already running; aborting start-up"<< std::endl;} return;}else{isStarted = true;}
        if(debugMode){ std::cout << "pixelDisplay::start - starting external pixel display module"<< std::endl; }

        //fork process and start external pixel display module
            pid_t pid = fork();
            if(pid == 0){ /* new process to be replaced */ execl("externalPixelDisplayModule", "", 0, 0); }
            else if(pid != 0){ /* this is the original process */ }
            else{ std::cout << "pixelDisplay::start - external pixel display module forking failure" << std::endl; *control = 2;}

        //wait for external pixel display module to respond
            if(debugMode){ std::cout << "pixelDisplay::start - waiting on external pixel display module to start"<< std::endl; }
            while( *control == 0 ){}
            if(debugMode){ std::cout << "pixelDisplay::start - external pixel display module has started and responded"<< std::endl; }
    }
    void pixelDisplay::stop(){
        if(debugMode){ std::cout << "pixelDisplay::stop - attempting to stop the external pixel display module"<< std::endl; }
        if(!isStarted){ if(debugMode){ std::cout << "pixelDisplay::stop - display module was never started"<< std::endl; } return;}
        if(debugMode){ std::cout << "pixelDisplay::stop - stopping external pixel display module"<< std::endl; }
        *control = 2;
    }

// private:
    unsigned int pixelDisplay::produceEightBitColourBin(float R, float G, float B){
        std::string bin = UINTtoBIN_systemSize(0);

        if( (R - 0.571428571428571) >= 0 ){ R -= 0.571428571428571; bin[0] = '1'; }
        if( (R - 0.285714285714286) >= 0 ){ R -= 0.285714285714286; bin[1] = '1'; }
        if( (R - 0.142857142857143) >= 0 ){ R -= 0.142857142857143; bin[2] = '1'; }

        if( (G - 0.571428571428571) >= 0 ){ G -= 0.571428571428571; bin[3] = '1'; }
        if( (G - 0.285714285714286) >= 0 ){ G -= 0.285714285714286; bin[4] = '1'; }
        if( (G - 0.142857142857143) >= 0 ){ G -= 0.142857142857143; bin[5] = '1'; }

        if( (B - 0.666666666666667) >= 0 ){ B -= 0.666666666666667; bin[6] = '1'; }
        if( (B - 0.333333333333333) >= 0 ){ B -= 0.333333333333333; bin[7] = '1'; }

        return BINtoUINT(bin);
    }
    float pixelDisplay::eightBitColour_extractRed(unsigned int colourUINT){
        std::string bin = UINTtoBIN_systemSize(colourUINT);
        float output = 0;
        if(bin[0] == '1'){ output += 0.571428571428571; /* += 4/7 */ }
        if(bin[1] == '1'){ output += 0.285714285714286; /* += 2/7 */ }
        if(bin[2] == '1'){ output += 0.142857142857143; /* += 1/7 */ }
        return output;
    }
    float pixelDisplay::eightBitColour_extractGreen(unsigned int colourUINT){
        std::string bin = UINTtoBIN_systemSize(colourUINT);
        float output = 0;
        if(bin[3] == '1'){ output += 0.571428571428571; /* += 4/7 */ }
        if(bin[4] == '1'){ output += 0.285714285714286; /* += 2/7 */ }
        if(bin[5] == '1'){ output += 0.142857142857143; /* += 1/7 */ }
        return output;
    }
    float pixelDisplay::eightBitColour_extractBlue (unsigned int colourUINT){
        std::string bin = UINTtoBIN_systemSize(colourUINT);
        float output = 0;
        if(bin[6] == '1'){ output += 0.666666666666667; /* += 2/3 */ }
        if(bin[7] == '1'){ output += 0.333333333333333; /* += 1/3 */ }
        return output;
    }

//printers and debug
    void pixelDisplay::printMemory(){
        for(unsigned int a = 0; a < this->pixels->size(); a+=3){
            //print data for this line
                std::cout << resize( std::to_string(produceEightBitColourBin( pixels->at( a+0 ),pixels->at( a+1 ),pixels->at( a+2 ) )),3) << " ";
            //next line
                if( (a/3 +1)%(*this->pixelCountX) == 0 ){ std::cout << std::endl; }
        }
    }
    void pixelDisplay::debug(bool onOff){ debugMode = onOff; }