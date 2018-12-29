#include "Command.h"
#include "Parser.h"


class AssignCommand : public Command
{
    Parser* parser;
    void takeOffQuotes(vector<string>::iterator &it);

public:
    AssignCommand(Parser* parser);
    void execute(vector<string>::iterator &it);
};