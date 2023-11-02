#include <stdio.h>
#include <mpi.h>
int main (int argc, char **argv)
{
    int rank, numtask;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtask);
    
    int a[5];
    a[0] = 10;
    a[1] = rank;
    if (rank == 1) {
	for (int i = 0; i < numtask; i++) {
	    if (i != 1) {
        	MPI_Send(&a[1], 1, MPI_INT, i, 99, MPI_COMM_WORLD);
	    }
	}
    } else {
	MPI_Recv(&a[0], 1, MPI_INT, 1, 99, MPI_COMM_WORLD, &status);
	printf("%d", a[0]);
    }
    MPI_Finalize();
}
