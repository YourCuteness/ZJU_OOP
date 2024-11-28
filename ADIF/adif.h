#ifndef _ADI_H_
#define _ADI_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

class extra
{
private:
    string name;
    int key;
    string value;

public:
    extra() : name(""), key(0), value(""){};
    extra(string n, int k, string v) : name(n), key(k), value(v){};
    string getName() { return name; };
    int getKey() { return key; };
    string getValue() { return value; };
    friend class ADI;
};

class ADI
{
private:
    int order;
    map<string, int> QSO_DATE;
    map<string, int> TIME_ON;
    map<string, int> FREQ;
    map<string, int> MODE;
    map<string, int> CALL;
    map<string, int> RST_SENT;
    map<string, int> RST_RCVD;
    map<string, extra> others;

public:
    ADI() : order(0), QSO_DATE(), TIME_ON(), FREQ(), MODE(), CALL(), RST_SENT(), RST_RCVD(), others(){};
    void parseAndStore(string line);
    void storeOrder(int o) { order = o; };
    void storeQSO_DATE(string qso_date) { QSO_DATE[qso_date] = qso_date.size(); };
    void storeTIME_ON(string time_on) { TIME_ON[time_on] = time_on.size(); };
    void storeFREQ(string freq) { FREQ[freq] = freq.size(); };
    void storeMODE(string mode) { MODE[mode] = mode.size(); };
    void storeCALL(string call) { CALL[call] = call.size(); };
    void storeRST_SENT(string rst_sent) { RST_SENT[rst_sent] = rst_sent.size(); };
    void storeRST_RCVD(string rst_rcvd) { RST_RCVD[rst_rcvd] = rst_rcvd.size(); };
    void storeOthers(string name, int key, string value) { others[name] = extra(name, key, value); };
    void clearQSO_DATE() { QSO_DATE.clear(); };
    void clearTIME_ON() { TIME_ON.clear(); };
    void clearFREQ() { FREQ.clear(); };
    void clearMODE() { MODE.clear(); };
    void clearCALL() { CALL.clear(); };
    void clearRST_SENT() { RST_SENT.clear(); };
    void clearRST_RCVD() { RST_RCVD.clear(); };
    void clearOthers(string name) { others.erase(name); };
    int getORDER() { return order; };
    map<string, int> getQSO_DATE() { return QSO_DATE; };
    map<string, int> getTIME_ON() { return TIME_ON; };
    map<string, int> getFREQ() { return FREQ; };
    map<string, int> getMODE() { return MODE; };
    map<string, int> getCALL() { return CALL; };
    map<string, int> getRST_SENT() { return RST_SENT; };
    map<string, int> getRST_RCVD() { return RST_RCVD; };
    map<string, extra> getOthers() { return others; };
};

string getCurrentDate();
string getCurrentTime();
void listadi(ADI adi);
void load(string filename, map<string, ADI> &adi);                               // 存储整个文件数据
void addRecord(map<string, ADI> &adi, string &freq, string &mode, string &call); // 增加一条记录
void store(map<string, ADI> adi);                                                // 储存到外部total.aci
void list(map<string, ADI> adi);                                                 // 打印所有数据
map<string, ADI> search_Date(map<string, ADI> &adi);                             // 按日期查找数据
map<string, ADI> search_Call(map<string, ADI> &adi);                             // 按呼号查找数据
void choice(map<string, ADI> &adi);                                              // 修改或删除数据
void adi2csv(map<string, ADI> adi);                                              // 将数据转换为csv格式

#endif
