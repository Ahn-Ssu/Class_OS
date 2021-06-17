#include <pthread.h>

/*
    cond. var 사용하기 (monitor)
    1) mutex와 함께 운용해서 mutual exclusive 보장
    2) cond_init() 함수로 초기화  // 얘도 INITIALIZAER 있ㅇ므 PTHREAD_COND_INITIALIZER
    3) pthread_cond_wait()으로 대기
    4) pthread_cond_signal()으로 헤제
    5) pthread_cond_destroy rss 해제
*/


pthread_mutex_t mutex;  // 뮤텍스 서포터
pthread_cond_t cond;    // cond var 타입





/*
    1. cond. var init
        1) global 위치에서 cond_t 초기
        2) local 위치에서 function을 이용한 초기화 
*/
pthread_cond_t globalCond = PTHREAD_COND_INITIALIZER;


int main(){

    pthread_cond_init(&cond, NULL);

    /*
        2. cond var 잠금  
            1) pthread_cond_wait(), 뮤텍스랑 같이 잠궈버림
    */
   pthread_mutex_lock(&mutex);
   pthread_cond_wait(&cond, &mutex);

    /*
        3. cond var 해제 
            1) pthread_cond_signal()
    */ 
   pthread_cond_signal(&cond);
   pthread_mutex_unlock(&mutex);

    /*
        4. cond var 반납(파괴) 
            1) pthread_cond_destroy()
    */
   pthread_cond_destroy(&cond);
   pthread_mutex_destroy(&mutex);
}


