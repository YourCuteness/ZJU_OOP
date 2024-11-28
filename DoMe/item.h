#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>
using namespace std;

class Item
{
private:
    int Playtime;
    bool IsGot;
    string Comment;

public:
    Item(int playtime = 0, bool isGot = false, string comment = "");
    ~Item(){};
    virtual void print();
    void parse(int playtime, bool isGot, string comment);
};

#endif