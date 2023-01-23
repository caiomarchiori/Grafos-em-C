#include <stdio.h>
#include <stdlib.h>

//Problema 2: Estradas Escuras

/*--- FUNCOES AUXILIARES PARA A IMPLEMENTACAO DO ALGORITIMO DE KRUSKAL ----*/

int compare(const void *p1,const void *p2){
    const int (*x)[2] = p1;
    const int (*y)[2] = p2;

    /*  ordenado baseado nos pesos das arestas
        retorno <0 O elemento apontado por p1 vem antes do elemento apontado por p2
        retorno =0 O elemento apontado por p1 é equivalente ao elemento apontado por p2
        retorno >0 O elemento apontado por p1 vai depois do elemento apontado por p2*/

    return (*x)[2]-(*y)[2];
}

/*Union by Rank (Uniao por Ordenacao): pendurar a arvore de menor altura na ́arvore de maior altura
Cada no so precisa saber quem  ́e o seu pai e o seu rank, assim utiliza-se 2 vetores
Baseado nos slides do prof Jurair Rosa*/

void makeSet(int parent[],int rank[],int num_vertex){   // criar conjuntos para os vertices do grafo
    for(int i=0;i<num_vertex;i++){
        parent[i] = i;
        rank[i] = 0;
    }
}

int findSet(int parent[],int key){   // encontrar o representante do conjunto no qual o vertice faz parte
    while(key != parent[key]){
        key = parent[key];
    }
    return key;
}

void Union(int x,int y,int parent[],int rank[]){ // juncao de dois conjuntos (arvore de x aponta para arvore de y)
    int rx = findSet(parent,x);
    int ry = findSet(parent,y);

    if(rx == ry)
        return;

    if(rank[rx] > rank[ry])
        parent[ry] = rx;

    else{
        parent[rx] = ry;
        if(rank[rx] == rank[ry])
            rank[ry] = rank[ry] + 1;    // aumenta o rank, pendurou a de menor rank como filha da de maior rank
    }
}

/*funcao baseada nos slides da prof Laura Assis*/
void Kruskal(int num_vertex,int num_edges,int graph[num_edges][3]){

    qsort(graph,num_edges,sizeof(graph[0]),compare);    // qsort organiza o grafo de forma crescente, pode-se acessar os menores pesos/distancias

    int parent[num_vertex];
    int rank[num_vertex];

    makeSet(parent,rank,num_vertex);    // inicializar o vetor de pai e de rank

    int minCost = 0;    // peso da MST
    int tot = 0;    // peso original do grafo
    int p1,p2,wt;

    for(int i=0;i<num_edges;i++){
        p1 = findSet(parent,graph[i][0]);
        p2 = findSet(parent,graph[i][1]);
        wt = graph[i][2];

        tot = tot + wt;

        if(p1 != p2){   // representantes diferentes, devemos uni-los
            Union(p1,p2,parent,rank);
            minCost += wt;  // calcula-se o peso da MST

            printf("%d->%d = %d$\n",graph[i][0],graph[i][1],wt);
        }
    }

    printf("\nValor inicial %d$\n",tot);

    printf("\nCusto minimo: %d$\n",minCost);

    printf("\nQuantidade maxima diaria de dolares economizado: %d$\n\n",tot-minCost);

    //printf("%d\n",tot-minCost); // calculo para descobrir quanto foi economizado
}

int main(){

    int m,n;    // nemero de juncoes (vertices)e o numero de estradas (arestas) em Byteland

    while(1){

        printf("Insira o numero de juncoes e o numero de estradas em Byteland: ");
        scanf("%d %d", &m, &n);

        if(m != 0 && n != 0){
            int graph[n][3];    // representando o grafo por matriz de adjacencia de n (arestas) x 3 (origem,destino e peso)

            printf("\nInsira a estrada bidirecional e sua distancia (v1,v2,peso):\n");

            for(int i=0;i<n;i++){
                scanf("%d",&graph[i][0]);
                scanf("%d",&graph[i][1]);
                scanf("%d",&graph[i][2]);
            }
            printf("\nIluminacao das estradas: \n\n");
            Kruskal(m,n,graph);
        }

        else
            break;
    }

    return 0;

}
