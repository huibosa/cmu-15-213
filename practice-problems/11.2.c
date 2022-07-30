#include <arpa/inet.h>
#include <csapp.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  struct in_addr inaddr;
  uint32_t addr;
  char buf[MAXBUF];

  if (argc != 2) {
    fprintf(stderr, "usage: %s <hex number>\n", argv[0]);
    exit(0);
  }

  // sscanf(argv[1], "%x", &addr);
  addr = (uint32_t)strtoul(argv[1], NULL, 16);
  inaddr.s_addr = htonl(addr);

  if (!inet_ntop(AF_INET, &inaddr, buf, MAXBUF)) {
    unix_error("inet_ntop");
  }

  printf("%s\n", buf);

  return 0;
}
