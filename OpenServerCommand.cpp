//
// Created by anton on 12/20/18.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <cmath>
#include "OpenServerCommand.h"
#include "FactoryExpressionNumeric.h"
#include "Lexer.h"


OpenServerCommand ::OpenServerCommand(Parser* dataBase) {
    data = dataBase;
}

/**
 * Method reads arguments, necessary to implement creation of server, that is
 * number of port, and frequency, with which values will be readed from client.
 * For this purpose, it calles function "initializeArguments", and runs thread
 * on static function "runServer" of class Server, that runs server.
 */
void OpenServerCommand :: execute(vector<string>::iterator &it) {
    pthread_t trid;
    ArgumentForServerRunning* arguments = new ArgumentForServerRunning();

    initializeVariables(it);
    arguments->portNum = portNum;
    arguments->frequency = frequency;
    arguments->parser = data;
    pthread_create(&trid, NULL, Server::runServer, (void*) arguments);
}


/**
 * Method reads arguments from text file, tries to create numeric expressions
 * from string that readed. If numeric expressions are valid, and pointers to them,
 * returned by "getNumericExpression" method of class Parses, are not equal to
 * nullptr, it sets member variables, and deletes expressions. Else, it throws
 * exception.
 */
void OpenServerCommand ::initializeVariables(vector<string>::iterator &it) {
        Expression *temp1, *temp2;

        it++;

        temp1 = data->getNumericExpression(it);
        temp2 = data->getNumericExpression(it);

        if(temp1 != NULL && temp2 != NULL) {
            portNum = temp1->calculate();
            frequency = temp2->calculate();

            delete temp1;
            delete temp2;

            if(frequency < 0) {
                throw RunTimeException("Frequency cant be negative");
            } else if(fmod(portNum, 1.0) != 0) {
                throw RunTimeException("Port number must be integer value");
            }

        } else {

            if(temp1 != NULL)
                delete temp1;
            if(temp2 != NULL)
                delete temp2;

            throw RunTimeException("Invalid arguments");
        }

}



