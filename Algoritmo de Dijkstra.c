#include <stdio.h>
#include <stdlib.h>
#define INF 999999999
#define VERTEX 251

/*------- ESTRUTURA DA FILA ---------*/

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

int n,m;// QUANTIDADE DE VERTICES NO GRAFO
        // '' ARESTAS

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
    struct queue *q = newQueue(VERTEX);
	dist[source] = 0;   // distancia 0 porque e o proprio vertice
	enqueue(q,source);
	while(!isEmpty(q)){
		int p = front(q);
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
