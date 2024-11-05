#include "input_store.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void clear_input_buffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void inputSparseMatrix(SparseMatrix *matrix)
{
    char input[100];
    int scanned;
    
    printf("Enter number of \033[31;47mrows\033[0m: ");
    clear_input_buffer();
    fgets(input, sizeof(input), stdin);
    while (sscanf(input, "%d", &matrix->rows) != 1 || matrix->rows <= 0) 
    {
        printf("\033[41mInvalid input. Please enter a positive integer for rows: \033[0m");
        fgets(input, sizeof(input), stdin);
    }

    printf("Enter number of \033[32;47mcolumns\033[0m: ");//為什麼這裡又不用buffer？
    fgets(input, sizeof(input), stdin);
    while (sscanf(input, "%d", &matrix->cols) != 1 || matrix->cols <= 0) 
    {
        printf("\033[41mInvalid input. Please enter a positive integer for columns: \033[0m");
        fgets(input, sizeof(input), stdin);
    }

    int maxNonZeroCount = matrix->rows * matrix->cols;
    
    printf("Enter number of \033[33;47mnon-zero terms\033[0m: ");
    fgets(input, sizeof(input), stdin);
    while (sscanf(input, "%d", &matrix->NonZeroCount) != 1 ||
           matrix->NonZeroCount > maxNonZeroCount || matrix->NonZeroCount < 0) 
    {
        if (matrix->NonZeroCount > maxNonZeroCount) 
        {
            printf("\033[31mError: The number of non-zero terms cannot exceed %d for a %dx%d matrix.\033[0m\n", 
                   maxNonZeroCount, matrix->rows, matrix->cols);
                   exit(1);
        }
        else 
        {
            printf("\033[41mInvalid input. Please enter a non-negative integer for non-zero terms: \033[0m");
        }
        fgets(input, sizeof(input), stdin);
    }


    if (matrix->NonZeroCount > MAX_TERMS)
    {
        printf("\033[31mError: Exceeding maximum number of terms allowed.\033[0m\n");
        exit(1);
    }

    int prevRow = -1, prevCol = -1;

    for (int i = 0; i < matrix->NonZeroCount; i++)
    {
        printf("Enter \033[31mrow\033\[0m, \033[32mcolumn\033[0m and value for term %d: ", i + 1);
        scanf("%d %d %lf", &matrix->data[i].row, &matrix->data[i].col, &matrix->data[i].value);
        if (matrix->data[i].row >= matrix->rows || matrix->data[i].col >= matrix->cols ||
            matrix->data[i].row < 0 || matrix->data[i].col < 0)
        {
            printf("\033[31mError: Invalid position for row or column.\033[0m\n");
            exit(1);
        }

        // row-major order
        if (matrix->data[i].row < prevRow || 
            (matrix->data[i].row == prevRow && matrix->data[i].col <= prevCol))
        {
            printf("\033[31mError: Input is not in row-major order.\033[0m\n");
            exit(1);
        }

        prevRow = matrix->data[i].row;
        prevCol = matrix->data[i].col;
    }
}

void input_layers(Layer *layers, int num_layers) 
{
    for (int i = 0; i < num_layers; i++) 
    {   
        printf("\033[4mInput Matrix W%d:\033[0m\n", i + 1);
        inputSparseMatrix(&layers[i].W);
        printf("\033[4mInput Matrix B%d:\033[0m\n", i + 1);
        inputSparseMatrix(&layers[i].B);
    }
}