#include <iostream>

using namespace std;

class noh {
    friend class fila;
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

class fila {
    private:
        noh* mInicio;
        noh* mFim;
        unsigned mTamanho;

    public:
        fila();
        ~fila();
        unsigned tamanho();
        void enfileira(int dado);
        int desenfileira();
        void limpaFila();
        bool vazia();
};

fila::fila() {
    mInicio = NULL;
    mFim = NULL;
    mTamanho = 0;
}

fila::~fila() {
    limpaFila();
}

void fila::limpaFila() {
    while (not vazia()) {
        desenfileira();
    }
}

unsigned fila::tamanho() {
    return mTamanho;
}

void fila::enfileira(int dado) {
    noh* novo = new noh(dado);
    if (mTamanho == 0) {
        mInicio = novo;
    } else {
        mFim->mProximo = novo;
    }
    mFim = novo;
    mTamanho++;
}

int fila::desenfileira() {
    int valor = mInicio->mValor;
    noh* temp = mInicio;
    mInicio = mInicio->mProximo;
    delete temp;
    mTamanho--;
    if (mTamanho == 0) {
        mFim = NULL;
    }
    return valor;
}

bool fila::vazia() {
    return (mTamanho == 0);
}

int main() {
    fila f1;
    int num;
    cout << "Digite os números a serem enfileirados: ";
    cin >> num;

    while (num >= 0) {
        f1.enfileira(num);
        cin >> num;
    }

    cout << "Tamanho: " << f1.tamanho() << endl;

    cout << "Elementos: ";
    
    while (not f1.vazia()) {
        cout << f1.desenfileira() << " ";
    }
    cout << endl;

    return 0;
}