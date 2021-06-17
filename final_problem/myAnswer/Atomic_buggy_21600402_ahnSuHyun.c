/****

	This program adds the numbers in a long array.
	It contains two version of SumArray() function:
		one is a single-threaded version and the other is a multi-threaded version.

	The multi-threaded version is SLOW and returns INCORRECT result.
	Correct the bugs of the multi-threaded version.
	It should return the sample value with SumArray() and be much faster for a long array than the single-threaded version fully utilizing the computing power of multiple processors.

	Copy:
		cp Atomic_buggy.c Atomic_<student_id>_<Eng_name>.c

	Compilation:
		gcc Atomic_buggy.c -pthread						// compile this program
		gcc Atomic_<student_id>_<Eng_name>.c -pthread	// compile your solution

	Usage:
		a.out [no_thread] [array_size]

	INCORRECT example)
		SumArray(data, 10000000)         = 45000000, elapsed time = 0.100216
		SumArray_MT(data, 10000000, 4)   = 179999996, elapsed time = 3.502350		// INCORECT and SLOW

	INCORRECT example)
		$ ./a.out
		SumArray(data, 10000000)         = 45000000, elapsed time = 0.099604
		SumArray_MT(data, 10000000, 4)   = 45000000, elapsed time = 0.890311		// correct but SLOW

	Correct example)
		$ ./a.out
		SumArray(data, 10000000)         = 45000000, elapsed time = 0.099625
		SumArray_MT(data, 10000000, 4)   = 45000000, elapsed time = 0.036292		// correct and faster


	To prevent race condition, this program uses the _Atomic type in the gcc extensions.
	For the __atomic_store() and __atomic_add_fetch(), refer the following documents.
		(Korean) http://www.secmem.org/blog/2020/01/17/gcc-extensions/
		(English) https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html


****/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

#define DEFAULT_SIZE 10000000
#define MAX_THREAD 64

typedef struct {
	int thread_idx;
	int no_thread;

	int size;
	int *data;
	_Atomic int *sum;
} ThreadInfo;


int SumArray(int *data, int size);
int SumArray_MT(int *data, int size, int no_thread);
void* ThreadFn(void *vparam);


int main(int argc, char *argv[])
// DO NOT modify this function.
{
	int no_thread = 4;
	if(argc >= 2)
		no_thread = atoi(argv[1]);
	if(no_thread == 0)
		no_thread = 4;

	int size = DEFAULT_SIZE;
	if(argc >= 3)
		size = atoi(argv[2]);
	if(size == 0)
		size = DEFAULT_SIZE;

	int *data = (int *)malloc(size * sizeof(int));
	for(int i = 0; i < size; i++)
		data[i] = i % 10;			// % 10 is to prevent overflow

	struct timeval start_time, end_time;
	
	gettimeofday(&start_time, NULL);
	int sum1 = SumArray(data, size);
	gettimeofday(&end_time, NULL);

	float timeDiff1 = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.F;
	printf("SumArray(data, %d)\t = %d, elapsed time = %f\n", size, sum1, timeDiff1);

	gettimeofday(&start_time, NULL);
	int sum2 = SumArray_MT(data, size, no_thread);
	gettimeofday(&end_time, NULL);
	float timeDiff2 = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.F;
	printf("SumArray_MT(data, %d, %d)\t = %d, elapsed time = %f\n", size, no_thread, sum2, timeDiff2);

	free(data);

	return 0;
}

int SumArray(int *data, int size)
// DO NOT modify this function.
{
	int sum = 0;

	for(int i = 0; i < size; i++)
		sum += data[i];

	return sum;
}

int SumArray_MT(int *data, int size, int no_thread)
// Multi-threaded version of SumArray()
// This function should return the same value as SumArray().
// Additionally it should be faster for a long array on a multi-core environment.
// TO DO: modify this function to correct the bug, if necessary.
{
	if(no_thread > MAX_THREAD)
		no_thread = MAX_THREAD;

	pthread_t tid[no_thread];
	ThreadInfo param[no_thread];

	_Atomic int sum = 0;		// this is sufficient for this program

	// thread-safe initialization (not essential in this program)
	int val = 0;
	__atomic_store(&sum, &val, __ATOMIC_SEQ_CST);


	for(int i = 0; i < no_thread; i++){
		param[i].thread_idx = i;
		param[i].no_thread = no_thread;

		param[i].size = size;
		param[i].data = data;
		param[i].sum = &sum;

		pthread_create(&tid[i], NULL, ThreadFn, &param[i]);
	}

	for(int i = 0; i < no_thread; i++)
		pthread_join(tid[i], NULL);

	
	return sum;
}

void* ThreadFn(void *vparam)
// TO DO: modify this function to make it correct and fast!
//
// Hint)
//		__atomic_add_fetch() adds data[i] to param->sum atomically avoiding race condition.
//		However, this function places a constraint on the parallel execution of threads,
//		and therefore, slows down speed.
{
	ThreadInfo *param = (ThreadInfo*)vparam;

	int *data = param->data;
	int size = param->size;
	int no_thread = param->no_thread;

	int sum = 0;


	for(int i = param->thread_idx; i < size; i+=no_thread)
	//	__atomic_add_fetch(param->sum, data[i], __ATOMIC_SEQ_CST);
		//*(param->sum) += data[i];
		sum += data[i];

//	*(param->sum) += sum;
	__atomic_add_fetch(param->sum, sum, __ATOMIC_SEQ_CST);
	return NULL;
}

