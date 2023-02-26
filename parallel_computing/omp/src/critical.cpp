//
// Created by vitaly on 26.02.23.
//
#include <ctime>
#include <iostream>

#define ROWS 6
#define COLS 8
#define threads 16

int main() {
    printf("\nTASK10\n");
    std::srand(time(nullptr));
    int **matrix = new int *[ROWS];
    //    std::printf("Matrix:\n");
    for (int i = 0; i < ROWS; ++i) {
        matrix[i] = new int[COLS];
        for (int j = 0; j < COLS; ++j) {
            matrix[i][j] = rand() % (ROWS * COLS);
            //            std::printf("%d ", matrix[i][j]);
        }
        //        std::printf("\n");
    }
    int max = matrix[0][0];
    int min = matrix[0][0];

#pragma omp parallel for num_threads(threads) shared(matrix, max, min) default(none)
    for (int i = 0; i < ROWS; ++i) {
#pragma omp parallel for num_threads(threads) shared(matrix, max, min, i) default(none)
        for (int j = 0; j < COLS; ++j) {
#pragma omp critical
            if (max < matrix[i][j]) {
                max = matrix[i][j];
            }
#pragma omp critical
            if (min > matrix[i][j]) {
                min = matrix[i][j];
            }
        }
    }
    std::printf("max = %d\tmin = %d\n", max, min);

    for (int i = 0; i < ROWS; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}