#ifndef SIMULATOR1_INTERPRETER_H
#define SIMULATOR1_INTERPRETER_H

#include <map>
#include <vector>
#include <string>
#include <iterator>
#include <list>
#include "Parser.h"
using namespace std;

class Interpreter
{
    Parser* parser;

public:
    Interpreter(Parser* parser);
    void interperate(vector<string> &values);
    void readLine(vector<string>::iterator &it);
};

#endif