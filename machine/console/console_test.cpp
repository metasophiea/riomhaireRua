#include <iostream>

#include "console.h"

int main(){
    std::cout << "Hello" << std::endl;

    console obj = console(8);
    //obj.debug(true);

    obj.write(129); //attempt to access prePrint edit commands while outside of prePrint edit mode


    //testing the prePrint functionality
    obj.write(128); //begin prePrint
    obj.write(132); //select code to edit
    obj.write(129); //clear code of current data

    obj.write(72);  //H
    obj.write(101); //e
    obj.write(108); //l
    obj.write(108); //l
    obj.write(111); //o
    obj.write(10);  //(new line)

    obj.write(131); //finish writing

    obj.write(132); //print code 132


    obj.write(130); //clear all buffer codes
    obj.write(132); //attempt to print the code created before the clearing


    return 0;
}