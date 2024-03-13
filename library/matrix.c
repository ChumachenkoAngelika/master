#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "matrix.h"
#include <stdbool.h>



matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix){values, nRows, nCols};
}


matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}


void freeMemMatrix(matrix *m){
    for (int i = 0; i < m->nRows; i++){
        free(m->values[i]);
    }
    free(m->values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(&ms[i]);
    }
    free(ms);
}


void inputMatrix(matrix *m) {
    printf("inputting nRows: ");
    scanf("%d", &m->nRows);

    printf("inputting nCols: ");
    scanf("%d", &m->nCols);


    m->values = (int **)malloc(m->nRows * sizeof(int *));
    for (int i = 0; i < m->nRows; i++) {
        m->values[i] = (int *)malloc(m->nCols * sizeof(int));
    }


    printf("inputting elements:\n");
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            printf("element [%d][%d]: ", i, j);
            scanf("%d", &m->values[i][j]);
        }
    }
}


void outputMatrix(matrix m){
    for (int i = 0; i < m.nRows; i++){
        for (int j = 0; j < m.nCols; j++){
            printf("%d", m.values[i][j]);
        }
    }
}


void outputMatrices(matrix *ms, int nMatrices){
    for (int n = 0; n < nMatrices; n++){
        printf("Matrix %d: \n", n+1);
        for (int i = 0; i < ms[n].nRows; i++){
            for (int j = 0; j < ms[n].nCols; j++){
                printf("%d ", ms[n].values[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}


void swapRows(matrix m, int i1, int i2){
    assert(i1 >= 0 && i1 <m.nRows);
    assert(i2 >= 0 && i2 < m.nRows);

    int *temp = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = temp;
}



void swapColumns(matrix m, int j1, int j2){
    assert(j1 >= 0 && j1 <m.nCols);
    assert(j2 >= 0 && j2 < m.nCols);

    int *temp = m.values[j1];
    m.values[j1] = m.values[j2];
    m.values[j2] = temp;
}

int getSum(int *a, int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}


void insertionSort(int *arr, int n) {
    for(int i = 1; i < n; i++) {
        int current = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > current) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = current;
    }
}


void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)) {
    int sumArray[100];
    for(int i = 0; i < m.nRows; i++) {
        sumArray[i] = criteria(m.values[i], m.nCols);
    }

    insertionSort(sumArray, m.nRows);

    matrix sortedMatrix = m;
    for(int i = 0; i < m.nRows; i++) {
        for(int j = 0; j < m.nCols; j++) {
            sortedMatrix.values[i][j] = m.values[sumArray[i]][j];
        }
    }

    for(int i = 0; i < m.nRows; i++) {
        for(int j = 0; j < m.nCols; j++) {
            m.values[i][j] = sortedMatrix.values[i][j];
        }
    }
}


void swapCols(int matrix[][3], int col1, int col2, int rows) {
    for (int i = 0; i < rows; i++) {
        int temp = matrix[i][col1];
        matrix[i][col1] = matrix[i][col2];
        matrix[i][col2] = temp;
    }
}

void selectionSortColsMatrixByColCriteria(int matrix[][3], int rows, int cols, int (*criteria)(int*, int)) {
    for (int i = 0; i < cols; i++) {
        int minIndex= i;
        for (int j = i+1; j < cols; j++) {
            if (criteria(matrix[i], rows) > criteria(matrix[j], rows)) {
                minIndex =j;
            }
        }
        swapCols(matrix, i, minIndex, rows);
    }
}

int sumCriteria(int* col, int rows) {
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        sum += col[i];
    }
    return sum;
}


bool isSquareMatrix(matrix *m) {
    if (m->nRows == m->nCols) {
        return true;
    } else {
        return false;
    }
}


bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols) {
        return false;
    }

    for (int i = 0; i < m1->nRows; i++) {
        for (int j = 0; j < m1->nCols; j++) {
            if (m1->values[i][j] != m2->values[i][j]) {
                return false;
            }
        }
    }

    return true;
}


bool isEMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        return false; // Не является квадратной матрицей, не может быть единичной
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (i == j && m->values[i][j] != 1) {
                return false; // Диагональные элементы не равны 1
            }
            if (i != j && m->values[i][j] != 0) {
                return false; // Недиагональные элементы не равны 0
            }
        }
    }

    return true; // единичная
}


bool isSymmetricMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        return false; // Не квадратная не может быть симметричной
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                return false; // Элементы не симметричны
            }
        }
    }

    return true; // Матрица является симметричной
}


void transposeSquareMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        printf("false\n");//если матрица не квадратная, а значит и не соответствует нашему условию.
        return;
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = i + 1; j < m->nCols; j++) {
            int temp = m->values[i][j];
            m->values[i][j] = m->values[j][i];
            m->values[j][i] = temp;
        }
    }
}


void transposeMatrix(matrix *m) {
    matrix transposed;
    transposed.nRows = m->nCols; // Количество строк новой матрицы равно количеству столбцов исходной
    transposed.nCols = m->nRows; // Количество столбцов новой матрицы равно количеству строк исходной

    // Выделяем память для новой матрицы
    transposed.values = (int **)malloc(transposed.nRows * sizeof(int *));
    for (int i = 0; i < transposed.nRows; i++) {
        transposed.values[i] = (int *)malloc(transposed.nCols * sizeof(int));
    }

    // Транспонирование матрицы
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            transposed.values[j][i] = m->values[i][j];
        }
    }

    // Освобождаем память, занимаемую исходной матрицей
    for (int i = 0; i < m->nRows; i++) {
        free(m->values[i]);
    }
    free(m->values);

    // Присваиваем новую матрицу исходной
    m->nRows = transposed.nRows;
    m->nCols = transposed.nCols;
    m->values = transposed.values;
}


position getMinValuePos(matrix m) {
    position minPos;
    minPos.rowIndex = 0;
    minPos.colIndex = 0;
    int minValue = m.values[minPos.rowIndex][minPos.colIndex];

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < minValue) {
                minValue = m.values[i][j];
                minPos.rowIndex = i;
                minPos.colIndex = j;
            }
        }
    }

    return minPos;
}


position getMaxValuePos(matrix m) {
    position maxPos;
    maxPos.rowIndex = 0;
    maxPos.colIndex= 0;

    int maxValue = m.values[maxPos.rowIndex][maxPos.colIndex];

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > maxValue) {
                maxValue = m.values[i][j];
                maxPos.rowIndex = i;
                maxPos.colIndex = j;
            }
        }
    }

    return maxPos;
}

matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];
    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows,size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];
    return ms;
}
