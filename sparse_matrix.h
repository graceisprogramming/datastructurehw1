#pragma once
#define MAX_TERMS 101

typedef struct 
{
    int row;
    int col;
    double value;
} Triple;

typedef struct
{
    int rows;
    int cols;
    int NonZeroCount;
    Triple data[MAX_TERMS];
} SparseMatrix;

typedef struct 
{
    SparseMatrix W;
    SparseMatrix B;
} Layer;
//SparseMatrix result;
void initializeSparseMatrix(SparseMatrix *matrix, int rows, int cols, int NonZeroCount);
void printSparseMatrix(SparseMatrix *matrix);