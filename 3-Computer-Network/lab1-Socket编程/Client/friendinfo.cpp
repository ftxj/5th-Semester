#include "FriendInfo.h"
#include "formattime.h"
void Myfriend::get_new_msg(std::string s){
    if(s[0] == '@'){
        std::string ss = s.substr(1);
        formatTime t(ss);
        this->friendtimeMsg.push_back(t);
    }
    else if(s[0] == '!'){
        this->friendinfoMsg.push_back(s);
    }
    this->unReadMsg.push_back(s);
    last_msg = s;
}
