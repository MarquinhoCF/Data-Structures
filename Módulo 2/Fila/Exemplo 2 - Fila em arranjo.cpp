#include <iostream>

using namespace std;

class filaCircular {
    private:
        int posInicio;
        int posFim;
        int* mDados;
        unsigned mCapacidade;
        unsigned mTamanho;

    public:
        filaCircular(int capacidade);
        ~filaCircular();
        unsigned tamanho();
        void enfileira(int dado);
        int desenfileira();
        bool vazia();
        void depura(); // QUEBRA DE ESTRURA!!!
};

filaCircular::filaCircular(int capacidade) {
    posInicio = -1;
    posFim = -1;
    mCapacidade = capacidade;
    mDados = new int[mCapacidade];
    mTamanho = 0;
}

filaCircular::~filaCircular() {
    delete[] mDados;
}

unsigned filaCircular::tamanho() {
    return mTamanho;
}

void filaCircular::enfileira(int dado) {
    if (mTamanho <= mCapacidade){
        posFim++;
        posFim = posFim % mCapacidade;
        mDados[posFim] = dado;
        if (mTamanho == 0){
            posInicio++;
        }
        mTamanho++;
    } else {
        cerr << "Fila cheia!!" << endl;
    }
     
}

int filaCircular::desenfileira() {
    if (mTamanho > 0) {
        int aux = mDados[posInicio];
        mTamanho--;
        if (mTamanho > 0) {
            posInicio++;
            posInicio = posInicio % mCapacidade;
        } else {
            posInicio = -1;
            posFim = -1;
        }
        return aux;
    } else {
        cerr << "Fila vazia!!" << endl;
        return -1;
    }
}

bool filaCircular::vazia() {
    return (mTamanho == 0);
}

// QUEBRA DE ESTRURA!!!
void filaCircular::depura() {
    cout << "Inicio: " << posInicio << endl;
    cout << "Fim: " << posFim << endl;
    cout << "Tamanho: " << mTamanho << endl;
    cout << "Vetor de dados: ";
    for (unsigned i = 0; i < mCapacidade; i++){
        cout << mDados[i] << " ";
    }
    cout << endl;
}

int main() {
    filaCircular f1(12);
    
    int num;
    cout << "Digite 8 números a serem enfileirados: ";
    for (int i = 0; i < 8; i++) {
        cin >> num;
        f1.enfileira(num);
    }

    cout << "Tamanho: " << f1.tamanho() << endl;

    cout << "5 elementos: ";
    for (int i = 0; i < 5; i++) {
        cout << f1.desenfileira() << " ";
    }
    cout << endl;
    
    cout << "Digite mais 8 números a serem enfileirados: ";
    for (int i = 0; i < 8; i++) {
        cin >> num;
        f1.enfileira(num);
    }

    cout << "5 elementos: ";
    for (int i = 0; i < 5; i++) {
        cout << f1.desenfileira() << " ";
    }
    cout << endl;

    f1.depura();

    return 0;
}