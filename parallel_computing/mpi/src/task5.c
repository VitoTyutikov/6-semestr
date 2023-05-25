#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
//Скалярное произведение векторов
#define N 10

void data_init(double *v1, double *v2) {
    for (int i = 0; i < N; i++) {
        v1[i] = i % 100;
        v2[i] = i % 100;
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double v1[N];
    double v2[N];
    if (rank == 0)
        data_init(v1, v2);

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

    double *v1_local = malloc(sizes[rank] * sizeof(double));
    double *v2_local = malloc(sizes[rank] * sizeof(double));
    MPI_Scatterv(v1, sizes, displs, MPI_DOUBLE, v1_local, sizes[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatterv(v2, sizes, displs, MPI_DOUBLE, v2_local, sizes[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double *prod_local = malloc(sizes[rank] * sizeof(double));
    for (int i = 0; i < sizes[rank]; i++)
        prod_local[i] = v1_local[i] * v2_local[i];

    double prod[N];
    MPI_Gatherv(prod_local, sizes[rank], MPI_DOUBLE, prod, sizes, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            printf("%f ", prod[i]);
        }
        printf("\n");
    }

    free(sizes);
    free(displs);
    free(v1_local);
    free(v2_local);
    free(prod_local);
    MPI_Finalize();
}