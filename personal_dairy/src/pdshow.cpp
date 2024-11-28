#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
    string filename = "personal_dairy.txt";
    ifstream inputFile(filename);
    string date = argv[1];
    int sign = 0;
    string line;
    map<string, string> data;
    while (getline(inputFile, line))
    {
        size_t pos = line.find(':');
        if (pos != string::npos)
        {
            string current_date = line.substr(0, pos);
            string current_content = line.substr(pos + 1);
            if (current_date == date)
            {
                data[current_date] = current_content;
                sign = 1;
                break;
            }
        }
    }
    if (sign == 0)
        cout << date << ":No entry found for the given date" << endl;
    else
        cout << date << ":" << data[date] << endl;
    inputFile.close();
    return 0;
}
