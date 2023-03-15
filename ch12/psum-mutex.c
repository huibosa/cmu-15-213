#include <csapp.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXTHREADS 32

void* sum_mutex(void* vargp);  // Thread routine

// Global shared variables
long gsum = 0;           // Global sum
long nelems_per_thread;  // Number of elements to sum
sem_t mutex;             // Mutex to protect golbal sum

int main(int argc, char* argv[]) {
  long nthreads, nelems, log_nelems, myid[MAXTHREADS];
  pthread_t tid[MAXTHREADS];

  if (argc != 3) {
    fprintf(stderr, "usage: %s <nthread> <log_nelems>\n", argv[0]);
    exit(0);
  }
  nthreads = atoi(argv[1]);
  log_nelems = atoi(argv[2]);
  nelems = (1L << log_nelems);
  nelems_per_thread = nelems / nthreads;
  sem_init(&mutex, 0, 1);

  for (int i = 0; i < nthreads; i++) {
    myid[i] = i;
    Pthread_create(&tid[i], NULL, sum_mutex, &myid[i]);
  }
  for (int i = 0; i < nthreads; i++) {
    Pthread_join(tid[i], NULL);
  }

  if (gsum != ((nelems - 1) * nelems) / 2) {
    printf("Error: result=%ld\n", gsum);
  }

  return 0;
}

void* sum_mutex(void* vargp) {
  long myid = *((long*)vargp);
  long start = myid * nelems_per_thread;
  long end = start + nelems_per_thread;

  for (long i = start; i < end; i++) {
    P(&mutex);
    gsum += i;
    V(&mutex);
  }
  return 0;
}
