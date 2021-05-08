#include <stdio.h>

#define MAX_DIM 512

typedef struct {
	int dim;
	float data[MAX_DIM];
} StaticVector;

// define a new type 'Vector' by aliasing StaticVector
typedef StaticVector Vector;

void FillVector(Vector *vec, int dim, int dir);
float GetVectorData(Vector *vec, int idx);
void SetVectorData(Vector *vec, int idx, float v);
void DisplayVector(Vector *vec);
float DotProduct_slow(Vector vec1, Vector vec2);
float DotProduct(Vector *vec1, Vector *vec2);


int main()
{
	Vector vec1, vec2;

	FillVector(&vec1, 10, 0);
	printf("vec1 = ");
	DisplayVector(&vec1);

	FillVector(&vec2, 10, 1);
	printf("vec2 = ");
	DisplayVector(&vec2);

	printf("DotProduct_slow(vec1, vec2) = %f\n", DotProduct_slow(vec1, vec2));

	printf("DotProduct(&vec1, &vec2) = %f\n", DotProduct(&vec1, &vec2));

	return 0;
}

void FillVector(Vector *vec, int dim, int dir)
// TO DO: Implement this function
{
	vec->dim = dim;

	/* TO DO:
		if dir == 0, fill vec->data with 1, 2, ..., dim-1, dim
		otherwise,   fill vec->data with dim, dim-1, ..., 2, 1
	*/
}

float GetVectorData(Vector *vec, int idx)
{
	return vec->data[idx];
}

void SetVectorData(Vector *vec, int idx, float v)
{
	vec->data[idx] = v;
}

float DotProduct_slow(Vector vec1, Vector vec2)
{
	if(vec1->dim != vec2->dim){
		printf("Error! vec1->dim = %d, vec2->dim = %d\n", vec1->dim, vec2->dim);
		return 0.F;
	}
	
	float dot = 0.F;
	for(int i = 0; i < vec1.dim; i++)
		dot += vec1.data[i] * vec2.data[i];

	return dot;
}

float DotProduct(Vector *vec1, Vector *vec2)
// TO DO: Implement this function.
//        The result should be the same as that of DotProduct_slow().
{
	if(vec1->dim != vec2->dim){
		printf("Error! vec1->dim = %d, vec2->dim = %d\n", vec1->dim, vec2->dim);
		return 0.F;
	}

	// TO DO: Return the sum of vec1->data[i] * vec2->data[i],
	//        for 0 <= i < vec->dim
}

void DisplayVector(Vector *vec)
{
	for(int i = 0; i < vec->dim; i++)
		printf("%.2f ", vec->data[i]);

	printf("(dim = %d)\n", vec->dim);
}

