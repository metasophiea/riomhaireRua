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
        setUp();
    }
visualDisplay::~visualDisplay(){}

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
        glfwInit();
        window = glfwCreateWindow(windowWidth, windowHeight, "Rua - 16x16 Visual Port", NULL, NULL);
        glfwMakeContextCurrent(window);
        glfwSwapInterval(0);
    }
    void visualDisplay::render(){
        std::string temp;
        for(unsigned int y = 0; y < pixelCountY; y++){
            for(unsigned int x = 0; x < pixelCountX; x++){
                glBegin(GL_QUADS);
                temp = pixelArray[x + y*16];
                glColor3f( eightBitColour_extractRed(temp),eightBitColour_extractGreen(temp),eightBitColour_extractBlue(temp) ); 
                glVertex3f(    -1            + pixelWidth*x ,  1             - pixelHeight*y , 0.0f);
                glVertex3f(    -1+pixelWidth + pixelWidth*x ,  1             - pixelHeight*y , 0.0f);
                glVertex3f(    -1+pixelWidth + pixelWidth*x ,  1-pixelHeight - pixelHeight*y , 0.0f);
                glVertex3f(    -1            + pixelWidth*x ,  1-pixelHeight - pixelHeight*y , 0.0f);
                glEnd();
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void visualDisplay::shutDown(){
        glfwTerminate();
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