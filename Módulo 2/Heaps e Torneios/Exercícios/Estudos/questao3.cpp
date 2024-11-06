#include <iostream>   

typedef unsigned TCodProcesso;

struct Processo {
    TCodProcesso mCodigo;
    int mPrioridade;
};

bool operator>(Processo p1, Processo p2) {
    return p1.mPrioridade > p2.mPrioridade;
}

bool operator<(Processo p1, Processo p2) {
    return p1.mPrioridade < p2.mPrioridade;
}

class Heap {
    // classe Heap (max-heap, o maior fica na raiz/inicio)
    public:
        // Criar heap sem dados e com capacidade informada
        Heap(int cap);
        // Destruttor
        ~Heap();
        // Inserir um dado na heap
        bool Inserir(TCodProcesso codigo, int prioridade);
        // Retira e retorna a raiz
        bool Retirar(TCodProcesso* ptCodigo, int* ptPrioridade);
        // Verifica se a heap está vazia
        bool Vazia();
    private:
        void ArrumarDescendo(int i);
        void ArrumarSubindo(int i);
        inline int Direito(int i);
        inline int Esquerdo(int i);
        inline int Pai(int i);
        Processo* heap;
        int capacidade;
        int tamanho;
};

using namespace std;

Heap::Heap(int cap) {
    capacidade = cap;
    heap = new Processo[cap];
    tamanho = 0;
}

Heap::~Heap() {
    delete heap;
}

void Heap::ArrumarDescendo(int i) {
    // Arruma as posicoes de i para baixo.
    
    int esq = Esquerdo(i);
    int dir = Direito(i);
    // Primeiro considero q i seja o maior
    int maior = i;

    // se a posição de "esq" não for inválida, comparo "esq" com i e atualizo maior
    if ((esq < tamanho) and (heap[esq] > heap[maior])){
        maior = esq;
    }

    // se a posição de "dir" não for inválida, comparo "dir" com i e atualizo maior
    if ((dir < tamanho) and (heap[dir] > heap[maior])){
        maior = dir;
    }

    // se maior não for i mais, é preciso trocar e chamar recursivamente corrigeDescendo novamente
    // note que se maior for trocado ele sempre terá profundidade maior q anteriormente
    if (maior != i){
        swap(heap[i], heap[maior]);
        ArrumarDescendo(maior);
    }
}

void Heap::ArrumarSubindo(int i) {
    // Arruma as posicoes de i para cima.
    int p = Pai(i);

    // Se o valor q tiver em i for maior que o valor que estiver em pai, é necessário trocar
    // Note que se for trocado pai sempre terá profundidade menor q anteriormente
    // Se i == 0, resulta em -1/2 que resulta em 0, não precisa preocupar em testar se i é igual a 0
    if (heap[i] > heap[p]){
        swap(heap[i], heap[p]);
        ArrumarSubindo(p);
    }
}

int Heap::Pai(int i) {
    return (i - 1)/2;
}

int Heap::Esquerdo(int i) {
    return 2*i + 1;
}

int Heap::Direito(int i) {
    return 2*i + 2;
}

bool Heap::Retirar(TCodProcesso* ptCodigo, int* ptPrioridade) {
    // Retira um codigo/prioridade, retornando os dois valores.
    // Retorna falso se o heap estiver vazio.
    if (tamanho == 0){
        return false;
    }
    
    int raiz = 0; // Posição do dado Inicial
    int fim = tamanho - 1; // Posição do dado Final: no caso, numa heap que começa em 0, o final é tamanho - 1
    Processo aux = heap[raiz];
    ptCodigo = &aux.mCodigo;
    ptPrioridade = &aux.mPrioridade;
    swap(heap[raiz], heap[fim]);
    tamanho--;
    ArrumarDescendo(raiz);
    return true;
}

bool Heap::Vazia() {
    return (tamanho == 0);
}

bool Heap::Inserir(TCodProcesso codigo, int prioridade) {
    // Insere um codigo/prioridade no heap.
    // Retorna falso se o heap estiver cheio.
    if (tamanho == capacidade){
        return false;
    }

    // tamanho tbm representa a posição logo após a última
    Processo processo;
    processo.mCodigo = codigo;
    processo.mPrioridade = prioridade;
    heap[tamanho] = processo;
    ArrumarSubindo(tamanho);
    tamanho++;
    return true;
}

int main() {
    unsigned capacidade;
    cin >> capacidade;
    Heap heap(capacidade);
    char comando;
    TCodProcesso codigo;
    int prioridade;
    do {
        cin >> comando;
        switch (comando) {
            case 'i': // inserir um processo no heap
                cin >> codigo >> prioridade;
                heap.Inserir(codigo, prioridade);
                break;
            case 'o': // obter um processo do heap
                if (heap.Retirar(&codigo, &prioridade))
                    cout << codigo << ' ' << prioridade << endl;
                else
                    cout << "Nao encontrado" << endl;
                break;
            case 's': //sair
                break;
        }
    } while (comando != 's');
    return 0;
}