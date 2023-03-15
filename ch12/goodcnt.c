// #include <csapp.h>
#include <semaphore.h>
#include <stdlib.h>
#include <csapp.h>

void* thread(void* vargp);  // Thread routine prototype

// Global shared variable
volatile long cnt;  // Counter
sem_t mutex;        // Semaphore that protects counter

int main(int argc, char* argv[]) {
  long niters;
  pthread_t tid1, tid2;

  if (argc != 2) {
    printf("usage: %s <niters>\n", argv[0]);
    exit(0);
  }
  niters = atoi(argv[1]);

  Sem_init(&mutex, 0, 1);

  // Create therads and wait for them to finish
  Pthread_create(&tid1, NULL, thread, &niters);
  Pthread_create(&tid2, NULL, thread, &niters);
  Pthread_join(tid1, NULL);
  Pthread_join(tid2, NULL);

  // Check result
  if (cnt != (2 * niters)) {
    printf("BOOM! cnt=%ld\n", cnt);
  } else {
    printf("OK cnt=%ld\n", cnt);
  }

  return 0;
}

void* thread(void* vargp) {
  long niters = *((long*)vargp);
  for (long i = 0; i < niters; i++) {
    P(&mutex);
    cnt++;
    V(&mutex);
  }
  return NULL;
}
