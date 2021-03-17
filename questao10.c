#include <stdio.h>
#include <stdlib.h>

#define V 5
#define INICIO 99999

void dijkstra(int graph[V][V], int source, int n);
void inicializaV(int graph[V][V], int custo [V][V], int n);
void distVis(int custo[V][V], int dist[V], int visit[V], int next[V], int source, int cont, int n);
void arestas(int custo[V][V], int dist[V], int visit[V], int next[V], int cont, int n);

int main()
{

    /* Criando o grafo relacionado ao exercicio */
    int graph[V][V] = {
        {0, 2, 0, 5, 0},
        {0, 0, 3, 4, 0},
        {7, 0, 0, 0, 0},
        {0, 0, 0, 0, 6},
        {4, 0, 0, 0, 0}};

    // executa a função de dijkstra
    dijkstra(graph, V, 0);

    return 0;
}

void inicializaV(int graph[V][V], int custo[V][V], int n){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if (graph[i][j] == 0)
                custo[i][j] = INICIO;
            else
                custo[i][j] = graph[i][j];
        }
    }
}

void distVis(int custo[V][V], int dist[V], int visit[V], int next[V], int source, int cont, int n){
    int i;
    for (i = 0; i < n; i++)
    {
        dist[i] = custo[source][i];
        next[i] = source;
        visit[i] = 0;
    }

    dist[source] = 0;
    visit[source] = 1;
    cont = 1;
}

void arestas(int custo[V][V], int dist[V], int visit[V], int next[V], int cont, int n){
    int i, prox, distmin;
    while (cont < n - 1){
        distmin = INICIO;
        for (i = 0; i < n; i++){
            if (dist[i] < distmin && !visit[i]){
                distmin = dist[i];
                prox = i;
            }
        }

        visit[prox] = 1;
        for (i = 0; i < n; i++){
            if (!visit[i]){
                if ((distmin + custo[prox][i]) < dist[i]){
                    dist[i] = distmin + custo[prox][i];
                    next[i] = prox;
                }
            }
        }
        cont++;
    }
}

void dijkstra(int graph[V][V], int n, int source)
{
    int custo[V][V], visit[V], next[V], dist[V];
    int i, j, cont;
    char cities[V][20] = {"Sao Paulo", "Ribeirao Preto", "Campinas", "Pocos de Caldas", "Rio de Janeiro"};

    inicializaV(graph, custo, n);
    distVis(custo, dist, visit, next, source, cont, n);
    arestas(custo, dist, visit, next, cont, n);

    for (i = 0; i < n; i++){
        if (i == source){
            printf("De %s para %s:Não existe\n", cities[source], cities[i]);
            printf("Custo:-\n");
        }
        if (i != source){
            printf("%s ", cities[source]);
            j = i;
            do{
                j = next[j];
                if (j != 0){
                    printf("-> %s", cities[j]);
                }
                else{
                     printf("-> %s", cities[i]);
                }
            } while (j != source);
            printf("\n");
            printf("Custo:%d\n", dist[i]);
        }
    }
}