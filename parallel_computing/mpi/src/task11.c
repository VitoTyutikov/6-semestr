#include <mpi.h>
#include <stdio.h>
// Циклическая передача данных
int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int data;

    if (rank == 0) {
        data = size;
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&data, 1, MPI_INT, size - 1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("data = %d\n", data);
    } else {
        MPI_Recv(&data, 1, MPI_INT, rank - 1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        data += rank;
        int dest = (rank + 1) % size;
        MPI_Send(&data, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}