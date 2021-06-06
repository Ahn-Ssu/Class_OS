/*
	hw7_1.c and hw7_1_main.c are the solution of the Dining Philosophers Problem using Moniter.
	This program implements the concept of Monitor using functions, pthread_mutex_t and pthread_cond_t.

	Following the instructions, complete this program

	Compilation:
		gcc hw7_1.c hw7_1_main.c Console.c -pthread -lm

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <unistd.h>
#include <pthread.h>

#include "Console.h"

#include "hw7_1.h"


#define DEFAULT_NO_PHIL 5

typedef struct {
	int phil_idx;
	int no_phil;

	Philosophers *dp;
	int screen_width;
	int screen_height;
} ThreadParam;

int thread_cont = TRUE;
void* ThreadFn(void *vParam);

int main(int argc, char *argv[])
{
	int no_phil = 0;
	if(argc > 1)
		no_phil = atoi(argv[1]);
	if(no_phil <= 0)
		no_phil = DEFAULT_NO_PHIL;

	srand(time(NULL));
	clrscr();

	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	pthread_t tid[MAX_PHIL];
	ThreadParam param[MAX_PHIL];

	Philosophers dp;
	// TO DO: initialize dp using no_phil
	Philosophers_Init(&dp, no_phil);

	Philosophers_Display(&dp, screen_width, screen_height);

	for(int i = 0; i < 1; i++){
		param[i].phil_idx = i;
		param[i].no_phil = no_phil;

		param[i].dp = &dp;
		param[i].screen_width = screen_width;
		param[i].screen_height = screen_height;

		// TO DO: create thread using ThreadFn and param[i] 
		pthread_create(&tid[i], NULL, ThreadFn, &param[i]);
	}

	PrintXY(1, 1, "Press 'q' to quit!\n");
	
	// Check key stroke and philosopher states every 0.1 sec.
	while(1){
		gotoxy(1, 1);
		if(kbhit() && getch() == 'q')		// if 'q' was pressed, break the loop
			break;

		Philosophers_Check(&dp);

		usleep(100000);
	}

	// TO DO: terminate threads using thread_cont
	thread_cont = FALSE;

	// TO DO: wait for the threads
	for(int i = 0; i < no_phil; i++){
		pthread_join(tid[i], NULL);
	}

	// TO DO: destroy dp
	Philosophers_Destroy(&dp);

	clrscr();
	printf("Bye!\n");

	return 0;
}

void* ThreadFn(void *vParam)
{
	ThreadParam *param = (ThreadParam*)vParam;

	Philosophers *dp = param->dp;
	int idx = param->phil_idx;

	while(thread_cont){
		// picking up
		Philosophers_PickUp(dp, idx);

		Philosophers_Check(dp);

		// eating
		Philosophers_Display(dp, param->screen_width, param->screen_height);
		usleep((rand() % 500 + 500) * 1000);

		// putting down
		Philosophers_PutDown(dp, idx);

		// thinking
		Philosophers_Display(dp, param->screen_width, param->screen_height);
		usleep((rand() % 500 + 1000) * 1000);
	}

	return NULL;
}

