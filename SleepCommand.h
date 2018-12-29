//
// Created by gal on 12/26/18.
//

#ifndef SIMULATOR1_SLEEPCOMMAND_H
#define SIMULATOR1_SLEEPCOMMAND_H
#include "Command.h"
#include "Expression.h"
#include "Parser.h"
#include "unistd.h"
using namespace std;

class SleepCommand : public Command {

    Parser* parser;

public:
    SleepCommand(Parser* parser);
    /**
    * Method uses method from library "chrono". to send current thread to sleep
    * for number of milliseconds.
    * @param it - pointer to argument string.
    */
    void execute(vector<string>::iterator &it);
};


#endif //SIMULATOR1_SLEEPCOMMAND_H