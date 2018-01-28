#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H
#include "BasicSocket.h"

class ClientSocket : public BasicSocket{
public:
    ClientSocket(QWidget*);
    ~ClientSocket();
    void bind_port();
    void connect_server();
private:
    WSADATA wD;
};
#endif // CLIENTSOCKET_H
