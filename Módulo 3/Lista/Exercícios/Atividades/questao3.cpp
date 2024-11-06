/* 
 * Classe lista, uma lista dinamicamente encadeada
 * 
 * by Joukim, 2017-2019, Estruturas de Dados
 * alterado em 2023 by Renato
 * alterado em 2023 by Marcos
 */

#include <iostream>
#include <cstdlib>

using namespace std;

struct equipe{
    string nomeEquipe;
    string lider;
    string linguagem; 
    int qtdMembros;
};

class noh {
friend class lista;
private:
    equipe elenco; // poderia ser outro tipo de variável
    noh* proximo;
public:
    //noh();
    noh(equipe d);
};

// construindo time chamando seu construtor
noh::noh(equipe d){
    elenco = d;
    proximo = NULL;
}


// lista dinamicamente encadeada
class lista {
private:
    noh* primeiro;
    //noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
     // imprime reverso a partir de um nó -> exemplo de uso de recursão
    void imprimeReversoAux(noh* umNoh);
public:
    // construtores e destrutor
    lista();
    lista(const lista& umaLista);
    ~lista();
    // sobrecarga do operador de atribuição
    lista& operator=(const lista& umaLista);  
    // inserção, remoção e procura
    inline void insere(equipe elenco);
    void insereListaVazia(equipe elenco);
    void insereNoFim(equipe elenco);
    void insereNoInicio(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);
    int procura(string valor); // retorna a posição do nó com va
    // métodos adicionais (impressão, vazia)
    void imprime();
    void imprimeReverso();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
    int getTamanho();
};


// constrói uma lista inicialmente vazia
lista::lista() {
    primeiro = NULL;
    //ultimo = NULL;
    tamanho = 0;
}

// construtor de cópia
lista::lista(const lista& umaLista) {
    primeiro = NULL;
    //ultimo = NULL;
    tamanho = 0;

    // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;  
    }
}

// destrutor da lista (chama função privada auxiliar)
lista::~lista( ) {
    removeTodos();
}    

// remove todos os elementos da lista
void lista::removeTodos( ) {
    noh* aux = primeiro;
	noh* temp;

	while (aux != NULL) {
		temp = aux;
		aux = aux->proximo;
		delete temp;
	}

	//redirecionamento de ponteiros
	tamanho = 0;
	primeiro = NULL;
	//ultimo = NULL;
}    

// sobrecarga do operador de atribuição
lista& lista::operator=(const lista& umaLista){
    // limpa a lista atual
    removeTodos();
    // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

inline void lista::insere(equipe elenco){
    insereNoFim(elenco);
}

void lista::insereListaVazia(equipe elenco){
    noh* novo = new noh(elenco); // cria um nó com o valor
    primeiro = novo;
    //ultimo = novo;
    tamanho = 1;
}

// insere no final da lista
void lista::insereNoFim(equipe elenco) {
    if (vazia()) { 
        insereListaVazia(elenco);
    } else {
        noh* novo = new noh(elenco); // cria um nó com o valor
		noh* aux = primeiro;

		while (aux->proximo != NULL) {
			aux = aux->proximo;
		}
        
        aux->proximo = novo;
        tamanho++;
    }
}

// insere no início da lista
void lista::insereNoInicio(equipe elenco) {
    if (vazia()) { 
        insereListaVazia(elenco);
    } else {
        noh* novo = new noh(elenco); // cria um nó com o valor
        novo->proximo = primeiro;
        primeiro = novo;
        tamanho++;
    }
}

// insere em uma determinada posição da lista
void lista::insereNaPosicao(int posicao, equipe elenco){
	// * primeiro criamos um nó
	noh* novo = new noh(elenco);

	// * agora inserimos o nó na lista
	// verificamos antes se é possível inserir na posição
	if ((posicao <= tamanho) && (posicao >= 0)) {
		if (vazia()) {
			primeiro = novo;
			//ultimo = novo;
		} else if (posicao == 0) { // insere no inicio
			novo->proximo = primeiro;
			primeiro = novo;
		} else if (posicao == tamanho) { // insere no fim
			insereNoFim(elenco);
		} else { // insere no meio da lista
			noh* aux = primeiro;
			int posAux = 0;

			//chegando na posição da lista
			while (posAux < (posicao - 1)) {
				aux = aux->proximo;
				posAux++;
			}
			novo->proximo = aux->proximo;
			aux->proximo = novo;
		}
	tamanho++;
	} else {
        throw runtime_error("Posição Inexistente!");
	}
}

//procura a posição de um determinado elemento
int lista::procura(string valor) {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } else {
        noh* aux = primeiro;

        int posAux = 0;

        while ((aux != NULL) && (aux->elenco.nomeEquipe != valor)) {
            posAux++;
            aux = aux->proximo;
        }

        if (aux == NULL) {
            throw runtime_error("Nao encontrado");
        }
        return posAux;
    }
}


// método básico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void lista::imprime() {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } else {
        noh* aux = primeiro;

        while (aux != NULL) {
            cout << "(" << aux->elenco.nomeEquipe << ", ";
            cout << aux->elenco.lider << ", ";
            cout << aux->elenco.linguagem << ", ";
            cout << aux->elenco.qtdMembros << ")" << endl;
            aux = aux->proximo;
        }
    }
}

// verifica se a lista está vazia
inline bool lista::vazia() {
    return (primeiro == NULL);
}
   
void lista::removeNoFim() {
    if (vazia()) {
        throw runtime_error("Remoção em lista vazia!");
	}

	noh* aux = primeiro;
	noh* anterior = NULL;

	while (aux->proximo != NULL) {
		anterior = aux;
		aux = aux->proximo;
	}
    
    // paramos no último nó da lista
	// equipe retorno = aux->elenco;
	// precisa tratar remoção de lista com um único elemento
	// se anterior continua nulo, lista só tinha um elemento
	if (anterior == NULL) {
   	    primeiro = NULL;  
	} else {
	    anterior->proximo = NULL;
    } 

	// remove o último nó da lista
    delete aux;

	tamanho--;

	//return retorno;
}
    
void lista::removeNoInicio() {
    if (vazia()){
        throw runtime_error("Remoção em lista vazia!");
    } else {
        noh* aux = primeiro;
        equipe retorno = aux->elenco;
        primeiro = aux->proximo;
        delete aux;
        tamanho--;

        /*if (vazia()) {
            ultimo = NULL;
        }*/

        //return retorno;
    }
}


int main() {
    lista minhaLista;
    equipe info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': // inserir
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoFim(info);
                    break;             
                case 'm': // inserir
                    cin >> posicao;
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNaPosicao(posicao,info);
                    break;             
                case 's': // remover
                    cin >> nomeEquipe;
                    cout << minhaLista.procura(nomeEquipe) <<endl;
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
