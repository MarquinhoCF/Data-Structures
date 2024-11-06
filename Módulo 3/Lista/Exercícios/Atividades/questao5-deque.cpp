/* 
 * Classe deque, uma lista dinamicamente duplamente encadeada
 * 
 * by Joukim, 2017-2019, Estruturas de Dados
 * alterado em 2023 by Renato
 */

#include <iostream>
#include <cstdlib>

using namespace std;

struct acaoPrograma{
    int identificador;
    string nomeAcao;
    int tempoExecucao; 
    int tempoConsumido;
};


class noh {
friend class deque;
private: 
    acaoPrograma acao; // poderia ser outro tipo de variável
    noh* proximo;
    noh* anterior;
public:
    //noh();
    noh(acaoPrograma d);
};

// construindo dado chamando seu construtor
noh::noh(acaoPrograma d){
    acao = d;
    proximo = NULL;
    anterior = NULL;
}


// lista dinamicamente encadeada
class deque {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista    
public:
    deque();
    deque(const deque& umaDeque);
    ~deque();
    // sobrecarga do operador de atribuição
    deque& operator=(const deque& umaDeque);  
    // inserção, remoção e procura
    void insere(acaoPrograma acao);
    void insereNoFim(acaoPrograma acao);
    void insereNoInicio(acaoPrograma acao);
    void insereNaPosicao(int posicao, acaoPrograma acao);
    int procura(string valor); // retorna a posicao
    void imprime();
    inline bool vazia();
    acaoPrograma removeNoFim();
    acaoPrograma removeNoInicio();
};


// constrói uma lista inicialmente vazia
deque::deque() {
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

// construtor de cópia
deque::deque(const deque& umaDeque) {
	primeiro = NULL;
	ultimo = NULL;
    tamanho = 0;

	// percorre a lista recebida como parâmetro, copiando os dados
	noh* aux = umaDeque.primeiro;
	
	while (aux != NULL) {
		insereNoFim(aux->acao);
		aux = aux->proximo;
	}
}

// destrutor da lista (chama função privada auxiliar)
deque::~deque( ) {
    removeTodos();
}    

// remove todos os elementos da lista
void deque::removeTodos( ) {
    noh* aux = primeiro;
	noh* temp = NULL;

	while (aux != NULL) {
		temp = aux;
		aux = aux->proximo;
		delete temp;
	}

	//redirecionamento de ponteiros
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}    

// sobrecarga do operador de atribuição
deque& deque::operator=(const deque& umaDeque){
    // limpa a lista atual
    removeTodos();
     // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaDeque.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->acao);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

inline void deque::insere(acaoPrograma acao) {
    insereNoFim(acao);
}

// insere por no final da lista
void deque::insereNoFim(acaoPrograma acao) {
    // * primeiro criamos um nó
	noh* novo = new noh(acao);

	// * agora inserimos o nó na lista
	// se a lista estiver vazia, inserimos o primeiro nó
	if (vazia()) { // ou (primeiro == NULL) ou (tamanho == 0)
		primeiro = novo;
		ultimo = novo;
	} else { // já tem elementos na lista insere no final
		ultimo->proximo = novo;
		novo->anterior = ultimo;
		ultimo = novo;
	}
	tamanho++;
}

// insere no início da lista
void deque::insereNoInicio(acaoPrograma acao) {
    // * primeiro criamos um nó
	noh* novo = new noh(acao);

	// * agora inserimos o nó na lista
	// se a lista estiver vazia, inserimos o primeiro nó
	if (vazia()) { // ou (primeiro == NULL) ou (tamanho == 0)
		primeiro = novo;
		ultimo = novo;
	} else { // já tem elementos na lista insere no início
		novo->proximo = primeiro;
		primeiro->anterior = novo;
		primeiro = novo;
	}
	tamanho++;
}

// insere em uma determinada posição da lista
void deque::insereNaPosicao(int posicao, acaoPrograma acao){
    cout << "Operação não permitida!" << endl;
}             

int deque::procura(string valor) {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } else {
        noh* aux = primeiro;

        int posAux = 0;

        while ((aux != NULL) && (aux->acao.nomeAcao != valor)) {
            posAux++;
            aux = aux->proximo;
        }

        if (aux == NULL) {
            posAux = - 1;
        }
        return posAux;
    }
}

// método básico que *percorre* uma lista, imprimindo seus elementos
void deque::imprime() {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } else {
        noh* aux = primeiro;

        while (aux != NULL) {
            cout << "(" << aux->acao.identificador << ", ";
            cout << aux->acao.nomeAcao << ", ";
            cout << aux->acao.tempoExecucao << ", ";
            cout << aux->acao.tempoConsumido << ")" << endl;
            aux = aux->proximo;
        }

        cout << " IMPRIMINDO REVERSO " << endl;

        aux = ultimo;
        while (aux != NULL) {
            cout << "(" << aux->acao.identificador << ", ";
            cout << aux->acao.nomeAcao << ", ";
            cout << aux->acao.tempoExecucao << ", ";
            cout << aux->acao.tempoConsumido << ")" << endl;
            aux = aux->anterior;
        }
    }
}

// verifica se a lista está vazia
inline bool deque::vazia() {
    return (tamanho == 0);
}

acaoPrograma deque::removeNoInicio() {
    if (vazia()) {
		throw runtime_error("Remoção em lista vazia!");
	} else {
        noh* removido = primeiro;
        acaoPrograma retorno = removido->acao;
        primeiro = primeiro->proximo;
        if (primeiro != NULL){
            primeiro->anterior = NULL;
        }
        delete removido;

        tamanho--;
        if (vazia()) {
            primeiro = NULL;
        }

        return retorno;
    }
}


acaoPrograma deque::removeNoFim() {
    if (vazia()) {
		throw runtime_error("Remoção em lista vazia!");
	} else {
        noh* removido = ultimo;
        acaoPrograma retorno = removido->acao;
        ultimo = ultimo->anterior;
        if (ultimo != NULL){
            ultimo->proximo = NULL;
        }
        delete removido;

        tamanho--;
        if (vazia()) {
            ultimo = NULL;
        }

        return retorno;
    }
}

bool removeElementQualq(deque& umaDeque, string nomeEquipe) {
	if (umaDeque.vazia()) {
		throw runtime_error("Remoção em lista vazia!");
	} else {
		deque Aux;
		acaoPrograma dado;
		
		bool retirou = false;
		while (not umaDeque.vazia()) {
			dado = umaDeque.removeNoInicio();
			if (dado.nomeAcao == nomeEquipe) {
				retirou = true;
			} else {
				Aux.insereNoFim(dado);
			}
		}
		
		while (not Aux.vazia()) {
			dado = Aux.removeNoInicio();
			umaDeque.insereNoFim(dado);
		}
		
		return retirou;
	}
}


int main() {
    deque minhaDeque;
    acaoPrograma info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaDeque.insereNoInicio(info);
                    break;
                case 'h': // inserir
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaDeque.insereNoFim(info);
                    break;             
                case 'm': // inserir
                    cin >> posicao;
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaDeque.insereNaPosicao(posicao,info);
                    break;             
                case 's': // procurar
                    cin >> nomeEquipe;
                    posicao = minhaDeque.procura(nomeEquipe);
                    if(posicao == -1)
                        cout << "Nao encontrado"<< endl;
                    else
                        cout << posicao << endl;
                    break;                    
                case 'r': // remover
                    minhaDeque.removeNoInicio();
                    break;
                case 'a': // remover
                    minhaDeque.removeNoFim();
                    break;                                   
                case 'p': // limpar tudo
                    minhaDeque.imprime();
                    break;
                case 'x':
					cin >> nomeEquipe;
					if (not (removeElementQualq(minhaDeque, nomeEquipe))) {
						cout << "Nao encontrado"<< endl;
					}
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
    cout << endl;
    return 0;
}
