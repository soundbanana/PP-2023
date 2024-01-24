#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    MPI_Comm comm = MPI_COMM_WORLD;
    int rank, gsize, root = 0, *sendbuf, rbuf[100];
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &gsize);

    if (rank == root) {
        sendbuf = (int *)malloc(gsize*100*sizeof(int));
        for (int i = 0; i < gsize*100; i++) {
            sendbuf[i] = i;
        }
    }

    MPI_Scatter(sendbuf, 100, MPI_INT, rbuf, 100, MPI_INT, root, comm);

    printf("Process %d received: ", rank);
    for (int i = 0; i < 100; i++) {
        printf("%d ", rbuf[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}
