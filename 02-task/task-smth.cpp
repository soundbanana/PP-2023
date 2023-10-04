#include <stdio.h>
#include <omp.h>

void Function1()
{
    printf("Function1\n");
}

void Task1()
{
    printf("Task1\n");    
}

void Task2()
{
    printf("Task2\n");    
}

void Task3()
{
    printf("Task3\n");    
}

int main()
{
    int x = 10;

#pragma omp_for
    for (int i = 0; i < x; i++)
        Function1();
#pragma omp_sections{}
#pragma omp_section
    {
        Task1();
    }
#pragma omp_section
    {
        Task2();
    }
#pragma omp_section
    {
        Task3();
    }
}


