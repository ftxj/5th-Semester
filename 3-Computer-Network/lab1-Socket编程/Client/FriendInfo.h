#ifndef FRIENDINFO_H
#define FRIENDINFO_H
#include "usersocket.h"
#include "formattime.h"
#include "personitem.h"
class Myfriend{
public:
    void get_new_msg(std::string);
    std::string id;
    std::string ip;
    int port;

    UserSocket* pus;
    personItem* vec;

    formatTime last_send_or_recv;
    std::string last_msg;
    std::vector<std::string> friendinfoMsg;
    std::vector<formatTime> friendtimeMsg;

    std::vector<std::string> myinfoMsg;
    std::vector<formatTime> mytimeMsg;

    std::vector<std::string> unReadMsg;

};

#endif // FRIENDINFO_H
