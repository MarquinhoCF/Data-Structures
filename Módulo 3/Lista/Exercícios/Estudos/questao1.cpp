#include <iostream>
#include <cstdlib>

using namespace std;

// para facilitar a troca de int para outro tipo
// estamos criando um apelido para int chamado Dado
// - comisso destaca-se que a lista pode ser uma
// lista de qualquer objeto, não apenas inteiros...
// ou seja: é uma lista de dados
typedef int Dado; // typedef permite criar 

class noh {
	friend class lista;
	private:
    /* Dado está como uma constante para não permitir alteração */
		const Dado dado;
		noh* proximo;
		
	public:
		//noh();
		noh(Dado d = 0);
};

// construindo dado chamando construtor
// note o uso de inicialização em lista, já que o dado é atributo cosntante
noh::noh(Dado d) : dado(d) {
	proximo = NULL;
}

class lista{
	private:
		noh* primeiro;
		noh* ultimo;
		int tamanho;
		void removeTodos(); // rmove todos os elementos da lista
		// imprime reverso a partir de um nó -> exeplo de uso de recursão
		void imprimeReversoAux(noh* umNoh);
		
	public:
	// construtores e destrutor
		lista();
		lista(const lista& umaLista);
		~lista();
		// sobregcarga do operador de atribuição
		lista& operator=(const lista& umalista);
		// inserção e remoção e procura
		inline void insere(Dado dado);
		void insereNoFim(Dado dado);
		void insereNoInicio(Dado dado);
		void insereNaPosicao(int posicao, Dado dado);
		int procura(Dado valor); // retorna a posição do nó com valor indicado
		// métodos adicionais (impressão, vazia)
		void imprime();
		void imprimeReverso();
		inline bool vazia();
		int removeNoFim();
		int removeNoInicio();
};

lista::lista() {
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}

// construtor de cópia
lista::lista(const lista& umaLista) {
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
lista::~lista() {
	removeTodos();
}

// remove todos os elementos da lista
void lista::removeTodos() {
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
lista& lista::operator=(const lista& umalista) {
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
void lista::insere(Dado dado) {
	insereNoFim(dado);
}

// insere no final da lista
void lista::insereNoFim(Dado dado) {
	// * primeiro criamos um nó
	noh* novo = new noh(dado);

	// * agora inserimos o nó na lista
	// se a lista estiver vazia, inserimos o primeiro nó
	if (vazia()) { // ou (primeiro == NULL) ou (tamanho == 0)
		primeiro = novo;
		ultimo = novo;
	} else { // já tem elementos na lista insere no final
		ultimo->proximo = novo;
		ultimo = novo;
	}
	tamanho++;
}

// insere no início da lista
void lista::insereNoInicio(Dado dado) {
	// * primeiro criamos um nó
	noh* novo = new noh(dado);

	// * agora inserimos o nó na lista
	// se a lista estiver vazia, inserimos o primeiro nó
	if (vazia()) { // ou (primeiro == NULL) ou (tamanho == 0)
		primeiro = novo;
		ultimo = novo;
	} else { // já tem elementos na lista insere no início
		novo->proximo = primeiro;
		primeiro = novo;
	}
	tamanho++;
}

// insere em uma determinada posição da lista
void lista::insereNaPosicao(int posicao, Dado dado) {
	// * primeiro criamos um nó
	noh* novo = new noh(dado);

	// * agora inserimos o nó na lista
	// verificamos antes se é possível inserir na posição
	if ((posicao <= tamanho) && (posicao >= 0)) {
		if (vazia()) { // ou (primeiro == NULL) ou (tamanho == 0)
			primeiro = novo;
			ultimo = novo;
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
			aux->proximo = novo;
		}
	tamanho++;
	} else {
		cerr << "Posicao inexistente!!" << endl;
		exit(EXIT_FAILURE);
	}
}

int lista::procura(Dado dado) {
	noh* aux = primeiro;

	int posAux = 0;

	while ((aux != NULL) && (aux->dado != dado)) {
		posAux++;
		aux = aux->proximo;
	}

	if (aux == NULL) {
		posAux = -1;
	}
	return posAux;
}

inline bool lista::vazia() {
	return (tamanho == 0);
}

// método básico que *percorre*uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void lista::imprime() {
	noh* aux = primeiro;

	while (aux != NULL) {
		cout << aux->dado << " ";
		aux = aux->proximo;
	}
	cout << endl;
}

// usamos a recursão (pilha de recursão) para imprimir reverso
// paar isso precisamos de função auxiliar
void lista::imprimeReverso() {
	imprimeReversoAux(primeiro);
	cout << endl;
}

void lista::imprimeReversoAux(noh* umNoh) {
	if (umNoh != NULL) {
		imprimeReversoAux(umNoh->proximo);
		cout << umNoh->dado << " ";
	}
}

int lista::removeNoFim() {
	if (vazia()) {
		cerr << "Remocao em lista vazia!!" << endl;
		exit(EXIT_FAILURE);
	}

	noh* aux = primeiro;
	noh* anterior;

	while (aux->proximo != NULL) {
		anterior = aux;
		aux = aux->proximo;
	}

	// parei no penúltimo
    int retorno = ultimo->dado;
	delete ultimo;

	aux->proximo = NULL;
	ultimo = anterior;

	tamanho--;
	if (vazia()) {
		primeiro = NULL;
	}

    return retorno;
}

int lista::removeNoInicio() {
	if (vazia()) {
		cerr << "Remocao em lista vazia!!" << endl;
		exit(EXIT_FAILURE);
	}

	noh* removido = primeiro;
    int retorno = removido->dado;
	primeiro = primeiro->proximo;
	delete removido;

	tamanho--;
	if (vazia()) {
		primeiro = NULL;
	}

    return retorno;
}

int main(){
	lista Lista1, Lista2;
	
	int valor;
	
	do {
		cin >> valor;
		if (valor >= 0) {
            Lista1.insere(valor);
        }
	} while (valor >= 0);

    Lista1.imprime();

	do {
		cin >> valor;
		if (valor >= 0) {
            Lista2.insere(valor);
        }
	} while (valor >= 0);

    Lista2.imprime();

	bool termina = true;
	lista resultante;
	int num1, num2, soma;
	int vai1 = 0;
	while (termina) {
        cout << "entrou no while" << endl;
		if (!Lista1.vazia()) {
			num1 = Lista1.removeNoFim();
		} else {
			num1 = 0;
		}

		if (!Lista2.vazia()) {
			num2 = Lista2.removeNoFim();
		} else {
			num2 = 0;
		}

		soma = num1 + num2 + vai1;
		vai1 = 0;
        cout << soma << " ";
		if (soma > 10) {
			soma -= 10;
			resultante.insere(soma);
			vai1 = 1;
		} else {
			resultante.insere(soma);
		}

		if ((num1 == 0) && (num2 == 0) && (vai1 == 0)){
			termina = false;
            cout << "entrou no termina!" << endl;
		}
	}

	resultante.imprime();
	
	return 0;
}