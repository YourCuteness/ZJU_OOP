#ifndef _NUMBERDISPLAY_H_
#define _NUMBERDISPLAY_H_

#include <iostream>
#include <string>

using namespace std;

class NumberDisplay
{
private:
    int limit;
    int value;

public:
    NumberDisplay(int limit) : limit(limit), value(0) {} // create a number display with a given up-limit
    void setValue(int v);                                // set the value
    int getValue();                                      // get the value
    string toString();                                   // get a string description of the value, with leading 0 for value less than 10
    bool dida();                                         // increase the value by one, turn over to zero if the value reaches the limit, returns true if the value turned to zero
};

#endif