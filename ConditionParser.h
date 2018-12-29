

#ifndef SIMULATOR1_CONDITIONALPARSER_H
#define SIMULATOR1_CONDITIONALPARSER_H

#include <list>
#include "Parser.h"
#include "Interpreter.h"
#include "Lexer.h"

class ConditionParser : public Command {

Parser* parser;
Interpreter* inter;
vector<string> condition;
vector<string> backupCondition;
vector<string> bracketsContent;

public:
    ConditionParser(Parser* newParser,Interpreter* inter);
    virtual void execute(vector<string>::iterator &it);
    bool conditionSatisfied();
    void runContent();
};


#endif //SIMULATOR1_CONDITIONALPARSER_H

