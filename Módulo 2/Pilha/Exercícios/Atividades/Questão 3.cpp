/* Classe pilha encadeada
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 * 
 * modified by Marcos Carvalho Ferreira, 2023
 * 
 */
#include <iostream>
#include <stdexcept>

using namespace std;

struct Dado {
    string nome;
    char tipo;
    int valor;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Dado& umDado) {
    cout << "Nome: " << umDado.nome << " Tipo: " << umDado.tipo << " Valor: " << umDado.valor << endl;
}

class Noh {
    friend class Pilha;
    private:
        Dado mDado; // poderia ser outro tipo de variável
        Noh* mProx;
    public:
        Noh(Dado v) {
            mDado = v;
            mProx = NULL;
        }        
};

class Pilha {
    public:
        // Constrói pilha vazia.
        Pilha();
        // Destrutor que desaloca memória.
        ~Pilha();
        // Retira e retorna o valor que estiver no mPtTopo da pilha.
        // Escreve uma mensagem de erro se não for possível desempilhar.
        Dado Desempilhar(); // retorna o mPtTopo da Pilha.
        // Insere um valor na pilha.
        void Empilhar(const Dado& d);
        // Apagar todos os dados da pilha.
        void LimparTudo();
        // Imprime o valor que está no mPtTopo sem desempilhar.
        inline void Topo();
        // Informa se a pilha está Vazia.
        inline bool Vazia();
        void Ordenar();
    private:
        Noh* mPtTopo;
        int mTam;
};

Pilha::Pilha() {
    mPtTopo = NULL;
    mTam = 0;
}

Pilha::~Pilha() {
    // para destruir a pilha limpa-se tudo
    LimparTudo();
}

Dado Pilha::Desempilhar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!"); // a lista está vazia
    
    // extraímos o dado do topo
    Dado dado = mPtTopo->mDado;
    // criamos um nó temporario que aponta para o topo da pilha
    Noh* temporario = mPtTopo;
    // atribuimos o nó topo ao proximo nó
    mPtTopo = mPtTopo->mProx;
    // desalocamos o nó temporario
    delete temporario;
    // decrementamos o tanho da pilha
    mTam--;

    return dado;
}

void Pilha::Empilhar(const Dado& d) {
    // criamos um novo nó com o dado fornecido
    Noh* novo = new Noh(d);
    // atribui-se o topo ao próximo nó da pilha para garantir encadeamento
    novo->mProx = mPtTopo;
    // o topo recebe o novo nó
    mPtTopo = novo;
    // a pilha aumenta de tamanho
    mTam++;
}

void Pilha::LimparTudo() {
    // enquanto não estiver vazia irá desempilhar
    while (not Vazia()) {
        Desempilhar();
    }
}

void Pilha::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!"); // a lista está vazia
    
    // imprime os dados do topo sem desempilhá-lo
    Dado dado = mPtTopo->mDado;
    imprimir_dado(dado);
}

bool Pilha::Vazia() {
    // só está vazia se o tamnho da pilha for igual a 0
    return (mTam == 0);
}

void Pilha::Ordenar(){	
	Pilha aux;
	Dado dado1, dado2;
	
	for (int i = 0; i < mTam; i++){
		while (not Vazia()){
			dado1 = Desempilhar();
			if (not Vazia()){
				dado2 = Desempilhar();
				
				if (dado1.valor < dado2.valor){
					aux.Empilhar(dado1);
					Empilhar(dado2);
				} else {
					Empilhar(dado1);
					aux.Empilhar(dado2);
				}
			} else {
				aux.Empilhar(dado1);
			}
		}
		
		do {
			dado1 = aux.Desempilhar();
			Empilhar(dado1);
		} while (not aux.Vazia());
	}
}

int main() {
    Pilha pilha;
    Dado info;
    char comando;
    do {
        try{
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
                    pilha.Topo();
                    break;
                case 'o': // ordenar              
                    pilha.Ordenar();
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
