//
// Created by vitaly on 25.02.23.
//

#include <cstdio>
#include <omp.h>

#define SIZE 16000

int main() {
    printf("\nTASK8\n");
    int a[SIZE];
    double start, end;
#pragma omp parallel for shared(a) default(none)
    for (int i = 0; i < SIZE; ++i) {
        a[i] = i;
    }

    double *res=new double [SIZE];
    res[0] = a[0];
    res[SIZE - 1] = a[SIZE - 1];
    //1
    start = omp_get_wtime();
#pragma omp parallel num_threads(8) shared(a, res) default(none)
    {
#pragma omp for schedule(static, 8)
        for (int i = 1; i < SIZE - 1; ++i) {
            res[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    end = omp_get_wtime();
    printf("Time = %lf9 with static and 8\n", end - start);

    //2
    start = omp_get_wtime();
#pragma omp parallel num_threads(8) shared(a, res) default(none)
    {
#pragma omp for schedule(static, 4)
        for (int i = 1; i < SIZE - 1; ++i) {
            res[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    end = omp_get_wtime();
    printf("Time = %lf9 with static and 4\n", end - start);

    //3
    start = omp_get_wtime();
#pragma omp parallel num_threads(8) shared(a, res) default(none)
    {
#pragma omp for schedule(guided, 8)
        for (int i = 1; i < SIZE - 1; ++i) {
            res[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    end = omp_get_wtime();
    printf("Time = %lf9 with guided and 8\n", end - start);

    //4
    start = omp_get_wtime();
#pragma omp parallel num_threads(8) shared(a, res) default(none)
    {
#pragma omp for schedule(guided, 4)
        for (int i = 1; i < SIZE - 1; ++i) {
            res[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    end = omp_get_wtime();
    printf("Time = %lf9 with guided and 4\n", end - start);

    //5
    start = omp_get_wtime();
#pragma omp parallel num_threads(8) shared(a, res) default(none)
    {
#pragma omp for schedule(dynamic, 8)
        for (int i = 1; i < SIZE - 1; ++i) {
            res[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    end = omp_get_wtime();
    printf("Time = %lf9 with dynamic and 8\n", end - start);

    //6
    start = omp_get_wtime();
#pragma omp parallel num_threads(8) shared(a, res) default(none)
    {
#pragma omp for schedule(dynamic, 4)
        for (int i = 1; i < SIZE - 1; ++i) {
            res[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    end = omp_get_wtime();
    printf("Time = %lf9 with dynamic and 4\n", end - start);

    //7
    start = omp_get_wtime();
#pragma omp parallel num_threads(8) shared(a, res) default(none)
    {
#pragma omp for schedule(auto)
        for (int i = 1; i < SIZE - 1; ++i) {
            res[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    end = omp_get_wtime();
    printf("Time = %lf9 with auto\n", end - start);

    delete[]res;

    return 0;
}