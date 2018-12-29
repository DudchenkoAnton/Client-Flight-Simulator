//
// Created by anton on 12/21/18.
//

#include "NotEqual.h"


double NotEqual :: calculate() {

    if(left->calculate() != right->calculate())
        return 1;
    else
        return 0;

}