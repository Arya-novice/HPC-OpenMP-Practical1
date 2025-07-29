#include <stdio.h>
#include <omp.h>
int main(){
#pragma omp parallel
{
   printf("Hello, World (Parallel)\n");
}
return 0;
}
