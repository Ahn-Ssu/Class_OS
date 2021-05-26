/*
	This program is a solution of The Dining Philosophers Problem

	Mission:
		[IMPORTANT] Read this code carefully and fully understand.
		Synchronize the philosopher threads following the instructions.
	
	Hints)
		1. Modify DisplayPhilosophers() to be mutually exclusive
			1a. Declare and initialize a mutex as a global variable
			1b. Implement the entry and exit sections of DisplayPhilosophers().

		2. Synchronize the philosophers following the solution in the textbook or the lecture slide.
			2a. Initialize states and chopsticks
			2b. Pass states and chopsticks to the threads through ThreadParam
			2c. Implement the entry and exit sections of the thread function.
			  * Extend the solution in the textbook to prevent the ‘circular wait’ condition.
				- The even-number philosophers pick up the left chopsticks first.
				- The odd-number philosophers pick up the right chopsticks first.

		3. After the threads finishes, destroy all mutexes.

	Compilation:
		gcc hw6_2.c Console.c -pthread -lm

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <unistd.h>
#include <pthread.h>

#include "Console.h"

#define TRUE 1
#define FALSE 0

#define PI 3.141592

#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define NO_PHIL 5
enum State { THINKING, EATING, HUNGRY };		// HUNGRY is not used in this program
char StateName[3][32] = {
	"THINKING",
	"EATING",
	"HUNGRY  "						// not used in this program
};


typedef struct {
	int thread_idx;
	int no_phil;

	int *state;						// pointer to pass state array to the thread function
	pthread_mutex_t *chopstick;		// pointer to pass mutex array to the thread function

	int screen_width;
	int screen_height;
} ThreadParam;

int thread_cont = TRUE;
void* ThreadFn(void *vParam);



// TO DO: declare and initialize a mutex for DisplayPhilosophers().
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// display philosophers' states
void DisplayPhilosophers(int state[], int no_phil, int screen_width, int screen_height);

// check whether the philosophers violated the rule.
int CheckPhilosophers(int state[], int no_phil);

int main(int argc, char *argv[])
{
	srand(time(NULL));
	clrscr();

	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	pthread_t tid[NO_PHIL];
	ThreadParam param[NO_PHIL];

	int state[NO_PHIL] = { 0 };
	pthread_mutex_t chopstick[NO_PHIL];

	// TO DO: initialize state and chopstick
	//  ???? state already initialize...
	for (int i=0; i < NO_PHIL ; i ++){
		pthread_mutex_init(&chopstick[i], NULL);
		state[i] = 0 ;
	}

	DisplayPhilosophers(state, NO_PHIL, screen_width, screen_height);

	for(int i = 0; i < NO_PHIL; i++){
		param[i].thread_idx = i;
		param[i].no_phil = NO_PHIL;

		// TO DO: store state and chopstick in param[i]
		param[i].chopstick = chopstick;
		param[i].state = state;

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

		CheckPhilosophers(state, NO_PHIL);

		usleep(100000);
	}
	thread_cont = FALSE;					// terminate threads

	// TO DO: wait for the threads
	for(int i = 0 ; i< NO_PHIL; i ++){
		pthread_join(tid[i],NULL);
	}

	// TO DO: destroy mutexes
	pthread_mutex_destroy(&mutex);

	clrscr();
	printf("Bye!\n");

	return 0;
}

void* ThreadFn(void *vParam)
{
	ThreadParam *param = (ThreadParam*)vParam;

	int idx = param->thread_idx;
	int no_phil = param->no_phil;
	int *state = param->state;
	pthread_mutex_t *chopstick = param->chopstick;
	

	while(thread_cont){

		// TO DO: implement entry section
		if(idx % 2 == 0){
			pthread_mutex_lock(&(chopstick[ (idx+1) % no_phil])); // left
			pthread_mutex_lock(&(chopstick[idx])); // right
		}
		else{
			pthread_mutex_lock(&(chopstick[idx])); // right
			pthread_mutex_lock(&(chopstick[ (idx+1) % no_phil])); // left
		}

		state[idx] = EATING;

		CheckPhilosophers(state, no_phil);
		DisplayPhilosophers(state, no_phil, param->screen_width, param->screen_height);
		usleep((rand() % 500 + 500) * 1000);

		// TO DO: implement exit section
		
		// if(param->thread_idx % 2 == 0){
		// 	pthread_mutex_unlock(&(chopstick[ (idx+no_phil-1) % no_phil])); // left
		// 	pthread_mutex_unlock(&(chopstick[idx])); // right
		// }
		// else{
			
		// }

		if(idx % 2 == 1){
			pthread_mutex_unlock(&(chopstick[ (idx+1) % no_phil])); // left
			pthread_mutex_unlock(&(chopstick[idx])); // right
		}
		else{
			pthread_mutex_unlock(&(chopstick[idx])); // right
			pthread_mutex_unlock(&(chopstick[ (idx+1) % no_phil])); // left
		}
		state[idx] = THINKING;
		DisplayPhilosophers(state, no_phil, param->screen_width, param->screen_height);
		usleep((rand() % 500 + 1000) * 1000);
	}

	return NULL;
}

void DisplayPhilosophers(int state[], int no_phil, int screen_width, int screen_height)
// TO DO: make this function mutually exclusive using a mutex
{
	// TO DO: implement entry section
	pthread_mutex_lock(&mutex);

	int cx = (screen_width - 10) / 2;
	int cy = screen_height / 2;
	int radius = MIN(cx / 2, cy) * 4 / 5;


	for(int i = 0; i < no_phil; i++){
		int orientation = i * 360.F / no_phil;
		int dx = (int)(sin(orientation * PI/ 180) * radius * 2);
		int dy = -(int)(cos(orientation * PI/ 180) * radius);

		gotoxy(cx + dx - 5, cy + dy);
		printf("%d:%s", i, StateName[state[i]]);
	}

	gotoxy(screen_width, 1);
	fflush(stdout);

	// TO DO: implement exit section
	pthread_mutex_unlock(&mutex);
}

int CheckPhilosophers(int state[], int no_phil)
// DO NOT modify this function
{
	int i = 0;

	int ret = TRUE;

	for(i = 0; i < no_phil; i++){
		int prev = (i + no_phil - 1) % no_phil;
		int next = (i + 1) % no_phil;

		// check if neighboring philosophers are eating together
		if(state[i] == EATING && state[next] == EATING){
			printf("Error! state[%d] = %s, state[%d] = %s\n", i, StateName[state[i]], next, StateName[state[next]]);
			ret = FALSE;
			break;
		}

		// check if a philosopher is waiting unnecessarily
		if(state[i] == HUNGRY && state[prev] != EATING && state[next] != EATING){
			printf("Error! state[%d] = %s, state[%d] = %s, state[%d] = %s\n", prev, StateName[state[prev]], i, StateName[state[i]], next, StateName[state[next]]);
			ret = FALSE;
			break;
		}
	}

	// check for deadlock
	for(i = 0; i < no_phil && state[i] == HUNGRY; i++){}

	if(i == no_phil){
		printf("Error! Deadlock!\n");
		ret = FALSE;
	}

	if(ret == FALSE)
		MyPause();

	return ret;
}

