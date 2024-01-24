#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    MPI_Comm comm = MPI_COMM_WORLD;
    int gsize, *sendbuf, rank;
    int root = 0, rbuf[100];

    MPI_Comm_size(comm, &gsize);
    MPI_Comm_rank(comm, &rank);
    sendbuf = (int *)malloc(gsize*100*sizeof(int));

    if (rank == root) {
        // fill sendbuf with data
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
