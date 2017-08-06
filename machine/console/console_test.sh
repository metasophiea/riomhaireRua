#!/bin/bash

# copy in needed files
    cp ../metal/metal.* .

# compile files
    g++ -c metal.cpp

    g++ -c console.cpp

# compile and run
    g++ console_test.cpp *.o -o test
    ./test

# delete undeeded files
    rm metal.*
    rm console.o

    rm test