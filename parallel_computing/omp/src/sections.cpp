//
// Created by vitaly on 25.02.23.
//
#include <iostream>
#include <cstdio>
#include <omp.h>
#include <ctime>

int main() {
    int d[6][8];
    std::srand(time(nullptr));
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            d[i][j] = std::rand() % 10;
        }
    }

#pragma omp parallel sections shared(d) default(none)
    {
#pragma omp section
        {
            double avg = 0;
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 8; j++) {
                    avg += d[i][j];
                }
            }
            avg /= 48;
            std::printf("Average = %lf\t(c) Thread %d\n", avg, omp_get_thread_num());

        }
#pragma omp section
        {
            int min = d[0][0];
            int max = d[0][0];
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 8; j++) {
                    if (max < d[i][j])
                        max = d[i][j];
                    else if (min > d[i][j])
                        min = d[i][j];
                }
            }
            std::printf("max = %d\tmin = %d\t(c) Thread %d\n", max, min, omp_get_thread_num());
        }
#pragma omp section
        {
            int count3 = 0;
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 8; j++) {
                    if (d[i][j] % 3 == 0)
                        count3++;
                }
            }
            std::printf("Count of multiple of 3 = %d\t (c) Thread %d\n", count3, omp_get_thread_num());
        }
    };


//    for (int i = 0; i < 6; ++i)
//    {
//        for (int j = 0; j < 8; ++j)
//        {
//            std::printf("%d ", d[i][j]);
//        }
//        std::printf("\n");
//    }
    return 0;
}