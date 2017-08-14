#!/bin/bash

# copy in needed files
    cp ../metal/metal.* .

# compile files
    g++ -c metal.cpp
    g++ -c removeableMemory.cpp

# compile and run
    g++ removeableMemory_test.cpp *.o -o test
    ./test

# delete undeeded files
    rm metal.*
    rm removeableMemory.o

    rm test