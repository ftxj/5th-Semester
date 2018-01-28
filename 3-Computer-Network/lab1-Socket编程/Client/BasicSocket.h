#ifndef BASICSOCKET_H
#define BASICSOCKET_H
#include "Globalvar.h"

class BasicSocket{
public:

    void WarringMessage(int);
    void bind();
    void connect(const int port, const std::string ip);
    int send(std::string );
    std::vector<std::string> recv();

    SOCKET s;
    QWidget* parent;
};

#endif // BASICSOCKET_H
