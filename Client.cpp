//
// Created by anton on 12/23/18.
//

#include <strings.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include "Client.h"
#include "Lexer.h"
#include "RunTimeException.h"

void Client :: setSocketId(int newId) {
    socketId = newId;
    haveSocket = true;
}

void Client :: updateVariableValue(string path, double value) {
    int n;
    char buffer[256];


    if(!haveSocket) {
        throw RunTimeException("Error on sending updated value of variable to server: have no connection to server");
    } else {

        string message = constructBuffer(path, value);
        bzero(buffer,256);

        strcpy(buffer, message.c_str());
        strcat(buffer, "\r\n");

        /* Send message to the server */
        do {
            n = write(socketId, buffer, strlen(buffer));
        } while(n < 0);

        /* Now read server response */
        bzero(buffer,256);
        do {
            n = read(socketId, buffer, 255);
        } while(n < 0);

    }
}

string Client :: constructBuffer(string path, double value) {

    string message = "set " + path + " " + to_string(value);
    return message;
}

bool Client :: isConnected() {

    return haveSocket;
}

bool Client :: patIsValid(string path) {
    int n;
    Lexer lexer;
    char buffer[256];
    vector<string> chunks;
    string temp;

    string message = "get ";
    message.append(path);
    bzero(buffer,256);

    strcpy(buffer, message.c_str());
    strcat(buffer, "\r\n");

    /* Send message to the server */
    do {
        n = write(socketId, buffer, strlen(buffer));
    } while(n < 0);

    /* Now read server response */
    bzero(buffer,256);
    do {
        n = read(socketId, buffer, 255);
    } while(n < 0);

    temp = buffer;
    chunks = lexer.splitLine(temp, " ");
    if(chunks.back() == "(unknown)\r\n/>") {
        return false;
    }

    return true;
}

Client ::~Client() {
    if(haveSocket)
        close(socketId);
}