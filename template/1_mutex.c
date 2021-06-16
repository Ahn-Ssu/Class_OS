// POSIX mutex lock functions 
#include <pthread.h>

/*
    뮤텍스 처리 순서
        1) 생성 pthread_mutex_t 타입
        2) 초기화 : 초기화 상수를 사용하거나 함수 사용
        3) 잠금 : pthread_mutex_lock(&mutex);
        4) 해제 : pthread_mutex_unlock(&mutex);
        5) 반납 : pthread_mutex_destroy(&mutex);
*/




pthread_mutex_t myMutex;        // 뮤텍스 타입 
pthread_mutexattr_t myMuAttr;   // 원래 뮤텍스 행동양식 : 이거 보통 걍 NULL로 대체 

/* 
    1. mutex initialize 
        1) global 위치에서 mutex_t 초기화 하는 방법
        2) local 위치에서 mutex_t 초기화 하는 방법
*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(void){
    pthread_mutex_init(&mutex, NULL);

    /*
        2. 뮤텍스 잠금
            1) pthread_mutex_lock()     잠겨있으면 대기
            2) pthread_mutex_trylock()  잠겨있으면 바로 딴짓
     */

    pthread_mutex_lock(&mutex);
    pthread_mutex_trylock(&mutex); // 얘는 성공하면 0리턴, 실패시 따른거 리턴

     /*
        3. 뮤텍스 헤제
            1) pthread_mutex_unlock()   잠금 해제
     */

    pthread_mutex_unlock(&mutex);

    /* 
        4. 뮤텍스 RSS 회수 : 파괴 
    */
   pthread_mutex_destroy(&mutex);
}



