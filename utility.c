#include "utility.h"
#include "operations.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>

double getElementValue(SparseMatrix *matrix, int row, int col)
{
    for (int i = 0; i < matrix->NonZeroCount; i++)
    {
        if (matrix->data[i].row == row && matrix->data[i].col == col)
        {
            return matrix->data[i].value;
        }
    }
    return 0.0;
}
/*
SparseMatrix total(SparseMatrix *W, SparseMatrix *X, SparseMatrix *B)
{
    SparseMatrix result = sparse_matrix_multiply(W, X);
    result = sparse_matrix_add(&result, B);
    return result;
}
*/
void total(SparseMatrix *W, SparseMatrix *X, SparseMatrix *B, SparseMatrix *result) 
{
    *result = sparse_matrix_multiply(W, X);
    *result = sparse_matrix_add(result, B);
}

void applyReLU(SparseMatrix *matrix)
{
    for (int i = 0; i < matrix->NonZeroCount; i++)
    {
        matrix->data[i].value = fmax(0, matrix->data[i].value); 
    }
}