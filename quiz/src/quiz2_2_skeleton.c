/*
	This program is the solution of the bounded buffer problem.

	Mission)
		Following the instructions, complete the code to run similarly to the demo video.

	Requirement) Use Buffer for the thread parameters and DO NOT declare additional structure.

	Compilation)
		gcc quiz2_2.c -pthread

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "Console.h"


#define TRUE 1
#define FALSE 0

#define MAX_SIZE 256

typedef struct {			// use this structure for the thread parameter
	int buffer[MAX_SIZE];
	int size;
	int in, out;

	// TO DO: add semaphore variables (sem_t and/or pthread_mutex_t)
	//      see the solution of the bounded buffer problem in the textbook.
} Buffer;


void Buffer_Init(Buffer *buf, int size);
void Buffer_Destroy(Buffer *buf);
void Buffer_Insert(Buffer *buf, int value);
int Buffer_Delete(Buffer *buf);

void *Producer(void *vParam);
void *Consumer(void *vParam);

void Print_Producer(const char *format, ...);
void Print_Consumer(const char *format, ...);


int thread_cont = TRUE;

int main(int argc, char *argv[])
{
	int buf_size = 0;
	if(argc > 1)
		buf_size = atoi(argv[1]);
	if(buf_size <= 0)
		buf_size = 6;

	srand(time(NULL));

	Buffer buffer;
	// TO DO: initialize buffer by calling Buffer_Init() passing buf_size as the size parameter.
	

	// TO DO: create the producer thread passing buffer as the parameter


	// TO DO: create the consumer thread passing buffer as the parameter
	

	sleep(10);

	thread_cont = FALSE;
	// TO DO: signal empty and full to release the threads one more time.

	// TO DO: wait for the producer and consumer to terminate

	// TO DO: destroy buffer by calling Buffer_Destroy()

	printf("Bye!\n");	// this line must be executed.

	return 0;
	
}

void Buffer_Init(Buffer *buf, int size)
{
	// TO DO: initialize the semaphores (incl. mutex)


	buf->in = buf->out = 0;
	buf->size = size;
}

void Buffer_Destroy(Buffer *buf)
{
	// TO DO: destroy the semaphores (incl. mutex)


	buf->size = 0;
}

void Buffer_Insert(Buffer *buf, int value)
{
	// TO DO: implement entry section using semaphores (incl. mutex)


	buf->buffer[buf->in] = value;
	buf->in = (buf->in + 1) % buf->size;

	// TO DO: implement exit section using semaphores (incl. mutex)

}

int Buffer_Delete(Buffer *buf)
{
	int ret = 0;

	// TO DO: implement entry section using semaphores (incl. mutex)



	// TO DO: delete an item and store the deleted item to ret 
	//        use the queue deletion algorihtm



	// TO DO: implement exit section using semaphores (incl. mutex)


	return ret;
}

void *Producer(void *vParam)
// DO NOT modify this function
{
	Buffer *buf = (Buffer *)vParam;

	while(thread_cont){
		int new_value = rand() % 100;
		Print_Producer("Produced %d\n", new_value);
		usleep((rand() % 500 + 50) * 1000);
		
		Buffer_Insert(buf, new_value);
	}
}

void *Consumer(void *vParam)
// DO NOT modify this function
{
	Buffer *buf = (Buffer *)vParam;

	while(thread_cont){
		int retrieved_val = Buffer_Delete(buf);

		Print_Consumer("Consuming %d\n", retrieved_val);
		usleep((rand() % 500 + 100) * 1000);
	}
}


pthread_mutex_t display_mutex = PTHREAD_MUTEX_INITIALIZER;

void Print_Producer(const char *format, ...)
{
    va_list vl;

    pthread_mutex_lock(&display_mutex);

	printf("[Producer] ");

    va_start(vl, format);
    vprintf(format, vl);
    va_end(vl);

    fflush(stdout);

    pthread_mutex_unlock(&display_mutex);
}

void Print_Consumer(const char *format, ...)
{
    va_list vl;

    pthread_mutex_lock(&display_mutex);

	printf("\t\t\t\t\t[Consumer] ");

    va_start(vl, format);
    vprintf(format, vl);
    va_end(vl);

    fflush(stdout);

    pthread_mutex_unlock(&display_mutex);
}

