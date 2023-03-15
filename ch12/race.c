#include <csapp.h>
#define N 4

void* thread(void* vargp);

int main(void) {
  pthread_t tid[N];
  int myid[N];

  for (int i = 0; i < N; i++) {
    myid[i] = i;
    // Pthread_create(&tid[i], NULL, thread, &myid[i]);
    Pthread_create(&tid[i], NULL, thread, &i);
  }
  for (int i = 0; i < N; i++) {
    Pthread_join(tid[i], NULL);
  }

  return 0;
}

void* thread(void* vargp) {
  int myid = *((int*)vargp);
  printf("Hello from thread %d\n", myid);
  return NULL;
}
