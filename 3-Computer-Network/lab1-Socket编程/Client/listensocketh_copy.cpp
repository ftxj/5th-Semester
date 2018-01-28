#include "Listensocket.h"

ListenSocket::ListenSocket() {
    u_long iMode = 0;
    if (WSAStartup(wVersionRequest, &wD)) {
        printf("error when init\n");
    }
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void ListenSocket::bind() {
    addr.sin_family = AF_INET;
    addr.sin_port = htons(servert_port);
    addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    if (::bind(s, (LPSOCKADDR)&addr, sizeof(addr))) {
        printf("error when bind\n");
    }
    else {
        printf("bind success\n");
    }
}

void ListenSocket::listen() {
    if (::listen(s, SOMAXCONN)) {
        printf("error when listen\n");
    }
    else {
        printf("listen success\n");
    }
}

