#include "visualDisplay.h"

visualDisplay::visualDisplay(unsigned int bitCount, unsigned int pixelCountX, unsigned int pixelCountY, unsigned int windowWidth, unsigned int windowHeight):
    bareMetal(bitCount),
    pixelCountX(pixelCountX),
    pixelCountY(pixelCountY),
    windowWidth(windowWidth),
    windowHeight(windowHeight)
    {
        pixelWidth = 2*(((float)windowWidth/(float)pixelCountX)/(float)windowWidth);
        pixelHeight = 2*(((float)windowHeight/(float)pixelCountY)/(float)windowHeight);

        for(unsigned int a = 0; a < pixelCountX*pixelCountY; a++){ pixelArray.push_back(localSizeHex("0")); }
        selectedPixel = localSizeHex("0");

        for(unsigned int a = 0; a < pixelCountY*pixelCountX*3; ++a){ pixels->push_back(0); }
        setUp();
    }
visualDisplay::~visualDisplay(){}

//shared memory setup
struct shm_remove{
    shm_remove() { boost::interprocess::shared_memory_object::remove("visualDisplay_memory"); }
    ~shm_remove(){ boost::interprocess::shared_memory_object::remove("visualDisplay_memory"); }
} remover;
boost::interprocess::managed_shared_memory segment(boost::interprocess::create_only, "visualDisplay_memory", 65536);
ShmemAllocator alloc_inst (segment.get_segment_manager());
PixelVector* visualDisplay::pixels = segment.construct<PixelVector>("pixels")(alloc_inst);

void visualDisplay::setAddressBit       (unsigned int bit, bool value){ 
    std::string temp = HEXtoBIN(selectedPixel);
    if(value){ temp[bit] = '1'; }else{ temp[bit] = '0'; }
    selectedPixel = BINtoHEX(temp); 
}
void visualDisplay::setPixelBit         (unsigned int bit, bool value){ 
    std::string temp = HEXtoBIN(pixelArray[HEXtoUINT(selectedPixel)]);
    if(value){ temp[bit] = '1'; }else{ temp[bit] = '0'; }
    pixelArray[HEXtoUINT(selectedPixel)] = BINtoHEX(temp); 
    render();
}
bool visualDisplay::getAddressBit       (unsigned int bit){return HEXtoBIN(selectedPixel)[bit];}
bool visualDisplay::getPixelBit         (unsigned int bit){return HEXtoBIN(pixelArray[HEXtoUINT(selectedPixel)])[bit];}

void visualDisplay::setAddressByte          (std::string value){ selectedPixel = value;}
void visualDisplay::setPixelByte            (std::string value){ pixelArray[HEXtoUINT(selectedPixel)] = value; render(); }
std::string visualDisplay::getAddressByte   (){return selectedPixel;}
std::string visualDisplay::getPixelByte     (){return pixelArray[HEXtoUINT(selectedPixel)];}

void visualDisplay::display(){
    //x axis numbering
        for(unsigned int b = 0; b < getBitCount()/4; b++){ std::cout << " "; }
        std::cout << " | ";
        for(unsigned int a = 0; a < pixelCountX; a++){
            std::cout << localSizeHex(UINTtoHEX(a)) << " ";
        }std::cout << std::endl;

    //x axis divider
        for(unsigned int b = 0; b < getBitCount()/4; b++){ std::cout << "-"; }
        std::cout << "--";
        for(unsigned int a = 0; a < pixelCountX; a++){
            std::cout << "-";
            for(unsigned int b = 0; b < getBitCount()/4; b++){ std::cout << "-"; }
        }std::cout << std::endl;

    //y axis numbering, divider and data
        for(unsigned int a = 0; a < pixelCountY*pixelCountX; a+=16){
            std::cout << localSizeHex(UINTtoHEX(a)) << " | ";
            for(unsigned int b = 0; b < pixelCountX; b++){
                std::cout << localSizeHex(pixelArray[a+b]) << " ";
            }
            std::cout << std::endl;
        }
}

    //graphical functions
void visualDisplay::setUp(){
    pid_t pid = fork();
    if(pid == 0){ execl("pixelDisplayUnit", "", 0, 0); }
    else if(pid != 0){ /* all is well */ }
    else{ std::cout << "visual display forking failure" << std::endl; }
}
void visualDisplay::render(){
    std::string temp;
    for(unsigned int a = 0; a < pixelCountY*pixelCountX; a++){
        temp = pixelArray[a];
        pixels->at( 3*(a) +0 ) = eightBitColour_extractRed(temp);
        pixels->at( 3*(a) +1 ) = eightBitColour_extractGreen(temp);
        pixels->at( 3*(a) +2 ) = eightBitColour_extractBlue(temp);
    }
}
void visualDisplay::shutDown(){}

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