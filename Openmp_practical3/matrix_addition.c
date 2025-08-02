// matrix_addition.c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrix_add(int **A, int **B, int **C, int size) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
}

int** allocate_matrix(int size) {
    int **matrix = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++)
        matrix[i] = malloc(size * sizeof(int));
    return matrix;
}

void fill_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = rand() % 100;
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int thread_counts[] = {1, 2, 4, 8};

    for (int s = 0; s < 5; s++) {
        int size = sizes[s];
        int **A = allocate_matrix(size);
        int **B = allocate_matrix(size);
        int **C = allocate_matrix(size);
        fill_matrix(A, size);
        fill_matrix(B, size);

        for (int t = 0; t < 4; t++) {
            omp_set_num_threads(thread_counts[t]);
            double start = omp_get_wtime();
            matrix_add(A, B, C, size);
            double end = omp_get_wtime();
            printf("Size: %d, Threads: %d, Time: %f sec\n", size, thread_counts[t], end - start);
        }

        // Free memory
        for (int i = 0; i < size; i++) {
            free(A[i]); free(B[i]); free(C[i]);
        }
        free(A); free(B); free(C);
    }

    return 0;
}


