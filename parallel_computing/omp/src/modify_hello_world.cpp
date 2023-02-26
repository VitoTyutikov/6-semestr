//
// Created by vitaly on 26.02.23.
//
#include <iostream>
#include <omp.h>

#define threads 8

int main() {
    printf("\nTASK13\n");
    //1
#pragma omp parallel for num_threads(threads) default(none) ordered
    for (int i = 0; i < threads; ++i) {
        int nt = omp_get_num_threads();
        int tn = omp_get_thread_num();
#pragma omp ordered
        printf("num_thread = %d\t threads_num = %d\t Hello, World!\n", nt-tn-1, nt);
    }



    return 0;
}