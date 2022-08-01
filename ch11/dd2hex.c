#include <arpa/inet.h>
#include <csapp.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  struct in_addr inaddr;
  int rc;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <ip address>\n", argv[0]);
    exit(0);
  }

  rc = inet_pton(AF_INET, argv[1], &inaddr);
  if (rc == 0) {
    app_error("inet_pton error: invalid dotted decimal address");
  }
  else if (rc < 0){
    unix_error("inet_pton error");
  }

  printf("0x%x\n", ntohl(inaddr.s_addr));

  return 0;
}
