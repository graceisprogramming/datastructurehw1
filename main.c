#include <stdio.h>
#include <stdint.h>
#include "sparse_matrix.h"
#include "input_store.h"
#include "operations.h"
#include "utility.h"
#include <stdlib.h>

void clearInputBuffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    SparseMatrix W, X, B, Y, Z;
    Layer *layers;
    int choice, row, col, matrixChoice, numLayers;
    double value;

    while (1)
    {
        printf("\n\033[4mMenu:\033[0m\n");
        printf("1. Input Sparse Matrix W, X, B\n");
        printf("2. Output Element Value at a given position\n");
        printf("3. Multiply Matrices W and X to get Y\n");
        printf("4. Compute Z = W * X + B and output non-zero items\n");
        printf("5. Apply ReLU to Z\n");
        printf("6. Input and Compute Multi-Layer Network\n");
        printf("0. Exit\n");
        printf("\033[43;31mChoose an option: \033[0m");
        if (scanf("%d", &choice) != 1)
        {
            printf("\033[41mInvalid input. Please enter a number.\033[0m\n");
            clearInputBuffer();
            continue;
        }
        
        switch (choice)
        {
        case 1:
                printf("Input \033[4mMatrix W:\033[0m\n");
                inputSparseMatrix(&W);
                printf("Input \033[4mMatrix X:\033[0m\n");
                inputSparseMatrix(&X);
                printf("Input \033[4mMatrix B:\033[0m\n");
                inputSparseMatrix(&B);
                break;
        case 2:
                printf("Select Matrix [1-W, 2-X, 3-B]: ");
                if (scanf("%d", &matrixChoice) != 1) 
                {
                    printf("\033[41mInvalid input. Please enter a number.\033[0m\n");
                    clearInputBuffer();
                    continue;
                }
                printf("Enter row and column to fetch the value: ");
                if (scanf("%d %d", &row, &col) != 2) {
                    printf("\033[41mInvalid input. Please enter numbers for row and column.\033[0m\n");
                    clearInputBuffer();
                    continue;
                }
                switch (matrixChoice) 
                {
                    case 1:
                        value = getElementValue(&W, row, col);
                        break;
                    case 2:
                        value = getElementValue(&X, row, col);
                        break;
                    case 3:
                        value = getElementValue(&B, row, col);
                        break;
                    case 0:
                        return 0;
                    default:
                        printf("\033[41mInvalid matrix selection.\033[0m\n");
                        continue;
                }
                printf("Value at selected matrix[%d, %d] = %.2f\n", row, col, value);
                break;
            case 3:
                Y = sparse_matrix_multiply(&W, &X);
                printf("Matrix Y (W * X) computed.\n");
                printSparseMatrix(&Y);
                break;
            case 4:
                total(&W, &X, &B, &Z);
                printf("Full Connected Layer Z = W * X + B computed.\n");
                printSparseMatrix(&Z); // Output non-zero items of Z
                break;
            case 5:
                total(&W, &X, &B, &Z);
                applyReLU(&Z);
                printf("ReLU applied to Z.\n");
                printSparseMatrix(&Z);
                break;
            case 6:
                printf("Enter number of layers: ");
                if (scanf("%d", &numLayers) != 1) 
                {
                    printf("\033[41mInvalid input. Please enter a number.\033[0m\n");
                    clearInputBuffer();
                    continue;
                }
                layers = (Layer *)malloc(numLayers * sizeof(Layer));
                input_layers(layers, numLayers);
                
                printf("Input initial matrix X:\n");
                inputSparseMatrix(&X);

                Z = multi_layer_compute(layers, numLayers, &X);

                free(layers);
                break;
            case 0:
                printf("Exiting program.\n");
                return 0;
            default:
            printf("\033[41mInvalid choice.\033[0m\n");
        }
    }
    return 0;
}
