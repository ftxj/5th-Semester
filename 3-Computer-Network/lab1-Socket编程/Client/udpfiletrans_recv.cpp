#include "udpfiletrans_recv.h"
namespace rdt_recv{

udpFileTrans_Recv::udpFileTrans_Recv()
{

}
void udpFileTrans_Recv::begin(){
    if (NULL == (pfile_recv = fopen("recv.mkv", "wb"))) {
            printf("error when open file");
    }
    std::thread recv_thread(thread_function_recv, this);
    std::thread send_thread(thread_function_send, this);

    recv_thread.join();
    send_thread.join();
}

void udpFileTrans_Recv::get_fileLen(long fileLen){
    recv_file_length = fileLen;
}

void udpFileTrans_Recv::get_port(int p){
    WSAData wD;
    WSAStartup(wVersionRequest, &wD);

    client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    client_addr.sin_port = htons(p);

    if (bind(client_socket, (sockaddr*)&client_addr, sizeof(sockaddr_in)) == -1) {
        printf("bind error\n");
    }
}


void udpFileTrans_Recv::thread_function_recv(){
    char recv_buf_temp[1472 * 50];
    memset(recv_buf_temp, 0, 1472 * 50 * sizeof(char));
    long ack = 0, last_ack = 0, temp_ack;
    long orderd_last_ack = 0;
    long one_package_length = 0;
    long one_step_recv_bytes, one_step_remain_bytes;
    long gap, gap_size, recv_buf_base = 0;
    long package_begin = 0, one_step_size = 0, write_size = 1472 - 2 * sizeof(long);


    int flag_of_big = 0;
    memset(p_to_msgs_flag, -1, length_of_window_width * sizeof(long));

    while (recv_bytes_sum < recv_file_length) {
        one_step_recv_bytes = recvfrom(client_socket, recv_buf_temp, 1472 * 50 * sizeof(char), 0, (sockaddr*)&server_addr, &len);
        while (one_step_recv_bytes % length_of_recv_buf != 0) {
            one_step_recv_bytes += recvfrom(client_socket, recv_buf_temp + one_step_recv_bytes, 1472 * 50 * sizeof(char) - one_step_recv_bytes, 0, (sockaddr*)&server_addr, &len);
        }
        one_step_size = one_step_recv_bytes / length_of_recv_buf;
        for (int i = 0; i < one_step_size; ++i) {
            memcpy(&ack, recv_buf_temp + i * length_of_recv_buf, sizeof(long));
            memcpy(&last_ack, recv_buf_temp + i * length_of_recv_buf + sizeof(long), sizeof(long));

            while (ack <= orderd_last_ack && i + 1 < one_step_size) {
                i++;

                tm_ack_lost.lock();
                ack_lose_flag = ack_lose_flag >= 3 ? ack_lose_flag : ack_lose_flag + 1;
                tm_ack_lost.unlock();

                memcpy(&ack, recv_buf_temp + i * 1472, sizeof(long));
                memcpy(&last_ack, recv_buf_temp + i * 1472 + sizeof(long), sizeof(long));
            }

            if (ack <= orderd_last_ack) {
                tm_ack_lost.lock();
                ack_lose_flag = ack_lose_flag >= 3 ? ack_lose_flag : ack_lose_flag + 1;
                tm_ack_lost.unlock();
                continue;
            }

            if (orderd_last_ack == last_ack) {
                if (ack == recv_file_length) {
                    write_size = recv_file_length - last_ack;
                }
                recv_bytes_sum += length_of_write_buf;

                p_to_msgs_flag[recv_buf_base] = ack;
                memcpy(p_to_msgs + length_of_write_buf * recv_buf_base, recv_buf_temp + i * length_of_recv_buf + 2 * sizeof(long), write_size * sizeof(char));
                recv_buf_base = (recv_buf_base + 1) % length_of_window_width;
                if (left_window == 1) {
                    left_window_size++;
                }
                else if (right_window == 1) {
                    right_window_size++;
                }

                while (ack < p_to_msgs_flag[recv_buf_base]) {
                    ack = p_to_msgs_flag[recv_buf_base];
                    recv_buf_base = (recv_buf_base + 1) % length_of_window_width;
                    orderd_last_ack = ack;
                }
                orderd_last_ack = ack;

                if (left_window == 1 && left_window_size == length_of_window_width / 2) {
                    memset(p_to_msgs_flag,  -1, (length_of_window_width / 2 )* sizeof(long));
                    fwrite(p_to_msgs, sizeof(char), length_of_write_buf * left_window_size, pfile_recv);
                    left_window_size = 0;
                    right_window = 1;
                    left_window = 0;
                }
                else if (right_window == 1 && right_window_size == length_of_window_width / 2) {
                    memset(p_to_msgs_flag + (length_of_window_width / 2), -1, right_window_size * sizeof(long));
                    fwrite(p_to_msgs + length_of_write_buf * right_window_size, sizeof(char), length_of_write_buf * right_window_size, pfile_recv);
                    right_window_size = 0;
                    left_window = 1;
                    right_window = 0;
                }
            }
            else{
                flag_of_big += 1;
                gap = ack - orderd_last_ack;
                gap_size = gap / length_of_write_buf - 1;
                if (gap % length_of_write_buf != 0) {
                    gap_size += 1;
                }

                if (left_window == 1 && gap_size + recv_buf_base < length_of_window_width
                    && p_to_msgs_flag[gap_size + recv_buf_base] < ack) {

                    p_to_msgs_flag[gap_size + recv_buf_base] = ack;

                    if (gap_size + recv_buf_base >= length_of_window_width / 2)
                        right_window_size++;
                    else
                        left_window_size++;

                    recv_bytes_sum += length_of_write_buf;

                    memcpy(p_to_msgs + length_of_write_buf * (gap_size + recv_buf_base), recv_buf_temp + i * 1472 + 2 * sizeof(long), write_size * sizeof(char));
                }
                else if (right_window == 1 && (gap_size + recv_buf_base % (length_of_window_width / 2) < length_of_window_width)
                    && p_to_msgs_flag[(gap_size + recv_buf_base) % length_of_window_width] == -1){
                    p_to_msgs_flag[(gap_size + recv_buf_base) % length_of_window_width] = ack;

                    if (gap_size + recv_buf_base >= length_of_window_width)
                        left_window_size++;
                    else
                        right_window_size++;

                    recv_bytes_sum += 1472 - 2 * sizeof(long);
                    memcpy(p_to_msgs + length_of_write_buf * ((gap_size + recv_buf_base) % length_of_window_width),  recv_buf_temp + i * 1472 + 2 * sizeof(long), write_size * sizeof(char));
                }

                tm_ack_lost.lock();
                ack_lose_flag = ack_lose_flag >= 3 ? ack_lose_flag : ack_lose_flag + 1;
                tm_ack_lost.unlock();
            }
        }
        tm_send_ack.lock();
        send_ack = orderd_last_ack;
        tm_send_ack.unlock();
    }
    if (left_window == 1) {
        fwrite(p_to_msgs, sizeof(char), left_window_size * length_of_write_buf, pfile_recv);
        fwrite(p_to_msgs + length_of_window_width / 2, sizeof(char), length_of_write_buf * right_window_size, pfile_recv);
    }
    else {
        fwrite(p_to_msgs + length_of_window_width / 2, sizeof(char), length_of_write_buf * right_window_size, pfile_recv);
        fwrite(p_to_msgs, sizeof(char), left_window_size * length_of_write_buf, pfile_recv);
    }
}

void udpFileTrans_Recv::thread_function_send(){
    long last_ack = 0, last_resend_ack = 0;
    int x = 0;
    clock_t gap_time = clock();
    while (last_ack < recv_file_length) {
        tm_ack_lost.lock();
        if (ack_lose_flag >= 1){
            ack_lose_flag--;
        tm_ack_lost.unlock();
        //x++;
        //if(x == 3){
            sendto(client_socket, (char*)(void*)&send_ack, sizeof(long), 0, (sockaddr*)&server_addr, len);
           // x = 0;
        //}            //std::cout << send_ack << "\n";
        }
        else {
            tm_ack_lost.unlock();
        }

        tm_send_ack.lock();
        if (last_ack  < send_ack) {

            sendto(client_socket, (char*)(void*)&send_ack, sizeof(long), 0, (sockaddr*)&server_addr, len);

            last_ack = send_ack;
            //std::cout << send_ack << "\n";
        }
        tm_send_ack.unlock();
    }
}

}
