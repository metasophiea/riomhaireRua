# copy in needed files
    cp ../metal/metal.* .

# compile files
    g++ -c metal.cpp
    g++ -c memoryBlock.cpp
    g++ memoryBlock_test.cpp *.o -o test

# run test program
    ./test

# delete undeeded files
    rm metal.*
    rm memoryBlock.o
    rm test