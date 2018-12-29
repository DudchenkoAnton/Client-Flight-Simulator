#include "IfCommand.h"

IfCommand::IfCommand(Parser* Parser,Interpreter* interpreter) : ConditionParser(Parser,interpreter) {}


void IfCommand :: execute(vector<string>::iterator &it) {

    ConditionParser::execute(it);

    if(ConditionParser::conditionSatisfied())
         ConditionParser::runContent();
}
