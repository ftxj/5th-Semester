#include "formattime.h"

formatTime::formatTime(std::string &s){
    year = std::stoi(s.substr(0, s.find('/')));
    month = std::stoi(s.substr(s.find('/') + 1, s.find_last_of('/') - s.find('/') - 1));
    day = std::stoi(s.substr(s.find_last_of('/') + 1, s.find_first_of(' ') - s.find_last_of('/') - 1));
    hour = std::stoi(s.substr(s.find(' ') + 1, s.find(':') - s.find(' ') - 1));
    min = std::stoi(s.substr(s.find(':') + 1, 2));
    sec = std::stoi(s.substr(s.find_last_of(':') + 1, 2));
}
bool formatTime::isearly(formatTime &t){
    if(year < t.year){
        return true;
    }
    if(t.year < year){
        return false;
    }
    if(month < t.month){
        return true;
    }
    if(month > t.month){
        return false;
    }
    unsigned long long t1 = sec + min * 100 + hour * 100 * 100 + day * 100 * 100 * 100;
    unsigned long long t2 = t.sec + t.min * 100 + t.hour * 100 * 100 + t.day * 100 * 100 * 100;
    return t1 < t2;
}

bool formatTime::islater_than_one_day(formatTime &t){
    return !isearly(t) && (year != t.year || month != t.month || day != t.day);
}

bool formatTime::islater_than_four_min(formatTime &t){
    if(year < t.year){
        return false;
    }
    if(t.year < year){
        return true;
    }
    if(month < t.month){
        return false;
    }
    if(month > t.month){
        return true;
    }
    unsigned long long t1 = sec + min * 100 + hour * 100 * 100 + day * 100 * 100 * 100;
    unsigned long long t2 = t.sec + t.min * 100 + t.hour * 100 * 100 + t.day * 100 * 100 * 100;
    return t1 >= t2 + 400;
}

std::string formatTime::return_time_from_hour(){
    std::string fmt;
    fmt += std::to_string(hour);
    fmt += ":";
    if(min < 10){
        fmt += "0";
    }
    fmt += std::to_string(min);
    fmt += ":";
    if(sec <10){
        fmt += "0";
    }
    fmt += std::to_string(sec);
    return fmt;
}

std::string formatTime::return_time_from_year(){
    std::string fmt;
    fmt += std::to_string(year);
    fmt += "/";
    fmt += std::to_string(month);
    fmt += "/";
    fmt += std::to_string(day);
    fmt += " ";
    fmt += return_time_from_hour();
    return fmt;
}
