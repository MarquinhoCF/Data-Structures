#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

class vectorx {
    private:
        //atributos
        int* vetor;
        int tam;

    public:
        //construtores e destrutores
        vectorx();
        vectorx(int n);
        ~vectorx();

        //métodos
        void preenche();
        void imprime();
        void concatena(vectorx& vec1, vectorx& vec2);
        int getTam();
};

vectorx::vectorx( ) {
    vetor = new int[10];
    tam = 10;
}

vectorx::vectorx(int n) {
    vetor = new int[n];
    tam = n;
}

vectorx::~vectorx() {
    cout << "morri" << endl;
    delete[] vetor;
    tam = 0;
}

void vectorx::preenche() {
    for (int i = 0; i < tam; i++){
        vetor[i] = rand() % 100;
    }       
}

void vectorx::concatena(vectorx& vec1, vectorx& vec2){
    delete[] vetor;

    tam = vec1.tam + vec2.tam;
    vetor = new int[tam];
    
        
    for (int i = 0; i < vec1.tam; i++){
        vetor[i] = vec1.vetor[i];
    }

    for (int i = 0; i < vec2.tam; i++){
        vetor[i+vec1.tam] = vec2.vetor[i];
    }               
} 

void vectorx::imprime() {
    for (int i = 0; i < tam; i++){
        cout << vetor[i] << " ";
    }   
    cout << endl;
}

int vectorx::getTam(){
    return tam;
}





int main() {
    int tam1, tam2;
    cin >> tam1 >> tam2;
    
    // inicialiando gerador de n. aleat.
    // garantimos q sempre teremos números aleatórios
    srand(time(NULL));
    
    // criação dos vetores
    vectorx teste;
    vectorx vec1(tam1);
    vectorx vec2(tam2);

    vectorx vec3;

    //criação de um objeto por alocação dinâmica:
    vectorx *ptrVecx;
    ptrVecx = new vectorx;
    
    // preenchimento dos dados
    vec1.preenche();
    vec2.preenche();

    teste.preenche();
    ptrVecx->preenche();

    //concatenando
    vec3.concatena(vec1, vec2);
    
    // imprimindo os vetores
    teste.imprime();
    ptrVecx->imprime();
    vec1.imprime();
    vec2.imprime();
    vec3.imprime();
    
    cout << "Tamanho de vec1: " << vec1.getTam() << endl;

    // removendo ponteiro não utilizado
    delete ptrVecx;

    return 0;
}