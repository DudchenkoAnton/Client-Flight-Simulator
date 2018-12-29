//
// Created by gal on 12/26/18.
//

#include <iostream>
#include <chrono>
#include <thread>
#include "SleepCommand.h"

SleepCommand::SleepCommand(Parser* parser)
{
    this->parser = parser;
}

/**
 * Method uses method from library "chrono". to send current thread to sleep
 * for number of milliseconds.
 * @param it - pointer to argument string.
 */
void SleepCommand::execute(vector<string>::iterator &it)
{
    it++;
    double timeOfSleep = 0;
    Expression* varValue = this->parser->getNumericExpression(it);
    if(varValue != NULL) {
        timeOfSleep = varValue->calculate();
    }
    this_thread::sleep_for(std::chrono::milliseconds((int) timeOfSleep));
}