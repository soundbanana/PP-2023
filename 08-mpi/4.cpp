#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Проверка наличия как минимум двух процессов
    if (world_size < 2) {
        std::cerr << "This program requires at least two processes." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    const int message_size = 100;
    int send_buffer[message_size];
    int recv_buffer[message_size];

    // Инициализация данных для отправки
    for (int i = 0; i < message_size; ++i) {
        send_buffer[i] = world_rank * message_size + i;
    }

    // Определение партнера для передачи и приема данных
    int partner_rank = (world_rank + 1) % 2;

    // Отправка и прием данных с использованием MPI_Sendrecv
    MPI_Sendrecv(send_buffer, message_size, MPI_INT, partner_rank, 0,
                 recv_buffer, message_size, MPI_INT, partner_rank, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Вывод результатов
    std::cout << "Process " << world_rank << " sent: ";
    for (int i = 0; i < message_size; ++i) {
        std::cout << send_buffer[i] << " ";
    }

    std::cout << "\nProcess " << world_rank << " received: ";
    for (int i = 0; i < message_size; ++i) {
        std::cout << recv_buffer[i] << " ";
    }

    std::cout << std::endl;

    MPI_Finalize();

    return 0;
}