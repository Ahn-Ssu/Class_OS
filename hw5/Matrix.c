#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "Matrix.h"

Matrix *AllocMatrix(int row, int col)
{
	Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
	if(mat == NULL){
		printf("Failed to allocate memory (file %s line %d)\n", __FILE__, __LINE__);
		return NULL;
	}

	mat->row = row;
	mat->col = col;

	mat->data = (float**)malloc(row * sizeof(float*));
	if(mat->data == NULL){
		printf("Failed to allocate memory (file %s line %d)\n", __FILE__, __LINE__);
		free(mat);
		return NULL;
	}

	mat->data[0] = (float*)malloc(row * col * sizeof(float));
	if(mat->data[0] == NULL){
		printf("Failed to allocate memory (file %s line %d)\n", __FILE__, __LINE__);
		free(mat->data);
		free(mat);
		return NULL;

	}

	// set the array of pointers
	for(int i = 1; i < row; i++)
		mat->data[i] = mat->data[i-1] + col;

	// initialize all elements to zero
	memset(mat->data[0], 0, row * col * sizeof(float));
	
	return mat;
}

void FillMatrix(Matrix *mat)
{
	if(mat == NULL){
		printf("Empty matrix!\n");
		return;
	}

	int n = 1;
	for(int i = 0; i < mat->row; i++){
		for(int j = 0; j < mat->col; j++)
			SetData(mat, i, j, n++);
	}
}

void DeleteMatrix(Matrix *mat)
{
	if(mat){
		free(mat->data[0]);
		free(mat->data);
		free(mat);
	}
}

float GetData(Matrix *mat, int i, int j)
{
#ifdef	_DEBUG
	if(mat == NULL || i < 0 || i >= mat->row || j < 0 || j >= mat->col){
		if(mat == NULL)
			printf("mat == %p\n", mat);
		else
			printf("Invalid index i = %d (row = %d), j = %d (col = %d)\n",
				i, mat->row, j, mat->col);

		return 0.F;
	}
#endif	//	_DEBUG

	return mat->data[i][j];
}

void SetData(Matrix *mat, int i, int j, float v)
{
#ifdef	_DEBUG
	if(mat == NULL || i < 0 || i >= mat->row || j < 0 || j >= mat->col){
		if(mat == NULL)
			printf("mat == %p\n", mat);
		else
			printf("Invalid index i = %d (row = %d), j = %d (col = %d)\n",
				i, mat->row, j, mat->col);
		return;
	}
#endif	//	_DEBUG

	mat->data[i][j] = v;
}

void DisplayMatrix(Matrix *mat)
{
	if(mat == NULL){
		printf("Emtpy matrix!\n");
		return;
	}

	printf("%d x %d matrix\n", mat->row, mat->col);
	if(mat->row > 10 || mat->col > 10){
		// if the matrix is too large, do not display the elements
		return;
	}

	for(int i = 0; i < mat->row; i++){
		for(int j = 0; j < mat->col; j++){
			printf("%4f ", GetData(mat, i, j));
		}
		printf("\n");
	}
}

