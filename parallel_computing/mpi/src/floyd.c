#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int proc_rank;
int proc_size;

#define N 2500

int Min(int A, int B) {
    int Result = (A < B) ? A : B;
    if ((A < 0) && (B >= 0)) Result = B;
    if ((B < 0) && (A >= 0)) Result = A;
    if ((A < 0) && (B < 0)) Result = -1;
    return Result;
}

void distribute_k_row(int *adj_local, int n, int n_local, int k, int *k_row) {
    int rest = n;
    int local_size = rest / proc_size;
    int rank_contains_k;
    int row_offset = 0;
    for (rank_contains_k = 0; rank_contains_k < proc_size; rank_contains_k++) {
        if (k < row_offset + local_size) break;
        rest -= local_size;
        row_offset += local_size;
        local_size = rest / (proc_size - rank_contains_k - 1);
    }
    int local_row_num = k - row_offset;
    if (proc_rank == rank_contains_k) {
        for (int i = 0; i < n; i++) {
            k_row[i] = adj_local[local_row_num * n + i];
        }
    }
    MPI_Bcast(k_row, n, MPI_INT, rank_contains_k, MPI_COMM_WORLD);
}

void floyd(int *adj_local, int n, int n_local) {
    int *k_row = malloc(n * sizeof(int));
    int t1, t2;
    for (int k = 0; k < n; k++) {
        distribute_k_row(adj_local, n, n_local, k, k_row);
        for (int i = 0; i < n_local; i++)
            for (int j = 0; j < n; j++)
                if ((adj_local[i * n + k] != -1) && (k_row[j] != -1)) {
                    t1 = adj_local[i * n + j];
                    t2 = adj_local[i * n + k] + k_row[j];
                    adj_local[i * n + j] = Min(t1, t2);
                }
    }
    free(k_row);
}

void data_distr(int n, int proc_size, int *sizes, int *displs) {
    int rest = n;
    int k = rest / proc_size;
    sizes[0] = n / proc_size * n;
    displs[0] = 0;
    for (int i = 1; i < proc_size; i++) {
        rest -= k;
        k = rest / (proc_size - i);
        sizes[i] = k * n;
        displs[i] = displs[i - 1] + sizes[i - 1];
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &proc_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

    int *adj_matrix;
    int n;
    FILE *file;
    if (proc_rank == 0) {
        file = fopen("./test.txt", "r");
        adj_matrix = malloc(n * n * sizeof(int));
        if (1) {
            fscanf(file, "%d", &n);
            for (int i = 0; i < n * n; i++) fscanf(file, "%d", &adj_matrix[i]);
        } else {
            n = N;
            for (int i = 0; i < n * n; i++) {
                int rand_num = rand() % 1300;
                if (rand_num > 1000)
                    adj_matrix[i] = -1;
                else
                    adj_matrix[i] = rand_num;
            };
        }
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int *sizes = malloc(proc_size * sizeof(int));
    int *displs = malloc(proc_size * sizeof(int));
    data_distr(n, proc_size, sizes, displs);

    int *adj_local = malloc(sizes[proc_rank] * sizeof(int));
    MPI_Scatterv(adj_matrix, sizes, displs, MPI_INT, adj_local, sizes[proc_rank], MPI_INT, 0, MPI_COMM_WORLD);

    double start = MPI_Wtime();
    floyd(adj_local, n, sizes[proc_rank] / n);
    double end = MPI_Wtime();

    MPI_Gatherv(adj_local, sizes[proc_rank], MPI_INT, adj_matrix, sizes, displs, MPI_INT, 0, MPI_COMM_WORLD);

    if (proc_rank == 0) {
        printf("Time: %f | n = %d\n", end - start, n);

        fclose(file);
        free(adj_matrix);
    }

    free(sizes);
    free(displs);
    free(adj_local);

    MPI_Finalize();
    return 0;
}