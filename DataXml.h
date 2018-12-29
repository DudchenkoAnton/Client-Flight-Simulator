//
// Created by anton on 12/24/18.
//

#ifndef SIMULATOR1_DATAXML_H
#define SIMULATOR1_DATAXML_H

#include <map>
using namespace std;


class DataXml {

    map<string, int> order;

public:

    DataXml();
    map<string, int>* getOrderXml();

};


#endif //SIMULATOR1_DATAXML_H
