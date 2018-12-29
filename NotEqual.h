//
// Created by anton on 12/21/18.
//

#ifndef SIMULATOR1_NOTEQUAL_H
#define SIMULATOR1_NOTEQUAL_H


#include "BinaryExpression.h"

class NotEqual : public BinaryExpression {


public:
    NotEqual(Expression* newLeft, Expression* newRight) {
        left = newLeft;
        right = newRight;
    }
    virtual double calculate();

};


#endif //SIMULATOR1_NOTEQUAL_H
