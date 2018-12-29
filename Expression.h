//
// Created by anton on 12/14/18.
//

#ifndef SIMULATOR1_EXPRESSION_H
#define SIMULATOR1_EXPRESSION_H

class Expression {

public:
    virtual double calculate()=0;
    virtual ~Expression(){};
};

#endif //SIMULATOR1_EXPRESSION_H
