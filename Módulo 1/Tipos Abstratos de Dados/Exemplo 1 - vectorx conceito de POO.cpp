#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

struct vectorx{
    int* vetor;
    int tam;

    //Não preciso mais passar o vetor por ponteiro nas funções!!

    void inicializa(int n){
        vetor = new int[n];
        tam = n;
    }

    void finaliza(){
        delete[] vetor;
        tam = 0;
    }

    // função para preencher o vetor com dados aleatórios
    void preenche() {
        for (int i = 0; i < tam; i++){
            // Função rand devolve um número aleatório entre 0 e ao máximo valor prar int
            // Teremos um número entre 0 e 99, porque estamos pegando o resto da divisão do número aleatório por 100
            // Pra usar rand precisa da biblioteca 'cstdlib'
            vetor[i] = rand() % 100;
        }       
    }

    // concatena dois vetores, vec1 e vec2 em vec
    void concatena(vectorx& vec1, vectorx& vec2) {
        int tam1 = vec1.tam;
        int tam2 = vec2.tam;
        
        for (int i = 0; i < tam1; i++){
            vetor[i] = vec1.vetor[i];
        }

        for (int i = 0; i < tam2; i++){
            vetor[i+tam1] = vec2.vetor[i];
        }
    }

    void imprime() {
        for (int i = 0; i < tam; i++){
            cout << vetor[i] << " ";
        }   
        cout << endl;
    }

};

int main() {
    vectorx vec1, vec2, vec3;
    int tam1, tam2;

    cin >> tam1 >> tam2;
    
    // inicialiando gerador de n. aleat.
    // garantimos q sempre teremos números aleatórios
    srand(time(NULL));
    
    // criação dos vetores
    vec1.inicializa(tam1);
    vec2.inicializa(tam2);
    vec3.inicializa(tam1+tam2);
    
    // preenchimento dos dados
    vec1.preenche();
    vec2.preenche();
    vec3.concatena(vec1, vec2);
    
    // imprimindo os vetores
    vec1.imprime();
    vec2.imprime();
    vec3.imprime();
    
    // desalocação dos vetores
    vec1.finaliza();
    vec2.finaliza();
    vec3.finaliza();

    return 0;
}