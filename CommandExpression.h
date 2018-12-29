#include "Expression.h"
#include "Command.h"

class CommandExpression : public Expression {
Command * c;
vector<string>::iterator* it;

public:
    CommandExpression(Command* c,vector<string>::iterator* newIt);
    virtual double calculate();
};
