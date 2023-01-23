#include <stdio.h>
#include <stdlib.h>
#define TAM 40

/*------ ESTRUTURA DO GRAFO ---------------*/


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


/*------ ALGORITIMO BFS ---------------*/


struct fila{
  int vertices[TAM];
  int frente;
  int retaguarda;
};

struct fila * cria_fila() {
  struct fila* f = malloc(sizeof(struct fila));
  f->frente = -1;
  f->retaguarda = -1;
  return f;
}

int vazia(struct fila * f) {
  if (f->retaguarda == -1)
    return 1;
  else
    return 0;
}

void enfila(struct fila* f, int valor) {
  if (f->retaguarda == TAM - 1)
    printf("\nfila esta cheia!!");
  else {
    if (f->frente == -1)
      f->frente = 0;
    f->retaguarda++;
    f->vertices[f->retaguarda] = valor;
  }
}

int desenfila(struct fila* f) {
  int item;
  if(vazia(f)) {
    printf("fila esta vazia");
    item = -1;
  }
  else{
    item = f->vertices[f->frente];
    f->frente++;
    if(f->frente > f->retaguarda)
      f->frente = f->retaguarda = -1;
  }
  return item;
}

void printfila(struct fila* f) {
  int i = f->frente;
  if(vazia(f)){
    printf("fila esta vazia");
  }
  else{
    printf("\nfila contem: ");
    for (i = f->frente; i < f->retaguarda + 1; i++) {
      printf("%d ",f->vertices[i]);
    }
  }
}

void bfs(struct grafo* grafo, int vertive_inical,int vertices){
  printf("----- BFS -----\n");
  struct fila* q = cria_fila();
  grafo->cor[vertive_inical] = 1;

  enfila(q,vertive_inical);

  while(!vazia(q)){
    printfila(q);
    int vertice_atual = desenfila(q);
    printf("\nvisito: %d\n",vertice_atual);

    struct no* temp = grafo->adjlista[vertice_atual];

    while(temp){
      int verticeadj = temp->vertice;
      if(grafo->cor[verticeadj] == 0){
        grafo->cor[verticeadj] = 1;
        enfila(q,verticeadj);
      }
      temp = temp->prox;
    }
  }

}

int main(){

    struct grafo* grafo = cria_grafo(4);
    cria_aresta(grafo, 0, 1);
    cria_aresta(grafo, 0, 2);
    cria_aresta(grafo, 1, 2);
    cria_aresta(grafo, 2, 3);

    bfs(grafo, 0 , 4);
}
