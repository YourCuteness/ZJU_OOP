#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

// Function to update content for a specific date
int updateContent(const string &filename, const string &date)
{
    ifstream inputFile(filename);
    ofstream outputFile("temp.txt");
    map<string, string> data;

    int sign = 0;
    string line;
    while (getline(inputFile, line))
    {
        size_t pos = line.find(':');
        if (pos != string::npos)
        {
            string currDate = line.substr(0, pos);
            if (currDate == date)
            {
                sign = 1;
                continue;
            }
            string currContent = line.substr(pos + 1);
            data[currDate] = currContent;
        }
    }
    if (sign == 0)
    {
        cout << "Entry not found at " << date << endl;
        return 1;
    }
    for (const auto &pair : data)
    {
        outputFile << pair.first << ":" << pair.second << endl;
    }
    inputFile.close();
    outputFile.close();
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
    return 0; 
}

int main(int argc, char *argv[])
{
    string filename = "personal_dairy.txt";
    string date, content;
    int success = updateContent(filename, argv[1]);
    return success;
}
