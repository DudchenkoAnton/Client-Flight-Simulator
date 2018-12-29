//
// Created by anton on 12/14/18.
//

#ifndef SIMULATOR1_BINARYEXPRESSION_H
#define SIMULATOR1_BINARYEXPRESSION_H

#include "Expression.h"

class BinaryExpression : public Expression {

protected:
    Expression* right;
    Expression* left;

public:
    virtual ~BinaryExpression(){
        delete right;
        delete left;
    };

};

#endif //SIMULATOR1_BINARYEXPRESSION_H
