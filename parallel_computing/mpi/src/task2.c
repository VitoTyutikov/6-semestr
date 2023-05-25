#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
// Maксимум массива
#define N 100000

void data_init(double *a) {
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double a[N];
    if (rank == 0)
        data_init(a);

    MPI_Bcast(a, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int k = N / size;
    int i1 = k * rank;
    int i2 = k * (rank + 1);
    if (rank == size - 1)
        i2 = N;

    double max_local = 0.0;
    for (int i = i1; i < i2; i++)
        if (max_local < a[i])
            max_local = a[i];

    double max = 0;
    MPI_Reduce(&max_local, &max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("max = %f\n", max);

    MPI_Finalize();
    return 0;
}