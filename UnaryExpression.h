//
// Created by anton on 12/14/18.
//

#ifndef SIMULATOR1_UNARYEXPRESSION_H
#define SIMULATOR1_UNARYEXPRESSION_H

#include "Expression.h"

class UnaryExpression : public Expression {

protected:
    Expression* expression;
    virtual ~UnaryExpression(){};

};

#endif //SIMULATOR1_UNARYEXPRESSION_H
