// prefix_sum.c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// computes inclusive prefix-sum: out[i] = sum_{j=0..i} in[j]
int main() {
    int n;
    printf("Enter number of elements n: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    double *in = malloc(n * sizeof(double));
    double *out = malloc(n * sizeof(double));
    srand(0);
    for (int i = 0; i < n; ++i) in[i] = (double)(rand() % 10 + 1);

    int num_threads = omp_get_max_threads();

    double t0 = omp_get_wtime();

    double *partial = malloc((num_threads + 1) * sizeof(double));
    for (int i = 0; i <= num_threads; ++i) partial[i] = 0.0;

    // Phase 1: each thread computes prefix on its chunk and stores its chunk-sum
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int nth = omp_get_num_threads();
        int chunk = n / nth;
        int start = tid * chunk;
        int end = (tid == nth - 1) ? n : start + chunk;

        double s = 0.0;
        for (int i = start; i < end; ++i) {
            s += in[i];
            out[i] = s;
        }
        partial[tid] = s;
        #pragma omp barrier

        // Phase 2: compute offset (prefix of partial sums) serially by one thread
        #pragma omp single
        {
            double acc = 0.0;
            for (int i = 0; i < nth; ++i) {
                double tmp = partial[i];
                partial[i] = acc; // store offset for thread i
                acc += tmp;
            }
        }
        #pragma omp barrier

        // Phase 3: each thread adds offset to its output block (except first block)
        double offset = partial[tid];
        if (offset != 0.0) {
            for (int i = start; i < end; ++i) out[i] += offset;
        }
    }

    double t1 = omp_get_wtime();
    printf("Prefix-sum (inclusive) of %d elements: Time = %f s\n", n, t1 - t0);

    // sample output
    printf("in[0]=%f, out[0]=%f\n", in[0], out[0]);
    if (n > 1) printf("in[n-1]=%f, out[n-1]=%f\n", in[n-1], out[n-1]);

    free(in); free(out); free(partial);
    return 0;
}
