//
// Created by anton on 12/14/18.
//

#include "NumberExpression.h"

NumberExpression :: NumberExpression(string newVal) {

    bool seenDot = false;
    double integerPart = 0;
    double divisionPart = 0;
    double temp = 10;

    for(int i = 0; i < newVal.length(); ++i) {

        if(!seenDot && newVal.at(i) == '.') {
            seenDot = true;

        } else if(!seenDot) {
            integerPart *= 10;
            integerPart += (newVal.at(i) - '0');

        } else if(seenDot){
            divisionPart += (newVal.at(i) - '0') / temp;
            temp /= 10;

        }

    }

    value = integerPart + divisionPart;

}


double NumberExpression :: calculate() {
    return value;
};