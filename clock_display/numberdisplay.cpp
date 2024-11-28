#include <iostream>
#include <string>
#include "numberdisplay.h"

using namespace std;

void NumberDisplay::setValue(int v)
{
    this->value = v;
}

int NumberDisplay::getValue()
{
    return value;
}

string NumberDisplay::toString()
{
    string need = to_string(value);
    if (value < 10)
        need = "0" + need;
    return need;
}

bool NumberDisplay::dida()
{
    bool judge = false;
    value += 1;
    if (value == limit)
    {
        value = 0;
        judge = true;
    }
    return judge;
}