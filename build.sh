#!/bin/bash

g++ -c bareMetal.cpp
g++ -c logicUnit.cpp
g++ -c memoryBlock.cpp
g++ -c consoleAccess.cpp
g++ -c accessManager.cpp
g++ -c executer.cpp

g++ main.cpp *.o

./a.out