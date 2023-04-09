#include "Tasks.h"

#include <iostream>

#include "mpi.h"
void taskOne(int argc, char **argv);
int find_max(int arr[], int size, int rank, int num_procs);
int main(int argc, char **argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    taskOne(argc, argv);
    return 0;
}
void taskOne(int rank, char **argv) {
    printf("Hello, world! From process %d of %d\n", rank, size);
    MPI_Finalize();
}

int find_max(int arr[], int size, int rank, int num_procs) {
    int local_max = arr[0];

    // каждый процесс находит максимальный элемент в своей части массива
    for (int i = 1; i < size; i++) {
        if (arr[i] > local_max) {
            local_max = arr[i];
        }
    }

    int global_max;
    // собираем все локальные максимальные значения на процессе 0
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        return global_max;
    } else {
        return -1;  // возвращаем недопустимое значение на других процессах
    }
}