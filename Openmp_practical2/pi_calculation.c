#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    int num_points, count_seq = 0, count_par = 0;
    double x, y;
    double pi_seq, pi_par;
    double start_seq, end_seq, start_par, end_par;

    printf("Enter number of random points to generate: ");
    scanf("%d", &num_points);

    // Set seed for reproducibility
    srand(time(NULL));

    // Sequential Monte Carlo
    start_seq = omp_get_wtime();
    for (int i = 0; i < num_points; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x*x + y*y <= 1.0)
            count_seq++;
    }
    pi_seq = 4.0 * (double)count_seq / num_points;
    end_seq = omp_get_wtime();

    // Parallel Monte Carlo
    count_par = 0;
    start_par = omp_get_wtime();

    #pragma omp parallel
    {
        int thread_count = 0;
        unsigned int seed = time(NULL) ^ omp_get_thread_num(); // Thread-safe seeding
        #pragma omp for
        for (int i = 0; i < num_points; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x*x + y*y <= 1.0)
                thread_count++;
        }
        #pragma omp atomic
        count_par += thread_count;
    }

    pi_par = 4.0 * (double)count_par / num_points;
    end_par = omp_get_wtime();

    double time_seq = end_seq - start_seq;
    double time_par = end_par - start_par;
    double speedup = time_seq / time_par;

    printf("\nSequential Pi  = %.15f", pi_seq);
    printf("\nParallel Pi    = %.15f", pi_par);
    printf("\nTime (Sequential): %f seconds", time_seq);
    printf("\nTime (Parallel):   %f seconds", time_par);
    printf("\nSpeedup: %f\n", speedup);

    return 0;
}
