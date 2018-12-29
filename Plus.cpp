//
// Created by anton on 12/14/18.
//

#include "Plus.h"

double Plus::calculate() {
    return left->calculate() + right->calculate();
}