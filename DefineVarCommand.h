#include "Parser.h"

class DefineVarCommand : public Command {
    Parser* parser;
    void takeOffQuotes(vector<string>::iterator &it);
public:
    DefineVarCommand(Parser* parser);
    virtual void execute(vector<string>::iterator &it);
};

