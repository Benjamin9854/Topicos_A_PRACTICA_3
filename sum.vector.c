#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000 // Tamaño del vector

void fill_vector(int *vector, int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100;
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    int *A = NULL, *B = NULL, *C = NULL;
    int *local_A, *local_B, *local_C;
    int local_N;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_N = N / size;

    local_A = (int *)malloc(local_N * sizeof(int));
    local_B = (int *)malloc(local_N * sizeof(int));
    local_C = (int *)malloc(local_N * sizeof(int));

    if (rank == 0) {
        A = (int *)malloc(N * sizeof(int));
        B = (int *)malloc(N * sizeof(int));
        C = (int *)malloc(N * sizeof(int));

        srand(time(0));
        fill_vector(A, N);
        fill_vector(B, N);
    }

    MPI_Scatter(A, local_N, MPI_INT, local_A, local_N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(B, local_N, MPI_INT, local_B, local_N, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < local_N; i++) {
        local_C[i] = local_A[i] + local_B[i];
    }

    MPI_Gather(local_C, local_N, MPI_INT, C, local_N, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Vector C (suma de A y B):\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", C[i]);
            if (i % 10 == 9) printf("\n");
        }
        free(A);
        free(B);
        free(C);
    }

    free(local_A);
    free(local_B);
    free(local_C);

    MPI_Finalize();
    return 0;
}
