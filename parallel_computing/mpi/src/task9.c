#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
//Инвертировать массив
#define N 20

void data_init(int a[]) {
    for (int i = 0; i < N; i++)
        a[i] = i;
}

int gatherv_reversed(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf,
                     const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root,
                     MPI_Comm comm) {
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    MPI_Send(sendbuf, sendcount, sendtype, root, 654321, comm);
    if (rank == root) {
        MPI_Status status;
        for (int i = 0; i < size; i++) {
            int type_size = 0;
            MPI_Type_size(recvtype, &type_size);
            MPI_Recv(recvbuf + displs[i] * type_size, recvcounts[i], recvtype, size - 1 - i, 654321, comm, &status);
        }
    }

    MPI_Barrier(comm);

    return MPI_SUCCESS;
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int a[N];
    if (rank == 0)
        data_init(a);

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

    int *a_local = malloc(sizes[rank] * sizeof(int));
    MPI_Scatterv(a, sizes, displs, MPI_INT, a_local, sizes[rank], MPI_INT, 0, MPI_COMM_WORLD);

    int *reversed_local = malloc(sizes[rank] * sizeof(int));
    for (int i = 0; i < sizes[rank]; i++)
        reversed_local[i] = a_local[sizes[rank] - 1 - i];

    int reversed[N];
    gatherv_reversed(reversed_local, sizes[rank], MPI_INT, reversed, sizes, displs, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < N; i++)
            printf("%d ", reversed[i]);
        printf("\n");
    }

    free(sizes);
    free(displs);
    free(a_local);
    free(reversed_local);

    MPI_Finalize();
}