//
// Created by anton on 12/22/18.
//

#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <netdb.h>
#include <strings.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <vector>
#include "ConnectCommand.h"


using namespace std;

/**
 * Method starts from checking whether was created server, and if created
 * connection between server and FlightGear. If it is - method proceeds in
 * execution, else it waits for it. Then method initializes arguments, and
 * creates connestion with server of FlightGear simulator. Then it calls
 * for method of class Parser, to signal that connection between client and
 * server was created.
 * @param it
 */
void ConnectCommand :: execute(vector<string>::iterator &it) {

    while(!parser->signalFlightGearRunning(false)) {
        usleep(100);
    }

    initializeArguments(it);
    createConnectionWithServer();
    parser->setConnectionToServer(socketId);
    it++;
}

void ConnectCommand :: initializeArguments(vector<string>::iterator &it) {
    Expression* portNumberExpression;

    incrementIterator(it);
    serverIp = *it;
    incrementIterator(it);
    portNumberExpression = parser->getNumericExpression(it);

    if(portNumberExpression == NULL) {
        throw RunTimeException("Error in connection to FlightGear: expected numeric expression of port");
    }

    serverPortNum = (int) portNumberExpression->calculate();
    delete portNumberExpression;
}


void ConnectCommand :: incrementIterator(vector<string>::iterator &it) {

    it++;
    if(*it == "\n") {
        throw RunTimeException("Invalid syntax in connect command: expected more arguments");
    }

}

void ConnectCommand :: createConnectionWithServer() {
    int bind;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    /* Create a socket point */
    do {
        socketId = socket(AF_INET, SOCK_STREAM, 0);
    } while (socketId < 0);

    do{
        server = gethostbyname(serverIp.c_str());
    } while(server == NULL);


    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(serverPortNum);

    /* Now connect to the server */
    do {
        bind = connect(socketId, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    } while(bind < 0);
}


