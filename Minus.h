//
// Created by anton on 12/14/18.
//

#ifndef SIMULATOR1_MINUS_H
#define SIMULATOR1_MINUS_H


#include "BinaryExpression.h"

class Minus : public BinaryExpression {

public:

    Minus(Expression* newLeft, Expression* newRight) {
        left = newLeft;
        right = newRight;
    }

    virtual double calculate();

};


#endif //SIMULATOR1_MINUS_H
