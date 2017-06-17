#include "visualDisplay.h"
//constructors and destructors
    visualDisplay::visualDisplay(unsigned int bitCount, unsigned int pixelCountX, unsigned int pixelCountY, unsigned int windowWidth, unsigned int windowHeight):
        bareMetal(bitCount)
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
            this->selectedPixel = "0";

            start();
        }
    visualDisplay::~visualDisplay(){
        stop();
    }

//shared memory setup
    struct shm_remove{
        shm_remove() { boost::interprocess::shared_memory_object::remove(visualDisplay_sharedMemorySpaceName); }
        ~shm_remove(){ boost::interprocess::shared_memory_object::remove(visualDisplay_sharedMemorySpaceName); }
    } remover;
    boost::interprocess::managed_shared_memory segment(boost::interprocess::create_only, visualDisplay_sharedMemorySpaceName, pixelMemorySize);
    ShmemAllocator alloc_inst(segment.get_segment_manager());
    //now the objects
        PixelVector  *visualDisplay::pixels       = segment.construct<PixelVector> (visualDisplay_pixelMemory )(alloc_inst);
        unsigned int *visualDisplay::control      = segment.construct<unsigned int>(visualDisplay_control     )(0);
        float        *visualDisplay::pixelHeight  = segment.construct<float>       (visualDisplay_pixelHeight )(0);
        float        *visualDisplay::pixelWidth   = segment.construct<float>       (visualDisplay_pixelWidth  )(0);
        unsigned int *visualDisplay::windowHeight = segment.construct<unsigned int>(visualDisplay_windowHeight)(0);
        unsigned int *visualDisplay::windowWidth  = segment.construct<unsigned int>(visualDisplay_windowWidth )(0);
        unsigned int *visualDisplay::pixelCountY  = segment.construct<unsigned int>(visualDisplay_pixelCountY )(0);
        unsigned int *visualDisplay::pixelCountX  = segment.construct<unsigned int>(visualDisplay_pixelCountX )(0);

//setters
    void visualDisplay::setAddressByte(std::string value, unsigned int byteNumber){ 
        std::string output = "";
        for(unsigned int a = 0; a <= selectedPixel.length(); a++){
            if( a/(getBitCount()/4) == byteNumber ){
                for(unsigned int b = 0; b < value.length(); b++){ output = value[ value.length()-1-b ] + output; }
                a += (getBitCount()/4) -1;
            }
            else if( a == selectedPixel.length() ){}
            else{ output = selectedPixel[ selectedPixel.length()-1-a ] + output; }
        }

        selectedPixel = output;
    }
    void visualDisplay::setAddressBit(unsigned int bit, bool value, unsigned int byteNumber){
        std::string temp = HEXtoBIN(getAddressByte(byteNumber));
        if(value){ temp[ temp.length()-1-bit ] = '1'; }else{ temp[ temp.length()-1-bit ] = '0'; }
        setAddressByte(BINtoHEX(temp)); 
    }
    void visualDisplay::setPixelByte(std::string value){
        unsigned int pixelNumberByThree = HEXtoUINT(selectedPixel)*3;
        try{
            pixels->at( pixelNumberByThree+0 ) = eightBitColour_extractRed(value);
            pixels->at( pixelNumberByThree+1 ) = eightBitColour_extractGreen(value);
            pixels->at( pixelNumberByThree+2 ) = eightBitColour_extractBlue(value);
        }catch(std::out_of_range e){ /*std::cout << "visual display error - attempting to reach non-existant pixel: " << selectedPixel << std::endl;*/ }
    }
    void visualDisplay::setPixelBit(unsigned int bit, bool value){
        unsigned int pixelNumberByThree = HEXtoUINT(selectedPixel)*3;
        std::string temp = produceEightBitColourBin( pixels->at( pixelNumberByThree+0 ),pixels->at( pixelNumberByThree+1 ),pixels->at( pixelNumberByThree+2 ) );
        if(value){ temp[ temp.length()-1-bit ] = '1'; }else{ temp[ temp.length()-1-bit ] = '0'; }
        setPixelByte(BINtoHEX(temp));
    }

//getters
    std::string visualDisplay::getAddressByte(unsigned int byteNumber){ 
        unsigned int count = 0; std::string temp = "";
        
        for(int a = selectedPixel.length()-1; a >= 0; a--){
            temp = selectedPixel[a] + temp;
            if(temp.length() == (getBitCount()/4)){
                if(count == byteNumber){break;}
                temp = ""; count++;
            }
        }

        for(unsigned int a = temp.length(); a < (getBitCount()/4); a++){ temp = "0" + temp; }
        return temp;
    }
    bool visualDisplay::getAddressBit(unsigned int bit, unsigned int byteNumber){ 
        std::string temp = HEXtoBIN(getAddressByte(byteNumber));
        if( temp[ temp.length()-1-bit ] == '1' ){ return true; }else{ return false; } 
    }
    std::string visualDisplay::getPixelByte(){
        unsigned int pixelNumberByThree = HEXtoUINT(selectedPixel)*3;
        return BINtoHEX(produceEightBitColourBin( pixels->at( pixelNumberByThree+0 ),pixels->at( pixelNumberByThree+1 ),pixels->at( pixelNumberByThree+2 ) ));
    }
    bool visualDisplay::getPixelBit(unsigned int bit){
        unsigned int pixelNumberByThree = HEXtoUINT(selectedPixel)*3;
        return produceEightBitColourBin( pixels->at( pixelNumberByThree+0 ),pixels->at( pixelNumberByThree+1 ),pixels->at( pixelNumberByThree+2 ) )[bit];
    }

//pixel memory display funcsion
    void visualDisplay::display(){
        //divider
        for(unsigned int b = 0; b < *pixelCountX; b++){ std::cout << "--"; if( b < *pixelCountX-1 ){ std::cout << "-"; } }std::cout << std::endl;

        //print memory
        unsigned int pixelNumber;
        for(unsigned int a = 0; a < (*pixelCountY)*(*pixelCountX); a+=(*pixelCountX)){
            for(unsigned int b = 0; b < *pixelCountX; b++){
                pixelNumber = 3*(a+b);
                std::cout << BINtoHEX(produceEightBitColourBin( pixels->at( pixelNumber+0 ),pixels->at( pixelNumber+1 ),pixels->at( pixelNumber+2 ) )) << " ";
            }
            std::cout << std::endl;
        }
    }

    //display control
        void visualDisplay::start(){
            pid_t pid = fork();
            if(pid == 0){ /* new process to be replaced */ execl("displayUnit", "", 0, 0); }
            else if(pid != 0){ /* this is the original process */ }
            else{ std::cout << "display unit forking failure" << std::endl; *control = 2;}

            while( *control == 0 ){/*waiting on display unit to start*/}
        }
        void visualDisplay::stop(){
            *control = 2;
        }

//conversion functions
    std::string visualDisplay::produceEightBitColourBin(float R, float G, float B){
        std::string bin = localSizeBIN(HEXtoBIN("0"));

        if( (R - 0.571428571428571) >= 0 ){ R -= 0.571428571428571; bin[0] = '1'; }
        if( (R - 0.285714285714286) >= 0 ){ R -= 0.285714285714286; bin[1] = '1'; }
        if( (R - 0.142857142857143) >= 0 ){ R -= 0.142857142857143; bin[2] = '1'; }

        if( (G - 0.571428571428571) >= 0 ){ G -= 0.571428571428571; bin[3] = '1'; }
        if( (G - 0.285714285714286) >= 0 ){ G -= 0.285714285714286; bin[4] = '1'; }
        if( (G - 0.142857142857143) >= 0 ){ G -= 0.142857142857143; bin[5] = '1'; }

        if( (B - 0.666666666666667) >= 0 ){ B -= 0.666666666666667; bin[6] = '1'; }
        if( (B - 0.333333333333333) >= 0 ){ B -= 0.333333333333333; bin[7] = '1'; }

        return bin;
    }
    float visualDisplay::eightBitColour_extractRed(std::string colourHEX){
        std::string bin = localSizeBIN(HEXtoBIN(colourHEX));
        float output = 0;
        if(bin[0] == '1'){ output += 0.571428571428571; /* += 4/7 */ }
        if(bin[1] == '1'){ output += 0.285714285714286; /* += 2/7 */ }
        if(bin[2] == '1'){ output += 0.142857142857143; /* += 1/7 */ }
        return output;
    }
    float visualDisplay::eightBitColour_extractGreen(std::string colourHEX){
        std::string bin = localSizeBIN(HEXtoBIN(colourHEX));
        float output = 0;
        if(bin[3] == '1'){ output += 0.571428571428571; /* += 4/7 */ }
        if(bin[4] == '1'){ output += 0.285714285714286; /* += 2/7 */ }
        if(bin[5] == '1'){ output += 0.142857142857143; /* += 1/7 */ }
        return output;
    }
    float visualDisplay::eightBitColour_extractBlue(std::string colourHEX){
        std::string bin = localSizeBIN(HEXtoBIN(colourHEX));
        float output = 0;
        if(bin[6] == '1'){ output += 0.666666666666667; /* += 2/3 */ }
        if(bin[7] == '1'){ output += 0.333333333333333; /* += 1/3 */ }
        return output;
    }