//
// Created by anton on 12/14/18.
//

#include "Negation.h"

double Negation ::calculate() {
    return -1 * expression->calculate();
}