#include "Listensocket.h"

ListenSocket::ListenSocket(QWidget* p) {
    parent = p;
    if (WSAStartup(wVersionRequest, &wD)) {
        WarringMessage(WSAGetLastError());
    }
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(0);
    addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    if (::bind(s, (LPSOCKADDR)&addr, sizeof(addr))) {
        WarringMessage(WSAGetLastError());
    }
}

int ListenSocket::get_port(){
    struct sockaddr_in sin;
    int addrlen = sizeof(sin);
    if(getsockname(s, (struct sockaddr *)&sin, &addrlen) == 0 &&
       sin.sin_family == AF_INET &&
       addrlen == sizeof(sin))
    {
        int local_port = ntohs(sin.sin_port);
        return local_port;
    }
    return 0;
}
void ListenSocket::listen() {
    if (::listen(s, SOMAXCONN)) {
        WarringMessage(WSAGetLastError());
    }
}

UserSocket ListenSocket::accept(){
    UserSocket us;
    sockaddr_in sin;
    us.s = ::accept(s, &us.useraddr, &us.len);
    memcpy(&sin, &us.useraddr, sizeof(sin));
    us.ip = inet_ntoa(sin.sin_addr);
    us.port = ntohs(sin.sin_port);
    us.isConnected = true;
    return us;
}
