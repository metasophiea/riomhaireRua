#!/bin/bash

# copy in needed files
    cp ../metal/metal.* .
# compile files
    g++ -c metal.cpp
    g++ -c logicUnit.cpp

# write test file
    # Decalare tests
        #methodName, argumentLength, calculationMode, result, arg_1, arg_2, arg_3...
        declare lengthOfMeta=3;
        declare -a tests=(
            #checks
                logicCheck  1 0  10   10
                mathCheck   2 0  10   10    0
                mathCheck   2 0  246  -10   0
                mathCheck   2 0  10   10    1
                mathCheck   2 0  138  -10   1
                mathCheck   2 0  228  -100  1
                mathCheck   2 0  255  -128  1

            #logical
                #lone byte
                flip        1 0  245  10
                lRotate     1 0   20  10
                rRotate     1 0    5  10
                #multi byte
                AND         2 0    2  10  2
                NAND        2 0  253  10  2
                OR          2 0   10  10  2
                XOR         2 0    8  10  2
                NOR         2 0  245  10  2

            #math
                #lone byte
                convert     3 0  130 130  0  0
                convert     3 0  130 130  1  1
                convert     3 0  127 130  0  1
                convert     3 0  254 130  1  0

                inc         1 0  131 130
                inc         1 0    0 255
                inc         1 1  101 100
                inc         1 1  139 140

                dec         1 0  129 130
                dec         1 0  255   0
                dec         1 1   99 100
                dec         1 1  141 140

                neg         1 0  156 100
                neg         1 1  228 100
                #multi byte
                add         2 0  101 100  1
                add         2 0   44 100  200
                add         2 1  101 100  1
                add         2 1  127 127  1
                add         2 1   28 100  200
                add         2 1    1 128  1
                add         2 1  202 200  130

                sub         2 0   99 100  1
                sub         2 0  156 100  200
                sub         2 1   99 100  1
                sub         2 1  127 100  200
                sub         2 1  129 128  1
                sub         2 1  198 200  130
        );

    # go through each test
        declare skip=$((tests[1]+lengthOfMeta));
        declare methodName;
        declare calculationMode;
        declare args;
        declare expectedResult;

        for (( a=0; a<${#tests[@]}; a+=${skip} )) do
            skip=$((tests[a+1]+lengthOfMeta+1));
            #fill in method name, calculation mode and expected result
                methodName=${tests[a]};
                calculationMode=${tests[a+2]};
                expectedResult=${tests[a+lengthOfMeta]};

            #fill in args
                args=;
                for (( b=0; b<${tests[a+1]}; b++ )) do
                    args=${args}${tests[a+b+lengthOfMeta+1]};
                    if (( b < ${tests[a+1]}-1 ))
                    then args=${args},; fi
                done

            #write up new file
                > test.cpp
                echo '#include <iostream>' >> test.cpp
                echo '' >> test.cpp
                echo '#include "logicUnit.h"' >> test.cpp
                echo '' >> test.cpp
                echo 'int main(){' >> test.cpp
                echo '    logicUnit lu = logicUnit(8);' >> test.cpp
                echo '    lu.debug(false);' >> test.cpp
                echo '    lu.setCalculationMode('${calculationMode}');' >> test.cpp  
                echo '' >> test.cpp
                echo '    std::cout << "- '${methodName}' test -" << std::endl;' >> test.cpp
                echo '    std::cout << "Test: u.'${methodName}'('${args}') = '${expectedResult}' " << std::endl;' >> test.cpp
                echo '    if( lu.'${methodName}'('${args}') == '${expectedResult}' ){ std::cout << "- all good" << std::endl; }' >> test.cpp
                echo '    else{' >> test.cpp
                echo '        lu.debug(true);' >> test.cpp
                echo '        std::cout << "lu.'${methodName}'('${args}')" << std::endl;' >> test.cpp
                echo '        std::cout << lu.'${methodName}'('${args}') << std::endl;' >> test.cpp
                echo '        lu.debug(false);' >> test.cpp
                echo '        std::cout << "- failure" << std::endl;' >> test.cpp
                echo '        return 1;' >> test.cpp
                echo '    }' >> test.cpp
                echo '' >> test.cpp
                echo '    return 0;' >> test.cpp
                echo '}' >> test.cpp

            # compile and run
                g++ test.cpp *.o -o test
                if ./test; then echo;
                else echo; break; fi;

        done

# delete undeeded files
    rm metal.*
    rm logicUnit.o
    rm test.cpp
    rm test