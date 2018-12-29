#include <iostream>
#include <fstream>
#include <sstream>
#include "Init.h"
#include "RunTimeException.h"

int main(int argc, char* argv[])
{
    //If we get invalid amount of arguments we end the program
    if (argc != 2)
    {
        cout << "The program got invalid amount of arguments" << endl;
        return 1;
    }

    string src = argv[1];

    //If we receive the correct amount of input we run the program
    if (argc == 2)
    {
        try {
            Init init(src);
            init.run();
        }

            // if there was an exception through the running of the program we will print the relevent excepition comment
        catch (RunTimeException r) {
            r.printException();
        }
    }

    return 0;
}