#include <csapp.h>

void* thread(void* vargp);

int main(void) {
  pthread_t tid;
  Pthread_create(&tid, NULL, thread, NULL);
  Pthread_join(tid, NULL);

  return 0;
}

void* thread(void* vargp) {
  printf("Hello, world!\n");
  return NULL;
}
