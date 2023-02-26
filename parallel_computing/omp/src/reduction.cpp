//
// Created by vitaly on 25.02.23.
//
#include <iostream>
#include <cstdio>
#include <ctime>
#include <omp.h>


int main() {
    printf("\nTASK6\n");

    std::srand(time(nullptr));
    int a[100];
    for (int &i: a) {
//        i = 1;
        i = std::rand() % 100;
    }


    double avg = 0;
#pragma omp parallel for shared(a, avg) default(none)
    for (int i: a) {
        avg += i;
    }
    double avg_red = 0;
#pragma omp parallel for shared(a) reduction(+:avg_red) default(none)
    for (int i: a) {
        avg_red += i;
    }
    avg /= 100;
    avg_red /= 100;
    printf("Avg = %lf\t avg with reduction = %lf\n", avg, avg_red);
    return 0;
}