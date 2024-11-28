#include <iostream>
#include <string>
#include "clock.h"

using namespace std;

string Clock::toString()
{

    string hourStr = (hour < 10) ? "0" + to_string(hour) : to_string(hour);
    string minuteStr = (minute < 10) ? "0" + to_string(minute) : to_string(minute);
    string secondStr = (second < 10) ? "0" + to_string(second) : to_string(second);
    return hourStr + ":" + minuteStr + ":" + secondStr;
}

void Clock::dida()
{
    second++;
    if (second >= 60)
    {
        second %= 60;
        minute++;
        if (minute >= 60)
        {
            minute %= 60;
            hour++;
            if (hour >= 24)
            {
                hour %= 24;
            }
        }
    }
}