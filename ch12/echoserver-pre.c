// The main thread has
// Two states:
//    * Waiting for connection request
//    * Waiting for available buffer slot
// Two I/O events:
//    * Connection request arrives
//    * buffer slot becomes available
// Two transitions:
//    * Accept connection request
//    * Insert buffer item
//
// Each worker thread has
// One state:
//    * Waiting for available buffer item
// One transition:
//    * Remove buffer item

#include "sbuf.h"
#include <bits/pthreadtypes.h>
#include <csapp.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NTHREADS 4
#define SBUFSIZE 16

void echo_cnt(int connfd);
void* thread(void* vargp);

sbuf_t sbuf;  // Shared buffer of connected descriptors

int main(int argc, char* argv[]) {
  int listenfd, connfd;
  pthread_t tid;
  struct sockaddr_storage clientaddr;
  socklen_t clientlen;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }
  listenfd = Open_listenfd(argv[1]);

  sbuf_init(&sbuf, SBUFSIZE);
  for (int i = 0; i < NTHREADS; i++) {
    Pthread_create(&tid, NULL, thread, NULL);  // Create worker threads
  }

  for (;;) {
    clientlen = sizeof(struct sockaddr_storage);
    connfd = Accept(listenfd, (SA*)&clientaddr, &clientlen);
    sbuf_insert(&sbuf, connfd);  // Insert connfd in buffer
  }

  return 0;
}

void* thread(void* vargp) {
  Pthread_detach(pthread_self());
  for (;;) {
    int connfd = sbuf_remove(&sbuf);  // Remove connfd from buffer
    echo_cnt(connfd);                 // Service client
    Close(connfd);
  }
}
