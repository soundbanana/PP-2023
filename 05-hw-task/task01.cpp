#include <stdio.h>
#include <omp.h>

void checkParallelRegion() {
    if(omp_in_parallel()) {
        printf("Parallel area\n");
    } else {
        printf("Serial area\n");
    }
}

int main(int argc, char *argv[]) {
    checkParallelRegion();
    
    #pragma omp parallel
    {
        #pragma omp master
        {
            checkParallelRegion();
        }
    }
    return 0;
}