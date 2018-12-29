//
// Created by gal on 12/28/18.
//

#ifndef SIMULATOR1_RUNTIMEEXCEPTION_H
#define SIMULATOR1_RUNTIMEEXCEPTION_H
#include <string>
#include <iostream>
using namespace std;

class RunTimeException {
    string exception_comment;

public:
    RunTimeException(string comment);
    void printException();
};


#endif //SIMULATOR1_RUNTIMEEXCEPTION_H
