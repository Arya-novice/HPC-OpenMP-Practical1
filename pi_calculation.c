#include <stdio.h>
#include <omp.h>

int main() {
    int num_steps;
    double step, x, pi_seq = 0.0, pi_par = 0.0;
    double start_seq, end_seq, start_par, end_par;

    printf("Enter number of steps for Pi calculation: ");
    scanf("%d", &num_steps);

    step = 1.0 / (double) num_steps;

    // Sequential Pi calculation
    start_seq = omp_get_wtime();
    for (int i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        pi_seq += 4.0 / (1.0 + x * x);
    }
    pi_seq *= step;
    end_seq = omp_get_wtime();

    // Parallel Pi calculation
    start_par = omp_get_wtime();
    #pragma omp parallel for reduction(+:pi_par) private(x)
    for (int i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        pi_par += 4.0 / (1.0 + x * x);
    }
    pi_par *= step;
    end_par = omp_get_wtime();

    double time_seq = end_seq - start_seq;
    double time_par = end_par - start_par;
    double speedup = time_seq / time_par;

    printf("\nSequential Pi  = %.15f", pi_seq);
    printf("\nParallel Pi    = %.15f", pi_par);
    printf("\nTime (Sequential): %f seconds", time_seq);
    printf("\nTime (Parallel): %f seconds", time_par);
    printf("\nSpeedup: %f\n", speedup);

    return 0;
}
