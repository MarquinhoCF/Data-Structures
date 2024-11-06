#include <iostream>

using namespace std;

class pilha {
    private:
        int* vetor;
        int mPosTopo;
        int mTamanho;
        int mCapacidadeMax;

    public:
        pilha();
        pilha(int capacidadeMax);
        pilha(const pilha& umaPilha);
        ~pilha();
        unsigned tamanho();
        void empilha(int dado);
        void redimensionarCapacidade();
        int desempilha();
        int mostraTopo();
        bool vazia();
};

pilha::pilha() {
    mCapacidadeMax = 10;
    vetor = new int[mCapacidadeMax];
    mPosTopo = -1;
    mTamanho = 0;
}

pilha::pilha(int capacidadeMax) {
    mCapacidadeMax = capacidadeMax;
    vetor = new int[mCapacidadeMax];
    mPosTopo = -1;
    mTamanho = 0;
}

// Construtor de cópia
pilha::pilha(const pilha& umaPilha) {
    mPosTopo = umaPilha.mPosTopo;
    mTamanho = umaPilha.mTamanho;
    mCapacidadeMax = umaPilha.mCapacidadeMax;
    vetor = new int[mCapacidadeMax];
    for (int i; i < mTamanho; i++){
        vetor[i] = umaPilha.vetor[i];
    }
    /* Ou podemos usar isso, com a biblioteca 'cstring':
    memcpy(vetor, vec.vetor, tam);
    É mais eficiente também
    */
}

pilha::~pilha() {
    delete[] vetor;
    mPosTopo = 0;
    mTamanho = 0;
    mCapacidadeMax = 0;
}

unsigned pilha::tamanho() {
    return mTamanho;
}

void pilha::empilha(int dado) {
    cout << "Topo (antes): " << mPosTopo << endl;
    if (mTamanho == mCapacidadeMax) { // vetor cheio, precisa redimensionar
        redimensionarCapacidade();
    }
    vetor[mTamanho] = dado;
    mPosTopo = mTamanho;
    mTamanho++;
    cout << "Topo (depois): " << mPosTopo << endl;
    cout << "Tamanho: " << mTamanho << endl;
    cout << "Capacidade: " << mCapacidadeMax << endl;
}

int pilha::desempilha() {
    int valor = vetor[mPosTopo];
    mPosTopo--;
    mTamanho--;
    return valor;
}

bool pilha::vazia() {
    return (mTamanho == 0);
}

int pilha::mostraTopo() {
    return vetor[mPosTopo];
}

void pilha::redimensionarCapacidade() {
	mCapacidadeMax = mCapacidadeMax + 5;
    int *vetorSuporte = new int[mCapacidadeMax];
    for(int i = 0; i < mTamanho; i++) {
        vetorSuporte[i] = vetor[i];
	}
    delete [] vetor;
    vetor = vetorSuporte;
}

int main() {
    pilha p1;
    int num;
    cout << "Digite os números a serem empilhados: ";
    cin >> num;

    while (num >= 0) {
        p1.empilha(num);
        cin >> num;
    }

    cout << "Tamanho: " << p1.tamanho() << endl;

    cout << "Elementos: ";
    
    while (not p1.vazia()) {
        cout << p1.desempilha() << " ";
    }
    cout << endl;

    return 0;
}