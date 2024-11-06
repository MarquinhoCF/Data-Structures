/* Classe Fila encadeada
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
    string premio;
    char tipo;
    int tempo;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Dado& umDado) {
    cout << "Nome: " << umDado.nome << " Premio: " << umDado.premio << " Tipo: " << umDado.tipo << " tempo: " << umDado.tempo << endl;
}

class Noh {
    friend class Fila;
    private:
        Dado mDado; // poderia ser outro tipo de variável
        Noh* mProx;
    public:
        Noh(Dado v) {
            mDado = v;
            mProx = NULL;
        }        
};

class Fila {
    public:
        // Constrói Fila vazia.
        Fila();
        // Destrutor que desaloca memória.
        ~Fila();
        // Retira e retorna o elemento que estiver na frente da Fila.
        // Escreve uma mensagem de erro se não for possível desenfileirar.
        Dado Desenfileirar(); 
        // Insere um elemento na Fila.
        void Enfileirar(const Dado& d);
        // Apagar todos os dados da Fila.
        void LimparTudo();
        // Retorna o elemento que está na frente da Fila, sem desenfileirar.
        inline void Primeiro();
        // Informa se a Fila está Vazia.
        inline bool Vazia();
        void Contabilizar(int valor);
    private:
        Noh* mPtrPrimeiro;
        Noh* mPtrUltimo;
        int mTamanho;
};

Fila::Fila() {
    mPtrPrimeiro = NULL;
    mPtrUltimo = NULL;
    mTamanho = 0;
}

Fila::~Fila() {
    // para destruir a fila limpa-se tudo
    LimparTudo();
}

Dado Fila::Desenfileirar() {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");
    
    // obtemos o dado do primeiro
    Dado dado = mPtrPrimeiro->mDado;
    // Criamos um noh temporario que guarda a posição do primeiro
    Noh* temporario = mPtrPrimeiro;
    // Movemos o ponteiro para o proximo do antigo primeiro noh
    mPtrPrimeiro = temporario->mProx;
    // Desalocamos o no temporario
    delete temporario;
    // Decrementamos o tamanho
    mTamanho--;
    // Se a fila fica vazia presimos inválidar o ponteiro do primeiro
    if (Vazia()){
        mPtrPrimeiro = NULL;
    }
    return dado; // retornamos o dado obtido
}

void Fila::Enfileirar(const Dado& d) {
    // Criamos um novo no
    Noh* novo = new Noh(d);
    if (Vazia()){ // Se a fila estava vaia precisamos validar o primeiro ponteiro
        mPtrPrimeiro = novo;
    } else { // Se a fila não estava vaia atualizamos o ponteiro 'proximo' do antigo ultimo noh
        mPtrUltimo->mProx = novo;
    }
    mPtrUltimo = novo; // O ponteiro do ultimo recebe o endereço do novo noh
    mTamanho++; // Incrementamos o tamanho
}

void Fila::LimparTudo() {
     // enquanto não estiver vazia irá desenfileirar
    while (not (this->Vazia())){
        Desenfileirar();
    }
}

void Fila::Primeiro() {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");
    
    // imprime os dados do ponteiro do início sem desempilhá-lo
    Dado dado = mPtrPrimeiro->mDado;
    imprimir_dado(dado);
}

bool Fila::Vazia() {
    // só está vazia se o tamanho da fila for igual a 0
    return (mTamanho == 0);
}

void Fila::Contabilizar(int valor) {
	int soma = 0;
	bool para = false;
	Dado dado;
	Fila Aux;
	
	while (!para) {
		dado = Desenfileirar();
		soma += dado.tempo;
		if (soma < valor) {
			imprimir_dado(dado);
		} else {
			para = true;
			
			Aux.Enfileirar(dado);
			while (not Vazia()){
				dado = Desenfileirar();
				Aux.Enfileirar(dado);
			}
			
			while (not Aux.Vazia()){
				dado = Aux.Desenfileirar();
				Enfileirar(dado);
			}
		}
	}
}

int main() {
    Fila fila;
    Dado info;
    char comando;
    int n;
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.premio >> info.tipo >> info.tempo;
                    fila.Enfileirar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(fila.Desenfileirar());
                    break;
                case 'l': // limpar tudo
                    fila.LimparTudo();
                    break;
                case 'e': // espiar                
                    fila.Primeiro();
                    break;
                case 't':
					cin >> n;
					fila.Contabilizar(n);
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
    while (not fila.Vazia()) {
        imprimir_dado(fila.Desenfileirar());
    }
    cout << endl;
    return 0;
}
