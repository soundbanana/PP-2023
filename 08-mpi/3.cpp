#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    MPI_Comm comm = MPI_COMM_WORLD;
    int gsize, recvarray[100][150], *rptr;
    int root = 0, *sendbuf, myrank, bufsize, *stride;

    MPI_Datatype rtype;

    int i, *displs, *scounts, offset;

    MPI_Comm_size(comm, &gsize);
    MPI_Comm_rank(comm, &myrank);

    stride = (int *)malloc(gsize * sizeof(int));
    for (i = 0; i < gsize; i++) {
        stride[i] = (i + 1) * 150;
    }

    sendbuf = (int*)malloc(gsize * 100 * 150 * sizeof(int));
    for (i = 0; i < gsize * 100 * 150; i++) {
        sendbuf[i] = i;
    }

    displs = (int*)malloc(gsize * sizeof(int));
    scounts = (int*)malloc(gsize * sizeof(int));
    offset = 0;
    for (i = 0; i < gsize; ++i) {
        displs[i] = offset;
        offset += stride[i];
        scounts[i] = 100 - i;
    }

    MPI_Type_vector(100 - myrank, 1, 150, MPI_INT, &rtype);
    MPI_Type_commit(&rtype);
    rptr = &recvarray[0][myrank];
    MPI_Scatterv(sendbuf, scounts, displs, MPI_INT, rptr,
        1, rtype, root, comm);

    printf("Process %d received:\n", myrank);
    for (i = 0; i < 100 - myrank; i++) {
        printf("%d ", recvarray[i][myrank]);
    }
    printf("\n");

    MPI_Type_free(&rtype);
    free(stride);
    free(sendbuf);
    free(displs);
    free(scounts);

    MPI_Finalize();
    return 0;
}