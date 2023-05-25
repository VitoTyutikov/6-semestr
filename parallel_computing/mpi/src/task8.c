#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N_LOCAL 3

int scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf,
            int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    if (rank == root)
    {
        for (int i = 0; i < size; i++)
        {
            int type_size = 0;
            MPI_Type_size(sendtype, &type_size);
            MPI_Send(sendbuf + sendcount * i * type_size, sendcount, sendtype, i, 123456, comm);
        }
    }
    MPI_Status status;
    MPI_Recv(recvbuf, recvcount, recvtype, root, 123456, comm, &status);

    return status.MPI_ERROR;
}

int gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf,
           int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    MPI_Send(sendbuf, sendcount, sendtype, root, 654321, comm);
    if (rank == root)
    {
        MPI_Status status;
        for (int i = 0; i < size; i++)
        {
            int type_size = 0;
            MPI_Type_size(recvtype, &type_size);
            MPI_Recv(recvbuf + recvcount * i * type_size, recvcount, recvtype, i, 654321, comm, &status);
        }
    }

    MPI_Barrier(comm);

    return MPI_SUCCESS;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = size * N_LOCAL;
    int *a;
    if (rank == 0)
    {
        a = malloc(n * sizeof(int));
        printf("Rank 0 | init array | ");
        for (int i = 0; i < n; i++)
        {
            a[i] = i;
            printf("%d ", a[i]);
        }
        printf("\n");
    }

    int *a_local = malloc(N_LOCAL * sizeof(int));
    scatter(a, N_LOCAL, MPI_INT, a_local, N_LOCAL, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Rank %d | recv array | ", rank);
    for (int i = 0; i < N_LOCAL; i++)
        printf("%d ", a_local[i]);
    printf("\n");

    int *a_new;
    if (rank == 0)
        a_new = malloc(n * sizeof(int));
    gather(a_local, N_LOCAL, MPI_INT, a_new, N_LOCAL, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Rank 0 | gather array | ");
        for (int i = 0; i < n; i++)
            printf("%d ", a_new[i]);
        printf("\n");
        free(a);
        free(a_new);
    }
    free(a_local);

    MPI_Finalize();
}