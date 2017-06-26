#!/bin/bash

# copy in needed files
    cp ../metal/metal.* .
# compile files
    g++ -c metal.cpp
    g++ -c memoryBlock.cpp

# write test file
    # Decalare tests
        declare lengthOfMeta=2;
        declare className=memoryBlock;

        declare -a tests=( #methodName, argumentLength, result, arg_1, arg_2, arg_3...    
            printMemory 0 null
            setByte 2 null 0 10
            getByte 1 0 0
            setBit 3 null 1 0 true
            getBit 2 false 1 0
        );

    # go through each test
        declare skip=$((tests[1]+lengthOfMeta));
        declare methodName;
        declare args;
        declare displayArgs;
        declare expectedResult;

        for (( a=0; a<${#tests[@]}; a+=${skip} )) do
            skip=$((tests[a+1]+lengthOfMeta+1));
            #fill in method name, calculation mode and expected result
                methodName=${tests[a]};
                expectedResult=${tests[a+lengthOfMeta]};

            #fill in args
                args=; displayArgs=;
                for (( b=0; b<${tests[a+1]}; b++ )) do
                    args=${args}${tests[a+b+lengthOfMeta+1]};
                    displayArgs=${displayArgs}${tests[a+b+lengthOfMeta+1]};

                    for (( c=0; c<${#displayArgs}; c++ )) do
                        if [ '"' == ${displayArgs:c:1} ]
                        then 
                            if (( c > 0 ))
                            then
                                if [ "\\" != ${displayArgs:c-1:1} ] 
                                then displayArgs=${displayArgs:0:c}"\\"${displayArgs:c}; fi
                            else displayArgs="\\"${displayArgs}; fi
                        fi
                    done

                    if (( b < ${tests[a+1]}-1 ))
                    then args=${args},; displayArgs=${displayArgs},; fi
                done

            #write up new file
                > test.cpp
                echo '#include <iostream>' >> test.cpp
                echo '' >> test.cpp
                echo '#include "'${className}'.h"' >> test.cpp
                echo '' >> test.cpp
                echo 'int main(){' >> test.cpp
                echo '    '${className}' obj = '${className}'(8,256);' >> test.cpp
                echo '    obj.debug(false);' >> test.cpp
                echo '' >> test.cpp
                echo '    std::cout << "- '${methodName}' test -" << std::endl;' >> test.cpp

                if [ $expectedResult == 'null' ]
                then echo 'obj.'${methodName}'('${displayArgs}');' >> test.cpp
                else
                    echo '    std::cout << "Test: obj.'${methodName}'('${displayArgs}') = " << '${expectedResult}' << std::endl;' >> test.cpp
                    echo '    if( obj.'${methodName}'('${args}') == '${expectedResult}' ){ std::cout << "- all good" << std::endl; }' >> test.cpp
                    echo '    else{' >> test.cpp
                    echo '        obj.debug(true);' >> test.cpp
                    echo '        std::cout << "obj.'${methodName}'('${displayArgs}')" << std::endl;' >> test.cpp
                    echo '        std::cout << obj.'${methodName}'('${args}') << std::endl;' >> test.cpp
                    echo '        obj.debug(false);' >> test.cpp
                    echo '        std::cout << "- failure" << std::endl;' >> test.cpp
                    echo '        return 1;' >> test.cpp
                    echo '    }' >> test.cpp
                fi

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
    rm memoryBlock.o
    rm test.cpp
    rm test