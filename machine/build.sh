# copy files in
    cp metal/metal.* .

    cp console/console.* .
    cp memoryBlock/memoryBlock.* .
    cp accessManager/accessManager.* .

    cp logicUnit/logicUnit.* .
    cp executer/executer.* .
    cp programManager/programManager.* .

# compile
    g++ -c metal.cpp

    g++ -c console.cpp
    g++ -c memoryBlock.cpp
    g++ -c accessManager.cpp

    g++ -c logicUnit.cpp
    g++ -c executer.cpp
    g++ -c programManager.cpp

    g++ main.cpp *.o -o rua

# delete undeeded files
    rm metal.*

    rm console.*
    rm memoryBlock.*
    rm accessManager.*

    rm logicUnit.*
    rm executer.*
    rm programManager.*