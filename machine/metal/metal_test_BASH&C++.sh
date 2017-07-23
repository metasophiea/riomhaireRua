#!/bin/bash

# compile files
    g++ -c metal.cpp

# write test file
    # Decalare tests
        declare lengthOfMeta=2;
        declare className=metal;
        declare -a tests=( #methodName, argumentLength, result, arg_1, arg_2, arg_3...    
            # # get bit size
            #     getBitSize          0 8
            # # get maximum possible value
            #     getMaxPossibleValue 1 255 0
            #     getMaxPossibleValue 1 127 1
            # # UINTtoANYTHINGto do hex stuff
            #     UINTtoANYTHING 3 '"0"'  0   tempCharArray_hex 16
            #     UINTtoANYTHING 3 '"a"'  10  tempCharArray_hex 16
            #     UINTtoANYTHING 3 '"f"'  15  tempCharArray_hex 16
            #     UINTtoANYTHING 3 '"10"' 16  tempCharArray_hex 16
            #     UINTtoANYTHING 3 '"64"' 100 tempCharArray_hex 16
            #     UINTtoANYTHING 3 '"ff"' 255 tempCharArray_hex 16
            # # ANYTHINGtoUINT do hex stuff
            #     ANYTHINGtoUINT 3 0   '"0"'  tempCharArray_hex 16
            #     ANYTHINGtoUINT 3 10  '"a"'  tempCharArray_hex 16
            #     ANYTHINGtoUINT 3 15  '"f"'  tempCharArray_hex 16
            #     ANYTHINGtoUINT 3 16  '"10"' tempCharArray_hex 16
            #     ANYTHINGtoUINT 3 100 '"64"' tempCharArray_hex 16
            #     ANYTHINGtoUINT 3 255 '"ff"' tempCharArray_hex 16

            # # UINTtoANYTHING to do binary stuff
            #     UINTtoANYTHING 3 '"0"'        0   tempCharArray_bin 2
            #     UINTtoANYTHING 3 '"1010"'     10  tempCharArray_bin 2
            #     UINTtoANYTHING 3 '"1111"'     15  tempCharArray_bin 2
            #     UINTtoANYTHING 3 '"10000"'    16  tempCharArray_bin 2
            #     UINTtoANYTHING 3 '"1100100"'  100 tempCharArray_bin 2
            #     UINTtoANYTHING 3 '"11111111"' 255 tempCharArray_bin 2
            # # ANYTHINGtoUINT do binary stuff
            #     ANYTHINGtoUINT 3 0   '"0"'        tempCharArray_bin 2
            #     ANYTHINGtoUINT 3 10  '"1010"'     tempCharArray_bin 2
            #     ANYTHINGtoUINT 3 15  '"1111"'     tempCharArray_bin 2
            #     ANYTHINGtoUINT 3 16  '"10000"'    tempCharArray_bin 2
            #     ANYTHINGtoUINT 3 100 '"1100100"'  tempCharArray_bin 2
            #     ANYTHINGtoUINT 3 255 '"11111111"' tempCharArray_bin 2

            # # UINTtoHEX
            #     UINTtoHEX  1 '"0"'   0  
            #     UINTtoHEX  1 '"a"'   10 
            #     UINTtoHEX  1 '"f"'   15 
            #     UINTtoHEX  1 '"10"'  16 
            #     UINTtoHEX  1 '"64"'  100
            #     UINTtoHEX  1 '"ff"'  255
            #     UINTtoHEX  1 '"12c"' 300

            # # UINTtoHEX_systemSize
            #     UINTtoHEX_systemSize  1 '"00"' 0  
            #     UINTtoHEX_systemSize  1 '"0a"' 10 
            #     UINTtoHEX_systemSize  1 '"0f"' 15 
            #     UINTtoHEX_systemSize  1 '"10"' 16 
            #     UINTtoHEX_systemSize  1 '"64"' 100
            #     UINTtoHEX_systemSize  1 '"ff"' 255
            #     UINTtoHEX_systemSize  1 '"2c"' 300

            # # HEXtoUINT
            #     HEXtoUINT 1 0   '"0"'
            #     HEXtoUINT 1 10  '"a"'
            #     HEXtoUINT 1 16  '"10"'
            #     HEXtoUINT 1 100 '"64"'
            #     HEXtoUINT 1 255 '"ff"'
            #     HEXtoUINT 1 300 '"12c"'

            # # UINTtoBIN
            #     UINTtoBIN  1 '"0"'         0  
            #     UINTtoBIN  1 '"1010"'      10 
            #     UINTtoBIN  1 '"1111"'      15 
            #     UINTtoBIN  1 '"10000"'     16 
            #     UINTtoBIN  1 '"1100100"'   100
            #     UINTtoBIN  1 '"11111111"'  255
            #     UINTtoBIN  1 '"100101100"' 300

            # # UINTtoBIN_systemSize
            #     UINTtoBIN_systemSize  1 '"00000000"'   0  
            #     UINTtoBIN_systemSize  1 '"00001010"'  10 
            #     UINTtoBIN_systemSize  1 '"00001111"'  15 
            #     UINTtoBIN_systemSize  1 '"00010000"'  16 
            #     UINTtoBIN_systemSize  1 '"01100100"' 100
            #     UINTtoBIN_systemSize  1 '"11111111"' 255
            #     UINTtoBIN_systemSize  1 '"00101100"' 300

            # # BINtoUINT
            #     BINtoUINT 1 0   '"0"'       
            #     BINtoUINT 1 10  '"1010"'    
            #     BINtoUINT 1 15  '"1111"'    
            #     BINtoUINT 1 16  '"10000"'   
            #     BINtoUINT 1 100 '"1100100"' 
            #     BINtoUINT 1 255 '"11111111"' 
            #     BINtoUINT 1 300 '"100101100"'

            # # adjustBIN
            #     adjustBIN 3 '"10000000"' '"00000000"' 0 true
            #     adjustBIN 3 '"01000000"' '"00000000"' 1 true
            #     adjustBIN 3 '"00000000"' '"00000000"' 1 false

            # bitAdjustUINT_systemSize
                bitAdjustUINT_systemSize 3 0 0 0 false
                bitAdjustUINT_systemSize 3 1 0 7 true
                
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
                echo "char tempCharArray_hex[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};"  >> test.cpp
                echo "char tempCharArray_bin[] = {'0','1'};"  >> test.cpp
                echo '    '${className}' obj = '${className}'(8);' >> test.cpp
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
    rm metal.o
    rm test.cpp
    rm test