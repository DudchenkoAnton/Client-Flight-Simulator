//
// Created by anton on 12/21/18.
//

#ifndef SIMULATOR1_GREATEREQUAL_H
#define SIMULATOR1_GREATEREQUAL_H


#include "Expression.h"
#include "BinaryExpression.h"

class GreaterEqual : public BinaryExpression {


public:
    GreaterEqual(Expression* newLeft, Expression* newRight) {
        left = newLeft;
        right = newRight;
    }
    virtual double calculate();
};


#endif //SIMULATOR1_GREATEREQUAL_H
