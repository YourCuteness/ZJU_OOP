#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <iostream>
#include <string>

using namespace std;

class Clock
{
private:
    int hour;
    int minute;
    int second;

public:
    Clock(int hour, int minute, int second) : hour(hour), minute(minute), second(second) {} // create a clock with given time
    string toString();                                                                      // get a string description of "hh:mm:ss"
    void dida();                                                                            // run a second
};

#endif