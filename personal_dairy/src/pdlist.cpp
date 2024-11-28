#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int main(int argc, char *argv[])
{
    string filename = "personal_dairy.txt";
    ifstream inputFile(filename);

    string line;
    map<string, string> data;
    while (getline(inputFile, line))
    {
        size_t pos = line.find(':');
        if (pos != string::npos)
        {
            string current_date = line.substr(0, pos);
            string current_content = line.substr(pos + 1);
            data[current_date] = current_content;
        }
    }
    for (const auto &pair : data)
    {
        cout << pair.first << ":" << pair.second << endl;
    }
    inputFile.close();
    return 0;
}
