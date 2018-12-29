//
// Created by anton on 12/23/18.
//

#ifndef SIMULATOR1_CLIENT_H
#define SIMULATOR1_CLIENT_H

#include "string"
using namespace std;

/**
 * Class Client created for sending new values of variables to FlightGear simulator.
 * Method "setSocketId" sets number of socket, such that we will be able to send messages.
 * Method "pathIsValid" send message to server, to check whether FlightGear have sended path.
 * Method "updateVariableValue" inplements logic that sends commands "set" to FlightGear, with
 * path and new value.
 */
class Client {

    int socketId;
    bool haveSocket;

public:

    Client() : haveSocket(false) {};
    ~Client();
    void setSocketId(int);
    void updateVariableValue(string path, double value);
    string constructBuffer(string path, double value);
    bool isConnected();
    bool patIsValid(string path);

};


#endif //SIMULATOR1_CLIENT_H
