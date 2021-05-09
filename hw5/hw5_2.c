#include <stdio.h>
#include <malloc.h>

typedef struct {
	int dim;
	float *data;
} DynamicVector;

// define a new type 'Vector' by aliasing DynamicVector
typedef DynamicVector Vector;


DynamicVector* AllocVector(int dim);
void DeleteVector(DynamicVector *vec);

void FillVector(Vector *vec, int dim, int dir);

float GetVectorData(Vector *vec, int idx);
void SetVectorData(Vector *vec, int idx, float v);

void DisplayVector(Vector *vec);

float DotProduct(Vector *vec1, Vector *vec2);


int main()
{
	Vector *vec1 = AllocVector(10);
	Vector *vec2 = AllocVector(10);

	FillVector(vec1, 10, 0);
	printf("vec1 = ");
	DisplayVector(vec1);

	FillVector(vec2, 10, 1);
	printf("vec2 = ");
	DisplayVector(vec2);

	printf("DotProduct(vec1, vec2) = %f\n", DotProduct(vec1, vec2));

	DeleteVector(vec1);
	DeleteVector(vec2);

	return 0;
}

DynamicVector* AllocVector(int dim)
// This function creates an object of DynamicVector
// It allocates memory and set the fields of vec.
// TO DO: implement this function
{
	DynamicVector *vec = NULL;

	/* TO DO:
		1. Allocate vec by calling malloc(). The size should be sizeof(DynamicVector).
		2. If the memory was not properly allocated, print an error message 
		   and return NULL.
		3. Allocate vec->data by calling malloc(). The size should by dim * sizeof(float).

		4. If the memory was not properly allocated, print an error message,
		   free vec, and return NULL.
		5. Set vec->dim to dim

		6. return vec
	*/

	vec = (DynamicVector*)malloc(sizeof(DynamicVector));

	if ( vec == NULL){
		printf("Error! failed memory allocate to vec\n");
		return NULL;
	} 

	vec->data = (int*)malloc(vec->dim*sizeof(float));

	if (vec->data==NULL){
		printf("Error! failed memory allocate to vec->data\n");
		return NULL;
	}

	return vec;

}

void DeleteVector(DynamicVector *vec)
// This function release memroy used for vec
// TO DO: implement this function
{
	if(vec == NULL)
		return;


	/* TO DO:
		free vec->data
		free vec
	*/

	free(vec->data);
	free(vec);
}

void FillVector(Vector *vec, int dim, int dir)
// TO DO: implement this function
{
	vec->dim = dim;

	// TO DO: complete this function by reusing the code for hw5_1.c
	if (dir == 0)
		for(int i = 1 ; i <= vec->dim ; i++) vec->data[i-1] = i;
	else
		for(int i = 1 ; i <= vec->dim ; i++) vec->data[i-1] = vec->dim - (i-1);
}

float GetVectorData(Vector *vec, int idx)
{
	return vec->data[idx];
}

void SetVectorData(Vector *vec, int idx, float v)
{
	vec->data[idx] = v;
}

float DotProduct(Vector *vec1, Vector *vec2)
// TO DO: implement this function
{
	if(vec1->dim != vec2->dim){
		printf("Error! vec1->dim = %d, vec2->dim = %d\n", vec1->dim, vec2->dim);
		return 0.F;
	}

	// TO DO: complete this function by reusing the code for hw5_1.c
	float dot = 0.F;
	for (int i = 0 ; i < vec1->dim ; i ++)
		dot += vec1->data[i] * vec2->data[i] ;

	return dot;
}

void DisplayVector(Vector *vec)
{
	for(int i = 0; i < vec->dim; i++)
		printf("%.3f ", vec->data[i]);

	printf("(dim = %d)\n", vec->dim);
}

