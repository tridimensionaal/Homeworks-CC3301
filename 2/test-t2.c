#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "t2.h"

#ifdef VALGRIND
#define NITER 1
#else
#define NITER 5000000
#endif

// ----------------------------------------------------
// Funcion que entrega el tiempo transcurrido desde el lanzamiento del
// programa en milisegundos

static int time0= 0;

static int getTime0() {
    struct timeval Timeval;
    gettimeofday(&Timeval, NULL);
    return Timeval.tv_sec*1000+Timeval.tv_usec/1000;
}

static void resetTime() {
  time0= getTime0();
}

static int getTime() {
  return getTime0()-time0;
}

// ----------------------------------------------------
// Revisar: verifica que un string es un valor especifico

void revisar(char *s, char *valor) {
  if (strcmp(s, valor)!=0) {
    fprintf(stderr, "El string debio ser \"%s\", no \"%s\"\n", valor, s);
    exit(1);
  }
}

void revisar_reducir(char *s, char *res) {
  int len= strlen(s);
  char a[len+1000+1];
  for (int i= 0; i<500; i++)
    a[i]= ~((i+34)%256);
  strcpy(&a[500], s);
  for (int i= 0; i<500; i++)
    a[500+i+len+1]= ~((i+34)%256);
  reducir(&a[500]);
  revisar(&a[500], res);
  for (int i= 0; i<500; i++) {
    if (a[i]!= (char)~((i+34)%256)) {
      fprintf(stderr, "reducir escribio fuera del string\n");
      exit(1);
    }
  }
  for (int i= 0; i<500; i++) {
    if (a[500+i+len+1]!= (char)~((i+34)%256)) {
      fprintf(stderr, "reducir escribio fuera del string\n");
      exit(1);
    }
  }
}

void revisar_reduccion(char *s, char *res) {
  char *red= reduccion(s);
  revisar(red, res);
  free(red);
}

void revisar_serie(void (*fun)(char *s, char *res)) {
    (*fun)("", "");
    (*fun)(" ", " ");
    (*fun)("  ", " ");
    (*fun)("         ", " ");
    (*fun)("a", "a");
    (*fun)("palabra", "palabra");
    (*fun)("     palabra    ", " palabra ");
    (*fun)("palabra    ", "palabra ");
    (*fun)("     palabra", " palabra");
    (*fun)("hola    que   tal", "hola que tal");
    (*fun)("    hola    que   tal    ", " hola que tal ");
}

void bench_reducir(char *s) {
  char a[strlen(s)+1];
  strcpy(a, s);
  reducir(a);
}

void bench_reduccion(char *s) {
  char *res= reduccion(s);
  free(res);
}

char *reduccion_trivial(char *s) {
  char a[strlen(s)+1];
  strcpy(a, s);
  reducir(a);
  char *res= malloc(strlen(a)+1);
  strcpy(res, a);
  return res;
}

void bench_reduccion_trivial(char *s) {
  char *res= reduccion_trivial(s);
  free(res);
}

void bench_serie(void (*fun)(char *s)) {
    (*fun)("");
    (*fun)(" ");
    (*fun)("  ");
    (*fun)("         ");
    (*fun)("a");
    (*fun)("palabra");
    (*fun)("     palabra    ");
    (*fun)("palabra    ");
    (*fun)("     palabra");
    (*fun)("hola    que   tal");
    (*fun)("    hola    que   tal    ");
}

int main() {
  printf("Prueba de la parte a\n");

  {
    printf("Test 1: string vacio\n");
    char s[]= "";
    reducir(s);
    revisar(s, "");
    printf("Aprobado\n");
  }

  {
    printf("Test del enunciado\n");
    char s[]= "hola    que   tal";
    reducir(s);  // elimina espacios de "hola que tal"
    revisar(s, "hola que tal"); // No debe tocar "123"
    printf("Aprobado\n");
  }

  {
    printf("Test de una variacion del enunciado\n");
    char s[]= "    hola    que   tal  ";
    reducir(s);  // elimina espacios de "hola que tal"
    revisar(s, " hola que tal "); // No debe tocar "123"
    printf("Aprobado\n");
  }

  {
    printf("Tests adicionales\n");
    revisar_serie(revisar_reducir);
    printf("Aprobado\n");
  }

  printf("Prueba de la parte b\n");

  revisar_serie(revisar_reduccion);

  printf("Aprobado\n");
    
  printf("Benchmark de la parte a\n");

  resetTime();
  for (int k=0; k<NITER; k++)
    bench_serie(bench_reducir);
  int time_reducir= getTime();
  printf("Tiempo para reducir: %d\n", time_reducir);

  printf("Benchmark de la parte b\n");

  resetTime();
  for (int k=0; k<NITER; k++)
    bench_serie(bench_reduccion);
  int time_reduccion= getTime();
  printf("Tiempo para reduccion: %d\n", time_reduccion);

#ifndef VALGRIND
  if (time_reduccion*90/100<time_reducir) {
    fprintf(stderr, "%s\n",
       "El tiempo de deducir no es el 90% del tiempo de reduccion");
    exit(1);
  }
#endif

  printf("Benchmark de la parte b implementada a partir de la parte a\n");

  resetTime();
  for (int k=0; k<NITER; k++)
    bench_serie(bench_reduccion_trivial);
  int time_reduccion_trivial= getTime();
  printf("Tiempo para reduccion: %d\n", time_reduccion_trivial);

#ifndef VALGRIND
  if (time_reduccion_trivial*90/100<time_reduccion) {
    fprintf(stderr, "%s\n",
       "El tiempo de reduccion no es el 90% del tiempo de reduccion trivial");
    exit(1);
  }
#endif

  printf("Felicitaciones: Aprobo todos los tests\n");
  return 0;
}
