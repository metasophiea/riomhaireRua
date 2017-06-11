#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

typedef boost::interprocess::allocator<float, boost::interprocess::managed_shared_memory::segment_manager>  ShmemAllocator;
typedef boost::interprocess::vector   <float, ShmemAllocator> PixelVector;

static void error_callback(int error, const char* description){ fputs(description, stderr); }
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){ if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){ glfwSetWindowShouldClose(window, GL_TRUE); } } 
int main(void){
    boost::interprocess::managed_shared_memory segment(boost::interprocess::open_only, "visualDisplay_memory");
    PixelVector *pixels = segment.find<PixelVector>("pixels").first;

    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()){ exit(EXIT_FAILURE); }
    window = glfwCreateWindow(500, 500, "Rua - 16x16 Visual Port", NULL, NULL);
    if (!window){ glfwTerminate(); exit(EXIT_FAILURE); }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    //rendering loop
    while (!glfwWindowShouldClose(window)){
        float pixelHeight = 0.125;
        float pixelWidth = 0.125;
        unsigned int pixelCountY = 16;
        unsigned int pixelCountX = 16;
        
        for(unsigned int y = 0; y < pixelCountY; y++){
            for(unsigned int x = 0; x < pixelCountX; x++){
                glBegin(GL_QUADS);
                glColor3f( pixels->at( 3*(x + y*16) +0 ),pixels->at( 3*(x + y*16) +1 ),pixels->at( 3*(x + y*16) +2 )  ); 
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

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
