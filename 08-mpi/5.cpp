#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Создаем буферы для отправки и приема данных
    int sendbuf[size];
    int recvbuf[size];

    // Заполняем буфер отправки данными (в данном случае, рангом процесса)
    for (int i = 0; i < size; i++) {
        sendbuf[i] = rank + i;
    }

    // Выполняем all-to-all scatter/gather
    MPI_Alltoall(sendbuf, 1, MPI_INT, recvbuf, 1, MPI_INT, MPI_COMM_WORLD);

    // Выводим результат
    printf("Процесс %d: ", rank);
    for (int i = 0; i < size; i++) {
        printf("%d ", recvbuf[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}

