//
// Created by anton on 12/24/18.
//

#include "DataXml.h"


DataXml ::DataXml() {

    order["/instrumentation/airspeed-indicator/indicated-speed-kt"] = 1;
    order["/instrumentation/altimeter/indicated-altitude-ft"] = 2;
    order["/instrumentation/altimeter/pressure-alt-ft"] = 3;
    order["/instrumentation/attitude-indicator/indicated-pitch-deg"] = 4;
    order["/instrumentation/attitude-indicator/indicated-roll-deg"] = 5;
    order["/instrumentation/attitude-indicator/internal-pitch-deg"] = 6;
    order["/instrumentation/attitude-indicator/internal-roll-deg"] = 7;
    order["/instrumentation/encoder/indicated-altitude-ft"] = 8;
    order["/instrumentation/encoder/pressure-alt-ft"] = 9;
    order["/instrumentation/gps/indicated-altitude-ft"] = 10;
    order["/instrumentation/gps/indicated-ground-speed-kt"] = 11;
    order["/instrumentation/gps/indicated-vertical-speed"] = 12;
    order["/instrumentation/heading-indicator/indicated-heading-deg"] = 13;
    order["/instrumentation/magnetic-compass/indicated-heading-deg"] = 14;
    order["/instrumentation/slip-skid-ball/indicated-slip-skid"] = 15;
    order["/instrumentation/turn-indicator/indicated-turn-rate"] = 16;
    order["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"] = 17;
    order["/controls/flight/aileron"] = 18;
    order["/controls/flight/elevator"] = 19;
    order["/controls/flight/rudder"] = 20;
    order["/controls/flight/flaps"] = 21;
    order["/controls/engines/engine/throttle"] = 22;
    order["/engines/engine/rpm"] = 23;

}

map<string, int>* DataXml :: getOrderXml() {

    return &order;
}