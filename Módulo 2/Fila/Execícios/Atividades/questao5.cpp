/* Classe fila estatica
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 * 
 * modified by Marcos Carvalho Ferreira, 2023
 * 
 */
#include <iostream>

using namespace std;

const int FILAVAZIA = -1;
const int CAPACIDADE_FILA = 6;

struct Dado {
    string nome;
    string assunto;
    char tipo;
    int nProcesso;
};

// Imprime informações de um dado qualquer.
void imprimir_dado(const Dado& umDado){
   cout << "Nome: " << umDado.nome << " Assunto: " << umDado.assunto << " Tipo: " << umDado.tipo << " Processo: " << umDado.nProcesso << endl;
}

class Fila {
    private:
        Dado* mFila;
        int posPrimeiro, posUltimo, mTamanho;
    public:
        // Constrói fila vazia.
        Fila();
        // Destrutor que desaloca memória.
        ~Fila();
        // Retira e retorna o elemento que estiver na primeira posição.
        Dado Desenfileirar(); 
        // Insere um elemento na fila.
        void Enfileirar(const Dado& d);
        // Apagar todos os dados da fila.
        void LimparTudo();
        // Imprime os valores do elemento que está na frente da fila, sem Desenfileirar.
        inline void PrimeiroDaFila();
        // Informa se a fila está Vazia.
        inline bool Vazia();
        // Informa se a fila está Cheia.
        inline bool Cheia();
        void Ordenar();
};

Fila::Fila(){
    posPrimeiro = FILAVAZIA;
    posUltimo = FILAVAZIA;
    mFila = new Dado[CAPACIDADE_FILA];
    mTamanho = 0;
}

Fila::~Fila() {
    // para destruir a fila desalocamos o espaço alocado
    delete[] mFila;
}

Dado Fila::Desenfileirar() {
    if (this->Vazia()) throw runtime_error("Erro: fila vazia!");
    
    // obtemos o dado do primeiro
    Dado Aux = mFila[posPrimeiro];
    if (posPrimeiro == posUltimo) { // Removeu último elemento da fila: Colocamos valores inválidos para a posição
        posUltimo = -1;
        posPrimeiro = -1;
    } else { // Não é último elemento da fila. Incrementamos a posição e tratamos para ser uma fila circular
        posPrimeiro = (posPrimeiro + 1) % CAPACIDADE_FILA;
    }
    mTamanho--;
    return Aux;
}

void Fila::Enfileirar(const Dado& d) {
    if (this->Cheia()) throw runtime_error("Erro: fila cheia!");
      
    if (posPrimeiro == FILAVAZIA) { // Se a fila estava vazia precisamos validar a posição do Primeiro dado
        posPrimeiro++;
    }
    posUltimo = (posUltimo + 1) % CAPACIDADE_FILA; // Incrementamos a posição e tratamos para ser uma fila circular
    mFila[posUltimo] = d; // Armazenamos o dado no vetor na nova posição do último calculada
    mTamanho++;
}


void Fila::LimparTudo() {
    // enquanto não estiver vazia irá desenfileirar
    while (not (this->Vazia())){
        Desenfileirar();
    }
}

void Fila::PrimeiroDaFila() {
    if (this->Vazia()) throw runtime_error("Erro: fila vazia!");
         
    // imprime os dados do topo sem desemfileirá-lo
    Dado dado = mFila[posPrimeiro];
    imprimir_dado(dado);
}

bool Fila::Vazia() {
    // só está vazia se as posições do primeiro e do últimp forem iguais a FILAVAZIA
    return (mTamanho == 0);
}

bool Fila::Cheia() {
    // Como a fila é circular ela só estará cheia se uma dessas 2 condições forem verdadeiras
    return (mTamanho == CAPACIDADE_FILA);
}

void Fila::Ordenar(){	
	Fila aux, resultante;
	Dado dado1, dado2, dadoFinal;
	
	if (this->Vazia()) throw runtime_error("Erro: fila vazia!");
	
	if (mTamanho != 1) {
		
		while (not Vazia()) {
			dado1 = Desenfileirar();
			while (not Vazia()) {
				dado2 = Desenfileirar();
				
				if (dado1.nProcesso > dado2.nProcesso) {
					aux.Enfileirar(dado1);
					dado1 = dado2;
				} else {
					aux.Enfileirar(dado2);
				}
				
				if (mTamanho == 0) {
					resultante.Enfileirar(dado1);
				}
			}
			
			while (not aux.Vazia()) {
				dado1 = aux.Desenfileirar();
				Enfileirar(dado1);
			}
		}
		
		dadoFinal = dado1;
		
		while (not resultante.Vazia()) {
			dado1 = resultante.Desenfileirar();
			Enfileirar(dado1);
		}
		
		Enfileirar(dadoFinal);
	}
}


int main() {
    Fila fila;
    Dado info;
    char comando;
    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.assunto >> info.tipo >> info.nProcesso;
                    fila.Enfileirar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(fila.Desenfileirar());
                    break;
                case 'l': // limpar tudo
                    fila.LimparTudo();
                    break;
                case 'e': // espiar 
                    if(!fila.Vazia())                
                        fila.PrimeiroDaFila();
                    else
                        cout << "Erro: fila vazia!"<< endl;
                    break;
                case 'o': // ordenar
                    fila.Ordenar();
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
