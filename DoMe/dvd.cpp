#include "dvd.h"
#include <string>
#include <iostream>

using namespace std;

DVD::DVD(string director, string title, int playtime, bool isGot, string comment) : Item(playtime, isGot, comment)
{
    Director = director;
    Title = title;
}

void DVD::parse(string line)
{
    Director = " " + line.substr(line.find_first_not_of(" "), line.find_first_of(",") - line.find_first_not_of(" "));
    line = line.substr(line.find_first_of(",") + 1);
    Title = " " + line.substr(line.find_first_not_of(" "), line.find_first_of(",") - line.find_first_not_of(" "));
    line = line.substr(line.find_first_of(",") + 1);
    int Playtime = stoi(line.substr(line.find_first_not_of(" "), line.find_first_of(",") - line.find_first_not_of(" ")));
    line = line.substr(line.find_first_of(",") + 1);
    bool IsGot = (line.substr(line.find_first_not_of(" "), line.find_first_of(",") - line.find_first_not_of(" ")) == "1");
    line = line.substr(line.find_first_of(",") + 1);
    string Comment = line.substr(line.find_first_not_of(" "), line.find_first_of(",") - line.find_first_not_of(" "));
    Item::parse(Playtime, IsGot, Comment);
}

void DVD::print()
{
    cout << "----------------------------------------" << endl;
    cout << "Director: " << Director << endl;
    cout << "Title: " << Title << endl;
    Item::print();
    cout << "----------------------------------------" << endl;
}