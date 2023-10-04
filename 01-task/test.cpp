#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    printf("Sequential 1\n");

    #pragma omp parallel
{
    int thread_id = omp_get_thread_num();
    printf("Parallel thread %d\n", thread_id);
    // Add some computational workload here
    for (int i = 0; i < 10000000; i++) {
        // Some computation
    }
}


    printf("Sequential 2\n");

    return 0;
}
