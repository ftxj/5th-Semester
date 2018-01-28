#ifndef UDPFILETRANS_H
#define UDPFILETRANS_H
#include <QObject>
#include <WinSock2.h>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include "globalvar.h"
#include <iostream>
#include <string>
#include <list>
#include <mutex>
namespace rdt_send {

class UdpFileTrans{
public:
    UdpFileTrans();
    long getSumSend();
    void setFile(std::string);
    void setIpPort(std::string, int);
    long getFileLen();
    void begin();
public:
    long ack = 0;
private:
    void thread_function_fileRead();
    void thread_function_sendto();
    void thread_function_recvACK();
    void thread_function_timer();
private:
    std::string filename;
    std::string ip;
    int port;
private:
    FILE *pfile_send = NULL;
    SOCKET sever_socket = 0;
    sockaddr_in client_addr, sever_addr;
    char send_buf[length_of_send_buf];


    bool job_done = false;
    char p_to_msgs[length_of_window_width][length_of_send_buf];
    volatile int base = 0, next_pcg = 0, unfill_base = 0;
    volatile int not_sure_pcgs_tol_num = 0, wait_send_and_sure = 0;
    volatile long msgs_length[length_of_window_width];

    long next_not_sure_seq = 0, three_ack = 0;
    long file_length = 0;
    
    long next_not_read_seq = 0, last_read_seq = 0;
    clock_t clk;
    std::mutex tm_write_buf, tm_write_socket, tm_write_base, tm_write_not_sure_pcgs_tol_num, tm_write_clk;
    std::mutex tm_wait_send_and_sure, tm_write_next_pcg, tm_var;
    std::mutex tm_std_out;
};
}

#endif // UDPFILETRANS_H
