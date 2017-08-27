# copy files in
    cp metal/metal.* .

    cp console/console.* .
    cp memoryBlock/memoryBlock.* .    
    cp ../removableMemory/removableMemory.* .
    cp pixelDisplay/pixelDisplay.* .; cp pixelDisplay/externalPixelDisplayModule.* .
    cp vectorDisplay/vectorDisplay.* .; cp vectorDisplay/externalVectorDisplayModule.* .
    cp accessManager/accessManager.* .

    cp logicUnit/logicUnit.* .
    cp executer/executer.* .
    cp programManager/programManager.* .

# compile
    g++ -c metal.cpp

    g++ -c console.cpp
    g++ -c memoryBlock.cpp
    g++ -c removableMemory.cpp
    g++ -c pixelDisplay.cpp; g++ externalPixelDisplayModule.cpp -o externalPixelDisplayModule -framework OpenGL -lglfw3
    g++ -c vectorDisplay.cpp; g++ externalVectorDisplayModule.cpp -o externalVectorDisplayModule -framework OpenGL -lglfw3
    g++ -c accessManager.cpp

    g++ -c logicUnit.cpp
    g++ -c executer.cpp
    g++ -c programManager.cpp

    g++ main.cpp *.o -o rua

# delete un-needed files
    rm metal.*

    rm console.*
    rm memoryBlock.*
    rm removableMemory.*
    rm pixelDisplay.*; rm externalPixelDisplayModule.*;
    rm vectorDisplay.*; rm externalVectorDisplayModule.*;
    rm accessManager.*

    rm logicUnit.*
    rm executer.*
    rm programManager.*