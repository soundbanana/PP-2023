#include <omp.h>
 
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char* argv[])
{
    #pragma omp parallel
    {
        #pragma omp for
        for (int i=0; i < 2; i++) {
            printf("%d, %d, %d\n", i, omp_get_thread_num(), omp_get_num_threads());
        }
    }
}