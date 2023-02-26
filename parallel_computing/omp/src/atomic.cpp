//
// Created by vitaly on 26.02.23.

#include <iostream>

#define SIZE 30

int main() {
    printf("\nTASK11\n");
    std::srand(time(nullptr));
    int a[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        a[i] = std::rand() % SIZE;
    }
    int count = 0;
#pragma omp parallel for shared(count, a) default(none)
    for (int i = 0; i < SIZE; ++i) {
        if (a[i] % 9 == 0)
#pragma omp atomic
            count++;
    }
    std::printf("count = %d\n", count);
    return 0;
}