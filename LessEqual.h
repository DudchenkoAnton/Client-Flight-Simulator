//
// Created by anton on 12/21/18.
//

#ifndef SIMULATOR1_LESSEQUAL_H
#define SIMULATOR1_LESSEQUAL_H


#include "BinaryExpression.h"

class LessEqual : public BinaryExpression {


public:
    LessEqual(Expression* newLeft, Expression* newRight) {
        left = newLeft;
        right = newRight;
    }
    virtual double calculate();
};


#endif //SIMULATOR1_LESSEQUAL_H
