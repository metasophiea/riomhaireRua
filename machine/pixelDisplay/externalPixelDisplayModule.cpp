#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <GLFW/glfw3.h>
#include <iostream>

typedef boost::interprocess::allocator<float, boost::interprocess::managed_shared_memory::segment_manager>  ShmemAllocator;
typedef boost::interprocess::vector   <float, ShmemAllocator> PixelVector;

//shared pixel memory:
    #define pixelDisplay_sharedMemorySpaceName "pixelDisplay_memorySpace"
    //object names
        #define pixelDisplay_pixelMemory  "pixels"
        #define pixelDisplay_control      "control"     
        #define pixelDisplay_pixelHeight  "pixelHeight" 
        #define pixelDisplay_pixelWidth   "pixelWidth"  
        #define pixelDisplay_windowHeight "windowHeight"
        #define pixelDisplay_windowWidth  "windowWidth" 
        #define pixelDisplay_pixelCountY  "pixelCountY" 
        #define pixelDisplay_pixelCountX  "pixelCountX" 

int main(void){
    //attempt to collect shared memory data
    try{
        boost::interprocess::managed_shared_memory segment(boost::interprocess::open_only, pixelDisplay_sharedMemorySpaceName);

        PixelVector  *pixels       = segment.find<PixelVector> (pixelDisplay_pixelMemory ).first;
        unsigned int *control      = segment.find<unsigned int>(pixelDisplay_control     ).first;
        float        *pixelHeight  = segment.find<float>       (pixelDisplay_pixelHeight ).first;
        float        *pixelWidth   = segment.find<float>       (pixelDisplay_pixelWidth  ).first;
        unsigned int *windowHeight = segment.find<unsigned int>(pixelDisplay_windowHeight).first;
        unsigned int *windowWidth  = segment.find<unsigned int>(pixelDisplay_windowWidth ).first;
        unsigned int *pixelCountY  = segment.find<unsigned int>(pixelDisplay_pixelCountY ).first;
        unsigned int *pixelCountX  = segment.find<unsigned int>(pixelDisplay_pixelCountX ).first;

        //setup window
            GLFWwindow* window;
            glfwInit();
            window = glfwCreateWindow(*windowWidth, *windowHeight, "Rua - Visual Display", NULL, NULL);
            glfwMakeContextCurrent(window);
            glfwSwapInterval(1);

        //tell pixelDisplay that all is good
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