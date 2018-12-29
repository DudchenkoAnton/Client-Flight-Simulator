//
// Created by anton on 12/20/18.
//

#ifndef SIMULATOR1_OPENSERVERCOMMAND_H
#define SIMULATOR1_OPENSERVERCOMMAND_H


#include <string>
#include <vector>
#include "Command.h"
#include "Parser.h"
#include "DataXml.h"
#include "Server.h"


class OpenServerCommand : public Command {

    double frequency;
    double portNum;
    Parser* data;

    /**
    * Method reads arguments from text file, tries to create numeric expressions
    * from string that readed. If numeric expressions are valid, and pointers to them,
    * returned by "getNumericExpression" method of class Parses, are not equal to
    * nullptr, it sets member variables, and deletes expressions. Else, it throws
    * exception.
    */
    void initializeVariables(vector<string>::iterator &it);

public:


    OpenServerCommand(Parser* dataBase);
    /**
    * Method reads arguments, necessary to implement creation of server, that is
    * number of port, and frequency, with which values will be readed from client.
    * For this purpose, it calles function "initializeArguments", and runs thread
    * on static function "runServer" of class Server, that runs server.
    */
    void execute(vector<string>::iterator &it);

};


#endif //SIMULATOR1_OPENSERVERCOMMAND_H
