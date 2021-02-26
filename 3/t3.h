typedef struct nodo {
  int id, hash;
  struct nodo *izq, *der;
} Nodo;

void desbalancear(Nodo **pa, Nodo **pult);
Nodo *desbalanceado(Nodo *a, Nodo **pult);


