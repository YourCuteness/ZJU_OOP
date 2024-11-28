#include "item.h"
#include <string>
#include <iostream>

using namespace std;

Item::Item(int playtime, bool isGot, string comment)
{
    Playtime = playtime;
    IsGot = isGot;
    Comment = comment;
}

void Item::print()
{
    cout << "Playing time: " << Playtime << " minutes" << endl;
    if (IsGot)
        cout << "Got it: yes" << endl;
    else
        cout << "Got it: no" << endl;
    cout << "Comment: " << Comment << endl;
}

void Item::parse(int playtime, bool isGot, string comment)
{
    Playtime = playtime;
    IsGot = isGot;
    Comment = comment;
}