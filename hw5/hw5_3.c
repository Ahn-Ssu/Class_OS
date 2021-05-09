#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#include "Matrix.h"

#define MAX_LEN 64


Matrix *MultiplyMatrix(Matrix *mat1, Matrix *mat2);
Matrix *MultiplyMatrix_MT(Matrix *mat1, Matrix *mat2, int no_thread);


int main(int argc, char *argv[])
{
	if(argc < 3){
		printf("Usage:%s row col [no_thread=4]\n", argv[0]);
		return 0;
	}

	int row= atoi(argv[1]);
	int col = atoi(argv[2]);
	int no_thread = 4;
	if(argc >= 4)
		no_thread = atoi(argv[3]);

	printf("row = %d, col = %d, no_thread = %d\n", row, col, no_thread);

	Matrix *mat1 = AllocMatrix(row, col);
	FillMatrix(mat1);
	DisplayMatrix(mat1);

	Matrix *mat2 = AllocMatrix(col, row);
	FillMatrix(mat2);
	DisplayMatrix(mat2);

	struct timeval start, end;

	if(row < 100 && col < 100){
		printf("=== Single thread\n");

		gettimeofday(&start, NULL);

		Matrix *mat12 = MultiplyMatrix(mat1, mat2);
		Matrix *mat21 = MultiplyMatrix(mat2, mat1);

		gettimeofday(&end, NULL);

		DisplayMatrix(mat12);
		DisplayMatrix(mat21);

		float elapsed = (float)(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.F;
		printf("no_thread = %d, elapsed = %f\n", no_thread, elapsed);

		DeleteMatrix(mat12);
		DeleteMatrix(mat21);

	}


	{
		printf("=== %d threads\n", no_thread);
		gettimeofday(&start, NULL);

		Matrix *mat12 = MultiplyMatrix_MT(mat1, mat2, no_thread);
		Matrix *mat21 = MultiplyMatrix_MT(mat2, mat1, no_thread);

		gettimeofday(&end, NULL);

		DisplayMatrix(mat12);
		DisplayMatrix(mat21);

		float elapsed = (float)(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.F;
		printf("no_thread = %d, elapsed = %f\n", no_thread, elapsed);

		DeleteMatrix(mat12);
		DeleteMatrix(mat21);
	}

	DeleteMatrix(mat1);
	DeleteMatrix(mat2);

	return 0;
}

Matrix *MultiplyMatrix(Matrix *mat1, Matrix *mat2)
{
	if(mat1 == NULL || mat2 == NULL || mat1->col != mat2->row){
		printf("Invalid argument: mat1 = %p, mat2 = %p\n", mat1, mat2);
		if(mat1 && mat2){
			printf("mat1: %d x %d, mat2 : %d x %d\n",
				mat1->row, mat1->col, mat2->row, mat2->col);
		}
	}

	Matrix *res = AllocMatrix(mat1->row, mat2->col);
	if(res == NULL)
		return NULL;

	int limit = mat1->col;
	for(int i = 0; i < mat1->row; i++){
		for(int j = 0; j < mat2->col; j++){
			float sum = 0.F;
			for(int k = 0; k < limit; k++)
				sum += GetData(mat1, i, k) * GetData(mat2, k, j);
			SetData(res, i, j, sum);
		}
	}

	return res;
}

#define MAX_THREAD 1024

typedef struct {
	int thread_idx;
	int no_thread;
	Matrix *mat1;
	Matrix *mat2;
	Matrix *res;
} ThreadParam;

void* thread_fn(void *vparam);

Matrix *MultiplyMatrix_MT(Matrix *mat1, Matrix *mat2, int no_thread)
// TO DO: Implement the multi-threaded version MultiplyMatrix()
//        by following the instruction.
//		  The result should be the same as that of MultiplyMatrix()
{
	if(mat1 == NULL || mat2 == NULL || mat1->col != mat2->row){
		printf("Invalid argument: mat1 = %p, mat2 = %p\n", mat1, mat2);
		if(mat1 && mat2){
			printf("mat1: %d x %d, mat2 : %d x %d\n",
				mat1->row, mat1->col, mat2->row, mat2->col);
		}
	}

	Matrix *res = AllocMatrix(mat1->row, mat2->col);
	if(res == NULL)
		return NULL;

	pthread_t tid[MAX_THREAD];
	ThreadParam param[MAX_THREAD];

	/* TO DO:
		1. set parameters to appropriate values 
		2. launch threads no_thread times
		3. wait for the child threads

		The threads should run parallely.
	*/

// typedef struct {
// 	int thread_idx;
// 	int no_thread;
// 	Matrix *mat1;
// 	Matrix *mat2;
// 	Matrix *res;
// } ThreadParam;

    for (int i = 0 ; i < no_thread ; i ++){
        param[i].thread_idx = i;
        param[i].no_thread = no_thread;
        param[i].mat1 = mat1;
        param[i].mat2 = mat2;
        param[i].res = res;

        pthread_create(&tid[i], NULL, thread_fn, &param[i]);
    }

    for (int i = 0 ; i < no_thread ; i ++)
        pthread_join(tid[i], NULL);

	return res;
}

void* thread_fn(void *vparam)
// TO DO: read carefully and fully understand this code
{
	ThreadParam *param = (ThreadParam*)vparam;

	Matrix *mat1 = param->mat1;
	Matrix *mat2 = param->mat2;
	Matrix *res = param->res;

	int limit = mat1->col;
	int i = 0, j = 0;
	int r = param->thread_idx;
	for(i = 0; i < mat1->row; i++){
		for(j = r; j < mat2->col; j += param->no_thread){
			float sum = 0.F;
			for(int k = 0; k < limit; k++)
				sum += GetData(mat1, i, k) * GetData(mat2, k, j);
			SetData(res, i, j, sum);
		}

		r = j % mat2->col;
	}

	return NULL;
}

