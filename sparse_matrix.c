#include "sparse_matrix.h"
#include <stdio.h>
#include <stdint.h>

void initializeSparseMatrix(SparseMatrix *matrix, int rows, int cols, int NonZeroCount)
{
    if (NonZeroCount > MAX_TERMS)
    {
        printf("\033[31mError: Exceeding maximum number of terms allowed.\033[0m\n");
        return;//有沒有可能不夠？還是直接退出？
    }
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->NonZeroCount = 0;

    for (int i = 0; i < MAX_TERMS; i++)
    {
        matrix->data[i].row = -1;
        matrix->data[i].col = -1;
        matrix->data[i].value = 0.0;
    }
}

void printSparseMatrix(SparseMatrix *matrix)
{
    printf("Sparse Matrix: %d x %d with %d non-zero elements.\n", matrix->rows, matrix->cols, matrix->NonZeroCount);
    int hasNonZero = 0;
    for (int i = 0; i < matrix->NonZeroCount; i++)
    {
        if (matrix->data[i].value != 0)
        {
            printf("Row: %d, Col: %d, Value: %.2f\n", matrix->data[i].row, matrix->data[i].col, matrix->data[i].value);
            hasNonZero = 1;
        }
    }
    if (!hasNonZero)
    {
        printf("No non-zero elements in the matrix.\n");
    }
}