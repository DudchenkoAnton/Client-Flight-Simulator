//
// Created by anton on 12/18/18.
//

#ifndef SIMULATOR1_LESS_H
#define SIMULATOR1_LESS_H

#include "BinaryExpression.h"

class Less : public BinaryExpression {


public:
    Less(Expression* newLeft, Expression* newRight) {
        left = newLeft;
        right = newRight;
    }
    virtual double calculate();
};


#endif //SIMULATOR1_LESS_H
