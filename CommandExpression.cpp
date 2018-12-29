#include "CommandExpression.h"

CommandExpression::CommandExpression(Command* c, vector<string>::iterator* newIt)
{
    this->c = c;
    this->it = newIt;
}

double CommandExpression::calculate()
{
    this->c->execute(*this->it);
}