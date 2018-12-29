//
// Created by anton on 12/21/18.
//

#ifndef SIMULATOR1_PRINTCOMMAND_H
#define SIMULATOR1_PRINTCOMMAND_H

#include "Command.h"
#include "Parser.h"
#include <string>
#include <vector>

class PrintCommand : public Command {

    Parser* dataBase;

public:

    PrintCommand(Parser* parser) : dataBase(parser) {};
    /**
    * Method reads argument to command. If argument if variable, it prints value of that variable. If argument
    * is string, it takes off quotes, and prints contents of this string.
    * @param it - pointer to argument
    */
    virtual void execute(vector<string>::iterator &it);
};


#endif //SIMULATOR1_PRINTCOMMAND_H