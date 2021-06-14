#include <stdio.h> 
#include <time.h> 

int main() { 
  struct tm *date;
  const time_t t = time(NULL);
  
  date = localtime(&t);
  printf( "%d/%d/%d %d:%d:%d\n" ,
   date->tm_year + 1900 ,
   date->tm_mon + 1, 
   date->tm_mday, 
   date->tm_hour, 
   date->tm_min, 
   date->tm_sec ); 
   
   return 0;
    }

// https://tenlie10.tistory.com/109

// #include <stdio.h>
// #include <time.h>

// #define  BUFF_SIZE   1204

// int main()
// {
//    time_t     tm_time;
//    struct tm *st_time;
//    char       buff[BUFF_SIZE];

//    time(&tm_time);
//    st_time = localtime(&tm_time);
//    strftime(buff, BUFF_SIZE, "%Y년 %m월 %d일 - %l시 %M분 %S초 %p\n", st_time);

//    printf(buff);

//    return 0;
// }


// 출처: https://tenlie10.tistory.com/109 [유니티 게임 개발자]