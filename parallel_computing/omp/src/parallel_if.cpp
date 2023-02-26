#include <omp.h>

#include <cstdio>

int num_threads;

int main() {
    printf("\nTASK2\n");
    num_threads = 3;
#pragma omp parallel if (num_threads > 2) num_threads(num_threads) default(none) shared(num_threads)
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d of %d in first parallel region\n", thread_id, num_threads);
    }
    num_threads = 2;
#pragma omp parallel if (num_threads > 2) num_threads(num_threads) default(none) shared(num_threads)
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d of %d in second parallel region\n", thread_id, num_threads);
    }

    return 0;
}
