#ifndef _CD_H_
#define _CD_H_

#include <string>
#include "item.h"

class CD : public Item
{
private:
    string Artist;
    int Tracks;

public:
    CD(string artist = "", int tracks = 0, int playtime = 0, bool isGot = false, string comment = "");
    ~CD(){};
    void parse(string line);
    virtual void print();
};

#endif