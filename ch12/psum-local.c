#include <csapp.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXTHREADS 32

void* sum_array(void* vargp);  // Thread routine

// Global shared variables
long psum[MAXTHREADS];   // Global sum
long nelems_per_thread;  // Number of elements to sum

int main(int argc, char* argv[]) {
  long nthreads, nelems, log_nelems, myid[MAXTHREADS];
  long sum = 0;
  pthread_t tid[MAXTHREADS];

  if (argc != 3) {
    fprintf(stderr, "usage: %s <nthread> <log_nelems>\n", argv[0]);
    exit(0);
  }
  nthreads = atoi(argv[1]);
  log_nelems = atoi(argv[2]);
  nelems = (1L << log_nelems);
  nelems_per_thread = nelems / nthreads;

  for (int i = 0; i < nthreads; i++) {
    myid[i] = i;
    Pthread_create(&tid[i], NULL, sum_array, &myid[i]);
  }
  for (int i = 0; i < nthreads; i++) {
    Pthread_join(tid[i], NULL);
  }

  for (long i = 0; i < nthreads; i++) {
    sum += psum[i];
  }

  if (sum != ((nelems - 1) * nelems) / 2) {
    printf("Error: result=%ld\n", sum);
  }

  return 0;
}

void* sum_array(void* vargp) {
  long myid = *((long*)vargp);
  long start = myid * nelems_per_thread;
  long end = start + nelems_per_thread;
  long sum = 0;

  for (long i = start; i < end; i++) {
    sum += i;
  }
  psum[myid] = sum;

  return NULL;
}
