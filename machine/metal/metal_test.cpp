#include <iostream>

#include "metal.h"

int main(){
    std::cout << "Hello" << std::endl;

    metal obj = metal(8);
    obj.debug(true);

    std::cout << obj.BINtoUINT(obj.adjustBIN("000",2,true)) << std::endl;

    return 0;
}