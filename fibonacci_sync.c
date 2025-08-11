#include <stdio.h>
#include <omp.h>

// Recursive Fibonacci with OpenMP tasks and synchronization
long long fibonacci(int n) {
    if (n < 2)
        return n;

    long long x, y;

    #pragma omp task shared(x)
    x = fibonacci(n - 1);

    #pragma omp task shared(y)
    y = fibonacci(n - 2);

    #pragma omp taskwait // Wait for both tasks to finish
    return x + y;
}

int main() {
    int n;
    long long result;
    double start, end;

    printf("Enter value of n: ");
    scanf("%d", &n);

    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fibonacci(n);
        }
    }

    end = omp_get_wtime();

    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Execution Time: %f seconds\n", end - start);

    return 0;
}
