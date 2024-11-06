#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

typedef int dado;

class MinHeap{
    private:
        dado* heap;
        int capacidade;
        int tamanho;
        inline int pai(int i);
        inline int esquerdo(int i);
        inline int direito(int i);
        void arruma();
        void corrigeDescendo(int i); // Equivalente a heapify()
        void corrigeSubindo(int i);

    public:
        MinHeap(dado vet[], int tam);
        ~MinHeap();
        void imprime(); // Quebra de Estrutura para fins didáticos
        dado espiaRaiz();
        dado retiraRaiz();
        void insere(dado d);
};

MinHeap::MinHeap(dado vet[], int tam){
    capacidade = tam;
    heap = new dado[capacidade];

    // memcpy(ponteiro de destino, ponteiro de origem, quantidade de bytes a serem copiados)
    memcpy(heap, vet, tam * sizeof(dado));
    // equivale a esse código, mas mais eficiente
    /*for (int i; i < tam; i++){
        heap[i] = vet[i];
    }*/

    tamanho = tam;
    arruma();
}

MinHeap::~MinHeap(){
    delete[] heap;
}

void MinHeap::arruma(){
    // Arruma pega da metade do vetor "heap" e até q chegue a raiz ele decrementa chamando corriDescendo
    // Como nossa heap começa em 0 temos q subtrair 1
    for (int i = (tamanho/2 - 1); i >= 0; i--){
        corrigeDescendo(i);
        cout << i << ": ";
        imprime();
    }
}

int MinHeap::pai(int i){
    return (i - 1)/2;
}

int MinHeap::esquerdo(int i){
    return i*2 + 1;
}

int MinHeap::direito(int i){
    return i*2 + 2;
}

void MinHeap::corrigeDescendo(int i){
    int esq = esquerdo(i);
    int dir = direito(i);
    // Primeiro considero q i seja o menor
    int menor = i;

    // se a posição de "esq" não for inválida, comparo "esq" com i e atualizo menor
    if ((esq < tamanho) and (heap[esq] < heap[menor])){
        menor = esq;
    }

    // se a posição de "dir" não for inválida, comparo "dir" com i e atualizo menor
    if ((dir < tamanho) and (heap[dir] < heap[menor])){
        menor = dir;
    }

    // se menor não for i mais, é preciso trocar e chamar recursivamente corrigeDescendo novamente
    // note que se menor for trocado ele sempre terá profundidade maior q anteriormente
    if (menor != i){
        swap(heap[i], heap[menor]);
        corrigeDescendo(menor);
    }
}

void MinHeap::corrigeSubindo(int i){
    int p = pai(i);

    // Se o valor q tiver em i for menor que o valor que estiver em pai, é necessário trocar
    // Note que se for trocado pai sempre terá profundidade menor q anteriormente
    // Se i == 0, resulta em -1/2 que resulta em 0, não precisa preocupar em testar se i é igual a 0
    if (heap[i] < heap[p]){
        swap(heap[i], heap[p]);
        corrigeSubindo(p);
    }
}

void MinHeap::imprime(){ // Quebra de Estrutura
    for (int i = 0; i < tamanho; i++){
        cout << heap[i] << " ";
    }
    cout << endl;
}

dado MinHeap::espiaRaiz(){
    return heap[0];
}

dado MinHeap::retiraRaiz(){
    if (tamanho == 0){
        cerr << "Heap vazia!!" << endl;
        exit(EXIT_FAILURE);
    }
    
    int raiz = 0; // Posição do dado Inicial
    int fim = tamanho - 1; // Posição do dado Final: no caso, numa heap que começa em 0, o final é tamanho - 1
    dado aux = heap[raiz];
    swap(heap[raiz], heap[fim]);
    tamanho--;
    corrigeDescendo(raiz);
    return aux;
}

void MinHeap::insere(dado d){
    if (tamanho == capacidade){
        cerr << "heap cheia!!" << endl;
        exit(EXIT_FAILURE);
    }

    // tamanho tbm representa a posição logo após a última
    heap[tamanho] = d;
    corrigeSubindo(tamanho);
    tamanho++;
}

int main(){
    int tam;
    dado valor;
    cin >> tam;

    dado *vetor = new dado[tam];

    for (int i = 0; i < tam; i++){
        cin >> valor;
        vetor[i] = valor;
    }
	
    MinHeap *h = new MinHeap(vetor, tam);
	
    delete vetor;
    delete h;

    return 0;
}