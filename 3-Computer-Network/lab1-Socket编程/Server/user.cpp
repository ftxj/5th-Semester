#include "user.h"
#include "gg.h"
#include "lock.h"
User::User() : id(""), Us(0){}
int User::addFriend(string s) {
    lock l;
    s = l.encryption(s.c_str()).toStdString();
    ofstream fout;
    fout.open(gg::dataAddr + id, ios::app);
    fout << s << "\n";
    fout.close();
    return 0;
}
int User::setNewPsw(string name, string psw, string pro, string ans) {
    int linenum = 0;
    lock l;
    name = l.encryption(name.c_str()).toStdString();
    psw = l.encryption(psw.c_str()).toStdString();
    pro = l.encryption(pro.c_str()).toStdString();
    ans = l.encryption(ans.c_str()).toStdString();

    vector<string> v;
    ifstream fin;
    fin.open(gg::dataAddr + "all");
    string s, p, pr, an;
    while (getline(fin, s) && s != name) {
        v.push_back(s);
        continue;
    }
    getline(fin, p);
    getline(fin, pr);
    if (pr != pro) {
        return -1;
    }
    getline(fin, an);

    if (an != ans) {
        return -1;
    }
    v.push_back(s);
    v.push_back(psw);
    v.push_back(pr);
    v.push_back(an);
    while (getline(fin, s)) {
        v.push_back(s);
    }
    fin.close();

    ofstream newFile(gg::dataAddr + "all", ios::trunc);
    for (int i = 0; i < v.size(); ++i) {
        newFile << v[i] << "\n";
    }
    newFile.close();
    return 0;
}
int User::addUser(string name, string psw, string pro, string ans) {
    ofstream fout;
    lock l;
    fout.open(gg::dataAddr + "all", ios::app);
    name = l.encryption(name.c_str()).toStdString();
    psw = l.encryption(psw.c_str()).toStdString();
    pro = l.encryption(pro.c_str()).toStdString();
    ans = l.encryption(ans.c_str()).toStdString();

    fout << name << "\n";
    fout << psw << "\n";
    fout << pro << "\n";
    fout << ans << "\n";
    fout.close();
    return 0;
}
int User::verify() {
    ifstream fin;
    lock l;
    fin.open(gg::dataAddr + "all");
    string s;
    while (getline(fin, s)) {
        s = l.Deciphering(s.c_str()).toStdString();
        if(s != id){
            continue;
        }
        else{
            break;
        }
    }
    if (getline(fin, s)) {
        s = l.Deciphering(s.c_str()).toStdString();
        if(s == key){
            return 1;
        }
    }
    return 0;
}

void User::dosign_in() {
    DataBase D(id);
    vector<string> &s = D.get_friends();
    vector<offMsg> &sM = D.get_offMsg();
    int r;
    r = Us.send("login message");
    r = Us.send("% friend list %");
    for (auto i = s.begin(); i != s.end(); ++i) {
        r = Us.send((*i) + "#");
    }
    r = Us.send("% friend list end %");
    r = Us.send("% Msg list %");
    for (auto i = sM.begin(); i != sM.end(); ++i) {
        Us.send((*i).id);
        Us.send(to_string((*i).Msg.size()));
        for (auto j = (*i).Msg.begin(); j != (*i).Msg.end(); ++j) {
            Us.send(*j);
        }
    }
    Us.send("% Msg list end %");
    Us.send("% login message end %");
}
