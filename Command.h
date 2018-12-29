//
// Created by anton on 12/20/18.
//


#ifndef SIMULATOR1_COMMAND_H
#define SIMULATOR1_COMMAND_H

#include <string>
#include <vector>

using namespace std;

class Command {

public:

    virtual void execute(vector<string>::iterator &it) = 0;


};

#endif //SIMULATOR1_COMMAND_H

