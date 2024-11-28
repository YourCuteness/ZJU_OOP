#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "item.h"
#include <string>
#include <vector>

class Database
{
private:
    vector<Item *> Items;

public:
    Database();
    ~Database(){};
    void add(Item *item);
    void list();
};

#endif