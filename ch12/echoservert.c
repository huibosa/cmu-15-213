#include <csapp.h>
#include <bits/pthreadtypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

void* thread(void* vargp);
void echo(int connfd);

int main(int argc, char* argv[]) {
  int listenfd, *connfdp;
  struct sockaddr_storage clientaddr;
  socklen_t clientlen;
  pthread_t tid;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }

  listenfd = Open_listenfd(argv[1]);
  for (;;) {
    clientlen = sizeof(struct sockaddr_storage);
    connfdp = malloc(sizeof(int));
    *connfdp = Accept(listenfd, (SA*)&clientaddr, &clientlen);
    Pthread_create(&tid, NULL, thread, connfdp);
  }

  return 0;
}

void* thread(void* vargp) {
  int connfd = *((int*)vargp);
  Pthread_detach(Pthread_self());
  echo(connfd);
  Close(connfd);
  Free(vargp);
  return NULL;
}

void echo(int connfd) {
  char buf[MAXLINE];
  size_t n;
  rio_t rio;

  Rio_readinitb(&rio, connfd);
  while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
    printf("Server received %d bytes", (int)n);
    Rio_writen(connfd, buf, MAXLINE);
  }
  return;
}
