#include <csapp.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void echo(int connfd) {
  rio_t rio;
  char buf[MAXLINE];
  size_t n;

  Rio_readinitb(&rio, connfd);
  while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
    printf("Server received %d bytes\n", (int)n);
    Rio_writen(connfd, buf, n);
  }

  return;
}

void sigchld_handler(int sig) {
  while (waitpid(-1, 0, WNOHANG)) {
    ;
  }
  return;
}

int main(int argc, char* argv[]) {
  int listenfd, connfd;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }

  Signal(SIGCHLD, sigchld_handler);
  listenfd = Open_listenfd(argv[1]);
  for (;;) {
    clientlen = sizeof(struct sockaddr_storage);
    connfd = Accept(listenfd, (SA*)&clientaddr, &clientlen);
    if (Fork() == 0) {
      Close(listenfd);
      echo(connfd);
      Close(connfd);
      exit(0);
    }
    Close(connfd);
  }

  return 0;
}
