#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int n = 4;
    int matrix[n][n];
    if (rank == 0) {
        // fill the matrix
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matrix[i][j] = i * n + j;
            }
        }
        // send columns to other processes
        for (int i = 1; i < size; ++i) {
            MPI_Send(&matrix[0][2], 2, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else if (rank > 0 && rank < 5) {
        // receive two columns from process 0
        int columns[n][2];
        MPI_Recv(&columns[0][0], 2 * n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // print received columns
        printf("Rank %d received columns: ", rank);
        for (int i = 0; i < n; ++i) {
            printf("%d %d ", columns[i][0], columns[i][1]);
        }
        printf("\n");
    } else {
        // print the whole matrix
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
