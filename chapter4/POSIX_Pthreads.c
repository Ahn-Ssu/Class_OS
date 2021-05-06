#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum;
void *runner(void *param);

int main(int argc, char *argv[]){
    pthread_t tid;
    pthread_attr_t attr;

    if (argc < 2){
        fprintf(stderr, "usage: a.out <integer>\n");
        exit(0);
    }

    if (atoi(argv[1]) < 0 ){
        fprintf(stderr, "%d must be <= 0\\n", atoi(argv[1]));
        exit(0);
    }

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner, argv[1]); // 함수는 그냥 줘도, &를 붙여도 주소로 전달이 됨

    pthread_join(tid, NULL);

    printf("sum = %d\n", sum);
    return 0;
}

void *runner (void *param){
    int upper = atoi(param);
    int i;
    sum = 0;

    if (upper > 0 ){
        for ( i = 1 ; i <= upper ; i++) sum += i;
    }

    pthread_exit(0);
}