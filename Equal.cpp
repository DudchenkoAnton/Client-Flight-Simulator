//
// Created by anton on 12/21/18.
//

#include "Equal.h"

double Equal :: calculate() {

    if(left->calculate() == right->calculate())
        return 1;
    else
        return 0;

}