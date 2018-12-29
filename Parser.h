#ifndef SIMULATOR1_PARSER_H
#define SIMULATOR1_PARSER_H

#include <map>
#include <vector>
#include <string>
#include <iterator>
#include <list>
#include "Command.h"
#include "Expression.h"
#include "FactoryExpressionNumeric.h"
#include "Client.h"
#include "DataXml.h"
#include <pthread.h>


class Parser {
    map<string,Command*> commandTbl;
    DataXml dataXml;
    map<string,double> symbolTbl;
    map<string,string> pathTbl;
    Client client;
    bool flightGearRunning;
    bool closeServer;

protected:
    FactoryExpressionNumeric factory;

public:
    Parser() : flightGearRunning(false), closeServer(false) {};
    Command* getCmd(string str);
    double getVar(string str);
    string getPathByVariable(string str);
    bool haveCmd(string str);
    bool haveVar(string str);
    bool variableHavePath(string str);
    void addVar(string varName,double varValue);
    void addPath(string var,string path);
    void assignVarFromCode(string varName, double varValue);
    void assignPath(string var, string path);
    Expression* getNumericExpression(vector<string>::iterator &it);
    void replaceVariablesByValue(vector<string>::iterator it);
    void setConnectionToServer(int socketId);
    void sendUpdatedValueToServer(string varName, double newValue);
    bool variableIsBinded(string varName);
    bool checkValidityOfPath(string path);
    map<string, string>* getBindedVariables();
    void updateBindedVariables(map<string, string>);
    map<string, int>* getDataXml();
    bool pathIsBinded(string path);
    void updateSingleVar(string varName, double varValue);
    void setCmdMap(map<string,Command*> cmdTbl);
    bool signalFlightGearRunning(bool mode);
    void closeServerThread();
    bool checkServerClose();
};

#endif