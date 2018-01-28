#ifndef DATEBASE_H
#define DATEBASE_H
#include <WinSock2.h>
#include <stdio.h>
#include <fstream>
#include <thread>
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include "mainwindow.h"
#include "socketclass.h"
#include "user.h"
#include <QCryptographicHash>
using namespace std;
struct offMsg {
    string id;
    vector<string> Msg;
};

class DataBase {
    public:
        DataBase(string id);
        ~DataBase() { friends.~vector(); offlineMessage.~vector(); }
        vector<string>& get_friends() { return friends; }
        vector<offMsg>& get_offMsg() { return offlineMessage; }

    private:
        vector<string> friends;
        vector<offMsg> offlineMessage;
};
#endif // DATEBASE_H
