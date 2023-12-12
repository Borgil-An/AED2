#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int PESO;

typedef struct adjacencia {
    int vertice; // Serve para representar o destino
    PESO peso;    // Peso do vertice
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice {
    ADJACENCIA *head; // Apenas a cabeça da lista
} VERTICE;

typedef struct grafo {
    int vertices; // Numero de vertices do grafo (Max 20)
    int arestas;  // Arestas totais do grafo/
    VERTICE *adj;
} GRAFO;

void adicionaAresta(GRAFO *g, int origem, int destino, PESO peso);
GRAFO *criaGrafo(int numVertices);
void exibeGrafo(GRAFO *g);
void liberaGrafo(GRAFO *g);
GRAFO *geraGrafoAleatorio(int numVertices, int numArestas);
int existeAresta(GRAFO *g, int origem, int destino);
void exibeGrafoBonito(GRAFO *g);

int main(void) {
    int opcao;
    int numVertices;

    printf("Escolha uma opção:\n");
    printf("1. Criar grafo manualmente\n");
    printf("2. Gerar grafo aleatório\n");
    scanf("%d", &opcao);

    if (opcao == 1) {
        printf("Quantos vértices deseja que seu grafo tenha (até 20)? ");
        scanf("%d", &numVertices);

        if (numVertices <= 0 || numVertices > 20) {
            printf("Número de vértices inválido. O programa será encerrado.\n");
            return 1;
        }

        GRAFO *grafo = criaGrafo(numVertices);

        for (int i = 0; i < numVertices; i++) {
            int numArestas;
            printf("Quantas arestas para o vértice %d? ", i);
            scanf("%d", &numArestas);

            for (int j = 0; j < numArestas; j++) {
                int destino;
                PESO peso;
                printf("Digite o vértice de destino e o peso da aresta (origem %d): ", i);
                scanf("%d %d", &destino, &peso);
                adicionaAresta(grafo, i, destino, peso);
            }
        }

        exibeGrafoBonito(grafo);
        liberaGrafo(grafo);
    } else if (opcao == 2) {
        int numArestas;
        printf("Quantos vértices deseja que seu grafo aleatório tenha (até 20)? ");
        scanf("%d", &numVertices);

        printf("Quantas arestas deseja para o grafo aleatório? ");
        scanf("%d", &numArestas);

        GRAFO *grafoAleatorio = geraGrafoAleatorio(numVertices, numArestas);
        exibeGrafoBonito(grafoAleatorio);
        liberaGrafo(grafoAleatorio);
    } else {
        printf("Opção inválida. O programa será encerrado.\n");
        return 1;
    }

    return 0;
}

// Função para criar um grafo com o número especificado de vértices
GRAFO *criaGrafo(int numVertices) {
    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    if (!g) {
        printf("Erro ao alocar memória para o grafo.\n");
        exit(1);
    }

    g->vertices = numVertices;
    g->arestas = 0;
    g->adj = (VERTICE *)malloc(numVertices * sizeof(VERTICE));

    if (!g->adj) {
        printf("Erro ao alocar memória para os vértices.\n");
        free(g);
        exit(1);
    }

    for (int i = 0; i < numVertices; i++) {
        g->adj[i].head = NULL;
    }

    return g;
}

// Função para adicionar uma aresta entre dois vértices com um peso especificado
void adicionaAresta(GRAFO *g, int origem, int destino, PESO peso) {
    if (origem >= 0 && origem < g->vertices && destino >= 0 && destino < g->vertices) {
        ADJACENCIA *novaAresta = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));

        if (!novaAresta) {
            printf("Erro ao alocar memória para a aresta.\n");
            exit(1);
        }

        novaAresta->vertice = destino;
        novaAresta->peso = peso;
        novaAresta->prox = g->adj[origem].head;
        g->adj[origem].head = novaAresta;
        g->arestas++;
    } else {
        printf("Origem e/ou destino inválido(s).\n");
    }
}

// Função para exibir os dados armazenados no grafo
void exibeGrafo(GRAFO *g) {
    printf("\nGrafo com %d vértices e %d arestas:\n", g->vertices, g->arestas);
    for (int i = 0; i < g->vertices; i++) {
        printf("Vértice %d:", i);
        ADJACENCIA *atual = g->adj[i].head;
        while (atual) {
            printf(" -> %d (Peso: %d)", atual->vertice, atual->peso);
            atual = atual->prox;
        }
        printf("\n");
    }
}

// Função para liberar a memória alocada para o grafo
void liberaGrafo(GRAFO *g) {
    // Libera a memória alocada para as listas de adjacência
    for (int i = 0; i < g->vertices; i++) {
        ADJACENCIA *atual = g->adj[i].head;
        while (atual) {
            ADJACENCIA *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    // Libera a memória alocada para os vértices
    free(g->adj);

    // Libera a memória alocada para o grafo
    free(g);
}

// Função para gerar um número aleatório entre min e max (inclusive)
int randInt(int min, int max) {
    return   rand() % (max - min + 1) + min;
}

// Função para verificar se uma aresta já existe no grafo
int existeAresta(GRAFO *g, int origem, int destino) {
    ADJACENCIA *atual = g->adj[origem].head;
    while (atual) {
        if (atual->vertice == destino) {
            return 1; // Aresta já existe
        }
        atual = atual->prox;
    }
    return 0; // Aresta não existe
}

// Função para exibir as conexões do grafo de maneira mais bonita
void exibeGrafoBonito(GRAFO *g) {
    printf("\nConexões do Grafo:\n");

    for (int i = 0; i < g->vertices; i++) {
        printf("Vértice %d:", i);

        ADJACENCIA *atual = g->adj[i].head;
        while (atual) {
            printf(" -> %d (Peso: %d)", atual->vertice, atual->peso);
            atual = atual->prox;
        }

        printf("\n");
    }
}

// Função para gerar um grafo aleatório com um número especificado de vértices e arestas
GRAFO *geraGrafoAleatorio(int numVertices, int numArestas) {
    if (numVertices <= 0 || numVertices > 20 || numArestas < numVertices || numArestas > numVertices * (numVertices - 1)) {
        printf("Parâmetros inválidos para a geração do grafo aleatório.\n");
        exit(1);
    }

    GRAFO *g = criaGrafo(numVertices);
    srand(time(NULL));

    for (int i = 0; i < numArestas; i++) {
        int origem = randInt(0, numVertices - 1);
        int destino = randInt(0, numVertices - 1);
        PESO peso = randInt(1, 10); // Peso aleatório entre 1 e 10

        // Evita arestas para o mesmo vértice ou arestas duplicadas
        while (origem == destino || existeAresta(g, origem, destino)) {
            origem = randInt(0, numVertices - 1);
            destino = randInt(0, numVertices - 1);
        }

        adicionaAresta(g, origem, destino, peso);
    }

    return g;
}
