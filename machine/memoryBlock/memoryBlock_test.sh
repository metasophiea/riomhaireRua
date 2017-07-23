#!/bin/bash

# copy in needed files
    cp ../metal/metal.* .

# compile files
    g++ -c metal.cpp
    g++ -c memoryBlock.cpp

# compile and run
    g++ memoryBlock_test.cpp *.o -o test
    ./test

# delete undeeded files
    rm metal.*
    rm memoryBlock.o

    rm test