#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "maleta.h"

typedef struct {
    int n;
    int k;
    double maxW;
    int* z;
    double* v;
    double* w;
    double best;

} Args;

void *thread_function(void *params){
    Args *p = (Args *) params;
    int n = p->n;
    int k = p -> k;
    double maxW = p->maxW;
    int* z = p->z;
    double*v = p->v;
    double*w = p->w;
    p->best = llenarMaletaSec(w,v,z,n,maxW,k);
    return NULL;
}


double llenarMaletaPar(double w[], double v[], int z[], int n, double maxW, int k){
    pthread_t t[8];
    Args args[8];
    double best = 0;
    int kk = k/8;
    int size = sizeof(int);
    
    for(int i = 0; i < 8; i++){
        args[i].n = n;
        args[i].k = kk;
        args[i].maxW = maxW;
        args[i].v = v;
        args[i].w = w;
        int *zz = malloc(n*size);
        args[i].z = zz;
        args[i].best = 0;
        pthread_create(&t[i], NULL, thread_function, &args[i]);
    }

    int ii = 0;
    for(int i = 0; i < 8; i++){
        pthread_join(t[i],NULL);
        if(i==0){
            best = args[i].best;
        }
        else{
            if (args[i].best < best){
                best = args[i].best;
                ii = i;
            }
        }
    }

    for(int i = 0; i < n; i++){
        z[i] = args[ii].z[i];
    }
    for (int i = 0; i < 8; i++){
        free(args[i].z);
    }
    return best;
}

