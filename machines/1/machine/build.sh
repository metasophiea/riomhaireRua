#!/bin/bash

# import files and compile in correct order
    g++ -c bareMetal.cpp
    g++ -c logicUnit.cpp
    g++ -c memoryBlock.cpp
    g++ -c consoleAccess.cpp
    g++ -c accessManager.cpp
    g++ -c executer.cpp;
    g++ -c programManager.cpp 
    g++ main.cpp *.o -o rua

# delete produced object files
    rm bareMetal.o;
    rm logicUnit.o;
    rm memoryBlock.o;
    rm consoleAccess.o;
    rm accessManager.o;
    rm executer.o;
    rm programManager.o;