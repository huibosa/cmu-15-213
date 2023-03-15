#include <csapp.h>

int readcnt;     // Initially = 0
sem_t mutex, w;  // Both Initially = 1

void reader(void) {
  for (;;) {
    P(&mutex);
    readcnt++;
    if (readcnt == 1) {  // First in
      P(&w);
    }
    V(&mutex);

    // Critical section
    // Reading happens

    P(&mutex);
    readcnt--;
    if (readcnt == 0) {  // Last out
      V(&w);
    }
    V(&mutex);
  }
}

void writer(void) {
  for (;;) {
    P(&w);

    // Critical section
    // Reading happens

    V(&w);
  }
}
