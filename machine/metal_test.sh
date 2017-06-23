g++ -c metal.cpp

g++ metal_test.cpp metal.o -o test

./test

rm test