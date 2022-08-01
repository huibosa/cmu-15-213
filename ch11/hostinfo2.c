#include <csapp.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
  struct addrinfo *listp, hints;
  char buf[MAXLINE];
  struct sockaddr_in* sockp;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
  }

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  Getaddrinfo(argv[1], NULL, &hints, &listp);

  for (struct addrinfo* p = listp; p; p = p->ai_next) {
    sockp = (struct sockaddr_in*)p->ai_addr;
    Inet_ntop(AF_INET, &sockp->sin_addr, buf, MAXLINE);
    printf("%s\n", buf);
  }

  return 0;
}
