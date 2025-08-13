#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double rand_double() { return (double)rand() / RAND_MAX; }
int main() {
    int n;
    printf("Enter matrix size n (n x n): ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    // allocate matrices
    double **A = malloc(n * sizeof(double*));
    double **B = malloc(n * sizeof(double*));
    double **C = malloc(n * sizeof(double*));
    for (int i = 0; i < n; ++i) {
        A[i] = malloc(n * sizeof(double));
        B[i] = malloc(n * sizeof(double));
        C[i] = malloc(n * sizeof(double));
    }

    srand(0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            A[i][j] = rand_double();
            B[i][j] = rand_double();
            C[i][j] = 0.0;
        }

    double t0 = omp_get_wtime();
    #pragma omp parallel for collapse(2) schedule(static)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0.0;
            for (int k = 0; k < n; ++k) sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }
    }

    double t1 = omp_get_wtime();
    printf("Matrix multiply (%d x %d): Time = %f s\n", n, n, t1 - t0);

    // sample check
    printf("C[0][0]=%f, C[n-1][n-1]=%f\n", C[0][0], C[n-1][n-1]);

    for (int i = 0; i < n; ++i) { free(A[i]); free(B[i]); free(C[i]); }
    free(A); free(B); free(C);
    return 0;
}

