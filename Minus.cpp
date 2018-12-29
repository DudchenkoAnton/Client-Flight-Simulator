//
// Created by anton on 12/14/18.
//

#include "Minus.h"

double Minus ::calculate() {
    return left->calculate() - right->calculate();
}
