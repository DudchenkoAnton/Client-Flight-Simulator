//
// Created by anton on 12/22/18.
//

#ifndef SIMULATOR1_CONNECTCOMMAND_H
#define SIMULATOR1_CONNECTCOMMAND_H


#include "Parser.h"

/**
 * Purpose of class, is to create connection between our program, and server of FlightGear.
 */
class ConnectCommand : public Command {

    Parser* parser;
    string serverIp;
    int serverPortNum;
    int socketId;

    void createConnectionWithServer();
    void initializeArguments(vector<string>::iterator &it);
    void incrementIterator(vector<string>::iterator &it);

public:

    ConnectCommand(Parser* newParser) : parser(newParser), serverPortNum(0), socketId(0) {};

    /**
    * Method starts from checking whether was created server, and if created
    * connection between server and FlightGear. If it is - method proceeds in
    * execution, else it waits for it. Then method initializes arguments, and
    * creates connestion with server of FlightGear simulator. Then it calls
    * for method of class Parser, to signal that connection between client and
    * server was created.
    * @param it
    */
    virtual void execute(vector<string>::iterator &it);
};


#endif //SIMULATOR1_CONNECTCOMMAND_H
