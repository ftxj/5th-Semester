#ifndef USER_H
#define USER_H
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
#include "datebase.h"
using namespace std;

class User {
public:
    User(string s1, string s2, UserSocket s) :id(s1), key(s2), Us(s) {}
    User();
    int addUser(string name, string psw, string pro, string ans);
    int setNewPsw(string name, string psw, string pro, string ans);
    int addFriend(string id);
    int verify();
    void dosign_in();
    string id;
    string key;
    string ip;
    UserSocket Us;
};

#endif // USER_H
