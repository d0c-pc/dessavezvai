#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define true 1
#define false 0

/* ESTRUTURA BASICA DO GRAFO */
typedef int bool;
typedef int TIPOPESO;

typedef struct grafo{
    int vertices;
    int arestas;
    bool matriz[200][200]; // Matriz de Adjacencias
    int min_custo; // Custo minimo da Arvore Gerada
} GRAFO;

// Função que cria o GRAFO
GRAFO* criarGrafo(int v, int a){
    if(v <= 0 || a <=0) return NULL;

    GRAFO* gr = (GRAFO *)malloc(sizeof(GRAFO));

    gr->vertices = v;
    gr->arestas = a;

    int i, j;
    for(i = 0; i < gr->vertices; i++) for(j = 0; j < gr->vertices; j++) gr->matriz[i][j] = 0;
    
    return gr;
}

// Função que adiciona as ADJACENCIA na MATRIZ
bool criarAdjacencia(GRAFO* gr, int v1, int v2, TIPOPESO peso){
    if(v1 < 0 || v2 < 0)
        return false;

    gr->matriz[v1][v2] = peso;

    return true;
}

// Função que recebe como parametro um GRAFO e imprimi ele
void imprimirMatriz(GRAFO* gr){
    int i, j;

    for(i = 0; i < gr->vertices; i++){
        printf("\n");
        for(j = 0; j < gr->vertices; j++) printf("%i\t", gr->matriz[i][j]);
    }
    printf("\n");
}

// Calcular o menor custo entre os NÓS disponiveis
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

// Função que imprimi a ARVORE decorrente do Algoritmo de Prim no GRAFO
void imprimirPrim(GRAFO* gr, int p[], FILE* file_out){
    int i;
    fprintf(file_out, "%d \n", gr->min_custo);
    for(i = 1; i < gr->vertices; i++){
        fprintf(file_out, "%d %d  \n", p[i], i);
        //printf("%d  %d  \n", p[i], i);
    }
}

// Implementação do Algoritmo de PRIM 
void prim(GRAFO* gr, FILE* file_out){
    int p[gr->vertices]; // Um arranjo que armazena os predecessores
    int custo[gr->vertices]; 
    bool abertos[gr->vertices]; // Arranjo que armazena os NóS que não foram descubertos 
    
    int i, cont, k;
    for(i = 0; i < gr->vertices; i++){ // Laço que percorre todo o GRAFO e adiciona INFINITO nas distancias
        custo[i] = INT_MAX;
        abertos[i] = true;
    }

    custo[0] = 0; // Adicionar o custo do NÓ inicial
    p[0] = -1; // Adicionar a distancia -1 ao NÓ inicial

    for(cont = 0; cont < gr->vertices; cont++){
        int u = menorCusto(gr, custo, abertos);
        abertos[u] = false;
        gr->min_custo += gr->matriz[p[u]][u]; // Faz o somatório das distancias
        for(k = 0; k < gr->vertices; k++) 
            if(gr->matriz[u][k] && abertos[k] == true && gr->matriz[u][k] < custo[k]){
                p[k] = u;
                custo[k] = gr->matriz[u][k];
            }
    }

    //printf("\n\n\n");
    //printf("%d \n\n", gr->min_custo);
    imprimirPrim(gr, p, file_out);
}

int main(int argc, char* argv[]){

    int string[50];
    int i, v, t;
    int k = 0;

    FILE* file_in = fopen(argv[1], "r");
    if(file_in == NULL) fprintf(stderr, "Erro na Leitura do TXT");
    
    fscanf(file_in, "%d", &i);

    while(!feof(file_in)){
        //printf("%d \n", i);
        string[k] = i;
        fscanf(file_in, "%d", &i);
        k++;
    }

    // char buffer[50];
    // char* stringt[sizeof(string)];
    // for(t = 0; t < 35; t++) {
    //     snprintf(buffer, 50, "%d", string[t]);
    //     //stringt[t] = strdup(buffer);
    //     //printf("%s ", stringt[t]);

    //     char delim[] = " ";
    //     char* string_tratada = strtok(strdup(buffer), delim);
    //     while(string_tratada != NULL){
    //         printf("%s", string_tratada);
    //         string_tratada = strtok(NULL, delim);
    //     }  
    // } 
    
    GRAFO* gr = criarGrafo(string[0], string[1]);

    for(v = 2; v < k; v+=3) {
        criarAdjacencia(gr, string[v], string[v+1], string[v+2]);
        //printf("%d %d %d \n", string[v], string[v+1], string[v+2]);
    }
    fclose(file_in);
    FILE* file_out = fopen("arquivo_saida.txt", "w");

    prim(gr, file_out);

    return 0;
}
