#include "socketclass.h"
#include "gg.h"
ListenSocket::ListenSocket() {
    u_long iMode = 0;
    if (WSAStartup(gg::wVersionRequest, &wD)) {
        printf("error when init\n");
    }
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void ListenSocket::bind() {
    addr.sin_family = AF_INET;
    addr.sin_port = htons(gg::servert_port);
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

UserSocket ListenSocket::accept() {
    UserSocket us;
    sockaddr_in sin;
    us.s = ::accept(s, &us.useraddr, &us.len);
    memcpy(&sin, &us.useraddr, sizeof(sin));
    us.ip = inet_ntoa(sin.sin_addr);
    us.port = htons(sin.sin_port);
    return us;
}
UserSocket& UserSocket::operator= (const UserSocket& us){
    id = us.id;
    ip = us.ip;
    port = us.port;
    s = us.s;
    len = us.len;
    useraddr = us.useraddr;
}

void UserSocket::kill() {
    closesocket(s);
}
UserSocket::UserSocket(const UserSocket &us){
    id = us.id;
    ip = us.ip;
    port = us.port;
    s = us.s;
    this->len = us.len;
    useraddr = us.useraddr;
}
int UserSocket::send(string st) {
    string len = to_string(st.length()) + "|";
    len += st;
    return ::send(s, len.data(), len.length(), 0);
}

std::vector<std::string> UserSocket::recv() {
    std::vector<std::string> v;
    char recbuf[gg::buflen + 1];
    int r = ::recv(s, recbuf, gg::buflen, 0);
    if (r <= 0) {
        return v;
    }
    unsigned int beg = 0, lenend = 0;
    int len = 0;
    std::string res(recbuf);
    while (beg < res.length() && res[beg] >= '0' && res[beg] <= '9') {
        lenend = res.find("|", beg);
        len = std::stoi(res.substr(beg, lenend - beg));
        v.push_back(res.substr(lenend + 1, len));
        beg = lenend + len + 1;
    }
    return v;
}
