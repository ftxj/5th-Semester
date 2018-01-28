#ifndef LISTENSOCKETH_H
#define LISTENSOCKETH_H
#include "BasicSocket.h"
#include "Usersocket.h"

class ListenSocket : public BasicSocket{
public:
    ListenSocket(QWidget *p);
    bool isConnected;
    void listen();
    int get_port();
    UserSocket accept();
private:
    WSADATA wD;
    sockaddr_in addr;
};

#endif // LISTENSOCKETH_H
