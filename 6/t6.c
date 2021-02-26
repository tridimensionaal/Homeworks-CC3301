#include <pthread.h>

#include "t6.h"

// *** Esta implementacion no funciona porque no respeta orden de llegada ***

pthread_mutex_t m= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int visor = 0;
int num = 0;

void ocupar() {
  pthread_mutex_lock(&m);
  int mi_num = visor;
  while(mi_num != num){
      pthread_cond_wait(&cond,&m);
  }
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&m);
}

void desocupar() {
  pthread_mutex_lock(&m);
  visor++;
  num++;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&m);
}
