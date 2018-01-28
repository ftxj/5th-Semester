#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include <QMessageBox>
#include <WinSock2.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <list>
#include <algorithm>
#include <string>
#include <thread>
#include <cstring>
#include <ctime>
const std::string server_ip = "192.168.1.105";

const int server_port = 66008;
const int user_server_port = 9090;

const int self_user_port = 8989;

const unsigned int buflen = 255;


const WORD	wVersionRequest = 0x1001;

namespace rdt_send {
    const long length_of_max_send_window = 150;
    const long length_of_window_width = 5000;
    const long length_of_send_buf = 1472;
    const long length_of_fread_buf = 1472 - 2 * sizeof(long);
}


namespace rdt_recv {
    const int client_port = 33889;
    const long length_of_window_width = 300;
    const long length_of_recv_buf = 1472;
    const long length_of_write_buf = 1472 - 2 * sizeof(long);
}

#endif // GLOBALVAR_H

