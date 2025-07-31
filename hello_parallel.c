#include <stdio.h>
#include <omp.h>

int main() {
    int n;
    printf("Enter number of threads: ");
    scanf("%d", &n);
    omp_set_num_threads(n);

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Hello, World from thread %d\n", tid);
    }

    double end = omp_get_wtime();
    double par_time = end - start;

    printf("Parallel Execution Time: %f seconds\n", par_time);
    double speedup = seq_time / par_time;
    printf("Speed-Up = %f\n", speedup);


    return 0;
}
