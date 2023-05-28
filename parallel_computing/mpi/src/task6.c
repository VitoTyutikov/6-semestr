#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
//Maxmin матрицы
#define N 100
#define M 50

void data_init(double a[][M]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            a[i][j] = i * M + j;
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double a[N][M];
    if (rank == 0)
        data_init(a);

    int *sizes = malloc(size * sizeof(int));
    int *displs = malloc(size * sizeof(int));
    int rest = N;
    int k = rest / size;
    sizes[0] = N / size * M;
    displs[0] = 0;
    for (int i = 1; i < size; i++) {
        rest -= k;
        k = rest / (size - i);
        sizes[i] = k * M;
        displs[i] = displs[i - 1] + sizes[i - 1];
    }

    double *a_local = malloc(sizes[rank] * sizeof(double));
    MPI_Scatterv(a, sizes, displs, MPI_DOUBLE, a_local, sizes[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double min_local = -1;
    for (int i = 0; i < sizes[rank]; i += M) {
        double max_local2x = a_local[i];//max in line
        for (int j = i; j < i + M; j++)
            if (max_local2x < a_local[j])
                max_local2x = a_local[j];
        if (min_local > max_local2x || min_local == -1)
            min_local = max_local2x;
    }

    double max_local = -1;
    for (int i = 0; i < sizes[rank]; i += M) {
        double min_local2x = a_local[i];
        for (int j = i; j < i + M; j++)
            if (min_local2x > a_local[j])
                min_local2x = a_local[j];
        if (max_local < min_local2x)
            max_local = min_local2x;
    }

    double maxmin = 0.0;
    double minmax = 0.0;
    MPI_Reduce(&min_local, &maxmin, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&max_local, &minmax, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("maxmin = %f\n", maxmin);
        printf("minmax = %f\n", minmax);
    }

    free(sizes);
    free(displs);
    free(a_local);

    MPI_Finalize();
}