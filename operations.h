#pragma once

#include "sparse_matrix.h"
#include "input_store.h"
#include "utility.h"

void Tambah(SparseMatrix *matrix, int row, int col, double value);
double Ambil(const SparseMatrix *matrix, int row, int col) ;
SparseMatrix sparse_matrix_multiply(const SparseMatrix *A, const SparseMatrix *B);
SparseMatrix sparse_matrix_add(SparseMatrix *Y, SparseMatrix *B);
SparseMatrix multi_layer_compute(Layer *layers, int num_layers, SparseMatrix *input);
