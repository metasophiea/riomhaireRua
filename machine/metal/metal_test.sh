#!/bin/bash

# compile files
    g++ -c metal.cpp

# compile and run
    g++ metal_test.cpp *.o -o test
    ./test

# delete undeeded files
    rm metal.o

    rm test