//
// Created by vitaly on 25.02.23.
//
#include <cstdio>
#include <omp.h>
#include <ctime>
#include <iostream>

//parallel faster from ~500-1500
#define COLS 10
#define ROWS 10
#define threads 16

int *matrixMultVectorParallel(int **matrix, const int *vector);

int *matrixMultVector(int **matrix, const int *vector);

int main() {
    printf("\nTASK9\n");
    std::srand(time(nullptr));
    double start, end;
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
//    std::printf("\nVector:\n");
    int *vector = new int[COLS];
    for (int i = 0; i < COLS; ++i) {
        vector[i] = rand() % COLS;
//        std::printf("%d ", vector[i]);
    }
//    std::printf("\n");


    start = omp_get_wtime();
    int *res = matrixMultVector(matrix, vector);
    end = omp_get_wtime();
    delete[]res;
    std::printf("Series time = %lf\n", end - start);


    start = omp_get_wtime();
    res = matrixMultVectorParallel(matrix, vector);
    end = omp_get_wtime();
    delete[]res;
    std::printf("Parallel time = %lf\n", end - start);


    delete[]vector;
    for (int i = 0; i < ROWS; ++i) {
        delete[]matrix[i];
    }
    delete[]matrix;

//    for (int i = 0; i < ROWS; ++i) {
//        printf("%d ", res[i]);
//    }

    return 0;
}

int *matrixMultVectorParallel(int **matrix, const int *vector) {
    int *res = new int[ROWS];
#pragma omp parallel for num_threads(threads) shared(matrix, vector, res) default(none) schedule(auto)
    for (int i = 0; i < ROWS; ++i) {
        int sum = 0;
#pragma omp parallel shared(matrix, vector, res, sum, i) default(none)
        {
#pragma omp for  reduction(+:sum) schedule(auto)
            for (int j = 0; j < COLS; ++j) {
                sum += matrix[i][j] * vector[j];
            }
            res[i] = sum;
        }
    }
    return res;
}

int *matrixMultVector(int **matrix, const int *vector) {
    int *res = new int[ROWS];
    for (int i = 0; i < ROWS; ++i) {
        int sum = 0;
        for (int j = 0; j < COLS; ++j) {
            sum += matrix[i][j] * vector[j];
        }
        res[i] = sum;
    }
    return res;
}