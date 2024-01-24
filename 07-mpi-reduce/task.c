#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void DataInitialization(double x[], int N) {
    for (int i = 0; i < N; i++) {
        x[i] = rand() % 100;
    }
}

int main(int argc, char* argv[]) {
    double x[100], TotalSum, ProcSum = 0.0;
    int ProcRank, ProcNum, N = 100;
    MPI_Status Status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    if (ProcRank == 0)
        DataInitialization(x, N);

    MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int k = N / ProcNum;
    int i1 = k * ProcRank;
    int i2 = k * (ProcRank + 1);
    if (ProcRank == ProcNum - 1)
        i2 = N;
    for (int i = i1; i < i2; i++)
        ProcSum = ProcSum + x[i];

    MPI_Reduce(&ProcSum, &TotalSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Send(&ProcSum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    printf("Process %d sent message to process 0\n", ProcRank);

    if (ProcRank == 0) {
        for (int i = 1; i < ProcNum; i++) {
            MPI_Recv(&ProcSum, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &Status);
            printf("Received message from source %d with tag %d\n", Status.MPI_SOURCE, Status.MPI_TAG);
            printf("MPI_Status: MPI_SOURCE = %d, MPI_TAG = %d, MPI_ERROR = %d\n", Status.MPI_SOURCE, Status.MPI_TAG, Status.MPI_ERROR);
            TotalSum = TotalSum + ProcSum;
        }
        printf("\nTotal Sum = %10.2f\n", TotalSum);
    }

    MPI_Finalize();

    return 0;
}