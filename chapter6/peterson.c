#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <unistd.h>
#include <pthread.h>


void* ThreadFn(void *vParam);

typedef struct{
    int thread_idx;
    int *flag;
} ThreadParam;

int turn = 0 ;

int thread_cont = 1;

int main(int argc, char *argv[])
{

    pthread_t tid[2];
    ThreadParam param[2];

    int flag[2] = {0};

    for(int i = 0 ; i < 2 ; i ++){
        param[i].thread_idx = i;
        param[i].flag = flag;

        pthread_create(&tid[i], NULL, ThreadFn, &param[i]);
    }

	getchar();

	// termainte the threads
	thread_cont = 0;
	printf("Bye!\n");

	return 0;
}

void* ThreadFn(void *vParam)
{
	ThreadParam *param = (ThreadParam*)vParam;

	int idx = param->thread_idx;
    int *flag = param->flag;

    while(thread_cont){

        flag[idx] = 1;
        turn = (idx + 1)%2;

        printf("나는 pid%d다.\n\t현재 flag [%d, %d]\n\t현재 turn %d\n",idx, flag[0], flag[1], turn);
        while( flag[idx] && turn ==(idx+1)%2);

        printf("Critical section I'm pthread % d\n", idx);
        usleep((rand() % 500 + 1000) * 1000);

        flag[idx] = 0;
        turn = (idx + 1)%2; // added 이걸 더해서(?) 0101_00_1 같은 패턴이 생김, 안더하면 무조건 010101010101
        if (idx % 2 == 0 ) usleep((rand() % 500 + 100) * 100);
        else usleep((rand() % 500 + 1000) * 1000);
    }
	


	return NULL;
}
