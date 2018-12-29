#include "LoopCommand.h"

LoopCommand::LoopCommand(Parser* Parser,Interpreter* interpreter) : ConditionParser(Parser,interpreter){}


void LoopCommand :: execute(vector<string>::iterator &it) {

    ConditionParser::execute(it);

    while(ConditionParser::conditionSatisfied())
        ConditionParser::runContent();
}