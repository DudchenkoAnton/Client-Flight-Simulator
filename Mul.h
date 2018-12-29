//
// Created by anton on 12/14/18.
//

#ifndef SIMULATOR1_MUL_H
#define SIMULATOR1_MUL_H


#include "Expression.h"
#include "BinaryExpression.h"

class Mul : public BinaryExpression {

public:
    Mul(Expression* newLeft, Expression* newRight) {
        left = newLeft;
        right = newRight;
    }

    virtual double calculate();
};


#endif //SIMULATOR1_MUL_H
