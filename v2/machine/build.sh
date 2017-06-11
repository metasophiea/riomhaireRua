#!/bin/bash
# needs boost and GLFW libraries

g++ -c bareMetal.cpp
g++ -c logicUnit.cpp
g++ -c memoryBlock.cpp
g++ -c consoleAccess.cpp
g++ -c visualDisplay.cpp
g++ -c accessManager.cpp
g++ -c executer.cpp
g++ -c programManager.cpp 

g++ displayUnit.cpp -o displayUnit -framework OpenGL -lglfw3

g++ main.cpp *.o -o rua