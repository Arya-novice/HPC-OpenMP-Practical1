// matrix_scalar.c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n;
    double scalar;
    printf("Enter matrix size n (n x n): ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;
    printf("Enter scalar value: ");
    if (scanf("%lf", &scalar) != 1) return 1;

    double *A = malloc((size_t)n * n * sizeof(double));
    double *B = malloc((size_t)n * n * sizeof(double));
    srand(0);
    for (int i = 0; i < n * n; ++i) A[i] = (double)rand() / RAND_MAX;

    double t0 = omp_get_wtime();

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n * n; ++i) {
        B[i] = A[i] * scalar;
    }

    double t1 = omp_get_wtime();
    printf("Matrix-scalar multiply (%d x %d): Time = %f s\n", n, n, t1 - t0);
    printf("Sample: B[0]=%f, B[n*n-1]=%f\n", B[0], B[n*n-1]);

    free(A); free(B);
    return 0;
}
