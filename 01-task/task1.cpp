#include <stdio.h>
#include "omp.h"


int main() {
    int n = 1;
    printf("n в последовательной области (начало): %d\n", n);
#pragma omp parallel private(n) num_threads(4)
    {
        printf("Значение n в потоке (на входе): %d\n", n);
        /* Присвоим переменной n номер текущей нити */
        n = omp_get_thread_num();
        printf("Значение N в потоке (на выходе): %d\n", n);
    }
    printf("n в последовательной области (конец): %d\n", n);
}