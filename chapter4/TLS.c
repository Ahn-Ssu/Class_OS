#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREADS 3

__thread int tls;
int global;

void *func(void *arg)
{
    int num = (int)arg;
    tls = num;
    global = num;
    sleep(1);
    printf("Thread = %d | tls = %d | global = %d \n", num, tls, global);
}

int main()
{
    int ret;
    int num;
    pthread_t thread[THREADS];

    for (num = 0; num < THREADS; num++)
    {
        ret = pthread_create(&thread[num], NULL, &func, (void *)num);

        if (ret)
        {
            printf("error pthread_create\n");
            exit(1);
        }
    }

    for (num = 0; num < THREADS; num++)
    {
        ret = pthread_join(thread[num], NULL);

        if (ret)
        {
            printf("error pthread_join\n");
            exit(1);
        }
    }

    return 0;
}