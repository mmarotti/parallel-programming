#include <stdio.h>
#include <mpi.h>

float f(float x) {
  return x * x;
}

float calcula(float local_a, float local_b, int local_n, float h) {
  float integral;
  float x, i;
  integral = ( f(local_a) + f(local_b) ) / 2.0;

  x = local_a;

  for(i=1; i<=local_n; i++) {
    x += h;
    integral += f(x);
  }

  integral *= h;
  return integral;
}

main(int argc, char** argv) {
  int my_rank;
  int p; // número de processos
  float a=0.0, b=1.0; //intervalo a calcular
  float n=3068;// float número de trapezóides
  float h;
  float local_a, local_b;
  int local_n;
  float integral;
  float total;

  int source;
  int dest=0;
  int tag=200;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  h = (b-a) / n;

  local_n = n / p;
  local_a = a + my_rank * local_n * h;
  local_b = local_a + local_n * h;

  integral = calcula(local_a, local_b, local_n, h);

  MPI_Reduce(&integral, &total, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
  
  if(my_rank == 0) printf("Resultado: %f\n", total);

  MPI_Finalize();
}
