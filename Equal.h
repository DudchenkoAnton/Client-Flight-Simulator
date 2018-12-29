//
// Created by anton on 12/21/18.
//

#ifndef SIMULATOR1_EQUAL_H
#define SIMULATOR1_EQUAL_H


#include "BinaryExpression.h"

class Equal : public BinaryExpression {


public:
    Equal(Expression* newLeft, Expression* newRight) {
        left = newLeft;
        right = newRight;
    }
    virtual double calculate();
};


#endif //SIMULATOR1_EQUAL_H
