// vector_scalar_add.c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 200
#define SCALAR 5

void run_static_schedule(int chunk) {
    int a[SIZE], b[SIZE];
    for (int i = 0; i < SIZE; i++) a[i] = i;

    double start = omp_get_wtime();

    #pragma omp parallel for schedule(static, chunk)
    for (int i = 0; i < SIZE; i++)
        b[i] = a[i] + SCALAR;

    double end = omp_get_wtime();
    printf("STATIC | Chunk: %d | Time: %f\n", chunk, end - start);
}

void run_dynamic_schedule(int chunk) {
    int a[SIZE], b[SIZE];
    for (int i = 0; i < SIZE; i++) a[i] = i;

    double start = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic, chunk)
    for (int i = 0; i < SIZE; i++)
        b[i] = a[i] + SCALAR;

    double end = omp_get_wtime();
    printf("DYNAMIC | Chunk: %d | Time: %f\n", chunk, end - start);
}

void nowait_demo() {
    int a[SIZE], b[SIZE];
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < SIZE / 2; i++)
            b[i] = a[i] + SCALAR;

        #pragma omp for nowait
        for (int i = SIZE / 2; i < SIZE; i++)
            b[i] = a[i] + SCALAR;

        #pragma omp single
        printf("NOWAIT clause executed\n");
    }
}

int main() {
    int chunks[] = {5, 10, 20, 50};

    for (int i = 0; i < 4; i++) {
        run_static_schedule(chunks[i]);
        run_dynamic_schedule(chunks[i]);
    }

    nowait_demo();
    return 0;
}
