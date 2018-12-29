//
// Created by anton on 12/14/18.
//

#ifndef SIMULATOR1_PLUS_H
#define SIMULATOR1_PLUS_H


#include "BinaryExpression.h"

class Plus : public BinaryExpression{

public:
    Plus(Expression* newRight, Expression* newLeft) {
        right = newRight;
        left = newLeft;
    };

    virtual double calculate();



};


#endif //SIMULATOR1_PLUS_H
