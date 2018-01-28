#ifndef UDPFILETRANS_RECV_H
#define UDPFILETRANS_RECV_H
#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <time.h>
#include <string>
#include <mutex>
#include <ctime>
#include <iostream>
#include "globalvar.h"
namespace rdt_recv {

class udpFileTrans_Recv
{
public:
    udpFileTrans_Recv();
    void begin();
    void get_fileLen(long fileLen);
    void get_port(int p);
private:
    void thread_function_recv();
    void thread_function_send();
private:
    SOCKET client_socket;
    sockaddr_in client_addr, server_addr;
    int len = sizeof(sockaddr_in);
    FILE *pfile_recv = NULL;

    char p_to_msgs[length_of_window_width * length_of_write_buf];
    long p_to_msgs_flag[length_of_window_width];
    int left_window = 1, right_window = 0;
    int left_window_size = 0, right_window_size = 0;
    long p_to_ack[length_of_window_width];

    long recv_file_length = 0;
    long recv_bytes_sum = 0;
    int ack_lose_flag = 0;
    long send_ack = 0, re_send_ack = 0;
    int recv_buf_size = 0;
    std::mutex tm_send_ack, tm_ack_lost, tm_p_to_msgs;
};

}
#endif // UDPFILETRANS_RECV_H
