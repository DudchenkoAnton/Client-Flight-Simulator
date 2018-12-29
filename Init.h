//
// Created by anton on 12/25/18.
//

#ifndef SIMULATOR1_INIT_H
#define SIMULATOR1_INIT_H

#include <map>
#include "Interpreter.h"
#include "Lexer.h"
#include <iostream>
#include "CommandExpression.h"
#include "OpenServerCommand.h"
#include "DefineVarCommand.h"
#include "ConnectCommand.h"
#include "AssignCommand.h"
#include "IfCommand.h"
#include "LoopCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"



class Init {
    Lexer lex;
    Parser parser;
    Interpreter inter;
    map<string,Command*> commandTbl;

public:
    Init(string src);
    void run();
    ~Init();
};


#endif //SIMULATOR1_INIT_H