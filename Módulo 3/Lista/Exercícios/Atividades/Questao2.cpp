/* 
 * Classe listadup, uma lista dinamicamente duplamente encadeada
 * 
 * by Joukim, 2017-2019, Estruturas de Dados
 * alterado em 2023 by Renato
 * alterado em 2023 by Marcos
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
friend class listadup;
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
class listadup {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista    
public:
    listadup();
    listadup(const listadup& umaLista);
    ~listadup();
    // sobrecarga do operador de atribuição
    listadup& operator=(const listadup& umaLista);  
    // inserção, remoção e procura
    void insere(acaoPrograma acao);
    void insereNoFim(acaoPrograma acao);
    void insereNoInicio(acaoPrograma acao);
    void insereNaPosicao(int posicao, acaoPrograma acao);
    int procura(string valor); // retorna a posicao
    void imprime();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};


// constrói uma lista inicialmente vazia
listadup::listadup() {
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

// construtor de cópia
listadup::listadup(const listadup& umaLista) {
	primeiro = NULL;
	ultimo = NULL;
    tamanho = 0;

	// percorre a lista recebida como parâmetro, copiando os dados
	noh* aux = umaLista.primeiro;
	
	while (aux != NULL) {
		insereNoFim(aux->acao);
		aux = aux->proximo;
	}
}

// destrutor da lista (chama função privada auxiliar)
listadup::~listadup( ) {
    removeTodos();
}    

// remove todos os elementos da lista
void listadup::removeTodos( ) {
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
listadup& listadup::operator=(const listadup& umaLista){
    // limpa a lista atual
    removeTodos();
     // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->acao);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

inline void listadup::insere(acaoPrograma acao) {
    insereNoFim(acao);
}

// insere por no final da lista
void listadup::insereNoFim(acaoPrograma acao) {
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
void listadup::insereNoInicio(acaoPrograma acao) {
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
void listadup::insereNaPosicao(int posicao, acaoPrograma acao){
    // * primeiro criamos um nó
	noh* novo = new noh(acao);

	// * agora inserimos o nó na lista
	// verificamos antes se é possível inserir na posição
	if ((posicao <= tamanho) && (posicao >= 0)) {
		if (vazia()) { // ou (primeiro == NULL) ou (tamanho == 0)
			primeiro = novo;
			ultimo = novo;
		} else if (posicao == 0) { // insere no inicio
			novo->proximo = primeiro;
            primeiro->anterior = novo;
			primeiro = novo;
		} else if (posicao == tamanho) { // insere no fim
			ultimo->proximo = novo;
            novo->anterior = ultimo;
			ultimo = novo;
		} else { // insere no meio da lista
			noh* aux = primeiro;
			int posAux = 0;

			//chegando na posição da lista
			while (posAux < (posicao - 1)) {
				aux = aux->proximo;
				posAux++;
			}
			novo->proximo = aux->proximo;
			aux->proximo->anterior = novo;
			aux->proximo = novo;
			novo->anterior = aux;
		}
	tamanho++;
	} else {
		throw runtime_error("Posição Inexistente!");
	}
}
                   

int listadup::procura(string valor) {
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
void listadup::imprime() {
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
inline bool listadup::vazia() {
    return (tamanho == 0);
}

void listadup::removeNoInicio() {
    if (vazia()) {
		throw runtime_error("Remoção em lista vazia!");
	} else {
        noh* removido = primeiro;
        // acaoPrograma retorno = removido->acao;
        primeiro = primeiro->proximo;
        if (primeiro != NULL){
            primeiro->anterior = NULL;
        }
        delete removido;

        tamanho--;
        if (vazia()) {
            primeiro = NULL;
        }

        // return retorno;
    }
}


void listadup::removeNoFim() {
    if (vazia()) {
		throw runtime_error("Remoção em lista vazia!");
	} else {
        noh* removido = ultimo;
        // acaoPrograma retorno = removido->acao;
        ultimo = ultimo->anterior;
        if (ultimo != NULL){
            ultimo->proximo = NULL;
        }
        delete removido;

        tamanho--;
        if (vazia()) {
            ultimo = NULL;
        }

        // return retorno;
    }
}


int main() {
    listadup minhaLista;
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
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': // inserir
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNoFim(info);
                    break;             
                case 'm': // inserir
                    cin >> posicao;
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNaPosicao(posicao,info);
                    break;             
                case 's': // procurar
                    cin >> nomeEquipe;
                    posicao = minhaLista.procura(nomeEquipe);
                    if(posicao == -1)
                        cout << "Nao encontrado"<< endl;
                    else
                        cout << posicao << endl;
                    break;                    
                case 'r': // remover
                    minhaLista.removeNoInicio();
                    break;
                case 'a': // remover
                    minhaLista.removeNoFim();
                    break;                                   
                case 'p': // limpar tudo
                    minhaLista.imprime();
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