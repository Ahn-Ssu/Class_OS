#include <signal.h>
#include <stdio.h>
#include <unistd.h> // 여기에 슬립 있음 

/*      Defining sinal handler 
    typedef void (*sighandler_t)(int);
    sighandler_t signal(int signum, sighandler_t handler);
*/

void sig_handler(int sigNo);

// 이제 프로그램이 ctnl + c 로는 안죽고, 오버라이드 한 함수의 동작이 수행 됨 
int main(){
    int i = 0 ;
    signal(SIGINT, (void *)sig_handler);

    while(1){
        printf("%d \n", i++);
        sleep(1);
    }
    return 1;
}

void sig_handler(int signo){
    printf("SIGINT was received!\n");
}