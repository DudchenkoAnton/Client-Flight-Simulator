//
// Created by anton on 12/14/18.
//

#include "Mul.h"

double Mul ::calculate() {
    return left->calculate() * right->calculate();
}
