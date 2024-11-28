
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <chrono>
#include "adif.h"

using namespace std;

string getCurrentDate()
{
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    struct tm *parts = localtime(&now_c);

    char buffer[9];
    strftime(buffer, sizeof(buffer), "%Y%m%d", parts);
    return string(buffer);
}

string getCurrentTime()
{
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    struct tm *parts = localtime(&now_c);

    char buffer[7]; // "HHMMSS" + null terminator
    strftime(buffer, sizeof(buffer), "%H%M%S", parts);
    return string(buffer);
}

void listadi(ADI adi)
{
    map<string, int> qso_date = adi.getQSO_DATE();
    map<string, int> time_on = adi.getTIME_ON();
    map<string, int> freq = adi.getFREQ();
    map<string, int> mode = adi.getMODE();
    map<string, int> call = adi.getCALL();
    map<string, int> rst_sent = adi.getRST_SENT();
    map<string, int> rst_rcvd = adi.getRST_RCVD();
    map<string, extra> others = adi.getOthers();
    cout << qso_date.begin()->first << "," << time_on.begin()->first << "," << freq.begin()->first << "," << mode.begin()->first << "," << call.begin()->first << "," << rst_sent.begin()->first << "," << rst_rcvd.begin()->first << ",";
    for (auto &pair2 : others)
    {
        string name = pair2.second.getName();
        string value = pair2.second.getValue();
        cout << name << ":" << value << ",";
    }
    cout << endl;
    return;
}

void ADI::parseAndStore(string line) // 存储单行数据
{
    size_t start = 0, end = 0, mid = 0;
    while ((start = line.find("<")) != string::npos && (end = line.find(">")) != string::npos)
    {
        mid = line.find(":", start);
        if (mid > start && mid < end)
        {
            string tag = line.substr(start + 1, mid - start - 1);
            string value = line.substr(mid + 1, end - mid - 1);
            int key = stoi(value);
            start = line.find("<", end);
            if (start == string::npos)
                start = line.size();
            size_t sizeValue = static_cast<size_t>(key);
            sizeValue = (sizeValue < start - end - 1 ? sizeValue : start - end - 1);
            string content = line.substr(end + 1, sizeValue);
            order = 0;
            if ((tag == "qso_date" || tag == "QSO_DATE") && key != 8)
            {
                int zeroToAdd = 8 - content.size();
                content.append(zeroToAdd, '0');
                key = 8;
            }
            else if ((tag == "time_on" || tag == "TIME_ON") && key != 6)
            {
                int zeroToAdd = 6 - content.size();
                content.append(zeroToAdd, '0');
                key = 6;
            }
            if (tag == "qso_date" || tag == "QSO_DATE")
                QSO_DATE[content] = key;
            else if (tag == "time_on" || tag == "TIME_ON")
                TIME_ON[content] = key;
            else if (tag == "freq" || tag == "FREQ")
                FREQ[content] = key;
            else if (tag == "mode" || tag == "MODE")
                MODE[content] = key;
            else if (tag == "call" || tag == "CALL")
                CALL[content] = key;
            else if (tag == "rst_sent" || tag == "RST_SENT")
                RST_SENT[content] = key;
            else if (tag == "rst_rcvd" || tag == "RST_RCVD")
                RST_RCVD[content] = key;
            else
                others[tag] = extra(tag, key, content);
        }
        else if (mid == string::npos)
            break;
        else
            start = line.find("<", end);
        line.erase(0, start);
    }
}

void load(string filename, map<string, ADI> &adi)
{
    int state = 0;
    ifstream myfile;
    string line;
    myfile.open(filename);
    if (!myfile.is_open())
    {
        if (filename != "total.adi")
            cout << "Unable to open file." << endl;
        return;
    }
    if (filename != "total.adi")
        cin.ignore();
    bool eoh_ready = false;
    bool finduseful = false;
    while (getline(myfile, line))
    {
        size_t foundPosbig = line.find("<EOH>");
        size_t foundPossmall = line.find("<eoh>");
        size_t foundPosuseful = line.find("qso_date");
        size_t foundPosuseful2 = line.find("QSO_DATE");
        if (foundPosbig != string::npos || foundPossmall != string::npos || foundPosuseful != string::npos || foundPosuseful2 != string::npos)
        {
            if (foundPosuseful != string::npos || foundPosuseful2 != string::npos)
                finduseful = true;
            eoh_ready = true;
            break;
        }
    }
    if (eoh_ready)
    {
        string additional = "";
        while (1)
        {
            if (finduseful == false)
            {
                if (!getline(myfile, line))
                    break;
            }
            finduseful = false;
            if (!line.empty())
            {
                line = additional + line;
                size_t end = line.length();
                string check = line.substr(end - 4, 3);
                if (check == "eor" || check == "EOR")
                {
                    additional = "";
                    ADI adi_instance;
                    adi_instance.parseAndStore(line);
                    map<string, int> qso_date = adi_instance.getQSO_DATE();
                    map<string, int> time_on = adi_instance.getTIME_ON();
                    string timenow = qso_date.begin()->first + time_on.begin()->first;
                    auto it = adi.find(timenow);
                    if (it != adi.end())
                    {
                        if (state == 0)
                        {
                            int judge = 0;
                            ADI temp = it->second;
                            cout << "Record already exists!" << endl;
                            cout << "Original: ";
                            listadi(temp);
                            cout << "New     : ";
                            listadi(adi_instance);
                            string choice;
                            cout << "(S)kip, (R)eplace, (A)dd, (M)erge, (Q)uit:" << endl;
                            do
                            {
                                if (judge == 1)
                                    judge = 0;
                                getline(cin, choice);
                                if (choice == "S" || choice == "s")
                                    continue;
                                else if (choice == "R" || choice == "r")
                                    adi[timenow] = adi_instance;
                                else if (choice == "M" || choice == "m")
                                {
                                    map<string, extra> others = temp.getOthers();
                                    for (auto &pair : others)
                                    {
                                        string name = pair.second.getName();
                                        if (adi_instance.getOthers().find(name) == adi_instance.getOthers().end())
                                        {
                                            int key = pair.second.getKey();
                                            string value = pair.second.getValue();
                                            adi_instance.storeOthers(name, key, value);
                                        }
                                    }
                                    adi[timenow] = adi_instance;
                                }
                                else if (choice == "Q" || choice == "q")
                                    state = 1;
                                else
                                {
                                    cout << "Invalid input!" << endl;
                                    judge = 1;
                                    continue;
                                }
                            } while (judge == 1);
                        }
                        else if (state == 1)
                            continue;
                    }
                    // 键已经存在，可以在此处执行相应的操作
                    else
                        adi[timenow] = adi_instance;
                }
                else
                    additional = line;
            }
        }
    }
    return;
}

void addRecord(map<string, ADI> &adi, string &freq, string &mode, string &call)
{
    ADI newone;
    string ymd = getCurrentDate();
    cout << "QSO_DATE(" << ymd << "): ";
    string date;
    getline(cin, date);
    if (date == "")
        date = ymd;
    newone.storeQSO_DATE(date);
    string hms = getCurrentTime();
    cout << "TIME_ON(" << hms << "): ";
    string time;
    getline(cin, time);
    if (time == "")
        time = hms;
    newone.storeTIME_ON(time);
    cout << "FREQ(" << freq << "): ";
    string freqs;
    getline(cin, freqs);
    if (freqs == "" && freq != "")
        freqs = freq;
    else if (freqs == "" && freq == "")
        freqs = "0.000000";
    else if (freqs != "" && freq == "")
        freq = freqs;
    newone.storeFREQ(freqs);
    cout << "MODE(" << mode << "): ";
    string modes;
    getline(cin, modes);
    if (modes == "" && mode != "")
        modes = mode;
    else if (modes == "" && mode == "")
        modes = "SSB";
    else if (modes != "" && mode == "")
        mode = modes;
    newone.storeMODE(modes);
    cout << "CALL(" << call << "): ";
    string calls;
    getline(cin, calls);
    if (calls == "" && call != "")
        calls = call;
    else if (calls == "" && call == "")
        calls = "N0CALL";
    else if (calls != "" && call == "")
        call = calls;
    newone.storeCALL(calls);
    cout << "RST_SENT(59): " << endl;
    string rst_sent;
    getline(cin, rst_sent);
    if (rst_sent == "")
        rst_sent = "59";
    newone.storeRST_SENT(rst_sent);
    cout << "RST_RCVD(59): " << endl;
    string rst_rcvd;
    getline(cin, rst_rcvd);
    if (rst_rcvd == "")
        rst_rcvd = "59";
    newone.storeRST_RCVD(rst_rcvd);
    adi[date + time] = newone;
}

void store(map<string, ADI> adi)
{
    string filename = "m.adi";
    ofstream myfile;
    myfile.open(filename);
    myfile << "<EOH>" << endl;
    for (auto &pair : adi)
    {
        map<string, int> qso_date = pair.second.getQSO_DATE();
        map<string, int> time_on = pair.second.getTIME_ON();
        map<string, int> freq = pair.second.getFREQ();
        map<string, int> mode = pair.second.getMODE();
        map<string, int> call = pair.second.getCALL();
        map<string, int> rst_sent = pair.second.getRST_SENT();
        map<string, int> rst_rcvd = pair.second.getRST_RCVD();
        map<string, extra> others = pair.second.getOthers();
        myfile << "<QSO_DATE:" << qso_date.begin()->second << ">" << qso_date.begin()->first << "<TIME_ON:" << time_on.begin()->second << ">" << time_on.begin()->first << "<FREQ:" << freq.begin()->second << ">" << freq.begin()->first << "<MODE:" << mode.begin()->second << ">" << mode.begin()->first << "<CALL:" << call.begin()->second << ">" << call.begin()->first << "<RST_SENT:" << rst_sent.begin()->second << ">" << rst_sent.begin()->first << "<RST_RCVD:" << rst_rcvd.begin()->second << ">" << rst_rcvd.begin()->first;
        for (auto &pair2 : others)
        {
            string name = pair2.second.getName();
            int key = pair2.second.getKey();
            string value = pair2.second.getValue();
            myfile << "<" << name << ":" << key << ">" << value;
        }
        myfile << "<EOR>" << endl;
    }
    remove("total.adi");
    myfile.close();
    rename("m.adi", "total.adi");
}

void list(map<string, ADI> adi)
{
    for (auto &pair : adi)
    {
        if (pair.second.getORDER() != 0)
            cout << pair.second.getORDER() << ": ";
        ADI temp = pair.second;
        listadi(temp);
    }
    return;
}

map<string, ADI> search_Date(map<string, ADI> &adi)
{
    int sign = 0, total = 0;
    string startdate;
    string enddate;
    cout << "The begin date(yyyymmdd)" << endl;
    getline(cin, startdate);
    cout << "The end date(yyyymmdd)" << endl;
    getline(cin, enddate);
    if (enddate == "")
        enddate = startdate;
    map<string, ADI> result;
    for (auto &pair : adi)
    {
        ADI temp = pair.second;
        map<string, int> qso_date = temp.getQSO_DATE();
        string date = qso_date.begin()->first;
        if (date.compare(startdate) >= 0 && date.compare(enddate) <= 0)
        {
            total++;
            temp.storeOrder(total);
            pair.second.storeOrder(total);
            result[pair.first] = temp;
            sign = 1;
        }
    }
    if (sign == 0)
        cout << "No records found!" << endl;
    else
    {
        list(result);
        cout << "Number of records found: " << total << endl;
    }
    return result;
}

map<string, ADI> search_Call(map<string, ADI> &adi)
{
    int total;
    string call;
    int sign = 0;
    cout << "The call sign" << endl;
    getline(cin, call);
    map<string, ADI> result;
    for (auto &pair : adi)
    {
        ADI temp = pair.second;
        if (temp.getQSO_DATE().begin()->first == call || temp.getTIME_ON().begin()->first == call || temp.getFREQ().begin()->first == call || temp.getMODE().begin()->first == call || temp.getCALL().begin()->first == call || temp.getRST_SENT().begin()->first == call || temp.getRST_RCVD().begin()->first == call)
        {
            total++;
            temp.storeOrder(total);
            pair.second.storeOrder(total);
            result[pair.first] = temp;
            sign = 1;
        }
        else
        {
            map<string, extra> others = pair.second.getOthers();
            for (auto &pair2 : others)
            {
                if (pair2.second.getValue() == call)
                {
                    (total)++;
                    pair.second.storeOrder(total);
                    result[pair.first] = pair.second;
                    sign = 1;
                    break;
                }
            }
        }
    }
    if (sign == 0)
        cout << "No records found!" << endl;
    else
    {
        list(result);
        cout << "Number of records found: " << total << endl;
    }
    return result;
}

void choice(map<string, ADI> &adi)
{
    int state = 0;
    string opcode;
    cout << "(M)pdify, (D)elete, (Q)uit" << endl;
    do
    {
        cin >> opcode;
        if (opcode == "q" || opcode == "Q")
            return;
        else if (opcode == "m" || opcode == "M" || opcode == "d" || opcode == "D")
        {
            cout << "Enter the number of record:";
            int mychoice = 0, totalsign = 0;
            cin >> mychoice;
            for (auto it = adi.begin(); it != adi.end();)
            {
                if (it->second.getORDER() == mychoice)
                {
                    if (opcode == "m" || opcode == "M")
                    {
                        cout << "QSO_DATE,TIME_ON,FREQ,MODE,CALL,RST_SENT,RST_RCVD" << endl;
                        map<string, int> qso_date = it->second.getQSO_DATE();
                        map<string, int> time_on = it->second.getTIME_ON();
                        map<string, int> freq = it->second.getFREQ();
                        map<string, int> mode = it->second.getMODE();
                        map<string, int> call = it->second.getCALL();
                        map<string, int> rst_sent = it->second.getRST_SENT();
                        map<string, int> rst_rcvd = it->second.getRST_RCVD();
                        map<string, extra> others = it->second.getOthers();
                        cout << qso_date.begin()->first << "," << time_on.begin()->first << "," << freq.begin()->first << "," << mode.begin()->first << "," << call.begin()->first << "," << rst_sent.begin()->first << "," << rst_rcvd.begin()->first << ",";
                        for (auto &pair2 : others)
                        {
                            string name = pair2.second.getName();
                            string value = pair2.second.getValue();
                            cout << name << ":" << value << ",";
                        }
                        cout << endl;
                        cout << "QSO_DATE and TIME_ON can not be modified." << endl;
                        do
                        {
                            cout << "Enter the key you want to modify:" << endl;
                            string key;
                            if (cin.peek() == '\n')
                                cin.ignore(1);
                            getline(cin, key);
                            if (key == "QSO_DATE" || key == "TIME_ON" || key == "qso_date" || key == "time_on")
                            {
                                cout << "QSO_DATE and TIME_ON can not be modified." << endl;
                                continue;
                            }
                            cout << "Enter the value you want to modify:" << endl;
                            string value;
                            getline(cin, value);
                            if (key == "FREQ" || key == "freq")
                            {
                                it->second.clearFREQ();
                                it->second.storeFREQ(value);
                                totalsign = 1;
                            }
                            else if (key == "MODE" || key == "mode")
                            {
                                it->second.clearMODE();
                                it->second.storeMODE(value);
                                totalsign = 1;
                            }
                            else if (key == "CALL" || key == "call")
                            {
                                it->second.clearCALL();
                                it->second.storeCALL(value);
                                totalsign = 1;
                            }
                            else if (key == "RST_SENT" || key == "rst_sent")
                            {
                                it->second.clearRST_SENT();
                                it->second.storeRST_SENT(value);
                                totalsign = 1;
                            }
                            else if (key == "RST_RCVD" || key == "rst_rcvd")
                            {
                                it->second.clearRST_RCVD();
                                it->second.storeRST_RCVD(value);
                                totalsign = 1;
                            }
                            else
                            {
                                for (auto &family : others)
                                {
                                    if (family.second.getName() == key)
                                    {
                                        it->second.clearOthers(key);
                                        it->second.storeOthers(key, family.second.getKey(), value);
                                        totalsign = 1;
                                        break;
                                    }
                                }
                                if (totalsign == 0)
                                    cout << "Invalid key!" << endl;
                            }
                        } while (totalsign == 0);
                    }
                    else
                    {
                        it = adi.erase(it);
                        break;
                    }
                }
                if (totalsign == 1)
                    break;
                ++it;
            }
            for (auto &pair : adi)
            {
                if (pair.second.getORDER() != 0)
                    pair.second.storeOrder(0);
            }
        }
        else
        {
            cout << "Invalid input!" << endl;
            state = 1;
        }
    } while (state == 1);
    return;
}

void adi2csv(map<string, ADI> adi)
{
    ofstream myfile;
    myfile.open("total.csv");
    myfile << "QSO_DATE,TIME_ON,FREQ,MODE,CALL,RST_SENT,RST_RCVD,";
    vector<string> classes;
    for (auto &pair : adi)
    {
        ADI temp = pair.second;
        map<string, extra> others = temp.getOthers();
        for (auto &pair2 : others)
        {
            string name = pair2.second.getName();
            if (find(classes.begin(), classes.end(), name) == classes.end())
            {
                classes.push_back(name);
                myfile << name << ",";
            }
        }
    }
    myfile << endl;
    for (auto &pair : adi)
    {
        ADI temp = pair.second;
        map<string, int> qso_date = temp.getQSO_DATE();
        map<string, int> time_on = temp.getTIME_ON();
        map<string, int> freq = temp.getFREQ();
        map<string, int> mode = temp.getMODE();
        map<string, int> call = temp.getCALL();
        map<string, int> rst_sent = temp.getRST_SENT();
        map<string, int> rst_rcvd = temp.getRST_RCVD();
        myfile << qso_date.begin()->first << "," << time_on.begin()->first << "," << freq.begin()->first << "," << mode.begin()->first << "," << call.begin()->first << "," << rst_sent.begin()->first << "," << rst_rcvd.begin()->first << ",";
        map<string, extra> others = temp.getOthers();
        for (auto &pair2 : classes)
        {
            if (others.find(pair2) != others.end())
                myfile << others[pair2].getValue() << ",";
            else
                myfile << ",";
        }
        myfile << endl;
    }
    myfile.close();
    return;
}
