
#ifndef SIMULATOR1_IFCOMMAND_H
#define SIMULATOR1_IFCOMMAND_H

#include "ConditionParser.h"

class IfCommand : public ConditionParser {


public:
    IfCommand(Parser* Parser,Interpreter* interpreter);
    virtual void execute(vector<string>::iterator &it);
};

#endif //SIMULATOR1_IFCOMMAND_H