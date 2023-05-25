#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
// Умножение матрицы на вектор при разделении данных по столбцам
#define N 10
#define M 20

void data_init(double a_transp[][N], double v[]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) a_transp[i][j] = i * N + j;
        v[i] = i;
    }
}

void data_distr(int size, int *v_sizes, int *v_displs, int *a_sizes, int *a_displs) {
    int rest = M;
    int k = rest / size;
    v_sizes[0] = M / size;
    v_displs[0] = 0;
    a_sizes[0] = M / size * N;
    a_displs[0] = 0;
    for (int i = 1; i < size; i++) {
        rest -= k;
        k = rest / (size - i);
        v_sizes[i] = k;
        v_displs[i] = v_displs[i - 1] + v_sizes[i - 1];
        a_sizes[i] = k * N;
        a_displs[i] = a_displs[i - 1] + a_sizes[i - 1];
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double a_transp[M][N], v[M];
    if (rank == 0) data_init(a_transp, v);

    int *v_sizes = malloc(size * sizeof(int));
    int *v_displs = malloc(size * sizeof(int));
    int *a_sizes = malloc(size * sizeof(int));
    int *a_displs = malloc(size * sizeof(int));
    data_distr(size, v_sizes, v_displs, a_sizes, a_displs);

    double *a_local = malloc(a_sizes[rank] * sizeof(double));
    double *v_local = malloc(v_sizes[rank] * sizeof(double));
    MPI_Scatterv(a_transp, a_sizes, a_displs, MPI_DOUBLE, a_local, a_sizes[rank], MPI_DOUBLE, 0,
                 MPI_COMM_WORLD);
    MPI_Scatterv(v, v_sizes, v_displs, MPI_DOUBLE, v_local, v_sizes[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double res_local[N];
    for (int i = 0; i < N; i++) res_local[i] = 0.0;

    for (int i = 0; i < v_sizes[rank]; i++)
        for (int j = 0; j < N; j++) res_local[j] += a_local[i * N + j] * v_local[i];

    double res[N];
    MPI_Reduce(res_local, res, N, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < N; i++) printf("%f ", res[i]);
        printf("\n");
    }

    free(v_sizes);
    free(v_displs);
    free(a_sizes);
    free(a_displs);
    free(a_local);
    free(v_local);

    MPI_Finalize();
}