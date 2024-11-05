#include "operations.h"
#include "sparse_matrix.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERMS 101

void Tambah(SparseMatrix *matrix, int row, int col, double value) 
{
    if (matrix->NonZeroCount < MAX_TERMS) 
    {
        matrix->data[matrix->NonZeroCount].row = row;
        matrix->data[matrix->NonZeroCount].col = col;
        matrix->data[matrix->NonZeroCount].value = value;
        matrix->NonZeroCount++;
    }
    else
    {
        printf("\033[31mError: Maximum number of terms exceeded.\033[0m\n");
        exit(1);
    }
}

double Ambil(const SparseMatrix *matrix, int row, int col) 
{
    for (int i = 0; i < matrix->NonZeroCount; ++i) 
    {
        if (matrix->data[i].row == row && matrix->data[i].col == col) 
        {
            return matrix->data[i].value;
        }
    }
    return 0.0;
}

SparseMatrix sparse_matrix_multiply(const SparseMatrix *A, const SparseMatrix *B) 
{
    if (A->cols != B->rows) 
    {
        printf("\033[31mError: Matrix dimensions do not match for multiplication.\033[0m\n");
        exit(1);
    }

    SparseMatrix result;
    result.rows = A->rows;
    result.cols = B->cols;
    result.NonZeroCount = 0;

    for (int i = 0; i < A->rows; ++i) 
    {
        for (int j = 0; j < B->cols; ++j) 
        {
            double sum = 0.0;
            for (int k = 0; k < A->cols; ++k) 
            {
                sum += Ambil(A, i, k) * Ambil(B, k, j);
            }
            if (sum != 0) 
            {
                Tambah(&result, i, j, sum);
            }
        }
    }
    return result;
}

SparseMatrix sparse_matrix_add(SparseMatrix *Y, SparseMatrix *B) 
{
    if (Y->rows != B->rows || Y->cols != B->cols) 
    {
        printf("\033[31mError: Matrix dimensions do not match for addition.\033[0m\n");
        exit(1);
    }

    SparseMatrix result;
    result.rows = Y->rows;
    result.cols = Y->cols;
    result.NonZeroCount = 0;

    int i = 0, j = 0;
    while (i < Y->NonZeroCount && j < B->NonZeroCount) 
    {
        if (Y->data[i].row < B->data[j].row || (Y->data[i].row == B->data[j].row && Y->data[i].col < B->data[j].col)) {
            result.data[result.NonZeroCount++] = Y->data[i++];
        } else if (B->data[j].row < Y->data[i].row || (B->data[j].row == Y->data[i].row && B->data[j].col < Y->data[i].col)) {
            result.data[result.NonZeroCount++] = B->data[j++];
        } else {
            // Same position, sum the values
            double sum = Y->data[i].value + B->data[j].value;
            if (sum != 0) { // Only store non-zero sums
                result.data[result.NonZeroCount].row = Y->data[i].row;
                result.data[result.NonZeroCount].col = Y->data[i].col;
                result.data[result.NonZeroCount++].value = sum;
            }
            i++;
            j++;
        }
        if (result.NonZeroCount > MAX_TERMS) 
        {
            printf("\033[31mError: Exceeding maximum number of terms allowed.\033[0m\n");
            exit(1);
        }
    }

    // Copy remaining elements from Y
    while (i < Y->NonZeroCount) 
    {
        result.data[result.NonZeroCount++] = Y->data[i++];
    }

    // Copy remaining elements from B
    while (j < B->NonZeroCount) 
    {
        result.data[result.NonZeroCount++] = B->data[j++];
    }

    return result;
}

SparseMatrix multi_layer_compute(Layer *layers, int num_layers, SparseMatrix *input) 
{
    SparseMatrix current_output = *input;
    SparseMatrix product, temp;

    for (int i = 0; i < num_layers; ++i) 
    {
        product = sparse_matrix_multiply(&layers[i].W, &current_output);
        // printf("Multiplication result:\n");
        // printSparseMatrix(&product);
        temp = sparse_matrix_add(&product, &layers[i].B);
        // printf("Addition result:\n");
        // printSparseMatrix(&temp);
        current_output = temp; 

        printf("\033[32mZ%d result:\033[0m\n", i + 1);
        printSparseMatrix(&current_output); 
    }

    return current_output;
}