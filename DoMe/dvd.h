#ifndef _DVD_H_
#define _DVD_H_

#include "item.h"
#include <string>

class DVD : public Item
{
private:
    string Director;
    string Title;

public:
    DVD(string director = "", string title = "", int playtime = 0, bool isGot = false, string comment = "");
    ~DVD(){};
    void parse(string line);
    virtual void print();
};

#endif