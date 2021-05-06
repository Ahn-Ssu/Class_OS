#ifndef	__MATRIX__
#define	__MATRIX__

typedef struct {
    int row, col;
    float **data;
} Matrix;


Matrix *AllocMatrix(int row, int col);
void FillMatrix(Matrix *mat);
void DeleteMatrix(Matrix *mat);
float GetData(Matrix *mat, int i, int j);
void SetData(Matrix *mat, int i, int j, float v);
void DisplayMatrix(Matrix *mat);

#endif	//	__MATRIX__
