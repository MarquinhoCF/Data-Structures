/*
    MaxHeap, para alteração de prioridade
    by joukim & bruno, 2019
    alterado em 2023 by Renato
    alterado em 2023 by Marcos
*/

#include <iostream>
#include <utility> // para usar swap
#include <stdexcept> // para usar exceção com runtime_error

using namespace std;

struct dado {
    string nomeTarefa;
    char tipoTarefa;
    int energiaGasta;
    int tempoEstimado;
    int prioridade;
};

bool operator>(dado d1, dado d2) {
    if (d1.prioridade != d2.prioridade) {
		return d1.prioridade > d2.prioridade;
	} else {
		return d1.energiaGasta < d2.energiaGasta;
	}
    
}

bool operator<(dado d1, dado d2) {
    if (d1.prioridade != d2.prioridade) {
		return d1.prioridade < d2.prioridade;
	} else {
		return d1.energiaGasta > d2.energiaGasta;
	}
}

ostream& operator<<(ostream& output,const dado& d) {
    output << "[" << d.nomeTarefa << "/" << d.tipoTarefa << "/" << d.energiaGasta << "/" << d.tempoEstimado << "/" << d.prioridade <<"]"; 
    return output;
}

class MaxHeap {
private:
    dado* heap;
    int capacidade;
    int tamanho;
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i); 
    void corrigeDescendo(int i); 
    void corrigeSubindo(int i);
public:
    MaxHeap(int cap);
    ~MaxHeap();
    void imprime();
    dado retiraRaiz();
    void insere(dado d);
};

MaxHeap::MaxHeap(int cap) {
    capacidade = cap;
    heap = new dado[capacidade];
    tamanho = 0;
}

MaxHeap::~MaxHeap() {
   delete[] heap;
}

int MaxHeap::pai(int i) {
    return (i-1)/2;
}
    
int MaxHeap::esquerdo(int i) {
    return 2*i + 1;
}
    
int MaxHeap::direito(int i) {
    return 2*i + 2;
}
    
void MaxHeap::corrigeDescendo(int i) {
    int esq = esquerdo(i);
    int dir = direito(i);
    // Primeiro considero q i seja o maior
    int maior = i;

     // se a posição de "esq" não for inválida, comparo "esq" com i e atualizo maior
    if ((esq <= (tamanho - 1)) and (heap[esq] > heap[maior])){
	    maior = esq;    
    }
    
    // se a posição de "dir" não for inválida, comparo "dir" com i e atualizo maior
    if ((dir <= (tamanho - 1)) and (heap[dir] > heap[maior])){
        maior = dir;
    }

    // se maior não for i mais, é preciso trocar e chamar recursivamente corrigeDescendo novamente
    // note que se maior for trocado ele sempre terá profundidade maior q anteriormente
    if (maior != i) {
	    swap(heap[i], heap[maior]);
	    corrigeDescendo(maior);
    }
}

void MaxHeap::corrigeSubindo(int i) {
    int p = pai(i);

    // Se o valor q tiver em i for maior que o valor que estiver em pai, é necessário trocar
    // Note que se for trocado pai sempre terá profundidade menor q anteriormente
    // Se i == 0, resulta em -1/2 que resulta em 0, não precisa preocupar em testar se i é igual a 0
    if ((p >= 0) and (heap[i] > heap[p])) {
	    swap(heap[i],heap[p]);
	    corrigeSubindo(p);
    }
}
        
void MaxHeap::imprime() {
    if (tamanho == 0){
        throw runtime_error("Heap vazia!");
    }
    for (int i = 0; i < tamanho; i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}

dado MaxHeap::retiraRaiz() {
    if (tamanho == 0){
        throw runtime_error("Erro ao retirar raiz");
    }
    
    int raiz = 0; // Posição do dado Inicial
    int fim = tamanho - 1; // Posição do dado Final: no caso, numa heap que começa em 0, o final é tamanho - 1
    dado aux = heap[raiz];
    swap(heap[raiz], heap[fim]);
    tamanho--;
    corrigeDescendo(raiz);
    return aux;
}


void MaxHeap::insere(dado d){
    if (tamanho == capacidade){
        throw runtime_error("Erro ao inserir");
    }

    // tamanho tbm representa a posição logo após a última
    heap[tamanho] = d;
    corrigeSubindo(tamanho);
    tamanho++;
}


int main() {
    int capacidade;
    dado info;
    char comando;

    cin >> capacidade;
    MaxHeap meuHeap(capacidade);

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nomeTarefa >> info.tipoTarefa >> info.energiaGasta >> info.tempoEstimado >> info.prioridade;
                    meuHeap.insere(info);
                    break;
                case 'r': // remover
                    cout << meuHeap.retiraRaiz().nomeTarefa << endl;
                    break;
                case 'p': // limpar tudo
                    meuHeap.imprime();
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    cout << endl;
    return 0;
}
