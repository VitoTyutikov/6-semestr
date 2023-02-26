//
// Created by vitaly on 26.02.23.
//
#include <iostream>
#include <omp.h>

#define SIZE 30

int main() {
    printf("\nTASK12\n");
    std::srand(time(nullptr));
    int a[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        a[i] = rand() % SIZE;
    }
    omp_lock_t lock;
    omp_init_lock(&lock);
    int max = 1;
#pragma omp parallel for shared(a, lock, max) default(none)
    for (int i = 0; i < SIZE; ++i) {
        if (a[i] % 7 == 0) {
            omp_set_lock(&lock);
            if (max < a[i]) {
                max = a[i];
            }
            omp_unset_lock(&lock);
        }
    }
    omp_destroy_lock(&lock);
    if (max == 1)
        std::printf("a[i] %% 7 == 0 doesn't exists\n");
    else
        std::printf("max = %d\n", max);

    return 0;
}
