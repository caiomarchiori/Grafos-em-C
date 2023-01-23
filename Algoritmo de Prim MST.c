#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define VERTICE 5

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

/*------ ALGORITIMOS DE PRIM ---------------*/

int minimo(int key[], int mstSet[]) {   // achar o vertice com a menor chave
    int min = INT_MAX, min_index; // inicializar o valor minimo e sua posicao
    for(int i = 0; i < VERTICE; i++){ // percorrendo os vertices
        if(mstSet[i] == 0 && key[i] < min){ // se o vertice nao esta presente na arvore e se a chave nessa posicao for menor
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}

int MST(int parent[], int n, int grafo[VERTICE][VERTICE]) {    // printar a construcao da AGM, guardada no vetor de pais
    int tot = 0;
    printf("Aresta   Peso\n");
    for (int i = 1; i < VERTICE; i++){
        printf("%d - %d    %d \n", parent[i], i, grafo[i][parent[i]]);
        tot = tot + grafo[i][parent[i]];
    }
    printf("\nCusto da MST: %d\n",tot);

}

void Prin(int grafo[VERTICE][VERTICE]) {// construit a AGM e printa o resultado final
    printf("----- PRIM -----\n\n");
    int parent[VERTICE]; // guardar a AGM
    int key[VERTICE]; // valor do peso minimo da aresta em analisa
    int mstSet[VERTICE]; // Conjunto de vertices que nao esta na AGM ainda

    for (int i = 0; i < VERTICE; i++){ // Inicializar todas as chaves como infinito
        key[i] = INT_MAX;
        mstSet[i] = 0; // uso para verificar a presenca na arvore
    }

    key[0] = 0; // primeiro vertice
    parent[0] = -1; // raiz da AGM

    for (int i = 0; i < VERTICE - 1; i++) {
        int min = minimo(key, mstSet);// posicao da menor chave do conjunto de vertices nao incluidos na arvore
        mstSet[min] = 1; // adiciono o vertice selecionado no conjunto de vertices presente na AGM

        // grafo na posicao[minimo][v] "existe" na lista de adjacencia
        // se o vertice analisado ainda nao esta na arvore
        // se o elemento dessa posicao for menor que a chave

        for (int v = 0; v < VERTICE; v++){
            if (grafo[min][v] && mstSet[v] == 0 && grafo[min][v] < key[v]){
                parent[v] = min;
                key[v] = grafo[min][v];
            }
        }
    }

    MST(parent, VERTICE, grafo);
}

int main(){

    int grafo[VERTICE][VERTICE] = { { 0, 2, 0, 6, 0 }, { 2, 0, 3, 8, 5 },
            { 0, 3, 0, 0, 7 }, { 6, 8, 0, 0, 9 }, { 0, 5, 7, 9, 0 }, };

    Prin(grafo);

    return 0;
}
