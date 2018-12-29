//
// Created by anton on 12/14/18.
//

#include "FactoryExpressionNumeric.h"
#include "NumberExpression.h"
#include "Minus.h"
#include "Plus.h"
#include "Mul.h"
#include "Div.h"
#include "Negation.h"
#include "Less.h"
#include "Greater.h"
#include "GreaterEqual.h"
#include "LessEqual.h"
#include "Equal.h"
#include "NotEqual.h"
#include "RunTimeException.h"

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
Expression* FactoryExpressionNumeric :: makeExpression(vector<string>::iterator &it, int &steps) {

    if(shuntingYard(it, steps)) {
        return constructExpressionFromStack();
    }
    return NULL;
}

/**
 * Method runs logic of shunting yard algorithm. More specific, it goes through the
 * expression, takes next object of expression, and checks whether it number, bracket,
 * operator second operator (in case that last object was operator too), or it is coma,
 * ans act accordingly to it, calling appropriate methods, and changing flags. In the end
 * we get full queue, that consist of operators, ans numbers in proper order, in postfix
 * notation.
 */
bool FactoryExpressionNumeric :: shuntingYard(vector<string>::iterator &it, int &steps){
    bool firstItem = true;
    string tempStr;
    steps = 0;

    while(!endOfExpression && (*it != "\n")) {

        // check if string is number
        if(isNaturalNum(it.operator->()) || isNegativeInteger(*it)) {

            if(isSecondSuccessiveNumber(firstItem)) {
                return true;
            }
            enterNumberToQueue(*it.operator->(), firstItem);
            if(tempOperator != 0) {
                tempStr = tempOperator;
                pushOperator(tempStr);
            }

            tempOperator = 0;
            signAfterOperator = '+';


        // else if string is operator
        } else if(isOperator(*it.operator->())) {
            // id we already saw operator, handle the case
            if(tempOperator != 0) {
                handleSecondOperator(it);

            // else just push it to stack
            } else {
                if(firstItem || firsAfterOpenBracket) {
                    handleFirstStringIsOperator(it);
                    firsAfterOpenBracket = false;

                } else {
                    tempOperator = it.operator->()->at(0);
                }
            }

        // else if it is bracket, handle the case
        } else if(isBracket(*it.operator->())) {

            // if open bracket, just push
            if(it.operator->()->compare("(") == 0) {

                if(tempOperator != 0 || firstItem) {
                    if(tempOperator != 0) {
                        tempStr = tempOperator;
                        stack.push_back(tempStr);
                        tempOperator =0;
                    }
                    stack.push_back(*it.operator->());
                    numberBrackets++;
                    firsAfterOpenBracket = true;

                } else if(tempOperator == 0 && numberBrackets == 0){
                    return true;

                } else if(tempOperator == 0 && numberBrackets > 0) {

                    throw RunTimeException("Error: too many brackets in numeric expression");
                }

            // else call function that handles it
            } else {
                handleClosureBracket();
            }

            tempOperator = 0;
            signAfterOperator = '+';

        } else if(it.operator->()->compare(",") == 0) {

            // if we saw before operator - incorrect syntax
            if(tempOperator != 0 && numberBrackets != 0)
                throw RunTimeException("Error: invalid numeric expression");
            // else if number of variable - end of expression
            else
                endOfExpression = true;
        }
        // else if it is non if above, it is incorrect.
        else {
            // if it first string, means that just not numeric expression
            if(firstItem)
                return false;
            // else if not first, means that incorrect syntax
            else
                throw RunTimeException("Error: invalid numeric expression");
        }

        firstItem = false;
        it++;
        steps++;
    }

    while(!stack.empty()) {
        queue.push_front(stack.back());
        stack.pop_back();
    }
}

void FactoryExpressionNumeric :: enterNumberToQueue(string number, bool &firstItem) {

    // if we seen operator before, it's OK
    if(tempOperator != 0) {

        // if sign after operator is minus, change sign of a number
        if(signAfterOperator == '-') {
            changeSignOfNumber(number);
        }
        queue.push_front(number);

    } else if(firstItem || firsAfterOpenBracket) {
        queue.push_front(number);

    } else if(tempOperator == 0 && signAfterOperator == '-') {
        changeSignOfNumber(number);
        queue.push_front(number);
    }

    firsAfterOpenBracket = false;
}

bool FactoryExpressionNumeric ::  isSecondSuccessiveNumber(bool &firstItem) {

    if(tempOperator == 0 && (!firstItem && !firsAfterOpenBracket && signAfterOperator == '+')) {
        return true;
    }

    return false;
}

void FactoryExpressionNumeric :: handleFirstStringIsOperator(vector<string>::iterator &it) {


    if(*it == "-") {
        tempOperator = 0;
        signAfterOperator = '-';

    } else if(*it == "+") {
        return;
    } else {

        throw RunTimeException("First string is operator");
    }
}


// simple check if string is bracket
bool FactoryExpressionNumeric :: isBracket(const string &str) {

    if(str == "(" || str == ")")
        return true;

    return false;
}

// checks if string is one of operators
bool FactoryExpressionNumeric :: isOperator(const string &str) {

    if(str.length())
        if(str == "+" || str == "-" || str == "/" || str == "*" || str == "<" || str == ">"
        || str == ">=" || str == "<=" || str == "==" || str == "!=")
            return true;

    return false;
}

// checks if it is number equals of greater than zero
bool FactoryExpressionNumeric :: isNaturalNum(const string *str) {

    bool seenDot = false;

    for(int i = 0; i < str->length(); i++) {
        if(!seenDot && str->at(i) == '.') {
            seenDot = true;
        }
        else if(str->at(i) < '0' || str->at(i) > '9') {
            return false;
        }

    }

    return true;
}

// handles case when we see second operator after operator
void FactoryExpressionNumeric :: handleSecondOperator(vector<string>::iterator &it) {

    // plus after some operator don't change anything
    if(it.operator->()->compare("+") == 0) {
        return;

    // minus after operator changes
    } else if(it.operator->()->compare("-") == 0) {

        // if first operator was plus, it changes sign
        if(tempOperator == '+')
            tempOperator = '-';
        // second minus after minus is plus
        else if(tempOperator == '-')
            tempOperator = '+';
        // the same thing
        else if(tempOperator == '*' || tempOperator == '/') {
            if(signAfterOperator == '+')
                signAfterOperator = '-';
            else if(signAfterOperator == '-')
                signAfterOperator = '+';
        }
        return;

    } else if(it.operator->()->compare("*") == 0 || it.operator->()->compare("/") == 0) {
        throw RunTimeException("Error: invalid numeric expression - twi binary operators in sequence");
    }
}

// push operator to stack
void FactoryExpressionNumeric ::  pushOperator(string tempOperatorStr) {


    if (stack.empty()) {
        stack.push_back(tempOperatorStr);

    // if there is operator with greater precedence, push all to queue, and push current operator to stack
    } else if(precedence[stack.at(stack.size() - 1)] > precedence[tempOperatorStr]) {

        while(!stack.empty()) {
            queue.push_front(stack.back());
            stack.pop_back();
        }
        stack.push_back(tempOperatorStr);

    // else just push to stack
    } else if(precedence[stack.at(stack.size() - 1)] <= precedence[tempOperatorStr]) {

        stack.push_back(tempOperatorStr);
    }
}

// if there is closure bracket, put all operators in qeue, till u see opening brace
void FactoryExpressionNumeric :: handleClosureBracket() {

    while(stack.back() != "(") {
        queue.push_front(stack.back());
        stack.pop_back();

        if(stack.empty())
            throw RunTimeException("Error: invalid numeric expression - missing opening bracket");
    }

    stack.pop_back();
    numberBrackets--;
}


/**
 * Method called from makeExpression method, after executing shuntingYard method. It have ready
 * queue, and all it does, it takes some string from queue, looks whether it is number or operator,
 * and accordingly of thar, created proper type of expression. When queue ie empty, method returns
 * pointer to created Expression.
 * @return  = pointer to expression.
 */
Expression* FactoryExpressionNumeric :: constructExpressionFromStack() {
    vector<Expression*> stackOfExp;
    Expression* tempExp1;
    Expression* tempExp2;
    Expression* tempExp3;

    while(!queue.empty()) {
        string tempStr = queue.back();
        queue.pop_back();

        if(isPositiveInteger(tempStr)) {
            tempExp1 = new NumberExpression(tempStr);
            stackOfExp.push_back(tempExp1);


        } else if(isNegativeInteger(tempStr)) {
            tempStr.erase(0, 1);
            tempExp1 = new NumberExpression(tempStr);
            tempExp2 = new Negation(tempExp1);

            stackOfExp.push_back(tempExp2);

        } else {

            tempExp2 = stackOfExp.back();
            stackOfExp.pop_back();
            tempExp1 = stackOfExp.back();
            stackOfExp.pop_back();

            if(tempStr == "+") {
                tempExp3 = new Plus(tempExp1, tempExp2);
                stackOfExp.push_back(tempExp3);
            }
            else if(tempStr == "-") {
                tempExp3 = new Minus(tempExp1, tempExp2);
                stackOfExp.push_back(tempExp3);
            }
            else if(tempStr == "*") {
                tempExp3 = new Mul(tempExp1, tempExp2);
                stackOfExp.push_back(tempExp3);
            }
            else if(tempStr == "/") {
                tempExp3 = new Div(tempExp1, tempExp2);
                stackOfExp.push_back(tempExp3);
            }
            else if(tempStr == "<") {
                tempExp3 = new Less(tempExp1, tempExp2);
                stackOfExp.push_back(tempExp3);
            }
            else if(tempStr == ">") {
                tempExp3 = new Greater(tempExp1, tempExp2);
                stackOfExp.push_back(tempExp3);
            }
            else if(tempStr == ">=") {
                tempExp3 = new GreaterEqual(tempExp1, tempExp2);
                stackOfExp.push_back(tempExp3);
            }
            else if(tempStr == "<=") {
                tempExp3 = new LessEqual(tempExp1, tempExp2);
                stackOfExp.push_back(tempExp3);
            }
            else if(tempStr == "==") {
                tempExp3 = new Equal(tempExp1, tempExp2);
                stackOfExp.push_back(tempExp3);
            }
            else if(tempStr == "!=") {
                tempExp3 = new NotEqual(tempExp1, tempExp2);
                stackOfExp.push_back(tempExp3);
            }

        }

    }

    tempExp1 = stackOfExp.back();
    stackOfExp.pop_back();
    return tempExp1;
}


bool FactoryExpressionNumeric :: isPositiveInteger(const string num) {
    if(isNaturalNum(num)) {
        return true;
    }

    return false;
}

bool FactoryExpressionNumeric :: isNegativeInteger(const string num) {

    string temp = num;

    if(num.length() > 1) {
        temp.erase(0, 1);
        return isPositiveInteger(temp);
    }

    return false;
}

bool FactoryExpressionNumeric :: isNaturalNum(const string str) {

    bool seenDot = false;

    for(int i = 0; i < str.length(); i++) {
        if(!seenDot && str.at(i) == '.') {
            seenDot = true;
        }
        else if(str.at(i) < '0' || str.at(i) > '9') {
            return false;
        }

    }

    return true;
}


void  FactoryExpressionNumeric :: changeSignOfNumber(string &number) {

    if(isPositiveInteger(number)) {
        number = "-" + number;

    } else if(isNegativeInteger(number)) {

        number.erase(0, 1);
    }

}






