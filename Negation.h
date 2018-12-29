//
// Created by anton on 12/14/18.
//

#ifndef SIMULATOR1_NEGATION_H
#define SIMULATOR1_NEGATION_H


#include "UnaryExpression.h"

class Negation : public UnaryExpression {

public:
    Negation(Expression* newExp) {
        expression = newExp;
    }

    virtual double calculate();
    virtual ~Negation() {
        delete expression;
    }
};


#endif //SIMULATOR1_NEGATION_H
