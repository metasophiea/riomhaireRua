#!/bin/bash

# copy in needed files
    cp ../metal/metal.* .

    cp ../console/console.* .
    cp ../memoryBlock/memoryBlock.* .
    cp ../removableMemory/removableMemory.* .
    cp ../pixelDisplay/pixelDisplay.* .; cp ../pixelDisplay/externalPixelDisplayModule.cpp .
    cp ../vectorDisplay/vectorDisplay.* .;  cp ../vectorDisplay/externalVectorDisplayModule.cpp .

# compile files
    g++ -c metal.cpp

    g++ -c console.cpp
    g++ -c memoryBlock.cpp
    g++ -c removableMemory.cpp
    g++ -c pixelDisplay.cpp; g++ externalPixelDisplayModule.cpp -o externalPixelDisplayModule -framework OpenGL -lglfw3
    g++ -c vectorDisplay.cpp; g++ externalVectorDisplayModule.cpp -o externalVectorDisplayModule -framework OpenGL -lglfw3
 
    g++ -c accessManager.cpp

# compile and run
    g++ accessManager_test.cpp *.o -o test
    ./test

# delete undeeded files
    rm metal.*
    rm console.*
    rm memoryBlock.*
    rm removableMemory.*
    rm pixelDisplay.*; rm externalPixelDisplayModule*
    rm vectorDisplay.*; rm externalVectorDisplayModule*
    rm accessManager.o

    rm test