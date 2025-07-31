#include <stdio.h>
#include <omp.h>

int main() {
    int n;
    printf("Enter number of threads: ");

    double start = omp_get_wtime();

    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        printf("Hello, World from thread %d\n", i);
    }

    double end = omp_get_wtime();
    double seq_time = end - start;

    printf("Sequential Execution Time: %f seconds\n", seq_time);
    return 0;
}
