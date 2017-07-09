#include "vectorDisplay.h"

//construction/destruction
    vectorDisplay::vectorDisplay(unsigned int bitSize, unsigned int dataVector_size, unsigned int windowWidth, unsigned int windowHeight):
        metal(bitSize),
        selectedByte(0),
        selectedByte_vector( std::vector<unsigned int>() ),
        debugMode(false),isStarted(false)
        {
            //populate data vector memory
                for(unsigned int a = 0; a < dataVector_size; a++){ this->dataMemory->push_back(0); }

            *this->control      = 0;
            *this->windowHeight = windowHeight;
            *this->windowWidth  = windowWidth;

            //calculate number of bytes required for selectedByte_byteCount based on the memory size
                unsigned int selectedByte_byteCount = ceil( (double)UINTtoHEX(dataVector_size).length()/2 );

            //setup address access values
                for(unsigned int a = 0; a < selectedByte_byteCount; a++){ selectedByte_vector.push_back(0); }

        }
    vectorDisplay::~vectorDisplay(){
        stop();
    }

//shared memory setup
    struct vectorMemory_shm_remove{
        vectorMemory_shm_remove() { boost::interprocess::shared_memory_object::remove(vectorDisplay_sharedMemorySpaceName); }
        ~vectorMemory_shm_remove(){ boost::interprocess::shared_memory_object::remove(vectorDisplay_sharedMemorySpaceName); }
    } vectorMemory_remover;
    boost::interprocess::managed_shared_memory vectorMemory_segment(boost::interprocess::create_only, vectorDisplay_sharedMemorySpaceName, vectorMemorySize);
   vectorDisplay_ShmemAllocator vectorMemory_alloc_inst(vectorMemory_segment.get_segment_manager());
    //now the objects
         DataVector   *vectorDisplay::dataMemory   = vectorMemory_segment.construct<DataVector>  (vectorDisplay_vectorMemory)(vectorMemory_alloc_inst);
         unsigned int *vectorDisplay::control      = vectorMemory_segment.construct<unsigned int>(vectorDisplay_control     )(0);
         unsigned int *vectorDisplay::windowHeight = vectorMemory_segment.construct<unsigned int>(vectorDisplay_windowHeight)(0);
         unsigned int *vectorDisplay::windowWidth  = vectorMemory_segment.construct<unsigned int>(vectorDisplay_windowWidth )(0);

//readers and writers
     //address
        void vectorDisplay::setAddressByte(unsigned int byte, unsigned int value){
            if(debugMode){ std::cout << "vectorDisplay::setAddressByte("<<byte<<","<<value<<")"<< std::endl; }
            //input checking
                if( byte > selectedByte_vector.size() ){ std::cout << "vectorDisplay::setAddressByte - error: selected address byte out of range: " << byte << std::endl; return;}
                if( value > getMaxPossibleValue(0) ){ std::cout << "vectorDisplay::setAddressByte - error: value out of range: " << value << std::endl; return;}

            //add value to selectedByte_vector
                selectedByte_vector[ byte ] = value;
            //consolidate vector into the selectedByte unsigned int
                selectedByte = 0; for(unsigned int a = 0; a < selectedByte_vector.size(); a++){ selectedByte += pow(2,getBitSize()*a)*selectedByte_vector[a]; }

            if(debugMode){ 
                std::cout << "vectorDisplay::setAddressByte - new selectedByte_vector:" << std::endl;
                for(unsigned int a = 0; a < selectedByte_vector.size(); a++){ std::cout << a << " | " << selectedByte_vector[a] << std::endl; }
                std::cout << "vectorDisplay::setAddressByte - new selectedByte: " << selectedByte << std::endl;
            }
        }
        unsigned int vectorDisplay::getAddressByte(unsigned int byte){
            if(debugMode){ 
                std::cout << "vectorDisplay::getAddressByte("<<byte<<")"<< std::endl;
                std::cout << "vectorDisplay::getAddressByte - selectedByte_vector:" << std::endl;
                for(unsigned int a = 0; a < selectedByte_vector.size(); a++){ std::cout << a << " | " << selectedByte_vector[a] << std::endl; }
            }
            //input checking
                if( byte > selectedByte_vector.size() ){ std::cout << "vectorDisplay::getAddressByte - error: selected address byte out of range: " << byte << std::endl; return 0;}
                if(debugMode){ std::cout << "vectorDisplay::getAddressByte - gathered value: " << selectedByte_vector[ byte ] << std::endl; }

            //reverse gather this value
            return selectedByte_vector[ byte ];
        }
        void vectorDisplay::setAddressBit(unsigned int byte, unsigned int bit, bool value){
            if(debugMode){ std::cout << "vectorDisplay::setAddressBit("<<byte<<","<<bit<<","<<value<<")"<< std::endl; }
            //input checking
                if( bit >= getBitSize() ){ std::cout << "vectorDisplay::setAddressBit - error: selected bit out of range: " << bit << std::endl; return;}

            //get byte, adjust and set the byte to this new value
                setAddressByte(byte,bitAdjustUINT_systemSize(getAddressByte(byte),bit,value));
        }

        bool vectorDisplay::getAddressBit(unsigned int byte, unsigned int bit){
            if(debugMode){ std::cout << "vectorDisplay::getAddressBit("<<byte<<","<<bit<<")" << std::endl; }
            //input checking
                if( bit > getBitSize() ){ std::cout << "vectorDisplay::setAddressBit - error: selected bit out of range: " << bit << std::endl; return false;}

            //get address byte, then extract the bit and return it
            if(debugMode){ std::cout << "vectorDisplay::getAddressBit - gathered byte data in binary: " << UINTtoBIN_systemSize(getAddressByte(byte)) << std::endl; }
            return UINTtoBIN_systemSize(getAddressByte(byte))[bit] == '1' ? true : false;
        }
    //byte
        void vectorDisplay::setMemoryByte(unsigned int value){start();
            if(debugMode){ std::cout << "vectorDisplay::setMemoryByte("<<value<<")"<< std::endl; }
            //input checking
                if( value > getMaxPossibleValue(0) ){ std::cout << "vectorDisplay::setMemoryByte - error: value out of range: " << value << std::endl; return;}
                if(debugMode){ std::cout << "vectorDisplay::setMemoryByte - setting byte: " << selectedByte << std::endl; }

            //get colour values from the value and set the pixel colours
                try{
                    dataMemory->at( selectedByte ) = value; if(debugMode){ std::cout << "vectorDisplay::setMemoryByte - value: " << value << std::endl; }
                }catch(std::out_of_range e){ std::cout << "vectorDisplay::setMemoryByte - error - attempting to reach non-existant byte: " << selectedByte << std::endl; return;}
        }
        unsigned int vectorDisplay::getMemoryByte(){
            if(debugMode){ std::cout << "vectorDisplay::getMemoryByte - setting pixel: " << selectedByte << std::endl;}

            //gather the colours and convert them to a single unsigned int
                return dataMemory->at( selectedByte );
        }
        void vectorDisplay::setMemoryBit(unsigned int bit, bool value){
            if(debugMode){ std::cout << "vectorDisplay::setMemoryBit("<<bit<<","<<value<<")"<< std::endl; }
            //input checking
                if( bit > getBitSize() ){ std::cout << "vectorDisplay::setMemoryBit - error: selected bit out of range: " << bit << std::endl; return;}

            //get byte, adjust and set the byte to this new value
                setMemoryByte( bitAdjustUINT_systemSize(getMemoryByte(),bit,value) );
        }
        bool vectorDisplay::getMemoryBit(unsigned int bit){
            if(debugMode){ std::cout << "vectorDisplay::getMemoryBit("<<bit<<")"<< std::endl; }
            //input checking
                if( bit > getBitSize() ){ std::cout << "vectorDisplay::getMemoryBit - error: selected bit out of range: " << bit << std::endl; return false;}

            //get address byte, then extract the bit and return it
                return UINTtoBIN_systemSize(getMemoryByte())[bit] == '1' ? true : false;
        }

//display unit functions
    void vectorDisplay::start(){
        if(debugMode){ std::cout << "vectorDisplay::start - attempting to start the external vector display module"<< std::endl; }
        if(isStarted){ if(debugMode){ std::cout << "vectorDisplay::start - display module already running; aborting start-up"<< std::endl;} return;}else{isStarted = true;}
        if(debugMode){ std::cout << "vectorDisplay::start - starting external vector display module"<< std::endl; }

        //fork process and start external pixel display module
            pid_t pid = fork();
            if(pid == 0){ /* new process to be replaced */ execl("externalVectorDisplayModule", "", 0, 0); }
            else if(pid != 0){ /* this is the original process */ }
            else{ std::cout << "vectorDisplay::start - external vector display module forking failure" << std::endl; *control = 2;}

        //wait for external pixel display module to respond
            if(debugMode){ std::cout << "vectorDisplay::start - waiting on external vector display module to start"<< std::endl; }
            while( *control == 0 ){}
            if(debugMode){ std::cout << "vectorDisplay::start - external vector display module has started and responded"<< std::endl; }
    }
    void vectorDisplay::stop(){
        if(debugMode){ std::cout << "vectorDisplay::stop - attempting to stop the external vector display module"<< std::endl; }
        if(!isStarted){ if(debugMode){ std::cout << "vectorDisplay::stop - display module was never started"<< std::endl;} return;}
        if(debugMode){ std::cout << "vectorDisplay::stop - stopping external vector display module"<< std::endl; }
        *control = 2;
    }

//printers and debug
    void vectorDisplay::printMemory(){
        unsigned int bytePerLine = 16;

        for(unsigned int a = 0; a < this->dataMemory->size(); a++){
            //write y column stuff
                if( a%bytePerLine == 0 ){ std::cout << resize(std::to_string(a),std::to_string(dataMemory->size()).length()) << "|"; }
            
            //write data
                std::cout << resize(UINTtoHEX(dataMemory->at(a)),(getBitSize()/4)) << " ";

            //next line
                if( (a+1)%bytePerLine == 0 ){ std::cout << std::endl; }
        }
        std::cout << std::endl;
    }
    void vectorDisplay::debug(bool onOff){ debugMode = onOff; }