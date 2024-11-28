#include "database.h"
#include <string>
#include <vector>

using namespace std;

Database::Database()
{
    Items = vector<Item *>();
}

void Database::add(Item *item)
{
    Items.push_back(item);
}

void Database::list()
{
    for (auto item : Items)
    {
        item->print();
    }
}
