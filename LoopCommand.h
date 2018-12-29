#ifndef SIMULATOR1_LOOPCOMMAND_H
#define SIMULATOR1_LOOPCOMMAND_H

#include "ConditionParser.h"

class LoopCommand : public ConditionParser {

public:
    LoopCommand(Parser* Parser,Interpreter* interpreter);
    virtual void execute(vector<string>::iterator &it);
};

#endif