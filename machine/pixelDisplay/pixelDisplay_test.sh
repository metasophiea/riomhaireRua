#!/bin/bash

# copy in needed files
    cp ../metal/metal.* .
# compile files
    g++ -c metal.cpp
    g++ -c pixelDisplay.cpp
    g++ externalPixelDisplayModule.cpp -o externalPixelDisplayModule -framework OpenGL -lglfw3

# compile and run
    g++ pixelDisplay_test.cpp *.o -o test
    ./test

# delete undeeded files
    rm metal.*
    rm pixelDisplay.o
    rm externalPixelDisplayModule
    rm test