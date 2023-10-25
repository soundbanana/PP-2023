#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int n = 100; // Total number of elements to sum
    int local_n = n / world_size; // Number of elements each process will handle

    // Calculate the range of elements for this process
    int start = world_rank * local_n;
    int end = start + local_n;

    int *data = (int *)malloc(local_n * sizeof(int));
    for (int i = 0; i < local_n; i++) {
        data[i] = i + start;
    }

    int local_sum = 0;
    for (int i = 0; i < local_n; i++) {
        local_sum += data[i];
    }

    int global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("Total sum: %d\n", global_sum);
    }

    MPI_Finalize();

    return 0;
}
