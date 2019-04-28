#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOPESO;

typedef struct grafo{
    int vertices;
    int arestas;
    bool matriz[200][200]; // Matriz de Adjacencias
    int min_custo;
} GRAFO;

GRAFO* criarGrafo(int v, int a){
    if(v <= 0 || a <=0) return NULL;

    GRAFO* gr = (GRAFO *)malloc(sizeof(GRAFO));

    gr->vertices = v;
    gr->arestas = a;

    int i, j;
    for(i = 0; i < gr->vertices; i++) for(j = 0; j < gr->vertices; j++) gr->matriz[i][j] = 0;
    
    return gr;
}

bool criarAdjacencia(GRAFO* gr, int v1, int v2, TIPOPESO peso){
    if(v1 < 0 || v2 < 0) return false;

    gr->matriz[v1][v2] = peso;

    return true;
}

void imprimirMatriz(GRAFO* gr){
    int i, j;

    for(i = 0; i < gr->vertices; i++){
        printf("\n");
        for(j = 0; j < gr->vertices; j++) printf("%i\t", gr->matriz[i][j]);
    }
    printf("\n");
}

int menorCusto(GRAFO* gr, int custo[], bool abertos[]){
    int minimo = INT_MAX/2;
    int menor_indice;

    int i;
    for(i = 0; i < gr->vertices; i++) 
        if(abertos[i] == true && custo[i] < minimo){
            minimo = custo[i];
            menor_indice = i;
        } 

    return menor_indice;
}

void imprimirPrim(GRAFO* gr, int p[]){
    int i;
    for(i = 1; i < gr->vertices; i++){
        printf("%d \n", i);
        printf("%d -> %d  \n", p[i], i);
    }
}

void prim(GRAFO* gr){
    int p[gr->vertices]; // Um arranjo que armazena os predecessores
    int custo[gr->vertices]; //
    bool abertos[gr->vertices]; 
    
    int i, cont, k;
    for(i = 0; i < gr->vertices; i++){
        custo[i] = INT_MAX;
        abertos[i] = true;
    }

    custo[0] = 0;
    p[0] = -1;

    for(cont = 0; cont < gr->vertices; cont++){
        int u = menorCusto(gr, custo, abertos);
        abertos[u] = false;
        gr->min_custo += gr->matriz[p[u]][u];
        for(k = 0; k < gr->vertices; k++) 
            if(gr->matriz[u][k] /*&& abertos[k] == true*/ && gr->matriz[u][k] < custo[k]){
                p[k] = u;
                custo[k] = gr->matriz[u][k];
            }
    }

    printf("\n\n\n");
    printf("Custo Total da Arvore: %d \n\n", gr->min_custo);
    imprimirPrim(gr, p);
}

int main(void){
    //FILE* file = fopen("", "r"); // Ler os arquivos de entrada
    
    GRAFO* gr = criarGrafo(5, 5);

    
    criarAdjacencia(gr,0, 1, 2);
    criarAdjacencia(gr,0, 3, 6);
    criarAdjacencia(gr,1, 2, 3);
    criarAdjacencia(gr,1, 3, 8);
    criarAdjacencia(gr,1, 4, 5);
    criarAdjacencia(gr,2, 4, 7);
    criarAdjacencia(gr,3, 4, 9);

    imprimirMatriz(gr);

    printf("\n\n\n");

    prim(gr);
    return 0;
}