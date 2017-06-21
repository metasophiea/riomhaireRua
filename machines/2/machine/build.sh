#!/bin/bash
# needs boost and GLFW libraries

# import files and compile in correct order
    cp ../../1/machine/bareMetal.h .; cp ../../1/machine/bareMetal.cpp .;
    g++ -c bareMetal.cpp

    cp ../../1/machine/logicUnit.h .; cp ../../1/machine/logicUnit.cpp .;
    g++ -c logicUnit.cpp

    cp ../../1/machine/memoryBlock.h .; cp ../../1/machine/memoryBlock.cpp .;
    g++ -c memoryBlock.cpp

    cp ../../1/machine/consoleAccess.h .; cp ../../1/machine/consoleAccess.cpp .;
    g++ -c consoleAccess.cpp

    g++ -c visualDisplay.cpp
    g++ displayUnit.cpp -o displayUnit -framework OpenGL -lglfw3

    g++ -c accessManager.cpp
    g++ -c executer.cpp

    cp ../../1/machine/programManager.h .; cp ../../1/machine/programManager.cpp .;
    g++ -c programManager.cpp 

    cp ../../1/machine/main.cpp .;
    g++ main.cpp *.o -o rua

# delete imported files
    rm bareMetal.h; rm bareMetal.cpp;
    rm logicUnit.h; rm logicUnit.cpp;
    rm memoryBlock.h; rm memoryBlock.cpp;
    rm consoleAccess.h; rm consoleAccess.cpp;
    rm programManager.h; rm programManager.cpp;
    rm main.cpp;

# delete produced object files
    rm bareMetal.o;
    rm logicUnit.o;
    rm memoryBlock.o;
    rm consoleAccess.o;
    rm visualDisplay.o;
    rm accessManager.o;
    rm executer.o;
    rm programManager.o;