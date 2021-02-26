#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/wait.h>
#include<setjmp.h>

#include "viajante.h"

//Nótese que la siguiente implementación puede generar un resultado incorrecto. Lo anterior es debido a que primero se calcula la distancia, se verifica si es menor que la distancia actual y luego se actualiza la ruta asociada a la distancia mínima. Al utilizar una metodología que marca un punto de retorno en el inicio a través de setjmp, cuando se quiere volver al punto de inicio a través de longjmp, puede existir el caso en que se actualizó la distancia mínima y, justo al momento de actualizar la ruta asociada a la nueva distancia mínima, se activó la rutina de atención y se saltó al punto de retorno sin actualizar la ruta asociada a la nueva distancia mínima (o actualizando solo una parte de la ruta). De esa forma, en esos casos, el programa entrega una distancia mínima con una ruta no correspondiente.
jmp_buf excp;
void ring(){
    longjmp(excp,1);
}


double viajante(int z[], int n, double **m, int nperm) {
  double min= DBL_MAX; // la distancia mas corta hasta el momento
  void (*hdlr)() = signal(SIGINT,ring);
  if(setjmp(excp)==0){
      for (int i= 1; i<=nperm; i++) {
        int x[n+1];          // almacenara una ruta aleatoria
        gen_ruta_alea(x, n); // genera ruta x[0]=0, x[1], x[2], ..., x[n], x[0]=0
        // calcula la distancia al recorrer 0, x[1], ..., x[n], 0
        double d= dist(x, n, m);
        if (d<min) {    // si distancia es menor a la mas corta hasta el momento
          min= d;       // d es la nueva distancia mas corta
          for (int j= 0; j<=n; j++)
            z[j]= x[j]; // guarda ruta mas corta en parametro z
      } }}
  else{
  }

  signal(SIGINT, hdlr);
  return min;
}
