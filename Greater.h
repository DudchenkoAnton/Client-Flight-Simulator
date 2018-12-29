//
// Created by anton on 12/18/18.
//

#ifndef SIMULATOR1_GREATER_H
#define SIMULATOR1_GREATER_H


#include "BinaryExpression.h"

class Greater : public BinaryExpression {


public:
    Greater(Expression* newLeft, Expression* newRight) {
        left = newLeft;
        right = newRight;
    }
    virtual double calculate();
};


#endif //SIMULATOR1_GREATER_H
