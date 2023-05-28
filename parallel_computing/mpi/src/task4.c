#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
// Среднее арифметическое среди положительных чисел массива
#define N 100000

void data_init(double *a) {
    for (int i = 0; i < N; i++) a[i] = i + 1;
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double a[N];
    if (rank == 0) data_init(a);

    int *sizes = malloc(size * sizeof(int));
    int *displs = malloc(size * sizeof(int));
    int rest = N;
    int k = rest / size;
    sizes[0] = N / size;
    displs[0] = 0;
    for (int i = 1; i < size; i++) {
        rest -= k;
        k = rest / (size - i);
        sizes[i] = k;
        displs[i] = displs[i - 1] + sizes[i - 1];
    }

    double *x_local = malloc(sizes[rank] * sizeof(double));
    MPI_Scatterv(a, sizes, displs, MPI_DOUBLE, x_local, sizes[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
    double avg_info_local[2];
    avg_info_local[0] = 0.0;
    avg_info_local[1] = 0.0;
    for (int i = 0; i < sizes[rank]; i++) {
        avg_info_local[0] += x_local[i];
        avg_info_local[1]++;
    }

    double avg_info[2];
    avg_info[0] = 0.0;
    avg_info[1] = 0.0;
    MPI_Reduce(avg_info_local, avg_info, 2, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) printf("avg = %f\n", avg_info[0] / avg_info[1]);

    free(displs);
    free(sizes);
    free(x_local);

    MPI_Finalize();
}