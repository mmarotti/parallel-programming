#include <omp.h>
#include <stdio.h>

static long num_steps = 100000;
double step;

#define NMAX 50 // max de threads
#define NUM_THREADS 2

void main () {
  int i; double x, pi, sum[NMAX];
  int nthreads;

  step = 1.0/(double) num_steps;
  omp_set_num_threads (NUM_THREADS);

  #pragma omp parallel
  {
    int i, id, nthrds;
    id = omp_get_thread_num();
    nthrds = omp_get_num_threads();

    if (id == 0) nthreads = nthrds;

    for (i = id, sum[id] = 0.0; i < num_steps; i = i + nthrds){
      x = (i + 0.5) * step;
      sum[id] += 4.0 / (1.0 + x*x);
    }
  }

  for(i = 0, pi = 0.0; i < nthreads; i++) pi += sum[i] * step;

  printf("pi value: %f\n", pi);
}