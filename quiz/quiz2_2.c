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
	sem_t full, empty;
	pthread_mutex_t mutex;
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
	Buffer_Init(&buffer, buf_size);	

	pthread_t tid[2];
	// TO DO: create the producer thread passing buffer as the parameter
	pthread_create(&tid[0], NULL, Producer, &buffer);

	// TO DO: create the consumer thread passing buffer as the parameter
	pthread_create(&tid[1], NULL, Consumer, &buffer);
	

	sleep(10);

	thread_cont = FALSE;
	// TO DO: signal empty and full to release the threads one more time.
	sem_post(&buffer.empty);
	sem_post(&buffer.full);
	// TO DO: wait for the producer and consumer to terminate
	for (int i= 0 ; i < 2 ; i++) pthread_join(tid[i], NULL);
	// TO DO: destroy buffer by calling Buffer_Destroy()
	Buffer_Destroy(&buffer);

	printf("Bye!\n");	// this line must be executed.

	return 0;
	
}

void Buffer_Init(Buffer *buf, int size)
{
	// TO DO: initialize the semaphores (incl. mutex)
	sem_init(&(buf->full), 0, 0);
	sem_init(&(buf->empty), 0, size);
	pthread_mutex_init(&(buf->mutex), NULL);

	buf->in = buf->out = 0;
	buf->size = size;
}

void Buffer_Destroy(Buffer *buf)
{
	// TO DO: destroy the semaphores (incl. mutex)
	sem_destroy(&(buf->full));
	sem_destroy(&(buf->empty));
	pthread_mutex_destroy(&(buf->mutex));

	buf->size = 0;
}

void Buffer_Insert(Buffer *buf, int value)
{
	// TO DO: implement entry section using semaphores (incl. mutex)
	
	sem_wait(&(buf->empty));
	pthread_mutex_lock(&(buf->mutex));


	buf->buffer[buf->in] = value;
	buf->in = (buf->in + 1) % buf->size;

	// TO DO: implement exit section using semaphores (incl. mutex)
	pthread_mutex_unlock(&(buf->mutex));
	sem_post(&(buf->full));

}

int Buffer_Delete(Buffer *buf)
{
	int ret = 0;

	// TO DO: implement entry section using semaphores (incl. mutex)
	sem_wait(&(buf->full));
	pthread_mutex_lock(&(buf->mutex));


	// TO DO: delete an item and store the deleted item to ret 
	//        use the queue deletion algorihtm

	ret = buf->buffer[buf->out % buf->size];
	buf->out = (buf->out +1) % buf->size;


	// TO DO: implement exit section using semaphores (incl. mutex)
	pthread_mutex_unlock(&(buf->mutex));
	sem_post(&(buf->empty));

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

