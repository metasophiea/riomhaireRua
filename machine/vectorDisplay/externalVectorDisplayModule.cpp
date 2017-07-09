#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

typedef boost::interprocess::allocator<unsigned int, boost::interprocess::managed_shared_memory::segment_manager>  ShmemAllocator;
typedef boost::interprocess::vector   <unsigned int, ShmemAllocator> DataVector;

//shared vector memory:
    #define vectorMemorySize 65536
    #define vectorDisplay_sharedMemorySpaceName "vectorDisplay_memorySpace"
    //object names
        #define vectorDisplay_vectorMemory "vectorDisplay_data"
        #define vectorDisplay_control      "vectorDisplay_control"
        #define vectorDisplay_windowHeight "vectorDisplay_windowHeight"
        #define vectorDisplay_windowWidth  "vectorDisplay_windowWidth"

unsigned int unitLength = 128;

//function declarations
    void runCommands(DataVector *pixels, unsigned int *windowHeight, unsigned int *windowWidth);
    unsigned int drawPoly(DataVector *data, unsigned int offSet);
    void drawRectangle(unsigned int RGB, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int angle, unsigned int anc_X, unsigned int anc_Y);
    void drawCircle(unsigned int RGB, unsigned int x, unsigned int y, unsigned int radius);
    
//main
    int main(){
        //attempt to collect shared memory data
        try{
            boost::interprocess::managed_shared_memory segment(boost::interprocess::open_only, vectorDisplay_sharedMemorySpaceName);

            DataVector   *dataMemory   = segment.find<DataVector>  (vectorDisplay_vectorMemory).first;
            unsigned int *control      = segment.find<unsigned int>(vectorDisplay_control     ).first;
            unsigned int *windowHeight = segment.find<unsigned int>(vectorDisplay_windowHeight).first;
            unsigned int *windowWidth  = segment.find<unsigned int>(vectorDisplay_windowWidth ).first;

            //setup window
                GLFWwindow* window;
                glfwInit();
                window = glfwCreateWindow(*windowWidth, *windowHeight, "Rua - Visual Display", NULL, NULL);
                glfwMakeContextCurrent(window);
                glfwSwapInterval(1);

            //tell pixelDisplay that all is good
                *control = 1; 

            //rendering loop
                while(!glfwWindowShouldClose(window)){
                    if(*control == 2){break;}
                    glClear(GL_COLOR_BUFFER_BIT);

                    runCommands(dataMemory,windowHeight,windowWidth);

                    glfwSwapBuffers(window);
                    glfwPollEvents();
                }

            *control = 2;
            glfwDestroyWindow(window);
            glfwTerminate();

        }catch(boost::interprocess::interprocess_exception e){ std::cout << "Boost error - could not find shared memory space" << std::endl; return 1;}

        return 0;
    }

//utility functions 
    void extractEightBitColour(unsigned int colourUINT){
        float red, green, blue = 0;

        if( colourUINT >= 128 ){ colourUINT -= 128; red += 0.571428571428571;   /* += 4/7 */}
        if( colourUINT >= 64  ){ colourUINT -= 64 ; red += 0.285714285714286;   /* += 2/7 */} 
        if( colourUINT >= 32  ){ colourUINT -= 32 ; red += 0.142857142857143;   /* += 1/7 */}

        if( colourUINT >= 16  ){ colourUINT -= 16 ; green += 0.571428571428571; /* += 4/7 */}
        if( colourUINT >= 8   ){ colourUINT -= 8  ; green += 0.285714285714286; /* += 2/7 */} 
        if( colourUINT >= 4   ){ colourUINT -= 4  ; green += 0.142857142857143; /* += 1/7 */}

        if( colourUINT >= 2   ){ colourUINT -= 2  ; blue += 0.666666666666667;  /* += 2/3 */}
        if( colourUINT >= 1   ){ colourUINT -= 1  ; blue += 0.333333333333333;  /* += 1/3 */} 

        glColor3f( red, green, blue ); 
    }
//graphical command interpreter
    void runCommands(DataVector *data, unsigned int *windowHeight, unsigned int *windowWidth){
        //std::cout << data->at(0) << std::endl;
        // std::cout << data->size() << std::endl;

        for(unsigned int a = 0; a < data->size(); a++){
            //std::cout << "  " << a << "|" << data->at(a) << std::endl;

            switch(data->at(a)){
                case 0: /* nothing */ break;
                case 1: /* poly */ a += drawPoly(data,a); break;
                case 2: /* rectangle (rotated around top left corner) */ 
                    drawRectangle(data->at(a+1),data->at(a+2),data->at(a+3),data->at(a+4),data->at(a+5),data->at(a+6),0,0);
                    a += 6;
                    break;
                case 3: /* rectangle (rotated around centre) */
                    drawRectangle(data->at(a+1),data->at(a+2),data->at(a+3),data->at(a+4),data->at(a+5),data->at(a+6),128,128); 
                    a += 6;
                    break;
                case 4: /* circle */
                    drawCircle(data->at(a+1),data->at(a+2),data->at(a+3),data->at(a+4)); 
                    a += 4;
                    break;
            }

        }
    }

//drawing functions
    unsigned int drawPoly(DataVector *data, unsigned int offSet){
        glBegin(GL_POLYGON);
        
        //extract and apply colour 
            extractEightBitColour( data->at(offSet+1) );

        //collect first point and print that manually
            glVertex3f( ( -1+ ((float)data->at(offSet+2)/unitLength)) , (  1- ((float)data->at(offSet+3)/unitLength) )  ,0.0f);

        //loop through points until a copy is found, indicating the end of the shape
        // or, if we run to the end of the memory, stop and print
        unsigned int b = offSet + 4;
            while( !(data->at(b) == data->at(offSet+2) && data->at(b+1) == data->at(offSet+3)) ){
                glVertex3f( ( -1+ ((float)data->at(b++)/unitLength)) , (  1- ((float)data->at(b++)/unitLength) )  ,0.0f);
                if( b == data->size() ){break;}
            }

        glEnd();
        return b+1;
    }

    void drawRectangle(unsigned int RGB, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int angle, unsigned int anc_X, unsigned int anc_Y){
        float anchorX = (float)anc_X/256;
        float anchorY = (float)anc_Y/256;

        //extract and apply colour 
            extractEightBitColour( RGB );

        //print square
            glPushMatrix();
            glTranslatef( 
                -1+(float) ( x )/unitLength,
                 1-(float) ( y )/unitLength,
                0.0f 
            );
            glRotatef( 
                ((float)angle*1.40625), // (angle/256) * 360
                0.0,0.0,1.0
            );
            glRectf(
                -( (float)width*anchorX )/unitLength,
                ( (float)height*anchorY )/unitLength,
                ( (float)width*(1-anchorX) )/unitLength,
                -( (float)height*(1-anchorY) )/unitLength
            );
            glPopMatrix();
    }

    void drawCircle(unsigned int RGB, unsigned int x, unsigned int y, unsigned int radius){

        //extract and apply colour 
            extractEightBitColour( RGB );

        //print circle
            //setup precalculated values
            unsigned int triangleCount = 3; if(radius > 3){ triangleCount = radius; }
            float calculated_x = -1+(float)x/unitLength;
            float calculated_y =  1-(float)y/unitLength;
            float calculated_radius = (float)radius/unitLength;
            float calculated_2PI_div_triangleCount = M_PI*2 / triangleCount;

            //actual print
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f( calculated_x,calculated_y );
            for(unsigned int a = 0; a < triangleCount+1; a++){
                glVertex2f(
                    calculated_x + (calculated_radius * cos(a * calculated_2PI_div_triangleCount)), 
                    calculated_y + (calculated_radius * sin(a * calculated_2PI_div_triangleCount))
                );
            }
            glEnd();
    }