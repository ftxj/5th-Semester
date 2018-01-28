#include "BasicSocket.h"

int BasicSocket::send(std::string st) {
    std::string len = std::to_string(st.length()) + "|";
    len += st;
    return ::send(s, len.data(), len.length(), 0);
}

std::vector<std::string> BasicSocket::recv() {
    std::vector<std::string> v;
    char recbuf[buflen + 1];
    memset(recbuf, 0, (buflen + 1) * sizeof(char));
    int r = ::recv(s, recbuf, buflen, 0);
    if(r == SOCKET_ERROR){
        WarringMessage(5555);
    }
    unsigned int beg = 0, lenend = 0;
    int len = 0;
    std::string res(recbuf);
    while(beg < res.length() && res[beg] >= '0' && res[beg] <= '9'){
        if(res.find("|", beg) != std::string::npos){
            lenend = res.find("|", beg);
            len = std::stoi(res.substr(beg, lenend - beg));
            while(res.length() < beg + len){
                memset(recbuf, 0, (buflen + 1) * sizeof(char));
                ::recv(s, recbuf, buflen, 0);
                res += recbuf;
            }
            v.push_back(res.substr(lenend + 1, len));
            beg = lenend + len + 1;
        }
        else{
            memset(recbuf, 0, (buflen + 1) * sizeof(char));
            ::recv(s, recbuf, buflen, 0);
            res += recbuf;
        }
    }
    return v;
}

void BasicSocket::bind() {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 0;
    addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    int nRc = ::bind(s, (LPSOCKADDR)&addr, sizeof(addr));
    if (nRc) {
        WarringMessage(WSAGetLastError());
    }
}

void BasicSocket::connect(const int server_port, const std::string server_ip) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(server_port);
    addr.sin_addr.S_un.S_addr = inet_addr(server_ip.c_str());

    int nRc = ::connect(s, (LPSOCKADDR)&addr, sizeof(addr));
    if (nRc) {
        WarringMessage(WSAGetLastError());
    }
}

void BasicSocket::WarringMessage(int errorNum){
    printf("%d\n", errorNum);
    //QMessageBox::warning(parent,"Socket 错误", std::to_string(errorNum).c_str());
}
