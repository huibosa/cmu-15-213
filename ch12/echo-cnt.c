#include <csapp.h>

static int byte_cnt;  // Byte counter
static sem_t mutex;   // Mutex protects byte counter

static void init_echo_cnt(void) {
  Sem_init(&mutex, 0, 1);
  byte_cnt = 0;
}

void echo_cnt(int connfd) {
  int n;
  rio_t rio;
  char buf[MAXLINE];
  static pthread_once_t once = PTHREAD_ONCE_INIT;

  Pthread_once(&once, init_echo_cnt);
  Rio_readinitb(&rio, connfd);
  while ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0) {
    P(&mutex);
    byte_cnt += n;
    printf("server received %d (%d total) bytes on fd %d\n", n, byte_cnt, connfd);
    V(&mutex);
    Rio_writen(connfd, buf, MAXLINE);
  }
}
