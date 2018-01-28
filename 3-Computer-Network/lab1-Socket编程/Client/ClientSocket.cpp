#include "ClientSocket.h"

ClientSocket::ClientSocket(QWidget* p) {
    parent = p;
    if (WSAStartup(wVersionRequest, &wD)) {
        WarringMessage(WSAGetLastError());
    }
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

ClientSocket::~ClientSocket() {
    closesocket(s);
    parent->close();
}

void ClientSocket::bind_port(){
    this->bind();
}

void ClientSocket::connect_server(){
    this->connect(server_port, server_ip);
}
