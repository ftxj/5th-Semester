#include "Usersocket.h"

UserSocket::UserSocket(){
    if (WSAStartup(wVersionRequest, &wD)) {
        WarringMessage(WSAGetLastError());
    }
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    isConnected = false;
    len = sizeof(useraddr);
}

UserSocket::UserSocket(QWidget* p, SOCKET so) {
    isConnected = true;
    s = so;
    len = sizeof(useraddr);
    self = p;
}


void UserSocket::kill() {
    closesocket(s);
}


