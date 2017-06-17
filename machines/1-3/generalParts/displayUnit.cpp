#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <GLFW/glfw3.h>
#include <iostream>

typedef boost::interprocess::allocator<float, boost::interprocess::managed_shared_memory::segment_manager>  ShmemAllocator;
typedef boost::interprocess::vector   <float, ShmemAllocator> PixelVector;

//pixel memory:
    #define visualDisplay_sharedMemorySpaceName "visualDisplay_memorySpace"
    //object names
        #define visualDisplay_windowTitle  "windowTitle"
        #define visualDisplay_pixelMemory  "pixels"
        #define visualDisplay_control      "control"     
        #define visualDisplay_pixelHeight  "pixelHeight" 
        #define visualDisplay_pixelWidth   "pixelWidth"  
        #define visualDisplay_windowHeight "windowHeight"
        #define visualDisplay_windowWidth  "windowWidth" 
        #define visualDisplay_pixelCountY  "pixelCountY" 
        #define visualDisplay_pixelCountX  "pixelCountX" 

int main(void){
    //attempt to collect shared memory data
    try{
        boost::interprocess::managed_shared_memory segment(boost::interprocess::open_only, visualDisplay_sharedMemorySpaceName);

        PixelVector  *pixels       = segment.find<PixelVector> (visualDisplay_pixelMemory ).first;
        unsigned int *control      = segment.find<unsigned int>(visualDisplay_control     ).first;
        float        *pixelHeight  = segment.find<float>       (visualDisplay_pixelHeight ).first;
        float        *pixelWidth   = segment.find<float>       (visualDisplay_pixelWidth  ).first;
        unsigned int *windowHeight = segment.find<unsigned int>(visualDisplay_windowHeight).first;
        unsigned int *windowWidth  = segment.find<unsigned int>(visualDisplay_windowWidth ).first;
        unsigned int *pixelCountY  = segment.find<unsigned int>(visualDisplay_pixelCountY ).first;
        unsigned int *pixelCountX  = segment.find<unsigned int>(visualDisplay_pixelCountX ).first;

        //setup window
            GLFWwindow* window;
            glfwInit();
            window = glfwCreateWindow(*windowWidth, *windowHeight, "Rua - Visual Display", NULL, NULL);
            glfwMakeContextCurrent(window);
            glfwSwapInterval(1);

        //tell visualDisplay that all is good
            *control = 1; 

        //rendering loop
            unsigned int selectedPixel;
            while(!glfwWindowShouldClose(window)){
                if(*control == 2){break;}

                for(unsigned int y = 0; y < (*pixelCountY); y++){
                    for(unsigned int x = 0; x < (*pixelCountX); x++){
                        glBegin(GL_QUADS);
                        selectedPixel = 3*(x + y*(*pixelCountX));
                        glColor3f( pixels->at( selectedPixel+0 ),pixels->at( selectedPixel+1 ),pixels->at( selectedPixel+2 )  ); 
                        glVertex3f(    -1               + (*pixelWidth)*x ,  1                - (*pixelHeight)*y , 0.0f);
                        glVertex3f(    -1+(*pixelWidth) + (*pixelWidth)*x ,  1                - (*pixelHeight)*y , 0.0f);
                        glVertex3f(    -1+(*pixelWidth) + (*pixelWidth)*x ,  1-(*pixelHeight) - (*pixelHeight)*y , 0.0f);
                        glVertex3f(    -1               + (*pixelWidth)*x ,  1-(*pixelHeight) - (*pixelHeight)*y , 0.0f);
                        glEnd();
                    }
                }

                glfwSwapBuffers(window);
                glfwPollEvents();
            }

        *control = 1;
        glfwDestroyWindow(window);
        glfwTerminate();

    }catch(boost::interprocess::interprocess_exception e){ std::cout << "Boost error - could not find shared memory space" << std::endl; return 1;}
        
    return 0;
}