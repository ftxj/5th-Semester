#include "udpFileTrans.h"
namespace rdt_send {
UdpFileTrans::UdpFileTrans(){
    pfile_send = NULL;
    sever_socket = 0;
    job_done = false;
    base = 0, next_pcg = 0, unfill_base = 0;
    not_sure_pcgs_tol_num = 0, wait_send_and_sure = 0;
    ack = 0;
    msgs_length[length_of_window_width];
    next_not_sure_seq = 0, three_ack = 0;
    file_length = 0;
    next_not_read_seq = 0, last_read_seq = 0;
}

long UdpFileTrans::getSumSend(){
    return ack;
}
long UdpFileTrans::getFileLen(){
    return file_length;
}
void UdpFileTrans::setIpPort(std::string s, int i){
    WSAData wD;
    ip = s;
    port = i;
    WSAStartup(wVersionRequest, &wD);
    sever_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(INVALID_SOCKET == sever_socket){
        printf("error %d\n", WSAGetLastError());
    }

    sever_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    sever_addr.sin_family = AF_INET;
    sever_addr.sin_port = 0;
    if(bind(sever_socket,(LPSOCKADDR)&sever_addr, sizeof(sever_addr))){
        printf("error when bind UDP socket");
    }

    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.S_un.S_addr = inet_addr(s.c_str());
    client_addr.sin_port = htons(i);
}

void UdpFileTrans::setFile(std::string s){
    filename = s;
    if (NULL == (pfile_send = fopen(filename.c_str(), "rb"))) {
        printf("error when open file");
    }

    fseek(pfile_send, 0, SEEK_END);
    file_length = ftell(pfile_send);
    fseek(pfile_send, 0, SEEK_SET);
}

void UdpFileTrans::begin(){

    std::thread read_thread(thread_function_fileRead, this);
    std::thread send_thread(thread_function_sendto, this);
    std::thread recv_thread(thread_function_recvACK, this);
    std::thread time_thread(thread_function_timer, this);

    read_thread.join();
    send_thread.join();
    recv_thread.join();
    time_thread.join();

    fclose(pfile_send);
    closesocket(sever_socket);
}

void UdpFileTrans::thread_function_fileRead() {
    clock_t t = clock();
    while (!feof(pfile_send)) {
        tm_var.lock();
        if ((base < next_pcg && (unfill_base < base || unfill_base >= next_pcg)) ||
            (base > next_pcg && (unfill_base >= next_pcg && unfill_base < base)) ||
            (base == next_pcg && wait_send_and_sure < length_of_window_width)) {
        tm_var.unlock();

            next_not_read_seq += fread(p_to_msgs[unfill_base] + 2 * sizeof(long), sizeof(char), length_of_fread_buf, pfile_send);
            memcpy(p_to_msgs[unfill_base], &next_not_read_seq, sizeof(long));
            memcpy(p_to_msgs[unfill_base] + sizeof(long), &last_read_seq, sizeof(long));

            last_read_seq = next_not_read_seq;

            msgs_length[unfill_base] = next_not_read_seq;
            unfill_base = (unfill_base + 1) % length_of_window_width;

            tm_var.lock();
            wait_send_and_sure += 1;
            tm_var.unlock();
        }
        else {
            tm_var.unlock();
        }
    }
    tm_std_out.lock();
    std::cout << "read thread complete" << clock() - t << std::endl;
    tm_std_out.unlock();
}

void UdpFileTrans::thread_function_sendto() {
    clock_t t = clock();
    int temp;
    while (job_done == false) {
        tm_var.lock();
        if ((
                ((next_pcg >= base) && (next_pcg - base) < length_of_max_send_window
                    && wait_send_and_sure > (next_pcg - base)) ||
                ((base > next_pcg)  && (length_of_window_width - base + next_pcg) < length_of_max_send_window
                    && wait_send_and_sure > (length_of_window_width - base + next_pcg)) ||
                (three_ack)
            )){
        tm_var.unlock();
            if (three_ack == 1) {
                three_ack = 0;
                long x;
                memcpy(&x, p_to_msgs[base], sizeof(long));

                tm_std_out.lock();
                //std::cout << "	three ack " << x << "\n";
                tm_std_out.unlock();
                //std::cout << "resend"  << x  << "\n";
                tm_write_socket.lock();
                int xxxx = sendto(sever_socket, p_to_msgs[base], length_of_send_buf * sizeof(char), 0, (sockaddr*)&client_addr, sizeof(sockaddr));
                if(xxxx == -1){
                    int errorcode = WSAGetLastError();
                    printf("%d\n", errorcode);
                    continue;
                }
                tm_write_socket.unlock();
            }
            else {
                temp = next_pcg;
                tm_var.lock();
                next_pcg = (next_pcg + 1) % length_of_window_width;
                tm_var.unlock();
                long x;
                memcpy(&x, p_to_msgs[temp], sizeof(long));

                tm_write_socket.lock();
                int xxxx = sendto(sever_socket, p_to_msgs[temp], length_of_send_buf * sizeof(char), 0, (sockaddr*)&client_addr, sizeof(sockaddr));
                if(xxxx == -1){
                    int errorcode = WSAGetLastError();
                    printf("%d\n", errorcode);
                    continue;
                }
                //printf("send %d", x);
                tm_write_socket.unlock();
            }
        }
        else {
            tm_var.unlock();
        }
    }
    tm_std_out.lock();
    std::cout << "send thread complete" << clock() - t << std::endl;
    tm_std_out.unlock();
}

void UdpFileTrans::thread_function_recvACK() {
    clock_t beg = clock();
    int counter = 0;
    long last_recv = 0;
    int len = sizeof(sockaddr_in);
    while (job_done == false) {
        if (base == next_pcg) {
            continue; 
        }
        int xxx = recvfrom(sever_socket, (char*)(void*)&ack, sizeof(long), 0, (sockaddr*)&client_addr, &len);
        if(xxx == -1){
            int errorcode = WSAGetLastError();
            printf("%d\n", errorcode);
            continue;
        }
        //printf("recv %d\n", ack);
        if (ack >= file_length) {
            printf("recv success");
            job_done = true;
            return;
        }
        else if (ack == last_recv) {
            counter++;
            if (counter == 2) {
                counter = 0;
                tm_write_socket.lock();
                three_ack = 1;
                tm_write_socket.unlock();
            }
        }
        else if (ack > last_recv) {
            counter = 1;
            last_recv = ack;
            //*now_bytes = ack;
            tm_var.lock();
            while (msgs_length[base] <= ack && base != next_pcg) {
                base = (++base) % length_of_window_width;
                wait_send_and_sure--;
            }
            tm_var.unlock();
        }
    }
}

void UdpFileTrans::thread_function_timer() {
    long timer_front_ack = 0;
    long now_ack = 0;
    while (job_done == false) {
        std::this_thread::sleep_for(std::chrono::milliseconds(400));

        tm_var.lock();
        now_ack = msgs_length[base];
        tm_var.unlock();

        if (timer_front_ack == now_ack) {
            tm_write_socket.lock();
            tm_var.lock();
            for (int i = base; i != next_pcg; ++i) {
                sendto(sever_socket, p_to_msgs[base], length_of_send_buf * sizeof(char), 0, (sockaddr*)&client_addr, sizeof(sockaddr));
            }
            tm_var.unlock();
            tm_write_socket.unlock();
            long x;
            memcpy(&x, p_to_msgs[base], sizeof(long));
            tm_std_out.lock();
            std::cout << "			timeout resend" << x << "\n";
            tm_std_out.unlock();    
        }

        timer_front_ack = now_ack;
    }
}

}
