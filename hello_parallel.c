#include <stdio.h>
#include <omp.h>

int main() {
    int n;
    printf("Enter number of threads: ");
    scanf("%d", &n);
    omp_set_num_threads(n);

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Hello, World from thread %d\n", tid);
    }
    return 0;
}
