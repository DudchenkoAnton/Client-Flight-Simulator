#ifndef SIMULATOR1_SERVER_H
#define SIMULATOR1_SERVER_H


#include "Parser.h"

struct ArgumentForServerRunning {
    double portNum;
    double frequency;
    Parser* parser;
};

struct ArgumentForVarUpdating {
    string buffer;
    Parser* parser;
};


class Server {

public:
    /**
    * Method is created to run in it's own thread, hence it created static. It creates
    * server, and accepts connection from FlightGear simulator, using regular procedure
    * for such aims. Then, when connection initialized, it enters while loop, where it
    * reads buffer of socket, where stored all new values for variables, that appear in
    * xml file. Then it calls for another method, that sends this valies to our program.
    * Each iteration, it calls method "checkServerClose" that returns true, if it needed
    * to break loop, and end thread.
    * @param arg - set of arguments.
    * @return - void pointer.
    */
    static void* runServer(void* arg);
    /**
    * Method creates map of path and updated value, and sends it to parser. To gain this,
    * it creates map of updated variables, that it readed from socket, using method "split line"
    * of class Lexer, map orderXml, that holds path, and order that this path appears in xml file.
    * Then it gets from parses map of binded values, and manipulating with this three maps allow
    * us to get reulting map with path of variables, that needed to update (that defined in out
    * program, and binded to these paths), and new values, that we got ftom FlightGear simulator.
    * @param argument - struct of arguments.
    * @return - pointer to void.
    */
    static void* updateVariables(void* argument);

};


#endif //SIMULATOR1_SERVER_H
