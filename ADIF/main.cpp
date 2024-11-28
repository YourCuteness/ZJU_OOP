#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <map>
#include "adif.h"

using namespace std;

int main()
{
    int total = 0;
    string freq = "", moderecord = "", call = "";
    string filename = "total.adi";
    map<string, ADI> adi;
    load(filename, adi);
    while (1)
    {
        total = adi.size();
        cout << "Number of records in database: " << total << endl;
        cout << "1. Load (Merge) an ADIF file." << endl;
        cout << "2. List all records." << endl;
        cout << "3. Search records by date" << endl;
        cout << "4. Search recalls by call." << endl;
        cout << "5. Input a record." << endl;
        cout << "6. Export all to a CSV file." << endl;
        cout << "7. Exit." << endl;
        cout << "Please enter your choice: " << endl;
        string replace;
        int mode = 0;

        while (getline(cin, replace))
        {
            if (replace == "")
                continue;
            if (replace > "0" && replace < "8")
            {
                mode = stoi(replace);
                break;
            }
            else
                cout << "Invalid input, please enter a number between 1 and 7." << endl;
        }

        if (mode == 1)
        {
            cout << "Please enter the file name you want to load: " << endl;
            string newfile;
            cin >> newfile;

            load(newfile, adi);
            total = adi.size();
            store(adi);
        }

        else if (mode == 2)
        {
            list(adi);
            total = adi.size();
            cout << "Number of records in database: " << total << endl;
            cout << "Press any key to continue";
            cin.get();
        }

        else if (mode == 3)
        {
            search_Date(adi);
            choice(adi);
            store(adi);
        }

        else if (mode == 4)
        {
            search_Call(adi);
            choice(adi);
            store(adi);
        }

        else if (mode == 5)
        {
            addRecord(adi, freq, moderecord, call);
            store(adi);
        }

        else if (mode == 6)
            adi2csv(adi);

        else if (mode == 7)
            break;
    }
    return 0;
}
