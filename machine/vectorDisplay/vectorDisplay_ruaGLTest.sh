#!/bin/bash

# copy in needed files
    cp ../metal/metal.* .

# compile files
    g++ -c metal.cpp
    g++ -c vectorDisplay.cpp
    g++ externalVectorDisplayModule.cpp -o externalVectorDisplayModule -framework OpenGL -lglfw3

# compile and run
    g++ vectorDisplay_ruaGLTest.cpp *.o -o test
    ./test

# delete undeeded files
    rm metal.*
    rm vectorDisplay.o
    rm externalVectorDisplayModule
    rm test