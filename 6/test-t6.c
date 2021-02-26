#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "t6.h"

#define NMAX 30
#define M 5

int valores[M]= { 2, 5, 10, 20, NMAX };

static int turno;
static int desordenado;
static int funciona= 1;
static int ocupado= 0;

static void init() {
  turno= 0;
  desordenado= 0;
}

static void *th_fun(void *ptr) {
  int *pturno= ptr;
  printf("Thread %d solicita recurso\n", *pturno);
  ocupar();
  if (ocupado) {
    fprintf(stderr, "No se respeto exclusion mutua al ocupar el recurso\n");
    exit(1);
  }
  ocupado= 1;
  if (turno!=*pturno) {
    funciona= 0;
    desordenado= 1;
  }
  turno++;
  printf("Thread %d obtiene recurso\n", *pturno);
  ocupado= 0;
  desocupar();
  return NULL;
}

static pthread_t tasks[NMAX];
static int turnos[NMAX];

int main() {
  for (int k=0; k<M; k++) {
    init();
    int n= valores[k];
    printf("\n----------------------------------------\n");
    printf("Iniciando: thread principal obtiene el recurso\n");
    printf("%d threads solicitaran el recurso\n", n);
    ocupar();
  
    for (int i= 0; i<n; i++) {
      turnos[i]= i;
      sleep(1);
      pthread_create(&tasks[i], NULL, th_fun, &turnos[i]);
    }
  
    printf("\n<<< Thread principal desocupa el recurso >>>\n\n");
    desocupar();
  
    for (int i= 0; i<n; i++)
      pthread_join(tasks[i], NULL);
  
    if (desordenado)
      fprintf(stderr, "Los threads no respetaron orden de llegada\n");
    else
      printf("Bien.  Se respeto orden de llegada.\n");
  }

  if (funciona) {
    printf("Felicitaciones: su tarea funciona.  Los threads\n");
    printf("siempre fueron atendidos por orden de llegada.\n");
    return 0;
  }
  else {
    fprintf(stderr, "Lo siento.  Su tarea no funciona.\n");
    fprintf(stderr, "No respeta orden de llegada.\n");
    return 1;
  }
}
