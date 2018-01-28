#include "datebase.h"
#include "gg.h"
#include <QString>
#include "lock.h"
DataBase::DataBase(string id) {
    ifstream fin;
    lock l;
    fin.open(gg::dataAddr + id);
    string s;
    while (getline(fin, s)) {
        QString x = l.Deciphering(s.c_str());
        friends.push_back(x.toStdString());
    }
    fin.close();
    fin.open(gg::dataAddr + id + ".msg");
    offMsg message;
    while (getline(fin, s)) {
        s = l.Deciphering(s.c_str()).toStdString();
        if (!s.empty() && s[0] == '#') {
            if (!message.id.empty()) {
                offlineMessage.push_back(message);
            }
            message.id = s.substr(1, s.length() - 1);
            message.Msg.clear();
        }
        else {
            message.Msg.push_back(s);
        }
    }
    offlineMessage.push_back(message);
    fin.close();
}
