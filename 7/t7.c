#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>


#include "viajante.h"

int leer(int fd, void *vbuf, int n) {
  char *buf= vbuf;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf+= rc; /* avanzamos el buffer para no reescribir lo leido previamente */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}

double viajante_par(int z[], int n, double **m, int nperm, int p) {
    int pids[p];
    double min[p];
    int min_rut[p][n+1];

    int steps = nperm/p;

    for (int i = 0; i < p; i++){
        int fds[2];
        pipe(fds);

        init_rand_seed(random());

        if ((pids[i] = fork())==0){
            close(fds[0]);
            double min_hijo = viajante(z,n, m, steps);
            write(fds[1], &min_hijo, sizeof(double));
            write(fds[1], z, (n+1)*sizeof(int));
            exit(0);
                    
        }
        else{
            close(fds[1]);
            min[i] = fds[0];
            for (int j = 0; j <= n; j++){
                min_rut[i][j] = fds[0];
            }
        }
    }

    double real_min = DBL_MAX;

    for (int i = 0; i < p; i++){
        double actual_min;
        int actual_rut[n+1];
        leer(min[i], &actual_min, sizeof(double));

        for (int j = 0; j <= n; j++){
            leer(min_rut[i][j], &actual_rut[j], sizeof(int));
        }

        waitpid(pids[i], NULL,0);

        close(min[i]);
        for (int j = 0; j <= n; j++){
            close(min_rut[i][j]);
        }

        if (actual_min < real_min){
            real_min = actual_min;

            for (int j = 0; j <= n; j++){
                z[j] = actual_rut[j];
            }
        }
    }

    return real_min;
}
