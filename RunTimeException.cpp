//
// Created by gal on 12/28/18.
//

#include "RunTimeException.h"

RunTimeException::RunTimeException(string comment)
{
    this->exception_comment = comment;
}

void RunTimeException::printException()
{
    cout << "There was an exception in the program : \"" << this->exception_comment << "\"" << endl;
}
