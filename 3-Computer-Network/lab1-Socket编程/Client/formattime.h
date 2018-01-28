#ifndef FORMATTIME_H
#define FORMATTIME_H

#include <string>
#include <ctime>
class formatTime
{
public:
    formatTime():
        year(0), month(0), day(0),
        hour(0), min(0), sec(0){}
    formatTime(tm t):
        year(t.tm_year + 1900), month(t.tm_mon), day(t.tm_mday),
        hour(t.tm_hour), min(t.tm_min), sec(t.tm_sec){}
    formatTime(tm *t):
        year(t->tm_year + 1900), month(t->tm_mon), day(t->tm_mday),
        hour(t->tm_hour), min(t->tm_min), sec(t->tm_sec){}
    formatTime(std::string &s);
    formatTime(int tm_y, int tm_m, int tm_d, int tm_h, int tm_min, int tm_s):
        year(tm_y), month(tm_m), day(tm_d),
        hour(tm_h), min(tm_min), sec(tm_s){}
public:
    bool isearly(formatTime& t);
    bool islater_than_four_min(formatTime &t);
    bool islater_than_one_day(formatTime& t);

    std::string return_time_from_year();
    std::string return_time_from_hour();
private:
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
};

#endif // FORMATTIME_H
