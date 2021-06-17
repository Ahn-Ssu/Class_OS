/****

	This program is a BUGGY solution of the bounded buffer problem.
	It contains lots of bugs.

	Mission:
		Fix all bugs.

	Requirement: Use Buffer for the thread parameters and DO NOT declare additional structure.

	Copy:
		cp ProdCons_buggy.c ProdCons_<student_id>_<Eng_name>.c

	Compilation)
		gcc ProdCons_buggy.c -pthread			// compile this file
		gcc ProdCons_<student_id>_<Eng_name>.c	// compile your solution

****/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1
#define FALSE 0

#define MAX_SIZE 256
typedef struct {
	int buffer[MAX_SIZE];
	int size;
	int in, out;
	int count;

	// semaphores
	sem_t full;
	sem_t empty;
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
	Buffer_Init(&buffer, buf_size);
	
	// create producer thread
	pthread_t producer_id = 0;
	pthread_create(&producer_id, NULL, Producer, &buffer);

	// create consumer thread
	pthread_t consumer_id = 0;
	pthread_create(&consumer_id, NULL, Consumer, &buffer);
	
	sleep(10);

	sem_post(&buffer.empty);
	sem_post(&buffer.empty);
	// terminate threads
	thread_cont = FALSE;

	// wait for threads
	pthread_join(producer_id, NULL);
	pthread_join(consumer_id, NULL);

	Buffer_Destroy(&buffer);

	printf("Bye!\n");				// this line MUST run

	return 0;
	
}

void Buffer_Init(Buffer *buf, int size)
{
	sem_init(&buf->empty, 0, size);
	sem_init(&buf->full, 0, 0);
	pthread_mutex_init(&buf->mutex, NULL);

	buf->in = buf->out = 0;
	buf->size = size;
	buf->count = 0;

	for(int i=0;i<size;i++){
		buf->buffer[i]=0;
	}

}

void Buffer_Destroy(Buffer *buf)
{
	sem_destroy(&buf->empty);
	sem_destroy(&buf->full);
	pthread_mutex_destroy(&buf->mutex);

	//free(buf->buffer);
	buf->size = 0;
}

void Buffer_Insert(Buffer *buf, int value)
{
	sem_wait(&buf->empty);
	pthread_mutex_lock(&buf->mutex);

	buf->buffer[buf->in] = value;
	buf->in = (buf->in + 1) % buf->size;
	buf->count++;

	pthread_mutex_unlock(&buf->mutex);
	sem_post(&buf->full);
}

int Buffer_Delete(Buffer *buf)
{
	int ret = 0;

	sem_wait(&buf->full);
	pthread_mutex_lock(&buf->mutex);

	ret = buf->buffer[buf->out%buf->size];
	buf->out = (buf->out + 1) % buf->size;
	buf->count--;

	pthread_mutex_unlock(&buf->mutex);
	sem_post(&buf->empty);

	return ret;
}

void *Producer(void *vParam)
{
	Buffer *buf = (Buffer *)vParam;

	int new_value = 00;
	while(thread_cont){
		new_value += 10;
		Print_Producer("Produced %d\n", new_value);
		usleep((rand() % 500 + 50) * 1000);
		
		Buffer_Insert(buf, new_value);
	}
}

void *Consumer(void *vParam)
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

	printf("\t\t\t\t\t\t\t[Consumer] ");

    va_start(vl, format);
    vprintf(format, vl);
    va_end(vl);

    fflush(stdout);

    pthread_mutex_unlock(&display_mutex);
}

