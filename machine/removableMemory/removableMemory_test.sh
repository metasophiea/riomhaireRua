#!/bin/bash

# copy in needed files
    cp ../metal/metal.* .

# compile files
    g++ -c metal.cpp
    g++ -c removableMemory.cpp

# compile and run
    g++ removableMemory_test.cpp *.o -o test
    ./test

# delete undeeded files
    rm metal.*
    rm removableMemory.o

    rm test