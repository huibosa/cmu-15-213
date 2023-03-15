#include <csapp.h>
#define N 4

void* thread(void* vargp);

int main(void) {
  pthread_t tid[N];
  int* ptr;

  for (int i = 0; i < N; i++) {
    ptr = (int*)Malloc(sizeof(int));
    *ptr = i;
    Pthread_create(&tid[i], NULL, thread, ptr);
  }
  for (int i = 0; i < N; i++) {
    Pthread_join(tid[i], NULL);
  }

  return 0;
}

void* thread(void* vargp) {
  int myid = *((int*)vargp);
  Free(vargp);
  printf("Hello from thread %d\n", myid);
  return NULL;
}
