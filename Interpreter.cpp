#include "Interpreter.h"
#include "CommandExpression.h"
#include "NumberExpression.h"

Interpreter::Interpreter(Parser* parser)
{
    this->parser = parser;
}

// This function get the code parts and interpretes them according to the commnd rules defind in the program
void Interpreter::interperate(vector<string> &values)
{
    vector<string>::iterator it = values.begin();
    vector<string>::iterator end = values.end();

    // We will keep read command form code part until we will reach the end of the code
    while ((it != end) && (!it.operator->()->empty()))
    {
        readLine(it);

        // If we get to a \n we will skip it to get to the next command
        if (*it == "\n") {
            it++;
        }
    }
}

// This function reads a line from the code part and interperet it into a command and it's values
void Interpreter:: readLine(vector<string>::iterator &it)
{

    // If the word in the iterator is a name of a command we will create an command expression which will
    // hold a command of the type of the word in the iterator and activate it according to the paremters that
    // are found next to it in the code part and delete it afterwords to avoid memory leak
    if (parser->haveCmd(*it)) {
        Command* cmd = parser->getCmd(*it);
        CommandExpression *CmdExp = new CommandExpression(cmd, &it);
        CmdExp->calculate();
        delete CmdExp;
    }
    // If inside the iterator the is a variable form the symbol table we check if the next word in the
    // code part is "=" sign if it is we continue in the code and activate the assign command in the next iteration
    // else we throw an exception
    else if (parser->haveVar(*it)){

        it++;
        if (*it != "=")
        {
            throw RunTimeException("Error: command not recognized");
        }
    }
    // if we see an "}" we will skip it
    else if (*it == "}")
    {
        it++;
    }
    // if we havn't found none of the above we will throw an exception
    else
    {

        throw RunTimeException("Error: command not recognized");
    }
}