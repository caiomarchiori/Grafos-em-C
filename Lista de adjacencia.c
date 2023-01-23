#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct no{
  int vertice;
  struct no* prox;
};

struct grafo{
  int numVertices;
  struct no** adjlista;
  int* cor;
};

struct no * cria_no(int vertice){
  struct no* novo_no = malloc(sizeof(struct no));
  novo_no->vertice = vertice;
  novo_no->prox = NULL;
  return novo_no;
}

struct grafo * cria_grafo(int vertices){
  struct grafo* grafo = malloc(sizeof(struct grafo));
  grafo->numVertices = vertices;

  grafo->adjlista = malloc(vertices * sizeof(struct no*));
  grafo->cor = malloc(vertices * sizeof(int));

  for(int i = 0; i < vertices; i++){
    grafo->adjlista[i] = NULL;
    grafo->cor[i] = 0;
  }
  return grafo;
}

void cria_aresta(struct grafo* grafo, int vi, int vf) {
  // Adiciona aresta de vi para vf
  struct no* novo_no = cria_no(vf);
  novo_no->prox = grafo->adjlista[vi];
  grafo->adjlista[vi] = novo_no;

  // Adiciona aresta de vf para vi
  novo_no = cria_no(vi);
  novo_no->prox = grafo->adjlista[vf];
  grafo->adjlista[vf] = novo_no;
}


/*------ LISTA DE ADJACENCIA ---------------*/

void adjlist(struct grafo* grafo){
  for(int v = 0; v < grafo->numVertices; v++){
    struct no* temp = grafo->adjlista[v];
    printf("\nVertice %d: ", v);
    while (temp){
      printf("%d -> ", temp->vertice);
      temp = temp->prox;
      if(temp == NULL)
        puts("NULL");
    }
  }
}

int main(){

    struct grafo* grafo = cria_grafo(4);
    cria_aresta(grafo, 0, 1);
    cria_aresta(grafo, 0, 2);
    cria_aresta(grafo, 1, 2);
    cria_aresta(grafo, 2, 3);

    adjlist(grafo);
}
