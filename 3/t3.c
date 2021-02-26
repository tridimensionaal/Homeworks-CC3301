#include<stdlib.h>
#include "t3.h"

void desbalancear(Nodo **pa, Nodo **pult){
    if(*pa==NULL){
        *pult = NULL;
        return;
    }

    Nodo* I = (*pa) -> izq;
    Nodo* UI;
    desbalancear(&I, &UI);
    

    Nodo* D = (*pa) -> der;
    Nodo* UD;
    desbalancear(&D, &UD);

    (*pa) -> izq = NULL;

    if(D==NULL){
        *pult = *pa;
    }
    else{
        (*pa)->der = D;
        *pult = UD;
    }

 
    if(I==NULL){
    }
    else{
        UI -> der = *pa;
        *pa = I;
    }
 
    return;
}

Nodo *desbalanceado(Nodo *a, Nodo **pult){
    if(a==NULL){
        *pult = NULL;
        return NULL;
    }

    Nodo* I = a -> izq;
    Nodo* UI;
    Nodo* nodo_i = desbalanceado(I, &UI);

    Nodo* D = a -> der;
    Nodo* UD;
    Nodo* nodo_d = desbalanceado(D, &UD);

    Nodo* nodo = (Nodo*) malloc(sizeof(Nodo));
    nodo -> hash = (a -> hash);
    nodo -> id = (a -> id);
    nodo -> izq = NULL;
    nodo -> der = nodo_d;

    if(nodo_d == NULL){
        *pult = nodo;
    }
    else{
        *pult = UD;
    }

    if(nodo_i == NULL){
        return nodo;
   }
    else{
        (UI->der) = nodo;
        return nodo_i;
    }
}

