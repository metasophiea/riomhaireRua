#!/bin/bash

g++ -c errorHandler.cpp
g++ main.cpp *.o -o ruac

./ruac ../examplePrograms/tests/testProgram.rr output.rua