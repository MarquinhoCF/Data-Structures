/* 
 * Classe hash, uma tabela hash em que chaves e valores são strings
 * 
 * by Joukim, 2017-2018, Estruturas de Dados
 * Atualizado por Renato, 2023
 * Alterado por Marcos, 2023
 * 
 */
#include <iostream>

using namespace std;

const int UMPRIMO = 13;

int funcaoHash(string s, int M) {
    long h = 0;
    for (unsigned i = 0; i < s.length(); i++) {
        h = (UMPRIMO * h + s[i]) % M;   
    }
    return h;
}

class noh {
friend class tabelaHash;
private:
    string chave;
    char tipo;
    int valor;
    noh* proximo = NULL;
public:
    noh(){
        chave = "";
        tipo = 'a';
        valor = 1;        
    }
};

class tabelaHash {
private:
	int busca(string c);
    // vetor de ponteiros de nós
    noh** elementos;
    int capacidade;
public:
    // construtor padrão
    tabelaHash(int cap = 100);
    // destrutor 
    ~tabelaHash();
    // insere um valor v com chave c
    bool insere(string c, char t, int v);
    // recupera um valor associado a uma dada chave
    bool recupera(string c, char& t, int& v);
    // retira um valor associado a uma chave
    bool remove(string c);
    // percorrendo a tabela hash (para fins de debug)
    void imprime();
    bool vazia();
    bool modificaElemento(string chaveAnt, string c, char t, int v);
};

// construtor padrão
tabelaHash::tabelaHash(int cap) {
    capacidade = cap;
    elementos = new noh*[capacidade];
    for (int i = 0; i < capacidade; i++) { // Marcação de inválido para todas as posições do vetor
        elementos[i] = NULL;
    }
}

// destrutor
tabelaHash::~tabelaHash() {
    for (int i = 0; i < capacidade; ++i) { // Percorre o indice do vetor
        noh* atual = elementos[i];
        while(atual != NULL){ // Percorre a lista encadeada
            noh* aux = atual;
            atual = atual->proximo;
            delete aux; // Desaloca cada noh
        }
    }
    delete[] elementos; // Desaloca o vetor de nohs
}

// insere um valor v com chave c
bool tabelaHash::insere(string c, char t, int v) {
    int posicao = funcaoHash(c,capacidade);
    if (not (recupera(c, t, v))){
        if (elementos[posicao] == NULL){
            elementos[posicao] = new noh;
            elementos[posicao]->chave = c;
            elementos[posicao]->tipo = t;
            elementos[posicao]->valor = v;
        } else {
            noh* atual = elementos[posicao];

            // Criamos o nó
            noh* novo = new noh;
            novo->chave = c;
            novo->tipo = t;
            novo->valor = v;

            novo->proximo = atual;
		    elementos[posicao] = novo;
        }
        cout << "chave '" << c << "' inserida na posicao "<< posicao << endl;
        return true;
    } else {
        return false;
    }
}

// recupera um valor associado a uma dada chave
bool tabelaHash::recupera(string c, char& t, int& v) {
    int posicao = funcaoHash(c,capacidade);

    if (elementos[posicao] != NULL && elementos[posicao]->chave == c){
        t = elementos[posicao]->tipo;
        v = elementos[posicao]->valor;
        return true;
    } else { // Percorre a lista em caso de colisão
        noh* atual = elementos[posicao];
        
        while (atual != NULL &&  atual->chave != c) { // Percorre a lista até encontrar ou a lista terminar
            atual = atual->proximo;
        }

        if (atual != NULL && atual->chave == c){
            t = atual->tipo;
            v = atual->valor;
            return true;
        }else{
            return false;
        }
    }
}

// retorna a posicao de um item da lista
int tabelaHash::busca(string c) {
    int posicao = funcaoHash(c,capacidade);

    if (elementos[posicao] != NULL && elementos[posicao]->chave == c){
        return posicao;
    } else { // Percorre a lista em caso de colisão
        noh* atual = elementos[posicao];
        
        while (atual != NULL &&  atual->chave != c) { // Percorre a lista até encontrar ou a lista terminar
            atual = atual->proximo;
        }

        if (atual != NULL && atual->chave == c){
            return posicao;
        }else{
            return -1;
        }
    }
}

// retira um valor associado a uma chave
bool tabelaHash::remove(string c) {
    int posicao = funcaoHash(c, capacidade);

    if (vazia()) {
        throw runtime_error("Erro: hash vazia!");
    }

    if (elementos[posicao] != NULL && elementos[posicao]->chave == c){ // Item encontrado
        noh* aux = elementos[posicao];
        elementos[posicao] = elementos[posicao]->proximo; // Reposiciona o ponteiro para o próximo da lista
        delete aux; // Deleta o item
        return true;
    } else { // Verifica se o item está colidido
        noh* atual = elementos[posicao];
        noh* anterior;


        while (atual != NULL && atual->chave != c){ // Percorre a lista até encontrar ou a lista terminar
            anterior = atual;
            atual = atual->proximo;
        }

        if (atual != NULL && atual->chave == c){ // Item encontrado
            anterior->proximo = atual->proximo; // Reposiciona o ponteiro para o próximo da lista
            delete atual; // Deleta o item
            return true;
        } else {
            return false;
        }
    }
}

bool tabelaHash::vazia() {
    for (int i = 0; i < capacidade; i++) {
        if (elementos[i] != NULL) {
            return false;
        }
    }
    return true;
}

// percorrendo a tabela hash (para fins de depuração)
void tabelaHash::imprime( ) {
    noh* atual;
    for (int i = 0; i < capacidade; i++) {
        cout << i << ":";
        atual = elementos[i];
        while (atual != NULL) {
            cout << "[" << atual->chave << "/"
                 << atual->valor << "]";
            atual = atual->proximo;
        }
        cout << endl;
    }
    
}

bool tabelaHash::modificaElemento(string chaveAnt, string c, char t, int v){
	int posicao = busca(chaveAnt);
	
	if (posicao != -1) {
		remove(chaveAnt);
		
		posicao = funcaoHash(c,capacidade);
		
		if (elementos[posicao] == NULL){
			elementos[posicao] = new noh;
			elementos[posicao]->chave = c;
			elementos[posicao]->tipo = t;
			elementos[posicao]->valor = v;
		} else {
			noh* atual = elementos[posicao];

			// Criamos o nó
			noh* novo = new noh;
			novo->chave = c;
			novo->tipo = t;
			novo->valor = v;

			novo->proximo = atual;
			elementos[posicao] = novo;
		}
        return true;
	} else {
		return false;
	}
}

int main() {
    int tamanhoTH;
    cin >> tamanhoTH;
    tabelaHash tabela(tamanhoTH);
    char comando;
    string chave, chave2;
    char tipo = 'a';
    int valor = -1;    
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> chave >> tipo >> valor;
                    if (not tabela.insere(chave, tipo, valor))
						cout << "Erro na inserção: chave já existente!" << endl;
                    break;
                case 'r': // remover
                    cin >> chave;
                    if (not tabela.remove(chave))
                        cout << "Erro na remoção: chave não encontrada!" << endl;
                    break;
                case 'l': // busca
                    cin >> chave;
                    if (tabela.vazia()) {
                        throw runtime_error("Erro: hash vazia!");
                    } else if (not tabela.recupera(chave, tipo, valor))
                        cout << "Erro na busca: chave não encontrada!" << endl;
                    else
                        cout << "Tipo: " << tipo << " Valor: " << valor << endl;
                    break;
                case 'p': // mostrar estrutura
                    tabela.imprime();
                    break;
				case 'm':
					cin >> chave >> chave2 >> tipo >> valor;
					if (not tabela.modificaElemento(chave, chave2, tipo, valor))
                        cout << "Erro na modificação: chave não encontrada!" << endl;
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
    tabela.imprime();
    cout << endl;
    return 0;
}
