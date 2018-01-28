#ifndef SOCKETCLASS_H
#define SOCKETCLASS_H
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
using namespace std;

class UserSocket {
public:
    UserSocket() : len(sizeof(useraddr)) {}
    UserSocket(SOCKET so) : s(so), len(sizeof(useraddr)) {}
    UserSocket(const UserSocket&);
    UserSocket& operator=(const UserSocket&);
    int send(string st);
    void kill();
    std::vector<std::string> recv();
    string id;
    int len;
    sockaddr useraddr;
    std::string ip;
    unsigned short port;
    SOCKET s;
};

class ListenSocket{
public:
    ListenSocket();
    void bind();
    void listen();
    UserSocket accept();
private:
    SOCKET s;
    WSADATA wD;
    sockaddr_in addr;
};
#endif // SOCKETCLASS_H
