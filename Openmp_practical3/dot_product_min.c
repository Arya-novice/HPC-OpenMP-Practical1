// dot_product_min.c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int reverse_compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int a[SIZE], b[SIZE];
    int i;
    long long result = 0;

    // Initialize arrays
    for (i = 0; i < SIZE; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Sort a ascending and b descending
    qsort(a, SIZE, sizeof(int), compare);
    qsort(b, SIZE, sizeof(int), reverse_compare);

    // Parallel dot product with reduction
    #pragma omp parallel for reduction(+:result)
    for (i = 0; i < SIZE; i++) {
        result += a[i] * b[i];
    }

    printf("Minimum Scalar Product: %lld\n", result);
    return 0;
}
