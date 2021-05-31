/*

	This program drops down multiple balls by multiple threads.
	There is a critical region specified by the top and bottom coordinates.

	Mission:
		Read this code carefully and fully understand.
		Following the instructions, complete the code to ensure that only a fixed number (say, k) of balls can enter the critical region at each moment.
		(2 <= k < (<the number of balls> + 1) / 2)
		The program run similarly to the demo video.

	Requirement) DO NOT add any global variable.

	Hints) 
		1. Pass the top and bottom coordinates of the critical section to the threads through the ThreadParam structure
		2. Create and initialize as a global variable
		3. Implement entry section in ThreadFn()
		4. Implement exit section in ThreadFn()
		5. If the thread breaks the loop while the ball is in the critical region, signal all semaphores.
		6. Clean up: terminate the threads, wait for the threads to finis, destroy the semaphores.


	Compilation)
		gcc quiz2_1.c Console.c -pthread

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

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

	// TO DO: add more fields if necessary
} ThreadParam;

int thread_cont = TRUE;
void* ThreadFn(void *vParam);
sem_t sem;

int main(int argc, char *argv[])
{

	if(argc < 2){
		printf("Usage: %s <# of balls> <# of balls allowed to enter critical region>\n", argv[0]);
		return 0;
	}

	int no_thread = 0;

	no_thread = atoi(argv[1]);
	if(no_thread > MAX_THREAD)
		no_thread = MAX_THREAD;
	if(no_thread == 0)
		no_thread = 10;

	int ticket = 0;
	ticket = atoi(argv[2]);

	if(ticket < 2)
		ticket = 2;
	else if(ticket > (no_thread + 1) / 2)
		ticket = (no_thread + 1) / 2;

	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	srand(time(NULL));
	clrscr();

	// the top and bottom coordinates of the critical region
	int critical_top = screen_height / 3;
	int critical_bottom = screen_height * 2 / 3;

	// mark the critical region by horizontal lines
	DrawLine(1, critical_top, screen_width, critical_top, '-');
	DrawLine(1, critical_bottom, screen_width, critical_bottom, '-');
	
	// TO DO: initialize the semaphore

	pthread_t tid[MAX_THREAD] = { 0 };
	ThreadParam param[MAX_THREAD] = { 0 };

	for(int i = 0; i < no_thread; i++){
		param[i].thread_idx = i;
		param[i].no_thread = no_thread;
		param[i].screen_height = screen_height;
		param[i].x = screen_width * (i + 1) / (no_thread + 1);
		param[i].delay = rand() % 300;

		// TO DO: store required information to param[i],
		//	      and launch a thread using ThreadFn() and param[i].
	}

	PrintXY(1, screen_height + 1, "Press Enter to quit!\n");
	getchar();

	// TO DO: terminate the threads

	// TO DO: wait for the threads

	// TO DO: destroy the semaphore

	clrscr();
	gotoxy(1, 1);
	printf("Bye!\n");			// This line must be executed.

	return 0;
}

void* ThreadFn(void *vParam)
{
	ThreadParam *param = (ThreadParam*)vParam;

	int y = 1;
	int oldy = 1;
	while(thread_cont){
		// TO DO: implement entry section here 

		gotoxy(param->x, oldy);
		putchar(' ');

		gotoxy(param->x, y);
		putchar('*');

		fflush(stdout);

		// TO DO: implement exit section here 


		oldy = y;
		y++;
		if(y > param->screen_height)
			y = 1;

		gotoxy(1, 1);
		fflush(stdout);
		usleep(param->delay * 1000);
	}

	// TO DO: if the current thread broke loop in the critical region, signal semaphore

	return NULL;
}

