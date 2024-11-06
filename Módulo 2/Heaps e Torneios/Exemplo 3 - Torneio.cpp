#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

typedef int dado;
const int INVALIDO = -1;

class Torneio{
    private:
        dado* heap;
        int capacidade;
        int tamanho;
        int inicioDados;
        inline int pai(int i);
        inline int esquerdo(int i);
        inline int direito(int i);
        void arruma();
        void copiaMaior(int i); // Equivalente a heapify()
        void copiaSubindo(int i);

    public:
        Torneio(int numFolhas);
        Torneio(dado vet[], int tam);
        ~Torneio();
        void imprime(); // Quebra de Estrutura para fins didáticos
        void insere(dado d);
};

Torneio::Torneio(int numFolhas){
    // Determinando a capacidade:
    // número de possíveis pais é uma potência de 2 menos 1
    // capacidade é possíveis pais mais numFolhas
    // começamos com 1 pai e vamos dobrando a cada caso
    capacidade = 1;
    while (capacidade < numFolhas){
        capacidade *= 2;
    }
    // potência de 2 menos 1 + número de folhas
    capacidade = capacidade - 1 + numFolhas;
    heap = new dado[capacidade];
    inicioDados = capacidade - numFolhas;

    cout << "inicioDados: " << inicioDados << endl;
    cout << "capacidade: " << capacidade << endl;

    tamanho = 0;

    for (int i = 0; i < capacidade; i++){
        heap[i] = INVALIDO;
    }
}

Torneio::Torneio(dado vet[], int tam){
    // Determinando a capacidade:
    // número de possíveis pais é uma potência de 2 menos 1
    // capacidade é possíveis pais mais numFolhas
    // começamos com 1 pai e vamos dobrando a cada caso
    capacidade = 1;
    while (capacidade < tam){
        capacidade *= 2;
    }
    // potência de 2 menos 1 + tamanho do vetor
    capacidade = capacidade - 1 + tam;

    heap = new dado[capacidade];
    inicioDados = capacidade - tam;

    cout << "inicioDados: " <<  inicioDados << endl;
    cout << "capacidade: " <<  capacidade << endl;

    // memcpy(ponteiro de destino, ponteiro de origem, quantidade de bytes a serem copiados)
    // "&heap[inicioDados]" --> precisa copiar no endereço onde começa os dados
    memcpy(&heap[inicioDados], vet, tam * sizeof(dado));

    tamanho = tam;
    arruma();
}

Torneio::~Torneio(){
    delete[] heap;
}

void Torneio::arruma(){
    // Aplica "copiaMaior" na primeira metade dos elementos
    // Como nossa heap começa em 0 temos q subtrair 1
    cout << "arruma: " << inicioDados - 1 << endl;
    for (int i = inicioDados - 1; i >= 0; i--){
        copiaMaior(i);
    }
}

int Torneio::pai(int i){
    return (i - 1)/2;
}

int Torneio::esquerdo(int i){
    return i*2 + 1;
}

int Torneio::direito(int i){
    return i*2 + 2;
}

void Torneio::copiaMaior(int i){
    int esq = esquerdo(i);
    int dir = direito(i);
    cout << "i: " << i << " e: " << esq << " d: " << dir << endl;
    // Primeiro inicializo maior como inválido
    int maior = INVALIDO;

    // Verifico se esq tem um valor válido, se não atribuo inválido para a posição i
    if (esq < capacidade){
        // Verifico se dir tem um valor válido, e atribuo o maior como dir ou esq dependendo do qu for maior
        if ((dir < capacidade) and (heap[dir] > heap[esq])){
            maior = dir;
        } else {
            maior = esq;
        }
        // Atualizo a heap com o maior
        heap[i] = heap[maior];
    } else {
        heap[i] = INVALIDO;
    }
}

void Torneio::copiaSubindo(int i){
    int p = pai(i);

    // Se o valor q tiver em i for maior que o valor que estiver em pai, é necessário copiar
    // Note que se for copiado pai sempre terá profundidade menor q anteriormente
    // Se i == 0, resulta em -1/2 que resulta em 0, não precisa preocupar em testar se i é igual a 0
    if (heap[i] > heap[p]){
        heap[p] = heap[i];
        copiaSubindo(p);
    }
}

void Torneio::imprime(){ // Quebra de Estrutura
    for (int i = 0; i < capacidade; i++){
        cout << heap[i] << " ";
    }
    cout << endl;
}

void Torneio::insere(dado d){
    if (tamanho == capacidade){
        cerr << "Erro ao inserir!!" << endl;
        exit(EXIT_FAILURE);
    }

    // Primeira posição disponível --> o tanto q já tem + inicio dos dados
    heap[tamanho + inicioDados] = d;
    copiaSubindo(tamanho + inicioDados);
    tamanho++;
}

int main(){
    int tam = 9;
    dado vet1[] = {50, 2, 90, 20, 230, 43, 8, 34, 66};
	
    Torneio *h = new Torneio(vet1, tam);
    h->imprime();
    delete h;

    tam = 13;
    dado vet2[] = {50, 2, 90, 20, 230, 43, 8, 34, 66, 100, 110, 3, 13};
    
    h = new Torneio(vet2, tam);
    h->imprime();
    delete h;
    
    tam = 9;
    h = new Torneio(tam);

    for (int i = 0; i < tam; i++){
        h->insere(vet1[i]);
        h->imprime();
    }
    delete h;

    return 0;
}