//
// Created by anton on 12/21/18.
//

#include <iostream>
#include "PrintCommand.h"

/**
 * Method reads argument to command. If argument if variable, it prints value of that variable. If argument
 * is string, it takes off quotes, and prints contents of this string.
 * @param it - pointer to argument
 */
void PrintCommand ::execute(vector<string>::iterator &it) {
    Expression* tempExp;

    it++;
    string str = *it;

    if(str.at(0) == '\"' && str.at(str.length() - 1) == '\"') {
        str.erase(0, 1);
        str.erase(str.length() - 1, 1);

        cout << str << endl;

    } else if( dataBase->haveVar(*it)) {

        cout << dataBase->getVar(*it) << endl;
        it++;
    } else {

        tempExp = dataBase->getNumericExpression(it);
        if(tempExp != NULL)
            cout << tempExp->calculate() << endl;
        else {
            throw RunTimeException("Error syntax, throw exception");
        }
    }

    it++;

}