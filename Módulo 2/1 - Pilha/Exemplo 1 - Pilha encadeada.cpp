#include <iostream>

using namespace std;

class noh {
    friend class pilha;
    private:
        int mValor;
        noh* mProximo;
        
    public:
        noh(int valor);
};

noh::noh(int valor) {
    mValor = valor;
    mProximo = NULL;
    cout << "Nó criado: " << this << endl;
}

class pilha {
    private:
        noh* mTopo;
        int mTamanho;

    public:
        pilha();
        ~pilha();
        unsigned tamanho();
        void empilha(int dado);
        int desempilha();
        void limpaPilha();
        bool vazia();
};

pilha::pilha() {
    mTopo = NULL;
    mTamanho = 0;
}

pilha::~pilha() {
    limpaPilha();
}

void pilha::limpaPilha() {
    while (not vazia()) {
        desempilha();
    }
}

unsigned pilha::tamanho() {
    return mTamanho;
}

void pilha::empilha(int dado) {
    cout << "Topo (antes): " << mTopo << endl;
    noh* novo = new noh(dado);
    novo->mProximo = mTopo;
    mTopo = novo;
    mTamanho++;
    cout << "Topo (depois): " << mTopo << endl;
    cout << "Próximo do topo: " << mTopo->mProximo << endl;
}

int pilha::desempilha() {
    int valor = mTopo->mValor;
    noh* temp = mTopo;
    mTopo = mTopo->mProximo;
    delete temp;
    mTamanho--;
    return valor;
}

bool pilha::vazia() {
    return (mTamanho == 0);
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
    
    while (not (p1.vazia())) {
        cout << p1.desempilha() << " ";
    }
    cout << endl;

    return 0;
}