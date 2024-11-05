#pragma once

#include "sparse_matrix.h"

double getElementValue(SparseMatrix *matrix, int row, int col);
//SparseMatrix total(SparseMatrix *W, SparseMatrix *X, SparseMatrix *B);
void total(SparseMatrix *W, SparseMatrix *X, SparseMatrix *B, SparseMatrix *result);

void applyReLU(SparseMatrix *matrix);