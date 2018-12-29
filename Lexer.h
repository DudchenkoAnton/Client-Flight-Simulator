#ifndef SIMULATOR1_LEXER_H
#define SIMULATOR1_LEXER_H

#include <list>
#include <vector>
#include <string>
using namespace std;

class Lexer {

public:

    vector<string> getValues(string newLine);
    vector<string> splitLine(string s,string parser);
    string insertParserToken(string s,string parser);
    vector<string> delEmps(vector<string> vec);
};

#endif