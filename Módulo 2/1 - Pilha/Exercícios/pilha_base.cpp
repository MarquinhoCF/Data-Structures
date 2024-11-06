#include <iostream>
using namespace std;

typedef int Dado; // para facilitar a troca de int para outro tipo
 
// pilha implementada em arranjo 
class pilhav {
    private:
        int capacidade;
        Dado *dados;
        int tamanho;
        int posTopo;
    public:
        pilhav(int cap);
        ~pilhav();
        void empilha(Dado valor);
        Dado desempilha();
        Dado espia(); // acessa elemento do topo, mas não retira
        void depura(); // imprime os dados do vetor da pilha sem removê-los (desempilhar)
        void info();  // imprime informações da pilha (tamanho e  posição do topo)
};

pilhav::pilhav(int cap){
    int capacidade = cap;
    dados = new int[capacidade];
    tamanho = 0;
    posTopo = -1;
}

pilhav::~pilhav(){
    delete[] dados;
    posTopo = -1;
    tamanho = 0;
    capacidade = 0;
}

void pilhav::empilha(Dado valor){
    if (tamanho < capacidade) {
        dados[tamanho] = valor;
        posTopo = tamanho;
        tamanho++;
    }
}

Dado pilhav::desempilha(){
    Dado valor;
    if (tamanho > 0){
        valor = dados[posTopo];
        tamanho--;
        posTopo--;
    }

    if (posTopo == -1){
        valor = -1;
    }

    return valor;
}

Dado pilhav::espia(){
    return dados[posTopo];
}

void pilhav::depura(){
    for (int i = 0; i < tamanho; i++){
        cout << dados[i] << " ";
    }
    cout << endl;
}

void pilhav::info(){
    cout << tamanho << " " << posTopo << endl;
}

int main(){
    pilhav pilha(20);

    Dado dado1, dado2, dado3, dado4, dado5;
    cin >> dado1 >> dado2 >> dado3 >> dado4 >> dado5;

    Dado dado6, dado7, dado8, dado9;
    cin >> dado6 >> dado7 >> dado8 >> dado9;

    pilha.empilha(dado1);
    pilha.empilha(dado2);
    pilha.empilha(dado3);
    pilha.empilha(dado4);
    pilha.empilha(dado5);

    cout << pilha.desempilha() << " " << pilha.desempilha() << " " << pilha.desempilha() << endl;

    
    pilha.empilha(dado6);
    pilha.empilha(dado7);
    pilha.empilha(dado8);
    pilha.empilha(dado9);

    cout << pilha.desempilha() << " " << pilha.desempilha() << " " << pilha.desempilha() << endl;

    cout << pilha.espia() << endl;

    pilha.depura();

    pilha.info();

    return 0;
}