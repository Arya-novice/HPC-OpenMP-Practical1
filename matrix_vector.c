// matrix_vector.c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n;
    printf("Enter matrix size n (n x n): ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    double *A = malloc((size_t)n * n * sizeof(double));
    double *x = malloc(n * sizeof(double));
    double *y = malloc(n * sizeof(double));

    srand(0);
    for (int i = 0; i < n * n; ++i) A[i] = (double)rand() / RAND_MAX;
    for (int i = 0; i < n; ++i) x[i] = (double)rand() / RAND_MAX;

    double t0 = omp_get_wtime();

    // Parallel by rows: each thread computes several y[i] independently
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; ++i) {
        double sum = 0.0;
        double *Ai = &A[(size_t)i * n];
        for (int j = 0; j < n; ++j) sum += Ai[j] * x[j];
        y[i] = sum;
    }

    double t1 = omp_get_wtime();
    printf("Matrix-vector multiply (%d x %d): Time = %f s\n", n, n, t1 - t0);
    printf("Sample: y[0]=%f, y[n-1]=%f\n", y[0], y[n-1]);

    free(A); free(x); free(y);
    return 0;
}
