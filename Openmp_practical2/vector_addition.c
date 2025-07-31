#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n, i;
    double *a, *b, *c_seq, *c_par;

    printf("Enter size of vectors: ");
    scanf("%d", &n);

    a = (double*)malloc(n * sizeof(double));
    b = (double*)malloc(n * sizeof(double));
    c_seq = (double*)malloc(n * sizeof(double));
    c_par = (double*)malloc(n * sizeof(double));

    // Initialize vectors
    for(i = 0; i < n; i++) {
        a[i] = i + 1;
        b[i] = (i + 1) * 2;
    }

    // Sequential addition
    double start_seq = omp_get_wtime();
    for(i = 0; i < n; i++) {
        c_seq[i] = a[i] + b[i];
    }
    double end_seq = omp_get_wtime();

    // Parallel addition
    double start_par = omp_get_wtime();
    #pragma omp parallel for
    for(i = 0; i < n; i++) {
        c_par[i] = a[i] + b[i];
    }
    double end_par = omp_get_wtime();

    // Display vectors
    printf("\nVector A: ");
    for(i = 0; i < n; i++) printf("%.1f ", a[i]);

    printf("\nVector B: ");
    for(i = 0; i < n; i++) printf("%.1f ", b[i]);

    printf("\nSequential Result: ");
    for(i = 0; i < n; i++) printf("%.1f ", c_seq[i]);

    printf("\nParallel Result: ");
    for(i = 0; i < n; i++) printf("%.1f ", c_par[i]);

    // Speedup
    double seq_time = end_seq - start_seq;
    double par_time = end_par - start_par;
    double speedup = seq_time / par_time;

    printf("\n\nTime (Sequential): %f seconds", seq_time);
    printf("\nTime (Parallel): %f seconds", par_time);
    printf("\nSpeedup: %f\n", speedup);

    free(a); free(b); free(c_seq); free(c_par);

    return 0;
}
