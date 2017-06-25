#include <iostream>

#include "logicUnit.h"

int main(){    
    std::cout << "Hello" << std::endl;

    logicUnit lu = logicUnit(8);
    lu.debug(false);
    int testResult, testValue_1, testValue_2, testValue_3;

    std::cout << "- logicCheck test -" << std::endl;
    testValue_1 = 10;
    testValue_2 = 0;
    testValue_3 = 0;
    testResult = 10;
    if( lu.logicCheck(testValue_1) == testResult ){ std::cout << "- all good" << std::endl; }
    else{
        std::cout << "- failure" << std::endl;
        lu.debug(true);
        std::cout << "lu.logicCheck(10)" << std::endl;
        std::cout << lu.logicCheck(testValue_1) << std::endl;
        lu.debug(false);
        return 0;
    }std::cout << std::endl;
    
    return 0;
}


    //functions
        //checks
            // std::cout << "- logicCheck test -" << std::endl;
            // testValue_1 = 10;
            // testResult = 10;
            // if( lu.logicCheck(testValue_1) == testResult ){ std::cout << "- all good" << std::endl; }
            // else{
            //     std::cout << "- failure" << std::endl;
            //     lu.debug(true);
            //     std::cout << "lu.logicCheck(10)" << std::endl;
            //     std::cout << lu.logicCheck(testValue_1) << std::endl;
            //     lu.debug(false);
            //     return 0;
            // }std::cout << std::endl;

        //     std::cout << "- mathCheck test -" << std::endl;
        //     std::cout << "lu.mathCheck(10,0)" << std::endl;
        //     std::cout << lu.mathCheck(10,0) << std::endl;
        //     std::cout << std::endl << std::endl;

        //     std::cout << "- mathCheck test -" << std::endl;
        //     std::cout << "lu.mathCheck(-10,0)" << std::endl;
        //     std::cout << lu.mathCheck(-10,0) << std::endl;
        //     std::cout << std::endl << std::endl;

        //     std::cout << "- mathCheck test -" << std::endl;
        //     std::cout << "lu.mathCheck(10,1)" << std::endl;
        //     std::cout << lu.mathCheck(10,1) << std::endl;
        //     std::cout << std::endl << std::endl;

        //     std::cout << "- mathCheck test -" << std::endl;
        //     std::cout << "lu.mathCheck(-10,1)" << std::endl;
        //     std::cout << lu.mathCheck(-10,1) << std::endl;
        //     std::cout << std::endl << std::endl;

        //     std::cout << "- mathCheck test -" << std::endl;
        //     std::cout << "lu.mathCheck(-100,1)" << std::endl;
        //     std::cout << lu.mathCheck(-100,1) << std::endl;
        //     std::cout << std::endl << std::endl;

        //     std::cout << "- mathCheck test -" << std::endl;
        //     std::cout << "lu.mathCheck(-128,1)" << std::endl;
        //     std::cout << lu.mathCheck(-128,1) << std::endl;
        //     std::cout << std::endl << std::endl;

        // //logical
        //     //lone byte
        //     std::cout << "- flip test -" << std::endl;
        //     std::cout << "lu.flip(10)" << std::endl;
        //     std::cout << lu.flip(10) << std::endl;
        //     std::cout << std::endl << std::endl;

        //     std::cout << "- lRotate test -" << std::endl;
        //     std::cout << "lu.lRotate(10)" << std::endl;
        //     std::cout << lu.lRotate(10) << std::endl;
        //     std::cout << std::endl << std::endl;
            
        //     std::cout << "- rRotate test -" << std::endl;
        //     std::cout << "lu.rRotate(10)" << std::endl;
        //     std::cout << lu.rRotate(10) << std::endl;
        //     std::cout << std::endl << std::endl;

        //     //multi byte
        //     std::cout << "- AND test -" << std::endl;
        //     std::cout << "lu.AND(10,2)" << std::endl;
        //     std::cout << lu.AND(10,2) << std::endl;
        //     std::cout << std::endl << std::endl;

        //     std::cout << "- NAND test -" << std::endl;
        //     std::cout << "lu.NAND(10,2)" << std::endl;
        //     std::cout << lu.NAND(10,2) << std::endl;
        //     std::cout << std::endl << std::endl;
            
        //     std::cout << "- OR test -" << std::endl;
        //     std::cout << "lu.OR(10,2)" << std::endl;
        //     std::cout << lu.OR(10,2) << std::endl;
        //     std::cout << std::endl << std::endl;

        //     std::cout << "- NOR test -" << std::endl;
        //     std::cout << "lu.NOR(10,2)" << std::endl;
        //     std::cout << lu.NOR(10,2) << std::endl;
        //     std::cout << std::endl << std::endl;
            
        //     std::cout << "- XOR test -" << std::endl;
        //     std::cout << "lu.XOR(10,2)" << std::endl;
        //     std::cout << lu.XOR(10,2) << std::endl;
        //     std::cout << std::endl << std::endl;

        // //math
        //     //lone byte
        //     std::cout << "- convert test -" << std::endl;
        //         std::cout << "lu.convert(130,0,0)" << std::endl;
        //         std::cout << lu.convert(130,0,0) << std::endl;
        //         std::cout << std::endl << std::endl;

        //         std::cout << "lu.convert(130,1,1)" << std::endl;
        //         std::cout << lu.convert(130,1,1) << std::endl;
        //         std::cout << std::endl << std::endl;

        //         std::cout << "lu.convert(130,0,1)" << std::endl;
        //         std::cout << lu.convert(130,0,1) << std::endl;
        //         std::cout << std::endl << std::endl;

        //         std::cout << "lu.convert(130,0,1)" << std::endl;
        //         std::cout << lu.convert(130,1,0) << std::endl;
        //         std::cout << std::endl << std::endl;

        //     std::cout << "- increment test -" << std::endl;
        //         std::cout << "setting calculation mode to 0" << std::endl << std::endl; lu.setCalculationMode(0);
        //         std::cout << "lu.inc(130)" << std::endl;
        //         std::cout << lu.inc(130) << std::endl;
        //         std::cout << std::endl;

        //         std::cout << "lu.inc(256)" << std::endl;
        //         std::cout << lu.inc(256) << std::endl;
        //         std::cout << std::endl;

        //         std::cout << "setting calculation mode to 1" << std::endl << std::endl; lu.setCalculationMode(1);
        //         std::cout << "lu.inc(100)" << std::endl;
        //         std::cout << lu.inc(100) << std::endl;
        //         std::cout << std::endl << std::endl;

        //         std::cout << "lu.inc(140)" << std::endl;
        //         std::cout << lu.inc(140) << std::endl;
        //         std::cout << std::endl << std::endl;

        //     std::cout << "- decrement test -" << std::endl;
        //         std::cout << "setting calculation mode to 0" << std::endl << std::endl; lu.setCalculationMode(0);
        //         std::cout << "lu.dec(130)" << std::endl;
        //         std::cout << lu.dec(130) << std::endl;
        //         std::cout << std::endl;

        //         std::cout << "lu.dec(0)" << std::endl;
        //         std::cout << lu.dec(0) << std::endl;
        //         std::cout << std::endl;

        //         std::cout << "setting calculation mode to 1" << std::endl << std::endl; lu.setCalculationMode(1);
        //         std::cout << "lu.dec(100)" << std::endl;
        //         std::cout << lu.dec(100) << std::endl;
        //         std::cout << std::endl << std::endl;

        //         std::cout << "lu.dec(140)" << std::endl;
        //         std::cout << lu.dec(140) << std::endl;
        //         std::cout << std::endl << std::endl;

        //     std::cout << "- negitation test -" << std::endl;
        //         std::cout << "setting calculation mode to 0" << std::endl << std::endl; lu.setCalculationMode(0);
        //         std::cout << "lu.neg(100)" << std::endl;
        //         std::cout << lu.neg(100) << std::endl;
        //         std::cout << std::endl;

        //         std::cout << "setting calculation mode to 1" << std::endl << std::endl; lu.setCalculationMode(1);
        //         std::cout << "lu.neg(100)" << std::endl;
        //         std::cout << lu.neg(100) << std::endl;
        //         std::cout << std::endl;

        //     //multi byte
        //     std::cout << "- addition test -" << std::endl;
        //         std::cout << "setting calculation mode to 0" << std::endl << std::endl; lu.setCalculationMode(0);
        //         std::cout << "lu.add(100,1)" << std::endl;
        //         std::cout << lu.add(100,1) << std::endl;
        //         std::cout << std::endl;

        //         std::cout << "lu.add(100,200)" << std::endl;
        //         std::cout << lu.add(100,200) << std::endl;
        //         std::cout << std::endl;

        //         std::cout << "setting calculation mode to 1" << std::endl << std::endl; lu.setCalculationMode(1);
        //         std::cout << "lu.add(100,1)" << std::endl;
        //         std::cout << lu.add(100,1) << std::endl;
        //         std::cout << std::endl;

        //         std::cout << "lu.add(100,200)" << std::endl;
        //         std::cout << lu.add(100,200) << std::endl;
        //         std::cout << std::endl;

        //         std::cout << "lu.add(128,1)" << std::endl;
        //         std::cout << lu.add(128,1) << std::endl;
        //         std::cout << std::endl;

        //         std::cout << "lu.add(200,130)" << std::endl;
        //         std::cout << lu.add(200,130) << std::endl;
        //         std::cout << std::endl;

        //     std::cout << "- subtraction test -" << std::endl;
                
        //         // std::cout << "setting calculation mode to 0" << std::endl << std::endl; lu.setCalculationMode(0);
        //         // std::cout << "lu.sub(100,1)" << std::endl;
        //         // std::cout << lu.sub(100,1) << std::endl;
        //         // std::cout << std::endl;

        //         // std::cout << "lu.sub(100,200)" << std::endl;
        //         // std::cout << lu.sub(100,200) << std::endl;
        //         // std::cout << std::endl;

        //         // std::cout << "setting calculation mode to 1" << std::endl << std::endl; lu.setCalculationMode(1);
        //         // std::cout << "lu.sub(100,1)" << std::endl;
        //         // std::cout << lu.sub(100,1) << std::endl;
        //         // std::cout << std::endl;

        //         // std::cout << "lu.sub(100,200)" << std::endl;
        //         // std::cout << lu.sub(100,200) << std::endl;
        //         // std::cout << std::endl;

        //         // std::cout << "lu.sub(128,1)" << std::endl;
        //         // std::cout << lu.sub(128,1) << std::endl;
        //         // std::cout << std::endl;

        //         // std::cout << "lu.sub(200,130)" << std::endl;
        //         // std::cout << lu.sub(200,130) << std::endl;
        //         // std::cout << std::endl;





//     return 0;
// }