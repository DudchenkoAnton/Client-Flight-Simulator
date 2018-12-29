//
// Created by anton on 12/14/18.
//


#ifndef SIMULATOR1_NUMBER_H
#define SIMULATOR1_NUMBER_H

#include "UnaryExpression.h"
#include <string>

using namespace std;

class NumberExpression : public UnaryExpression {

    double value;

public:

    NumberExpression(string newVal);
    virtual double calculate();
};


#endif //SIMULATOR1_NUMBER_H
