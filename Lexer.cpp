#include <iostream>
#include "Lexer.h"

//This function inserts spacthe parser character before and after special characters so the splitter will work correctly
string Lexer::insertParserToken(string s,string parser)
{
    int i = 0;
    bool isQuote = false;
    string ans = "";

    while(i < s.size())
    {
        if (s[i] == '\"')
        {
            if (!isQuote)
                isQuote = true;
            else
                isQuote = false;
        }

        if (!isQuote && (((s[i] == '=') || (s[i] == '>') || (s[i] == '<') || (s[i] == '!')) && (s[i+1] == '=')))
        {
            ans += s[i];
            ans += s[i+1];
            i++;
            i++;
        }

        if (!isQuote && ((s[i] == '=') || (s[i] == '+') || (s[i] == '-') || (s[i] == '*') ||
                         (s[i] == '/') || (s[i] == '%') ||  (s[i] == '(') || (s[i] == ')') ||
                         (s[i] == ',') || (s[i] == '{') || (s[i] == '}')))
        {
            ans += parser + s[i] + parser;
        }

        else
        {
            if(s[i] != 0)
                ans += s[i];
        }
        i++;
    }

    return ans;
}

//This function splits the string values between th parser into a vector
vector<string> Lexer::splitLine(string s,string parser)
{
    vector<string> vec;

    while(s.size() > 0)
    {
        int i = s.find(parser);
        if (i != string::npos)
        {
            vec.push_back(s.substr(0, i)); //We push the string between the parser appearences into the vector
            s = s.substr(i + parser.size());
            if (s.size() == 0)
            {
                vec.push_back(s);
            }
        }

        else
        {
            vec.push_back(s);
            s="";
        }
    }
    return vec;
}

//This function deletes empty values inside the vector
vector<string> Lexer::delEmps(vector<string> vec)
{
    vector<string> ans;
    for (vector<string>::iterator it = vec.begin(); it != vec.end(); it++)
    {
        if (*it != "")
            ans.push_back(*it);
    }
    return ans;
}

//This function gets a line as a string and returns it's values in a vector
vector<string> Lexer::getValues(string line)
{
    string parsedString = insertParserToken(line," ");
    vector<string> rawVec = splitLine(parsedString," ");
    vector<string> values = delEmps(rawVec);
    return values;
}