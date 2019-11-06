#include "../Include/Time.h"

enum{
SECONDS, MINUTES, HOURS, DAYOFWEEK, DAYOFMONTH, MONTH, YEAR
};
extern void __time__(int id, int * time);

int getTime(int id);

int GetSeconds(){
    return getTime(SECONDS);
}

int GetMinutes(){
    return getTime(MINUTES);
}

int GetHours(){
    return getTime(HOURS);
}

int GetDayOfWeek(){
    return getTime(DAYOFWEEK);
}

int GetDayOfMonth(){
    return getTime(DAYOFMONTH);
}

int GetMonth(){
    return getTime(MONTH);
}

int GetYear(){
    return getTime(YEAR);
}


int getTime(int id){
    int time = -1;
    __time__(id,&time);

    return time;
}