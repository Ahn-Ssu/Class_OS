#include <semaphore.h>

/*
    세마포어 처리 순서
        1) 생성 : sem_t 타입으로 생성이 됩니다.
        2) 초기화 : 오직 함수만을 이용해서 초기화 할 수 있습니다. initializer로 초기화 불가능
        3) 잠금 : sem_wait() ; mutex는 lock점과 다릅니당 
        4) 해제 : sem_post() ; mutex는 unlock입니다.
        5) 반납 : sem_destroy() ; 
*/



sem_t mySem;    // 세마포어 타입!
int S = 200;    // 세마포어의 티켓수를 결정하기 위한 내가만든 변수

int main()
{
    /* 
        0. 세마포어의 사용
            세마포어의 동작지정은 모두 함수 안에서 function call형태로 지정이 된다. 
            초기화도 마찬가지임.
    */

    /* 
        1. 세마포어 초기화
            sem_init(세마포어 버퍼, 공유여부, 세마포어 초기 S 값);
    /*/
    sem_init(&mySem, 0, S);


    /* 
        2. 세마포어 잠금(진입)
            1) sem_wait()
    */
    sem_wait(&mySem);

    /* 
        2. 세마포어 해제(탈출)
            1) sem_post();
    */
    sem_post(&mySem);

    /* 
        4. 세마포어 RSS 회수 : 파괴
            1) sem_destroy()
    */
    sem_destroy(&mySem);
}