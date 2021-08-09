#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 10

int A[10][10] = {
  {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
  {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
  {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
  {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
  {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
  {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
  {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
  {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
  {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
  {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
};

int B[10][10] = {
  {10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
  {10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
  {10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
  {10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
  {10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
  {10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
  {10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
  {10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
  {10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
  {10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
};

int C[SIZE][SIZE];

void printMatrix(int matrix[SIZE][SIZE]) {
  for (int i = 0; i < SIZE; i++) {
    for(int j = 0; j < SIZE; j++) {
      printf("%d, ", matrix[i][j]);
    }
    printf("\n");
  }
}

void main(){ 
  int i, j, k;
  
  #pragma omp parallel for private(i, j, k) shared(A, B, C) num_threads(4) schedule(guided)
  for (i = 0; i < SIZE; i++){
    int iam = omp_get_thread_num();
    printf("Thread Num: %d, Iter: %d\n", iam, i);
    for (j = 0; j < SIZE; j++) {
      C[i][j] = 0.0;

      for (k = 0; k < SIZE; k++) {
        C[i][j] = C[i][j] + A[i][k] * B[k][j];
      }
    }
  }

  printMatrix(C);
}