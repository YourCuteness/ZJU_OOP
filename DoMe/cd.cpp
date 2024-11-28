#include "cd.h"
#include <string>
#include <iostream>

using namespace std;

CD::CD(string artist, int tracks, int playtime, bool isGot, string comment) : Item(playtime, isGot, comment)
{
    Artist = artist;
    Tracks = tracks;
}

void CD::parse(string line)
{
    Artist = " " + line.substr(line.find_first_not_of(" "), line.find_first_of(",") - line.find_first_not_of(" "));
    line = line.substr(line.find_first_of(",") + 1);
    Tracks = stoi(line.substr(line.find_first_not_of(" "), line.find_first_of(",") - line.find_first_not_of(" ")));
    line = line.substr(line.find_first_of(",") + 1);
    int Playtime = stoi(line.substr(line.find_first_not_of(" "), line.find_first_of(",") - line.find_first_not_of(" ")));
    line = line.substr(line.find_first_of(",") + 1);
    bool IsGot = (line.substr(line.find_first_not_of(" "), line.find_first_of(",") - line.find_first_not_of(" ")) == "1");
    line = line.substr(line.find_first_of(",") + 1);
    string Comment = line.substr(line.find_first_not_of(" "), line.find_first_of(",") - line.find_first_not_of(" "));
    Item::parse(Playtime, IsGot, Comment);
}

void CD::print()
{
    cout << "----------------------------------------" << endl;
    cout << "Artist: " << Artist << endl;
    cout << "Number of tracks: " << Tracks << endl;
    Item::print();
    cout << "----------------------------------------" << endl;
}