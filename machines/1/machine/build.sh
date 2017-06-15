#!/bin/bash

# import files and compile in correct order
    cp ../../generalParts/bareMetal.h .; cp ../../generalParts/bareMetal.cpp .;
    g++ -c bareMetal.cpp

    cp ../../generalParts/logicUnit.h .; cp ../../generalParts/logicUnit.cpp .;
    g++ -c logicUnit.cpp

    cp ../../generalParts/memoryBlock.h .; cp ../../generalParts/memoryBlock.cpp .;
    g++ -c memoryBlock.cpp

    cp ../../generalParts/consoleAccess.h .; cp ../../generalParts/consoleAccess.cpp .;
    g++ -c consoleAccess.cpp

    g++ -c accessManager.cpp
    g++ -c executer.cpp

    cp ../../generalParts/programManager.h .; cp ../../generalParts/programManager.cpp .;
    g++ -c programManager.cpp 

    cp ../../generalParts/main.cpp .;
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
    rm accessManager.o;
    rm executer.o;
    rm programManager.o;