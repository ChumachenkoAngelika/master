
#ifndef LABA_MATRIX_H
#define LABA_MATRIX_H
#include <stdbool.h>

typedef struct matrix {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;



matrix getMemMatrix(int nRows, int nCols);


matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);

void freeMemMatrix(matrix *m);


void freeMemMatrices(matrix *ms, int nMatrices);

void inputMatrix(matrix *m);


void outputMatrix(matrix m);

void outputMatrices(matrix *ms, int nMatrices);

void swapRows(matrix m, int i1, int i2);


void swapColumns(matrix m, int j1, int j2);

int getSum(int *a, int n);

void insertionSort(int *arr, int n);

void swapCols(int matrix[][3], int col1, int col2, int rows);

void selectionSortColsMatrixByColCriteria(int matrix[][3], int rows, int cols, int (*criteria)(int*, int));

int sumCriteria(int* col, int rows);

bool isSquareMatrix(matrix *m);


bool areTwoMatricesEqual(matrix *m1, matrix *m2);

bool isEMatrix(matrix *m);

bool isSymmetricMatrix(matrix *m);

void transposeSquareMatrix(matrix *m);


void transposeMatrix(matrix *m);

position getMinValuePos(matrix m);

position getMaxValuePos(matrix m);

matrix createMatrixFromArray(const int *a, int nRows, int nCols);

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows,size_t nCols);


#endif //LABA_MATRIX_H
