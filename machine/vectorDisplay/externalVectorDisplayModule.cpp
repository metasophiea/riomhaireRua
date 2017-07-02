#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <GLFW/glfw3.h>
#include <iostream>

typedef boost::interprocess::allocator<unsigned int, boost::interprocess::managed_shared_memory::segment_manager>  ShmemAllocator;
typedef boost::interprocess::vector   <unsigned int, ShmemAllocator> DataVector;

//shared vector memory:
    #define vectorMemorySize 65536
    #define vectorDisplay_sharedMemorySpaceName "vectorDisplay_memorySpace"
    //object names
        #define vectorDisplay_vectorMemory "data"
        #define vectorDisplay_control      "control"
        #define vectorDisplay_windowHeight "windowHeight"
        #define vectorDisplay_windowWidth  "windowWidth"

void runCommnads(DataVector *pixels, unsigned int *windowHeight, unsigned int *windowWidth);

int main(){
    std::cout << "Hello from display" << std::endl;
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

                runCommnads(dataMemory,windowHeight,windowWidth);

                glfwSwapBuffers(window);
                glfwPollEvents();
            }

        *control = 1;
        glfwDestroyWindow(window);
        glfwTerminate();

    }catch(boost::interprocess::interprocess_exception e){ std::cout << "Boost error - could not find shared memory space" << std::endl; return 1;}

    return 0;
}

void runCommnads(DataVector *data, unsigned int *windowHeight, unsigned int *windowWidth){
    //std::cout << dataM->at(0) << std::endl;
    // std::cout << data->size() << std::endl;

    for(unsigned int a = 0; a < data->size(); a++){
        //std::cout << "  " << a << "|" << data->at(a) << std::endl;

        switch(data->at(a)){
            case 0: break;
            case 1: //poly
                a++;
                glBegin(GL_POLYGON);
                
                //extract colour
                    glColor3f( (float)data->at(a++)/256 , (float)data->at(a++)/256 , (float)data->at(a++)/256 ); 

                //collect first point and print that manually
                    unsigned int X = data->at(a++), Y = data->at(a++);
                    glVertex3f( ( -1+ ((float)X/128)) , (  1- ((float)Y/128) )  ,0.0f);

                //loop through points until a copy is found, indicating the end of the shape
                    while( !(data->at(a) == X && data->at(a+1) == Y) ){
                        glVertex3f( ( -1+ ((float)data->at(a++)/128)) , (  1- ((float)data->at(a++)/128) )  ,0.0f);
                    }

                glEnd();
            break;
        }

    }
}