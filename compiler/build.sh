#!/bin/bash

g++ -c errorHandler.cpp
g++ main.cpp *.o -o ruac


./ruac ./testPrograms/rua.2/countFromZeroToNine.rr countFromZeroToNine.rua