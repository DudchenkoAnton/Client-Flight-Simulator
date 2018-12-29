//
// Created by anton on 12/14/18.
//

#ifndef SIMULATOR1_DIV_H
#define SIMULATOR1_DIV_H


#include "BinaryExpression.h"

class Div : public BinaryExpression{

public:
    Div(Expression* newLeft, Expression* newRight) {
        left = newLeft;
        right = newRight;
    }

    virtual double calculate();
};


#endif //SIMULATOR1_DIV_H
