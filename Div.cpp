//
// Created by anton on 12/14/18.
//

#include "Div.h"

double Div ::calculate() {

    if(right->calculate() == 0) {
        throw 0;
    } else {
        return left->calculate() / right->calculate();
    }
}