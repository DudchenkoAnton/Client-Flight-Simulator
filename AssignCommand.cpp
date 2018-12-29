#include <iostream>
#include "AssignCommand.h"

AssignCommand::AssignCommand(Parser* parser)
{
    this->parser = parser;
}

// This command will be used in case of assigning a value to an already created variable
void AssignCommand::execute(vector<string>::iterator &it)
{
    string varName = *(it-1); // we go one step ack on the vector to get the variable name
    if(!parser->haveVar(varName))
    {
        throw RunTimeException("Error in assigning value to variable: have no such variable");
    }

    it++;
    if(*it == "bind") // We check if it is a bind assigning or regular assigning
    {
        it++;
        takeOffQuotes(it);
        if (this->parser->variableHavePath(*it))
        {
            string path = parser->getPathByVariable(*it);
            this->parser->assignPath(varName, path);
        }

        else if(parser->checkValidityOfPath(*it))
        {
            this->parser->addPath(varName,*it);
        }

        else
        {
            throw RunTimeException("Error in binding to existing variable: path is invalid");
        }

    }
    else
    {
        Expression* varValue = this->parser->getNumericExpression(it);
        if(varValue != NULL)
        {
            // We update the symbol table and the server table with the new var value
            this->parser->assignVarFromCode(varName, varValue->calculate());
            delete varValue;
        }
        else
        {
            throw RunTimeException("Error in assigning value to variable: trying to assign not numeric value");
        }
    }

    it++;
}


void AssignCommand :: takeOffQuotes(vector<string>::iterator &it) {
    unsigned long length = it.operator->()->length();

    if(length >= 2 && it.operator->()->at(0) == '\"' && it.operator->()->at(length - 1) == '\"') {
        it.operator->()->erase(0,1);
        it.operator->()->erase(it.operator->()->length() - 1, 1);
    }
}