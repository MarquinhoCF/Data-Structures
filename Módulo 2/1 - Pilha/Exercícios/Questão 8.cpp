/* Classe pilha estatica
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 *
 * modified by Marcos Carvalho Ferreira, 2023
 * 
 */
#include <iostream>

using namespace std;

const int PILHAVAZIA = -1;
const int TAMANHOPILHA = 6;

struct Dado {
    string nome;
    char tipo;
    int valor;
};

// Imprime informações de um dado qualquer.
void imprimir_dado(const Dado& umDado){
    cout<< "Nome: " << umDado.nome << " ";
    cout<< "Tipo: " << umDado.tipo << " ";
    cout<< "Valor: " << umDado.valor << endl;
}

class Pilha {
    private:
        Dado* mPilha;
        int posTopo;
    public:
        // Constrói pilha vazia.
        Pilha();
        // Destrutor que desaloca memória.
        ~Pilha();
        // Retira e retorna o valor que estiver no topo da pilha.
        Dado Desempilhar(); 
        // Insere um elemento na pilha.
        void Empilhar(const Dado& d);
        // Apagar todos os dados da pilha.
        void LimparTudo();
        // Imprime o valor que está no topo sem desempilhar.
        inline void Topo();
        // Informa se a pilha está Vazia.
        inline bool Vazia();
        // Informa se a pilha está Cheia.
        inline bool Cheia();
        void Buscar(int var1, int var2);
};

Pilha::Pilha(){
    mPilha = new Dado[TAMANHOPILHA]; // aloca dinamicamente o vetor
    posTopo = PILHAVAZIA; // a posição para lista vazia é -1
}

Pilha::~Pilha() {
    delete[] mPilha; // desaloca-se o vetor
    posTopo = PILHAVAZIA;
}

Dado Pilha::Desempilhar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!"); // a pilha está vazia

    // extrai o dadi do vetor
    Dado dado = mPilha[posTopo];
    // decrementa o vetor
    posTopo--;
    return dado;
}

void Pilha::Empilhar(const Dado& d) {
    if (this->Cheia()) throw runtime_error("Erro: pilha cheia!"); // a pilha está cheia
    
    // incrementa o vetor (o primeiro valor é -1)
    posTopo++;
    // guardamos o dado na posição do topo
    mPilha[posTopo] = d;
}

void Pilha::LimparTudo() {
    // enquanto não estiver vazia irá desempilhar
    while (not Vazia()) {
        Desempilhar();
    }
}

void Pilha::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!"); // a pilha está vazia
    
    // imprime os dados do topo sem desempilhá-lo
    Dado dado = mPilha[posTopo];
    imprimir_dado(dado);
}

bool Pilha::Vazia() {
    // só está vazia se a posição do topo da pilha for igual a -1
    return (posTopo == PILHAVAZIA);
}

bool Pilha::Cheia() {
    // só está vazia se a posição do topo da pilha for igual a 5
    return ((posTopo + 1) == TAMANHOPILHA);
}

void Pilha::Buscar(int var1, int var2){
	Pilha aux;
	Dado dado;
	
	while (not Vazia()) {
        dado = Desempilhar();
        
        if ((dado.valor > var1) and (dado.valor < var2)){
			imprimir_dado(dado);
		}
		
		aux.Empilhar(dado);
    }
    
    while (not aux.Vazia()) {
        dado = aux.Desempilhar();
		Empilhar(dado);
    }
}

int main() {
    Pilha pilha;
    Dado info;
    char comando;
    int var1, var2;
    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.tipo >> info.valor;
                    pilha.Empilhar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(pilha.Desempilhar());
                    break;
                case 'l': // limpar tudo
                    pilha.LimparTudo();
                    break;
                case 'e': // espiar 
                    if(!pilha.Vazia())               
                        pilha.Topo();
                    else
                        cout << "Erro: pilha vazia!"<< endl;
                    break;
                case 'b': // espiar 
                    cin >> var1 >> var2;
                    pilha.Buscar(var1, var2);
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
    while (not pilha.Vazia()) {
        imprimir_dado(pilha.Desempilhar());
    }
    cout << endl;
    return 0;
}
