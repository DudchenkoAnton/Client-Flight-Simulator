#include <mutex>
#include <iostream>
#include "Parser.h"
#include "CommandExpression.h"
#include "DefineVarCommand.h"
#include "ConnectCommand.h"
#include "AssignCommand.h"
#include "ConditionParser.h"
#include "IfCommand.h"
#include "LoopCommand.h"
#include "OpenServerCommand.h"
#include "MutexClass.h"


bool Parser::haveCmd(string commandName)
{
    if (this->commandTbl.count(commandName) != 0)
        return true;
    else
        return false;
}

bool Parser::haveVar(string varName)
{
    if (this->symbolTbl.count(varName) != 0)
        return true;
    else
        return false;
}

bool Parser::variableHavePath(string path)
{
    if (this->pathTbl.count(path) != 0)
        return true;
    else
        return false;
}




Command* Parser::getCmd(string commandName)
{
    if(haveCmd(commandName)) {
        return this->commandTbl[commandName];

    } else {

        throw RunTimeException("Can't give not existing command");
    }

}

double Parser::getVar(string varName)
{
    if(haveVar(varName)) {
        return this->symbolTbl[varName];

    } else {

        throw RunTimeException("Can't give not existing variable");
    }
}

string Parser::getPathByVariable(string variable)
{
    if(variableHavePath(variable)) {
        return this->pathTbl[variable];

    } else {

        throw RunTimeException("Can't give not existing path");
    }
}





void Parser::addVar(string varName,double varValue)
{
    if(!haveVar(varName)) {
        symbolTbl[varName] = varValue;

    } else {

        throw RunTimeException("Try to add existing variable");
    }

}

void Parser::addPath(string varName ,string path)
{
    if(!variableHavePath(varName)) {
        pathTbl[varName] = path;

    } else {

        throw RunTimeException("Can't bind not existing variable");
    }
}



void Parser::assignVarFromCode(string varName, double varValue)
{

    if(haveVar(varName)) {
        if(pathTbl.find(varName) == pathTbl.end()) {
            updateSingleVar(varName, varValue);

        } else {
            sendUpdatedValueToServer(varName, varValue);
        }

    } else {

        throw RunTimeException("Updated variable not exist");
    }

}

void Parser :: updateSingleVar(string varName, double varValue) {

    pthread_mutex_t* mutex = MutexClass::getInstance()->getMutex();
    pthread_mutex_lock(mutex);

    symbolTbl[varName] = varValue;

    pthread_mutex_unlock(mutex);
}


void Parser::assignPath(string var, string path)
{
    pathTbl[var] = path;
}


Expression* Parser :: getNumericExpression(vector<string>::iterator &it) {
    Expression* tempExp;
    vector<string>::iterator tempIt = it;
    int steps = 0;

    vector<string> calcVec;
    while (*tempIt != "\n")
    {
        calcVec.push_back(*tempIt);
        tempIt++;
    }
    calcVec.push_back("\n");
    vector<string>::iterator calcIt = calcVec.begin();
    replaceVariablesByValue(calcIt);

    tempExp = factory.makeExpression(calcIt, steps);
    it += steps;
    return tempExp;
}


void Parser :: replaceVariablesByValue(vector<string>::iterator it) {

    while(*it != "\n") {

        if(haveVar(*it))
            *it = to_string(getVar(*it));

        ++it;
    }
}


void Parser :: setConnectionToServer(int socketId) {

    if(client.isConnected()) {
        throw RunTimeException("Already connected to server");

    } else {

        client.setSocketId(socketId);
    }
}

void Parser :: sendUpdatedValueToServer(string varName, double newValue) {

    if(variableIsBinded(varName)) {
        client.updateVariableValue(pathTbl[varName], newValue);

    } else {

        throw RunTimeException("Trying to update variable that not binded");
    }
}

bool Parser :: checkValidityOfPath(string path) {

    if(!client.isConnected()) {
        throw RunTimeException("Client is not connected");
    } else {

        if(pathIsBinded(path)) {
            return true;
        } else if(client.patIsValid(path)) {
            return true;
        } else {
            return false;
        }
    }
}

bool Parser :: pathIsBinded(string path) {

    for(auto it : pathTbl) {
        if(it.second == path)
            return true;
    }

    return false;
}


bool Parser :: variableIsBinded(string varName) {
    map<string, string>::iterator iter = pathTbl.find(varName);

    if(iter != pathTbl.end()) {
        return true;

    } else {

        return false;
    }
}

map<string, string>* Parser :: getBindedVariables() {
    return &pathTbl;
}

void Parser :: updateBindedVariables(map<string, string> updatedMapPathValue) {


    if(!pathTbl.empty()) {
        for(auto it : pathTbl) {
            if(updatedMapPathValue.find(it.second) != updatedMapPathValue.end()) {
                updateSingleVar(it.first, stoi(updatedMapPathValue[it.second]));
            }
        }
    }

}

map<string, int>* Parser :: getDataXml()
{
    return dataXml.getOrderXml();
}

void Parser::setCmdMap(map<string,Command*> cmdTbl)
{
    this->commandTbl = cmdTbl;
}


bool Parser :: signalFlightGearRunning(bool mode) {

    pthread_mutex_t* mutex = MutexClass::getInstance()->getMutex();
    pthread_mutex_lock(mutex);

    if(mode == true) {
        flightGearRunning = true;
    }

    pthread_mutex_unlock(mutex);

    return flightGearRunning;

}

void Parser :: closeServerThread() {

    cout << "get outside lock" << endl;

    pthread_mutex_t* mutex = MutexClass::getInstance()->getMutex();
    pthread_mutex_lock(mutex);

    cout << "get inside lock" << endl;

    closeServer = true;

    pthread_mutex_unlock(mutex);

    cout << " again get outside lock" << endl;

}

bool Parser :: checkServerClose() {
    bool temp;

    pthread_mutex_t* mutex = MutexClass::getInstance()->getMutex();
    pthread_mutex_lock(mutex);

    cout << "get to check: " << closeServer << endl;


    if(closeServer) {
        temp = true;
    } else {
        temp = false;
    }

    pthread_mutex_unlock(mutex);

    return temp;
}





