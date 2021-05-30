/*

	This program drops down multiple balls by multiple threads.
	There is a critical region specified by the top and bottom coordinates.

	Mission: 
		[IMPORTANT] Read this code carefully and fully understand.
		Modify the code to ensure that only one ball can enter the critical region at a time.

	Hints) 
		1. Pass the top and bottom coordinates of the critical section to the threads through the ThreadParam structure
		2. Create and initialize pthread_mutex_t as a global variable
		3. When a ball enters the critical region, lock the mutex (entry section)
		4. When a ball leaves the critical region, unlock the mutex (exit section)
		5. If the thread breaks the loop while the ball is in the critical region, unlock the mutex to release other threads.
		6. After the threads finishes, destroy all mutexes.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>

#include "Console.h"

#define TRUE 1
#define FALSE 0

#define MAX_THREAD 30

typedef struct {
	int thread_idx;
	int no_thread;
	int screen_height;
	int x;
	int delay;

	// TO DO: add fields to pass the vertical coordinates of the critical region
	// 해당 field가 각 스레드들의 progress를 보장해준다고 생각된다.
	int vertica; 


} ThreadParam;
int thread_cont = TRUE;

void* ThreadFn(void *vParam);

// TO DO: declare and initialize a mutex as a global variable
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sema;
// pthread_mutex_init(&mutex, NULL); err?
// 메인 함수 밖에서 함수를 호출하려는 동작을 하게 되면 C언어의 문법상 함수의 선언(declare)으로 컴파일러가 해석을 함


int main(int argc, char *argv[])
{	
	sem_init(&sema,0, 3);
	srand(time(NULL));
	clrscr();

	int no_thread = 0;
	if(argc > 1)
		no_thread = atoi(argv[1]);

	if(no_thread > MAX_THREAD)
		no_thread = MAX_THREAD;
	else if(no_thread == 0)
		no_thread = 5;

	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	// the top and bottom coordinates of the critical region
	int critical_top = screen_height / 3;
	int critical_bottom = screen_height * 2 / 3;

	// mark the critical region by horizontal lines
	DrawLine(1, critical_top, screen_width, critical_top, '-');
	DrawLine(1, critical_bottom, screen_width, critical_bottom, '-');
	
	pthread_t tid[MAX_THREAD];
	ThreadParam param[MAX_THREAD];
	

	for(int i = 0; i < no_thread; i++){
		param[i].thread_idx = i;
		param[i].no_thread = no_thread;
		param[i].screen_height = screen_height;
		param[i].x = screen_width * (i + 1) / (no_thread + 1);
		param[i].delay = rand() % 300;

		// TO DO: add code to store the vertical coordinates of the critical region in param[i]
		param[i].vertica  = critical_top;

		pthread_create(&tid[i], NULL, ThreadFn, &param[i]);
	}

	PrintXY(1, screen_height + 1, "Press Enter to quit!\n");
	getchar();

	// termainte the threads
	thread_cont = FALSE;

	for(int i = 0; i < no_thread; i++)
		pthread_join(tid[i], NULL);

	// TO DO: destroy mutex
	sem_destroy(&sema);

	clrscr();
	gotoxy(1, 1);
	printf("Bye!\n");

	return 0;
}

void* ThreadFn(void *vParam)
{
	ThreadParam *param = (ThreadParam*)vParam;

	int y = 1;
	int oldy = 1;

	while(thread_cont){
		// TO DO: implement entry section here 

		if (y==param->vertica){
			sem_wait(&sema);
		}
		

		gotoxy(param->x, oldy);
		putchar(' ');

		gotoxy(param->x, y);
		putchar('*');

		fflush(stdout);

		// TO DO: implement exit section here
		if ( y==(param->screen_height - param->vertica))
			sem_post(&sema);

		oldy = y;
		y++;
		if(y > param->screen_height)
			y = 1;

		gotoxy(1, 1);
		fflush(stdout);
		usleep(param->delay * 1000);
	}

	// TO DO: if current broke loop in the critical region, unlock mutex
	if (!thread_cont){
		sem_post(&sema);
	}
	


	return NULL;
}

