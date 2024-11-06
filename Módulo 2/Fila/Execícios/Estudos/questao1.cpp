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
    int tam, dado;
    cin >> tam;

    for (int i = 0; i < tam; i++){
        cin >> dado;
        f1.enfileira(dado);
    }
    
    fila f2;
    cin >> tam;

    for (int i = 0; i < tam; i++){
        cin >> dado;
        f2.enfileira(dado);
    }

    int dado1, dado2;
    fila filaAux;

    while (not f2.vazia()) {
        dado2 = f2.desenfileira();
        while (not f1.vazia()){
            dado1 = f1.desenfileira();
            if (dado1 != dado2) {
                filaAux.enfileira(dado1);
            }
        }
        while (not filaAux.vazia()){
            dado = filaAux.desenfileira();
            f1.enfileira(dado);
        }
    }

    while (not filaAux.vazia()){
        dado = filaAux.desenfileira();
        f1.enfileira(dado);
    }

    while (not f1.vazia()){
        cout << f1.desenfileira() << " ";
    }

    return 0;
}