//
// Created by vitaly on 25.02.23.
//
#include <cstdio>
#include <omp.h>

#define SIZE 12

int main() {
    printf("\nTASK7\n");

    int a[SIZE], b[SIZE], c[SIZE];

#pragma omp parallel num_threads(3) shared(a, b) default(none)
    {
#pragma omp for schedule(static, 4)
        for (int i = 0; i < SIZE; ++i) {
            a[i] = i + SIZE;
            b[i] = i - SIZE;
            std::printf("num_threads = %d\tthread_num = %d\ta[%d] = %d\tb[%d] = %d\n", omp_get_num_threads(),
                        omp_get_thread_num(), i, a[i], i, b[i]);
        }
    }
    std::printf("\n");
#pragma omp parallel num_threads(4) shared(a, b, c) default(none)
    {
#pragma omp for schedule(dynamic, 3)
        for (int i = 0; i < SIZE; ++i) {
            c[i] = a[i] + b[i];
            std::printf("num_threads = %d\tthread_num = %d\tc[%d] = %d\n", omp_get_num_threads(),
                        omp_get_thread_num(), i, c[i]);
        }
    }
    return 0;
}