#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
// Вычисление числа Пи методом Монте-Карло
#define ITER_AMT 100000000

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    srand(rank * rand());
    double hit_amt_local = 0;
    for (int i = 0; i < ITER_AMT; i++) {
        double x = ((double) rand()) * 2 / RAND_MAX - 1;
        double y = ((double) rand()) * 2 / RAND_MAX - 1;
        if (x * x + y * y <= 1)
            hit_amt_local++;
    }

    double hit_amt = 0;
    MPI_Reduce(&hit_amt_local, &hit_amt, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double pi = hit_amt / (ITER_AMT * size) * 4;
        printf("pi = %f\n", pi);
    }

    MPI_Finalize();
    return 0;
}