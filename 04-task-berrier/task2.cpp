#include <stdio.h>
#include <omp.h>
#include <iostream>
int main(int argc, char *argv[])
{
  double x[10001];
  double sum;
  int i;
  
for(i=0; i<10000; i++)
{ 
    x[i]=1;
}  

#pragma omp parallel for shared(x),reduction(+:sum)

for(i=0; i<10000; i++)
sum += x[i];

std::cout << "Sum: " << sum << std::endl;

return 0;
}