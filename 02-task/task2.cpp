#include <omp.h>
 
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char* argv[])
{
    #pragma omp parallel
    {
        for (int i=0; i<4;i++){
            printf("%d, %d, %d \n", i, omp_get_num_threads(), omp_get_thread_num());
        }
    }
}