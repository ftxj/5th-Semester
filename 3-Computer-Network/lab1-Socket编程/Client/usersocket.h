#ifndef USERSOCKET_H
#define USERSOCKET_H
#include "BasicSocket.h"

class UserSocket : public BasicSocket{
public:
    UserSocket();
    UserSocket(QWidget *p ,SOCKET so);

    bool isConnected;
    void kill();
    int len;
    sockaddr useraddr;
    std::string ip;
    unsigned short port;
    std::string id;
    QWidget* self;
    WSADATA wD;
};

#endif // USERSOCKET_H
