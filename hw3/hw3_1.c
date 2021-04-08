#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> 
#include <sys/time.h>


int main(int argc, char*argv[]){


  float req_delay;
  req_delay = argv[1]==NULL? 0 :atof(argv[1]);

  struct tm date;
  const time_t t = time(NULL);

  date = *localtime(&t);
    
  printf("current date = %d/%d/%d\n", date.tm_year+1900, date.tm_mon+1, date.tm_mday);
  printf("current time = %d:%d:%d\n",date.tm_hour, date.tm_min, date.tm_sec); 

  printf("\n");
  printf("waiting for %f sec using usleep()\n", req_delay);
  printf("\n");

  struct timeval start_time, end_time;
  struct tm start, end;
  
  
  gettimeofday(&start_time, NULL);
  start = *localtime(&start_time.tv_sec);
  usleep(req_delay*1000*1000);
  gettimeofday(&end_time, NULL);
  
  end = *localtime(&end_time.tv_sec);

  printf("start_time = (%ld %ld), %d:%d:%d\n", start_time.tv_sec, start_time.tv_usec, start.tm_hour, start.tm_min, start.tm_sec);
  printf("end_time   = (%ld %ld), %d:%d:%d\n", end_time.tv_sec, end_time.tv_usec, end.tm_hour, end.tm_min, end.tm_sec);
  printf("elapsed time = %ld.%06ld sec\n",end_time.tv_sec-start_time.tv_sec, end_time.tv_usec-start_time.tv_usec);  

}