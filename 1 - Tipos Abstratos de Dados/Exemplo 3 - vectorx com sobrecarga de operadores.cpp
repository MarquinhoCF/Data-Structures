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
        vectorx(const vectorx& vec); // CONSTRUTOR DE CÓPIA!!
        ~vectorx();

        /* 
         * Referências para sobrecarga de operadores:
         * http://www.hardware.com.br/comunidade/sobrecarga-operadores/1150421/
         * http://users.cms.caltech.edu/~donnie/cs11/cpp/cpp-ops.html
         * http://en.cppreference.com/w/cpp/language/operators
         * https://en.wikibooks.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading
         */
        
        // SOBRECARGA DE DE OPERADORES!!
        vectorx& operator+(const vectorx& vec); // Pra fazer concatenação
        vectorx& operator=(const vectorx& vec);

        //métodos
        void preenche();
        void imprime();
        //void concatena(vectorx& vec1, vectorx& vec2);
        int getTam();

        //implementar * para 2 funções
        int operator*(const vectorx& vec); //produto interno
        vectorx operator*(const int& n); //produto de um vetor  por um inteiro
        /* http://stackoverflow.com/questions/11704729/operand-order-in-operator-overload */
        // Não é método da classe 'vetorx', então usamos 'friend'
        friend vectorx operator*(const int& n, vectorx& vec); //produto de um inteiro por vetor
        
        int& operator[](int pos);
        
        // Não é método da classe 'vetorx', então usamos 'friend'
        friend ostream& operator<<( ostream& output, const vectorx& vec);
}; 

vectorx::vectorx( ) {
    vetor = new int[10];
    tam = 10;
}

vectorx::vectorx(int n) {
    vetor = new int[n];
    tam = n;
}

// Construtor de cópia
vectorx::vectorx(const vectorx& vec) {
    cout << "construtor de cópia!" << endl;
    tam = vec.tam;
    vetor = new int[tam];
    for (int i; i < tam; i++){
        vetor[i] = vec.vetor[i];
    }
    /* Ou podemos usar isso, com a biblioteca 'cstring':
    memcpy(vetor, vec.vetor, tam);
    É mais eficiente também
    */
}

vectorx::~vectorx() {
    cout << "morri" << endl;
    delete[] vetor;
    tam = 0;
}

vectorx& vectorx::operator=(const vectorx& vec) {
    cout << "atribuição" << endl;
    delete[] vetor;
    tam = vec.tam;
    vetor = new int[tam];
    for (int i; i < tam; i++){
        vetor[i] = vec.vetor[i]; 
    }

    return *this; // This é um ponteiro para o próprio objeto, é preciso dereferenciar
}

vectorx& vectorx::operator+(const vectorx& vec){
    vectorx* result;
    int tam1 = tam;
    int tam2 = vec.tam;

    result = new vectorx(tam1+tam2);
        
    for (int i = 0; i < tam1; i++){
        result->vetor[i] = vetor[i];
    }

    for (int i = 0; i < tam2; i++){
        result->vetor[i+tam1] = vec.vetor[i];
    }   
        
    return *result;             
} 

// Produto interno
int vectorx::operator*(const vectorx& vec) {
    int result = 0;

    if (tam != vec.tam){
        cerr << "tamanhos diferentes de vetores" << endl;
        exit(EXIT_FAILURE);
    } else {
        for (int i = 0; i < tam; i++) {
            result += vetor[i] * vec.vetor[i];
        }
    }

    // cout << result << endl;
    return result;
}

// Multiplicação de vetor por um inteiro
vectorx vectorx::operator*(const int& n) {
    vectorx result = *this;

    for (int i; i < tam; i++) {
        result.vetor[i] = n * result.vetor[i];
    }

    return result;
}

// Sobrecarga: Multiplicação de vetor por um inteiro
vectorx operator*(const int& n, vectorx& vec) {
    return vec*n;
}

void vectorx::preenche() {
    for (int i = 0; i < tam; i++){
        vetor[i] = rand() % 100;
    }       
}

ostream& operator<<( ostream& output, const vectorx& vec){
    for (int i = 0; i < vec.tam; i++) {
        output << vec.vetor[i] << " ";
    }
    output << endl;

    return output;
}

/*void vectorx::concatena(vectorx& vec1, vectorx& vec2){
    delete[] vetor;

    tam = vec1.tam + vec2.tam;
    vetor = new int[tam];
        
    for (int i = 0; i < vec1.tam; i++){
        vetor[i] = vec1.vetor[i];
    }

    for (int i = 0; i < vec2.tam; i++){
        vetor[i+vec1.tam] = vec2.vetor[i];
    }               
} */

void vectorx::imprime() {
    for (int i = 0; i < tam; i++){
        cout << vetor[i] << " ";
    }   
    cout << endl;
}

int vectorx::getTam(){
    return tam;
}

int& vectorx::operator[](int pos) {
    if ((pos < 0) or (pos >= tam)){
        cerr << "posição inválida" << endl;
        exit(EXIT_FAILURE);
    } else{
        return vetor[pos];
    }
}






int main() {
    int tam1, tam2;
    cin >> tam1 >> tam2;
    
    // inicialiando gerador de n. aleat.
    // garantimos q sempre teremos números aleatórios
    srand(time(NULL));
    
    // criação dos vetores
    vectorx teste1;
    vectorx vec1(tam1);
    vectorx vec2(tam2);

    vectorx vec3;

    //criação de um objeto por alocação dinâmica:
    vectorx *ptrVecx;
    ptrVecx = new vectorx;
    
    // preenchimento dos dados
    vec1.preenche();
    vec2.preenche();

    //pode dar erro se tentar acessar posição indevida
    vec2[5] = 10;

    //pode dar erro se os vetores não tiverem tamanhos iguais
    cout << vec1*vec2 << endl;

    teste1.preenche();
    ptrVecx->preenche();
    cout << "ok" << endl;

    //concatenando
    vec3 = vec1 + vec2;
    //vec3.concatena(vec1, vec2);
    
    //usando construtor de cópia
    vectorx teste2 = teste1;

    //sobrecarga do operador (=)
    vectorx teste3;
    teste3 = teste1;

    // imprimindo os vetores
    cout << vec1 << vec2 << vec3;
    cout << "teste1" << endl;
    cout << teste1;
    teste1 = teste1 * 2;
    cout << teste1;
    teste1 = 3 * teste1;
    cout << teste1 << teste2 << *ptrVecx;
    
    cout << endl;
    cout << "Tamanho de vec1: " << vec1.getTam() << endl;

    // removendo ponteiro não utilizado
    delete ptrVecx;

    return 0;
}