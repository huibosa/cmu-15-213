#include <csapp.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

void* thread(void* vargp);
void echo(int connfd);

int main(int argc, char* argv[]) {
  int listenfd, *connfdp;
  struct sockaddr_storage clientaddr;
  socklen_t clientlen;
  pthread_t tid;

  listenfd = Open_listenfd(argv[1]);
  for (;;) {
    clientlen = sizeof(struct sockaddr_storage);
    connfdp = Malloc(sizeof(int));
    *connfdp = Accept(listenfd, (SA*)&clientaddr, &clientlen);
    Pthread_create(&tid, NULL, thread, connfdp);
  }

  return 0;
}

void* thread(void* vargp) {
  int connfd = *((int*)vargp);
  Pthread_detach(pthread_self());
  Free(vargp);
  echo(connfd);
  Close(connfd);
  return NULL;
}

void echo(int connfd) {
  rio_t rio;
  char buf[MAXLINE];
  size_t n;

  Rio_readinitb(&rio, connfd);
  while ((n = Rio_readlineb(&rio, buf, MAXLINE)) > 0) {
    printf("Server reaceived %d bytes\n", (int)n);
    Rio_writen(connfd, buf, n);
  }
  return;
}
