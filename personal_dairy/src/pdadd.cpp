#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

// Function to update content for a specific date
void updateContent(const string &filename, const string &date, const string &content)
{
    ifstream inputFile(filename);
    ofstream outputFile("temp.txt");
    map<string, string> data;

    string line;
    while (getline(inputFile, line))
    {
        size_t pos = line.find(':');
        if (pos != string::npos)
        {
            string currDate = line.substr(0, pos);
            string currContent = line.substr(pos + 1);
            data[currDate] = currContent;
        }
    }
    data[date] = content;
    for (const auto &pair : data)
    {
        outputFile << pair.first << ":" << pair.second << endl;
    }
    inputFile.close();
    outputFile.close();
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}

int main(int argc, char *argv[])
{
    string filename = "personal_dairy.txt";
    string date, content;
    getline(cin, content);
    updateContent(filename, argv[1], content);
    return 0;
}
