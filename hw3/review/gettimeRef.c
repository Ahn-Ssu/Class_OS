#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
    struct timeval mytime;

    // 현재 시간을 얻어온다.
    gettimeofday(&mytime, NULL);
    printf("%ld:%ld\n", mytime.tv_sec, mytime.tv_usec);

    // 시간을 1시간 뒤로 되돌려서 설정한다.
    mytime.tv_sec -= 3600;
    settimeofday(&mytime, NULL);
    return 0;
}

// struct timeval tv; 
// time_t nowtime﻿;
// struct tm *nowtm;
// char tmbuf[64], buf[64];
// gettimeofday(&tv, NULL);
// nowtime = tv.tv_sec;
// nowtm = localtime(&nowtime);
// strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);
// snprintf(buf, sizeof buf, "%s.%06d", tmbuf, tv.tv_usec); 