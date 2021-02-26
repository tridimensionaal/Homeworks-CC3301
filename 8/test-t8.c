#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "viajante.h"

// ----------------------------------------------------
// Generacion de n ciudades aleatorias en un cuadrado de 1 x 1
// Las ciudades estan en un desierto, de modo que siempre hay un
// camino en linea recta desde una ciudad a otra.

static double **repartir_ciudades(int n) {
  double x[n+1], y[n+1];
  for (int i= 0; i<=n; i++) {
    x[i] = random() / ((double)RAND_MAX+1);
    y[i] = random() / ((double)RAND_MAX+1);
  }

  double **m= malloc((n+1)*sizeof(double*));
  for (int i= 0; i<=n; i++) {
    m[i]= malloc((n+1)*sizeof(double));
    for (int j= 0; j<=n; j++) {
      double dx= x[i]-x[j];
      double dy= y[i]-y[j];
      m[i][j]= sqrt(dx*dx+dy*dy);
    }
  }

  return m;
}

static void liberar_ciudades(double **m, int n) {
  for (int i= 0; i<=n; i++)
    free(m[i]);
  free(m);
}

// ----------------------------------------------------
// Version secuencial de viajante

double dist(int z[], int n, double **m) {
  double d= m[z[n]][0];    // distancia de z[n] a 0
  for (int i=0; i<n; i++) {
      d += m[z[i]][z[i+1]];
  }
  return d;
}

static void printRuta(int z[], int n) {
  for(int i=0; i<=n; i++) {
    printf("%d ", z[i]);
  }
  printf("0\n");
}

void gen_ruta_alea(int x[], int n) {
  x[0]= 0;
  for (int i= 1; i<=n; i++) {
    x[i]= i;
  }
  for (int i= 1; i<n; i++) { // para el caso i==n, intercambiaria x[n] y x[n]
    int r= random()%(n-i+1)+i; // elige intercambiar x[i] con x[r]
    int tmp= x[i];
    x[i]= x[r];
    x[r]= tmp;
  }
}

int main() {
  double **m6= repartir_ciudades(5);
  double **m33= repartir_ciudades(32);

  printf("Test 1: ejemplo con solo 6 ciudades\n");
  {
#ifndef VALGRIND
    int k= 50000000;
#else
    int k= 800000;
#endif
    int n= 5;
    double ref= 2.113459;
    double **m= m6;
    int z[n+1];
    srandom(1000000);
    printf("Calculando secuencialmente\n");
    double best= viajante(z, n, m, k);
    printf("Resultado final: nperm=%d distancia minima=%f\n", k, best);
    printf("Ruta: ");
    printRuta(z, n);
    if (fabs(dist(z, n, m)-best)>0.00000000001) {
      fprintf(stderr, "La distancia entregada es incorrecta para esa ruta\n");
      exit(1);
    }
    if (fabs(best-ref)>0.000001) {
      fprintf(stderr, "Resultado insuficiente, debió ser %f\n", ref);
      exit(1);
    }
    printf("Test 1 aprobado\n");
    printf("--------------------------------------------------\n");
    liberar_ciudades(m, n);
  }

  printf("Test 2: Un ejemplo grande con 33 ciudades\n");
  {
#ifndef VALGRIND
    int k= 10000000;
#else
    int k= 1000000;
#endif
    int n= 32;
    double ref= 10.8;
    double **m= m33;
    int z[n+1];
    srandom(1000000);
    printf("Calculando secuencialmente\n");
    double best= viajante(z, n, m, k);
    printf("Resultado final: nperm=%d distancia minima=%f\n", k, best);
    printf("Ruta: ");
    printRuta(z, n); 
    if (fabs(dist(z, n, m)-best)>0.00000000000001) {
      fprintf(stderr, "La distancia entregada es incorrecta para esa ruta\n");
      exit(1);
    }
    if (best>ref) {
      fprintf(stderr, "Resultado insuficiente, debio ser menor que %f\n", ref);
      exit(1);
    }
    printf("Test 2 aprobado\n");
    liberar_ciudades(m, n);
  }

  return 0;
}
