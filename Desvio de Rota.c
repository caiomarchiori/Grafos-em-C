#include <stdio.h>
#include <stdlib.h>
#define INF 999999999
#define VERTEX 251

// Problema 4: Desvio de Rota

/*------- ESTRUTURA DA FILA DE PRIRIDADE E SUAS RESPCTIVAS FUNCOES UTILIZADAS PELO ALGORITMO DE DIJKSTRA ---------*/

struct queue{
    int max_size;    // capacidade máxima
    int size;   // capacidade atual da fila
    int front;  // aponta para o 1 elemento da fila
    int rear;   //  aponta para o último elemento da fila
    int *items; // array para armazenar elementos da fila
};

struct queue* newQueue(int size){   // inicializar a fila
    struct queue *q = NULL; // evitar lixo
    q = (struct queue*)malloc(sizeof(struct queue));
    q->items = (int*)malloc(size * sizeof(int));
    q->max_size = size;
    q->front = 0;
    q->rear = -1;
    q->size = 0;

    return q;
}

int size(struct queue *q){ // retornar o tamanho atual da fila
    return q->size;
}

int isEmpty(struct queue *q){   // verificar se a fila esta vazia
    return !size(q);
}

int front(struct queue *q){    // retorna o 1 elemento da fila
    if(isEmpty(q))
        return;
    return q->items[q->front];
}

void enqueue(struct queue *q, int key){ // inserir elemento ao final da fila (rear)
    if(size(q) == q->max_size)
        return;

    q->rear = (q->rear + 1) % q->max_size;  // comportamento circular
    q->items[q->rear] = key;
    q->size++;
}

void dequeue(struct queue *q){  // retirar elemento do comeco da fila (front)
    if(isEmpty(q))
        return;

    q->front = (q->front + 1) % q->max_size;
    q->size--;

}

/*------- ALGORITMO DE DIJKSTRA ---------*/
// Baseado nos slides do prof Laura Assis

int n,m,c,k;// QUANTIDADE DE VERTICES NO GRAFO (CIDADES)
            // '' ARESTAS (ESTRADAS)
            // '' CIDADES NA ROTA DE SERVICO
            // CIDADE QUE O VEICULO FOI CONSERTADO

int graph[VERTEX][VERTEX];  // representacao do grafo por matriz de adjacencia
int dist[VERTEX];   //vetor de distancia

void Initialize_Single_Source(){    // inicializar o grafo e o vetor como infinito
	for(int i=0;i<=n;i++){
		dist[i] = INF;
		for(int j=0;j<=n;j++)
            graph[i][j] = INF;
	}
}

int Dijkstra(int source, int destiny){
    struct queue *q = newQueue(VERTEX); // criacao da fila de prioridades (predecessor)
	dist[source] = 0;   // distancia 0 porque e o proprio vertice
	enqueue(q,source);
	while(!isEmpty(q)){
		int p = front(q);   // elemento de maior prioridade
		dequeue(q);
		for(int i=0;i<n;i++){
			if(graph[p][i] != INF && dist[i] > dist[p] + graph[p][i]){  // relaxar as arestas do grafo (alteras as estimativas de caminhos mais curtos e predecessores)
				dist[i] = dist[p] + graph[p][i];    // menor distancia
				enqueue(q,i);
			}
		}
	}
	return dist[destiny];
}

int main(){

	while(1){

        // QUANTIDADE DE VERTICES (CIDADES) NO GRAFO (n)
        // '' ARESTAS (ESTRADAS)(m)
        // '' CIDADES NA ROTA DE SERVICO(c)
        // CIDADE QUE O VEICULO FOI CONSERTADO(k)

        scanf("%d %d %d %d", &n, &m, &c, &k);

        if(n != 0 && m != 0 && c != 0 && k != 0){

            Initialize_Single_Source(); // inicializar

            int u, v, p;    // cidades u e v com custo de pedagio p

            for(int i=1; i<=m; i++){

                scanf("%d %d %d", &u, &v, &p);

                if(u >= c && v >= c){   // se as duas cidades estiverem fora da rota

                    // adiciona a estrada normalmente
                    graph[u][v] = p;
                    graph[v][u] = p;
                }

                if(u >= c && v < c) // se v pertencer à rota
                    graph[u][v] = p;    // adiciona apenas a estrada que chega em v

                if(u < c && v >= c) // se u pertencer à rota
                    graph[v][u] = p;    // adiciona apenas a estrada que chega em u


                if(u < c && v < c && abs(u-v) == 1){    // se as duas cidades forem cidades consecutivas da rota
                    // adiciono a estrada normalmente
                    graph[u][v] = p;
                    graph[v][u] = p;
                }
            }

            printf("%d\n", Dijkstra(k, c-1));   // valor do menor caminho
        }

        else
            break;
    }

    return 0;
}
