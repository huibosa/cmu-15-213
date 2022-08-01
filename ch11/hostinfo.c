#include <csapp.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
  struct addrinfo *listp, hints;
  char buf[MAXLINE];
  int rc, flags;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <domain nam>\n", argv[0]);
    exit(0);
  }

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
  }

  flags = NI_NUMERICHOST;
  for (struct addrinfo* p = listp; p; p = p->ai_next) {
    getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
    printf("%s\n", buf);
  }

  Freeaddrinfo(listp);

  return 0;
}
