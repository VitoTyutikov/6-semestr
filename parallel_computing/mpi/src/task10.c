#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
//Время передачи для разных Send-oв (
#define N 1000000

void data_init(int a[], int a1[]) {
    for (int i = 0; i < N; i++) {
        a[i] = i + 1;
        a1[i] = -i - 1;
    }
}

void send_test() {
    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int a[N], a1[N];
    if (rank == 0)
        data_init(a, a1);

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        double start = MPI_Wtime();
        MPI_Send(a, N, MPI_INT, !rank, 1, MPI_COMM_WORLD);
        MPI_Recv(a1, N, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double end = MPI_Wtime();
        printf("Send() time = %f\n", end - start);
        printf("Send() check: 1 = %d, %d = %d\n", a1[0], N, a1[N - 1]);
    } else {
        MPI_Recv(a1, N, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(a1, N, MPI_INT, !rank, 2, MPI_COMM_WORLD);
    }
}

void ssend_test() {
    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int a[N], a1[N];
    if (rank == 0)
        data_init(a, a1);

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        double start = MPI_Wtime();
        MPI_Ssend(a, N, MPI_INT, !rank, 1, MPI_COMM_WORLD);
        MPI_Recv(a1, N, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double end = MPI_Wtime();
        printf("Ssend() time = %f\n", end - start);
        printf("Ssend() check: 1 = %d, %d = %d\n", a1[0], N, a1[N - 1]);
    } else {
        MPI_Recv(a1, N, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Ssend(a1, N, MPI_INT, !rank, 2, MPI_COMM_WORLD);
    }
}

void bsend_test() {
    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int a[N], a1[N];
    if (rank == 0)
        data_init(a, a1);

    int buffsize = 0;
    MPI_Pack_size(N, MPI_INT, MPI_COMM_WORLD, &buffsize);
    buffsize *= 2;
    void *buff = malloc(buffsize);
    MPI_Buffer_attach(buff, buffsize);
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        double start = MPI_Wtime();
        MPI_Bsend(a, N, MPI_INT, !rank, 1, MPI_COMM_WORLD);
        MPI_Recv(a1, N, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double end = MPI_Wtime();
        printf("Bsend() time = %f\n", end - start);
        printf("Bsend() check: 1 = %d, %d = %d\n", a1[0], N, a1[N - 1]);
    } else {
        MPI_Recv(a1, N, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Bsend(a1, N, MPI_INT, !rank, 2, MPI_COMM_WORLD);
    }
    MPI_Buffer_detach(buff, &buffsize);
    free(buff);
}

void rsend_test() {
    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int a[N], a1[N];
    if (rank == 0)
        data_init(a, a1);

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        double start = MPI_Wtime();
        MPI_Rsend(a, N, MPI_INT, !rank, 1, MPI_COMM_WORLD);
        MPI_Recv(a1, N, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double end = MPI_Wtime();
        printf("Rsend() time = %f\n", end - start);
        printf("Rsend() check: 1 = %d, %d = %d\n", a1[0], N, a1[N - 1]);
    } else {
        MPI_Recv(a1, N, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Rsend(a1, N, MPI_INT, !rank, 2, MPI_COMM_WORLD);
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    send_test();
    ssend_test();
    bsend_test();
    rsend_test();

    MPI_Finalize();
}