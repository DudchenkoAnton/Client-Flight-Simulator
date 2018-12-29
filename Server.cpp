//
// Created by anton on 12/27/18.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <iostream>
#include "Server.h"
#include "MutexClass.h"
#include "Lexer.h"
#include <string>

/**
 * Method is created to run in it's own thread, hence it created static. It creates
 * server, and accepts connection from FlightGear simulator, using regular procedure
 * for such aims. Then, when connection initialized, it enters while loop, where it
 * reads buffer of socket, where stored all new values for variables, that appear in
 * xml file. Then it calls for another method, that sends this valies to our program.
 * Eqch iteration, it calls method "checkServerClose" that returns true, if it needed
 * to break loop, and end thread.
 * @param arg - set of arguments.
 * @return - void pointer.
 */
void* Server :: runServer(void* arg) {

    ArgumentForServerRunning* arguments = (ArgumentForServerRunning*) arg;
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int  n, temp;
    Parser* parser = arguments->parser;
    ArgumentForVarUpdating* forVarUpdating = new ArgumentForVarUpdating();
    forVarUpdating->parser = parser;




    /* First call to socket() function */
    do{
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
    } while(n < 0);


    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = arguments->portNum;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    do {
        temp = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    } while(temp < 0);

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    pthread_mutex_t* mutex = MutexClass::getInstance()->getMutex();
    pthread_mutex_lock(mutex);

    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);

    pthread_mutex_unlock(mutex);

    parser->signalFlightGearRunning(true);

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    while(true) {
        /* If connection is established then start communicating */
        bzero(buffer,256);
        do {
            n = read( newsockfd,buffer,255 );
        } while(n < 0);

        /* Write a response to the client */
        do {
            n = write(newsockfd,"I got your message",18);
        } while(n < 0);

        string str = buffer;
        forVarUpdating->buffer = str;
        Server::updateVariables(forVarUpdating);

        if(parser->checkServerClose()) {
            close(sockfd);
            break;
        }

        usleep(1 / arguments->frequency * 1000);
    }
}

/**
 * Method creates map of path and updated value, and sends it to parser. To gain this,
 * it creates map of updated variables, that it readed from socket, using method "split line"
 * of class Lexer, map orderXml, that holds path, and order that this path appears in xml file.
 * Then it gets from parses map of binded values, and manipulating with this three maps allow
 * us to get resulting map with path of variables, that needed to update (that defined in out
 * program, and binded to these paths), and new values, that we got ftom FlightGear simulator.
 * @param argument - struct of arguments.
 * @return - pointer to void.
 */
void* Server :: updateVariables(void* argument) {
    string path, newValue, buffer;
    int i = 1;
    Lexer lexer;
    Parser* parser;
    ArgumentForVarUpdating* arg = (ArgumentForVarUpdating*) argument;

    buffer = arg->buffer;
    parser = arg->parser;


    vector<string> variablesFromServer = lexer.splitLine(buffer, ",");
    map<string, int>* orderXml = parser->getDataXml();
    map<string, string>* bindedVariables = parser->getBindedVariables();
    map<int, string> valuesToUpdate;
    map<string, string> resultingMap;

    if(!(*bindedVariables).empty()) {

        for(const auto it : *bindedVariables) {

            if(it == (*bindedVariables->end())) {
                break;
            }

            path = it.second;
            if(orderXml->find(path) != orderXml->end() && valuesToUpdate.find((*orderXml)[path]) == valuesToUpdate.end()) {
                valuesToUpdate[(*orderXml)[path]] = path;
            }
        }
    }

    for(auto it : variablesFromServer) {

        if(valuesToUpdate.find(i) != valuesToUpdate.end()) {
            resultingMap[valuesToUpdate[i]] = it;
        }
        i++;
    }

    parser->updateBindedVariables(resultingMap);
}