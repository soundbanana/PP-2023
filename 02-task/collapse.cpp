#include <omp.h>
 
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char* argv[])
{
    #pragma omp parallel
    {
        #pragma omp for collapse(2)
        for (int i=0; i < 2; i++) {
            for (int j=0; j<2;j++)
            {
                printf("%d, %d, %d\n", i, j, omp_get_thread_num());
            }
        }
    }
}