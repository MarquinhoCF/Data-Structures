#include <iostream>
using namespace std;

// Para ordenar descendo uma sub árvore com raíz em  i, do vetor vet[] e tam que é o tamanho da heap
void corrigeDescendo(int vet[], int tam, int i){
	int maior = i; // Inicializar a maior raiz, já que estamos baseando em uma heap que comece em 0
	int esq = 2 * i + 1; 
	int dir = 2 * i + 2;

	// Se o filho esquerdo for maior q a raiz
	if ((esq < tam) and (vet[esq] > vet[maior])){
        maior = esq;
    }

	// Se o filho direito for maior q a raiz
	if ((dir < tam) and (vet[dir] > vet[maior]))
		maior = dir;

	// Se o maior trocou
	if (maior != i) {
		swap(vet[i], vet[maior]);

		// Recursivamente heapfy e chamado para outra sub raiz
		corrigeDescendo(vet, tam, maior);
	}
}

// Função principal do heap sort
void heapSort(int vet[], int tam, bool crescente){
	// Pega da metade do vetor "heap" e até q chegue a raiz ele decrementa chamando heapfy
    // Como nossa heap começa em 0 temos q subtrair 1
	for (int i = (tam / 2 - 1); i >= 0; i--){
        corrigeDescendo(vet, tam, i);
    }

    if (crescente){
        // Um por um pegamos os elementos da heap
        for (int i = tam - 1; i >= 0; i--) {
            // Movemos a raiz atual para o fim
            swap(vet[0], vet[i]);

            // chamamos o max heapfy para a heap reduzida
            corrigeDescendo(vet, i, 0);
        }
    }
}

// Função de utilidade
void imprimeVetor(int vet[], int tam){
	for (int i = 0; i < tam; ++i)
		cout << vet[i] << " ";
	cout << "\n";
}

int main(){
	int vet[] = {60 ,20 ,40 ,70, 30, 10};
	int tam = sizeof(vet) / sizeof(vet[0]);

    cout << "Antes de ordenar: ";
	imprimeVetor(vet, tam);   

    heapSort(vet, tam, false);

    cout << "Ordenação descrescente: ";
	imprimeVetor(vet, tam);

	heapSort(vet, tam, true);

	cout << "Ordenação crescente: ";
	imprimeVetor(vet, tam);
	
    return 0;
}