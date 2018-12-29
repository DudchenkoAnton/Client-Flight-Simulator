//
// Created by anton on 12/18/18.
//

#include "Greater.h"

double Greater :: calculate() {

    if(left->calculate() > right->calculate())
        return 1;
    else
        return 0;

}