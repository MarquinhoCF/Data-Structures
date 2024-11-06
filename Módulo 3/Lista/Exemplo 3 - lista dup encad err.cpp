#include <iostream>
#include <cstdlib>
#include <stdexcept>

using namespace std;

// para facilitar a troca de int para outro tipo
// estamos criando um apelido para int chamado Dado
// - comisso destaca-se que a lista pode ser uma
// lista de qualquer objeto, não apenas inteiros...
// ou seja: é uma lista de dados
typedef int Dado; // typedef permite criar 

class noh {
	friend class listadup;
	private:
    /* Dado está como uma constante para não permitir alteração */
		const Dado dado;
		noh* proximo;
		noh* anterior;
		
	public:
		//noh();
		noh(Dado d = 0);
};

// construindo dado chamando construtor
// note o uso de inicialização em lista, já que o dado é atributo cosntante
noh::noh(Dado d) : dado(d) {
	proximo = NULL;
	anterior = NULL;
}

class listadup {
	private:
		noh* primeiro;
		noh* ultimo;
		int tamanho;
		void removeTodos(); // remove todos os elementos da lista
		
	public:
	// construtores e destrutor
		listadup();
		listadup(const listadup& umaLista);
		~listadup();
		// sobregcarga do operador de atribuição
		listadup& operator=(const listadup& umalista);
		// inserção e remoção e procura
		inline void insere(Dado dado);
		void insereNoFim(Dado dado);
		void insereNoInicio(Dado dado);
		void insereNaPosicao(int posicao, Dado dado);
		bool procura(Dado valor, int& posicao); // retorna a posição do nó com valor indicado
		// métodos adicionais (impressão, vazia)
		void imprime();
		inline bool vazia();
		void removeNoFim();
		void removeNoInicio();
		void removeValor(Dado dado);
};

listadup::listadup() {
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}

// construtor de cópia
listadup::listadup(const listadup& umaLista) {
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;

	// percorre a lista recebida como parâmetro, copiando os dados
	noh* aux = umaLista.primeiro;
	
	while (aux != NULL) {
		insereNoFim(aux->dado);
		aux = aux->proximo;
	}
}

// destrutor da lista (chama função privada auxiliar)
listadup::~listadup() {
	removeTodos();
}

// remove todos os elementos da lista
void listadup::removeTodos() {
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
	ultimo = NULL;
}

// sobrecarga do operador de atribuição
listadup& listadup::operator=(const listadup& umalista) {
	//limpa a lista
	removeTodos();

	// percorre a lista recebida como parâmetro, copiando os dados
	noh* aux = umalista.primeiro;

	while (aux != NULL) {
		insereNoFim(aux->dado);
		aux = aux->proximo;
	}

	return *this;
}

// insere por padrão no final da lisat
void listadup::insere(Dado dado) {
	insereNoFim(dado);
}

// insere no final da lista
void listadup::insereNoFim(Dado dado) {
	// * primeiro criamos um nó
	noh* novo = new noh(dado);

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
void listadup::insereNoInicio(Dado dado) {
	// * primeiro criamos um nó
	noh* novo = new noh(dado);

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
void listadup::insereNaPosicao(int posicao, Dado dado) {
	// * primeiro criamos um nó
	noh* novo = new noh(dado);

	// * agora inserimos o nó na lista
	// verificamos antes se é possível inserir na posição
	if ((posicao <= tamanho) and (posicao >= 0)) {
		if (vazia()) { // ou (primeiro == NULL) ou (tamanho == 0)
			primeiro = novo;
			ultimo = novo;
		} else if (posicao == 0) { // insere no inicio
			novo->proximo = primeiro;
			primeiro = novo;
		} else if (posicao == 0) { // insere no inicio
			novo->proximo = primeiro;
			primeiro = novo;
		} else if (posicao == tamanho) { // insere no fim
			ultimo->proximo = novo;
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
		throw runtime_error("Erro: posicao inexistente!");
	}
}

bool listadup::procura(Dado dado, int& posicao) {
	noh* aux = primeiro;

	posicao = 0;

	while ((aux != NULL) and (aux->dado != dado)) {
		posicao++;
		aux = aux->proximo;
	}

	if (aux == NULL) {
		posicao = -1;
        return false;
	} else {
        return true;
    }
}

// método básico que *percorre*uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void listadup::imprime() {
	noh* aux = primeiro;

	while (aux != NULL) {
		cout << aux->dado << " ";
		aux = aux->proximo;
	}
	cout << endl;

	// imprime reverso (para mostrar duplo encadeamento)
	aux = ultimo;
	while (aux != NULL) {
		cout << aux->dado << " ";
		aux = aux->anterior;
	}
	cout << endl;
}

void listadup::removeNoFim() {
	if (vazia()) {
		cerr << "Remocao em lista vazia!!" << endl;
		exit(EXIT_FAILURE);
	}

	noh* removido = ultimo;
	ultimo = ultimo->anterior;
	if (ultimo != NULL){
		ultimo->proximo = NULL;
	}
	ultimo->proximo = NULL;
	delete removido;

	tamanho--;
	if (vazia()) {
		ultimo = NULL;
	}
}

void listadup::removeNoInicio() {
	if (vazia()) {
		cerr << "Remocao em lista vazia!!" << endl;
		exit(EXIT_FAILURE);
	}

	noh* removido = primeiro;
	primeiro = primeiro->proximo;
	if (primeiro != NULL){
		primeiro->anterior = NULL;
	}
	delete removido;

	tamanho--;
	if (vazia()) {
		primeiro = NULL;
	}
}

void listadup::removeValor(Dado dado) {
	noh* aux = primeiro;

	while ((aux != NULL) and (aux->dado != dado)) {
		aux = aux->proximo;
	}

	if (aux == NULL) {
		cerr << "Erro: remocao de valor não encontrado!!" << endl;
		exit(EXIT_FAILURE);
	} else {
		noh* anterior = aux->anterior;
		noh* proximo = aux->proximo;
		if (anterior != NULL) {
			anterior->proximo = proximo;
		} else {
			primeiro = aux->proximo;
		}
		if (proximo != NULL) {
			proximo->anterior = anterior;
		} else {
			ultimo = aux->anterior;
		}
		delete aux;
	}
	tamanho--;
	if (vazia()) {
		primeiro = NULL;
		ultimo = NULL;
	}
}

// verifica se a lista está vazia
inline bool listadup::vazia() {
	return (tamanho == 0);
}

int main(){
	listadup minhaLista;
	
	cout << "*** Teste de Lista ***" << endl;
	
	minhaLista.insere(5);
	minhaLista.insere(3);
	minhaLista.insere(1);
	minhaLista.insere(0);
	minhaLista.insere(6);
	minhaLista.insereNoInicio(18);
    try {
        minhaLista.insereNaPosicao(12, 25);
    } catch (exception& e) {
        cout << e.what() << endl;
    }
	
	minhaLista.imprime();
	
    int posicao;
    
    if (minhaLista.procura(3, posicao)){
        cout << "Encontrado na posicao: " << posicao << endl;
    } else {
        cout << "Elemento nao encontrado!!" << endl;
    }
	
	
	return 0;
}