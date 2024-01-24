#include <stdio.h>
#include <mpi.h>

double f(double x) {
    return x * x;
}

int main(int argc, char *argv[]) {
    int rank, size;
    double a = 1.0, b = 3.0;
    int n = 16;  // количество прямоугольников (насколько больше, тем выше точность)

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double local_sum = 0.0;
    double delta_x = (b - a) / n;
    int local_n = n / size;
    int start = rank * local_n;
    int end = start + local_n;

    for (int i = start; i < end; i++) {
        double x_i = a + delta_x /2 + i * delta_x;
        local_sum += f(x_i) * delta_x;
    }

    double global_sum = 0.0;
    MPI_Barrier(MPI_COMM_WORLD); // Убедитесь, что вся обработка субсчетов завершена.

    if (rank == 0) {
        global_sum = local_sum;
        for (int i = 1; i < size; i++) {
            double temp_sum;
            MPI_Status status;
            MPI_Recv(&temp_sum, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
            global_sum += temp_sum;
        }
    } else {
        MPI_Send(&local_sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        printf("Приблизительная стоимость интеграции: %lf\n", global_sum);
    }

    MPI_Finalize();

    return 0;
}
