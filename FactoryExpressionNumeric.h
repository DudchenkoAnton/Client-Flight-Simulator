//
// Created by anton on 12/14/18.
//

#ifndef SIMULATOR1_FACTORYEXPRESSIONNUMERIC_H
#define SIMULATOR1_FACTORYEXPRESSIONNUMERIC_H


#include "Expression.h"
//#include "Parser.h"
#include <vector>
#include <list>
#include <string>
#include <map>
#include "RunTimeException.h"

using namespace std;

/**
 * Class creates creates numerix expression, using shanting yard algorithm.
 */
class FactoryExpressionNumeric {

    bool endOfExpression;
    int numberBrackets;
    char tempOperator;
    char signAfterOperator;
    vector<string> stack;
    list<string>  queue;
    map <string, int> precedence;
    bool firsAfterOpenBracket;


public:

    FactoryExpressionNumeric() : tempOperator(0), signAfterOperator('+'), endOfExpression(false), numberBrackets(0) {
        precedence[">"] = 1;
        precedence["<"] = 1;
        precedence[">="] = 1;
        precedence["<="] = 1;
        precedence["=="] = 1;
        precedence["!="] = 1;
        precedence["*"] = 3;
        precedence["/"] = 3;
        precedence["+"] = 2;
        precedence["-"] = 2;
        precedence["("] = 0;
    };

    /**
    * Method constructs numeric expression, returning pointer to that expression, that created
    * on heap. Firstly, it calls for shuntingTard method, that proccesses strong of expression,
    * and ends up with properly filled queue in postfix notation. Also, it returns true, if expression
    * is valid, and false otherwise. Then, if expression is valid, method calls for constructExpression
    * method, that takes each time from queue some objects, and iteratively make from them expressions.
    * After all, it returns pointer to recently created Expression.
    * @param it - pointer to expression.
    * @param steps - number of steps that was done in iteration through expression.
    * @return - pointer to Expression.
    */
    Expression* makeExpression(vector<string>::iterator &it, int &steps);

    /**
    * Method runs logic of shunting yard algorithm. More specific, it goes through the
    * expression, takes next object of expression, and checks whether it number, bracket,
    * operator second operator (in case that last object was operator too), or it is coma,
    * ans act accordingly to it, calling appropriate methods, and changing flags. In the end
    * we get full queue, that consist of operators, ans numbers in proper order, in postfix
    * notation.
    */
    bool shuntingYard(vector<string>::iterator &it, int &steps);

    /**
    * Method called from makeExpression method, after executing shuntingYard method. It have ready
    * queue, and all it does, it takes some string from queue, looks whether it is number or operator,
    * and accordingly of thar, created proper type of expression. When queue ie empty, method returns
    * pointer to created Expression.
    * @return  = pointer to expression.
    */
    Expression* constructExpressionFromStack();

    void handleSecondOperator(vector<string>::iterator &it);
    bool isOperator(const string &str);
    bool isBracket(const string &str);
    bool isNaturalNum(const string *str);

    void pushOperator(string tempOperator);
    void handleClosureBracket();

    bool isPositiveInteger(const string num);
    bool isNegativeInteger(string num);

    void handleFirstStringIsOperator(vector<string>::iterator &it);
    void enterNumberToQueue(string number, bool &firstItem);
    bool isSecondSuccessiveNumber(bool &firstItem);
    bool isNaturalNum(const string num);
    void changeSignOfNumber(string &number);

};


#endif //SIMULATOR1_FACTORYEXPRESSIONNUMERIC_H
