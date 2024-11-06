#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100
// quantidade de valores que é posspível ler na memória

//stuct para gerenciar os buffers
struct arquivo {
    FILE *f;
    int pos, MAX, *buffer;
};

void criaArquivoTeste(char *nome) {
    int i;
    FILE *f = fopen(nome, "w");
    srand(time(NULL));
    for (i = 1; i < 1000; i++) {
        fprintf(f, "%d\n", rand());
    }
    fprintf(f, "%d", rand());
    fclose(f);
}

void mergeSortExterno(char *nome){
    char novo[20];
    int numArqs = criaArquivosOrdenados(nome);
    int i, K = N / (numArqs + 1);

    remove(nome);
    merge(nome, numArqs, K);

    for (i = 0; i < numArqs; i++) {
        sprintf(novo, "Temp%d.txt", i+1);
        remove(novo);
    }
}

int criaArquivosOrdenados(char *nome) {
    int V[N], cont = 0, total = 0;
    char novo[20];
    FILE *f = fopen(nome, "r");
    while (!feof(f)) {
        fscanf(f, "%d", &V[total]);
        total++;
        // Buffer cheio: Salva em disco
        if (total == N) {
            cont++;
            sprintf(novo, "Temp%d.txt", cont);
            qsort(V, total, sizeof(int), compara);
            salvaArquivo(novo, V, total, 0);
            total = 0;
        }
    }
    // Sobraram dados no Buffer: Salva em Disco
    if (total > 0) {
        cont++;
        sprintf(novo, "Temp%d.txt", cont);
        qsort(V, total, sizeof(int), compara);
        salvaArquivo(novo, V, total, 0);
    }
    fclose(f);
    return cont;
}

void salvaArquivo(char *nome, int *V, int tam, int mudaLinhaFinal) {
    int i;
    FILE *f = fopen(nome, "a");
    for (i = 0; i < tam-1; i++) {
        fprintf(f, "%d\n", V[i]);
    }

    // controla a mudança de linha no final do arquivo
    if (mudaLinhaFinal == 0) {
        fprintf(f, "%d", V[tam-1]);
    } else {
        fprintf(f, "%d\n", V[tam-1]);
    }
    fclose(f);
}

void merge(char *nome, int numArqs, int K) {
    char novo[20];
    int i;
    int *buffer = (int*)malloc(K*sizeof(int));

    struct arquivo* arq;
    arq = (struct arquivo*)malloc(numArqs*sizeof(struct arquivo));

    for (i = 0; i < numArqs; i++) {
        sprintf(novo, "Temp%d.txt", i+1);
        arq[i].f = fopen(novo, "r");
        arq[i].MAX = 0;
        arq[i].pos = 0;
        // K -> quantidade de elementos que pode carregar na memória para cada um dos buffers
        arq[i].buffer = (int*)malloc(K*sizeof(int));
        preencheBuffer(&arq[i], K);
    }

    //enquanto houver arquivos para procurar
    int menor, qtdBuffer = 0;
    // Existe menor elemento? Coloca no buffer de saída salvar se o buffer está cheio
    while (procuraMenor(arq, numArqs, K, &menor) == 1) {
        buffer[qtdBuffer] = menor;
        qtdBuffer++;
        // Se verdadeiro o buffer de saída está cheio
        if (qtdBuffer == K) {
            salvaArquivo(nome, buffer, K ,1);
            qtdBuffer = 0;
        }
        // Sobraram dados no buffer? Salva em arquivo
        // salva dados ainda no buffer
        if (qtdBuffer != 0) {
            salvaArquivo(nome, buffer, qtdBuffer, 1);
        }

        for (i = 0; i < numArqs; i++) {
            free(arq[i].buffer);
        }

        free(arq);
        free(buffer);
    }
}

int procuraMenor(struct arquivo* arq, int numArqs, int K, int* menor) {
    int i, idx = -1;
    // Procura menor valor na primeira posição de cada buffer
    for (i = 0; i < numArqs; i++) {
        if (arq[i].pos < arq[i].MAX) {
            if (idx == -1) {
                idx = i;
            } else {
                if (arq[i].buffer[arq[i].pos] < arq[idx].buffer[arq[idx].pos]) {
                    idx = i;
                }
            }
        }
    }

    // Achou menor. Atualiza posição do buffer. Enche se estiver vazio.
    if (idx == -1) {
        *menor = arq[idx].buffer[arq[i].pos];
        arq[idx].pos++;
        if (arq[idx].pos == arq[idx].MAX) {
            preencheBuffer(&arq[idx], K);
        }
        return 1;
    } else {
        return 0;
    }
}

void preencheBuffer(struct arquivo* arq, int K) {
    int i;
    if (arq->f == NULL) {
        return;
    }

    arq->pos = 0;
    arq->MAX = 0;
    for (i = 0; i < K; i++) {
        if (!feof(arq->f)) { // Tem dados no arquivo? Lê e coloca no buffer
            fscanf(arq->f, "%d", &arq->buffer[arq->MAX]);
            arq->MAX++;
        } else { // Acabou os dados fecha o arquivo
            fclose(arq->f);
            arq->f = NULL;
            break;
        }
    }
}

int main() {
    criaArquivoTeste("dados.txt");
    mergeSortExterno("dados.txt");
    return 0;
}
