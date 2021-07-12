#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void main ( ) {
  #pragma omp parallel num_threads(6)
  {
    int ID = omp_get_thread_num();
    printf("hello(%d)", ID);
    printf("world(%d)\n",ID);
  }
}