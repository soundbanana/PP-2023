#include <stdio.h>
#include <omp.h>

int main(int argc, char*argv[]) {
    int n;
    #pragma omp parallel private(n)
    {
        n = omp_get_thread_num();
        printf("N Value (start): %d\n", n);

        #pragma omp single copyprivate(n) 
        {
            n = 100;   
        }

        printf("N Value (end): %d\n", n);
    }
    return 0;
}