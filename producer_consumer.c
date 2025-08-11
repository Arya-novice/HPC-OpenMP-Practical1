#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define BUFFER_SIZE 10
#define PRODUCE_COUNT 20

int buffer[BUFFER_SIZE];
int count = 0; // Number of items in buffer

void producer() {
    for (int i = 0; i < PRODUCE_COUNT; i++) {
        #pragma omp critical
        {
            if (count < BUFFER_SIZE) {
                buffer[count] = i;
                count++;
                printf("Producer %d produced item %d (count=%d)\n", omp_get_thread_num(), i, count);
            }
        }
    }
}

void consumer() {
    for (int i = 0; i < PRODUCE_COUNT; i++) {
        #pragma omp critical
        {
            if (count > 0) {
                int item = buffer[count - 1];
                count--;
                printf("Consumer %d consumed item %d (count=%d)\n", omp_get_thread_num(), item, count);
            }
        }
    }
}

int main() {
    omp_set_num_threads(4); // 2 producers + 2 consumers

    #pragma omp parallel sections
    {
        #pragma omp section
        producer();

        #pragma omp section
        producer();

        #pragma omp section
        consumer();

        #pragma omp section
        consumer();
    }

    return 0;
}

