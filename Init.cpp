#include "Init.h"
#include <iostream>
#include <fstream>
#include <sstream>

// We create a command table in the init func ctor
Init::Init(string src) :  inter(&parser)
{

    Command *OdsCmd = new OpenServerCommand(&parser);
    commandTbl["openDataServer"] = OdsCmd;

    Command *CntCmd = new ConnectCommand(&parser);
    commandTbl["connect"] = CntCmd;

    Command *DvCmd = new DefineVarCommand(&parser);
    commandTbl["var"] = DvCmd;

    Command *ifCmd = new IfCommand(&parser,&inter);
    commandTbl["if"] = ifCmd;

    Command *LpCommand = new LoopCommand(&parser,&inter);
    commandTbl["while"] = LpCommand;

    Command *AsgCommand = new AssignCommand(&parser);
    commandTbl["="] = AsgCommand;

    Command *PrintCmd = new PrintCommand(&parser);
    commandTbl["print"] = PrintCmd;

    Command *SleepCmd = new SleepCommand(&parser);
    commandTbl["sleep"] = SleepCmd;
};

// This Function runs the program
void Init::run()
{
    this->parser.setCmdMap(this->commandTbl);
    vector<string> fullCode;
    vector<string> newVec;
    string newLine;

    ifstream infile("code.txt");

    if(!infile.is_open())
    {
        ofstream outfile("code.txt");
        outfile << "";
        ifstream infile("code.txt");
    }

    // We insert every word in the file into a string vector
    while (getline(infile,newLine)) {
        newVec = lex.getValues(newLine);
        for (vector<string>::iterator it = newVec.begin(); it != newVec.end(); it++)
        {
            fullCode.push_back(*it);
        }
        // We push \n in the end of every line so we will know when each command ends
        fullCode.push_back("\n");
    }

    // We intreperte all the comannds in the input file one by one
    inter.interperate(fullCode);
    infile.close();
    parser.closeServerThread();
    usleep(500);

}

// In the dtor we delete all the commands we aloocated in the command table
Init::~Init()
{
    for (map<string, Command *>::iterator it = this->commandTbl.begin(); it != this->commandTbl.end(); it++)
    {
        delete(it->second);
    }
}