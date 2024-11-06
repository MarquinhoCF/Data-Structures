/* avl - Árvore Binária de Busca com Balanceamento AVL
 *
 * by Joukim, Outubro de 2019 - Estrutura de Dados (GCC216)
 * Caracteristicas de implementação outubro de 2019:
 * -> tratamento de exceção
 * -> usa dado na forma chave/valor
 * -> uso de métodos recursivos
 * -> sem duplo encadeamento
 * -> invés de transplanta, usa removeMenor
 */

#include <iostream>
#include <stdexcept>

using namespace std;

struct dado {
    unsigned chave;
    string nome;
    unsigned long long int cpf;
};


ostream& operator<<(ostream& saida, const dado& e) {
    saida << "Nome: " << e.nome << " | CPF: "  << e.cpf <<  " | Cod: " << e.chave ;
    return saida;
}

istream& operator>>(istream& entrada, dado& e) {
    entrada >> e.chave >> e.nome >> e.cpf;
    return entrada;
}

typedef unsigned tipoChave; // tipo da chave usada na comparação

class noh {
    friend class avl;
    private:
        dado elemento;
        noh* esq;
        noh* dir;
        unsigned altura;
    public:
        noh(const dado& umDado):
            elemento(umDado),  esq(NULL), dir(NULL), altura(1) { }
        ~noh() { }
        int fatorBalanceamento();
        void atualizarAltura();
        int informarAltura(noh* umNoh);
};

int noh::informarAltura(noh* umNoh) {
    if (umNoh == NULL) { // Verifica se o noh é nulo
        return 0; 
    } else {
        return umNoh->altura; // Retorna altura do noh
    }
}

int noh::fatorBalanceamento() {
    int altArvEsq = informarAltura(this->esq);
    int altArvDir = informarAltura(this->dir);
    return altArvEsq - altArvDir;
}

// Calcula e atualiza a altura de um nó.
void noh::atualizarAltura() {
    int altArvEsq = informarAltura(this->esq);
    int altArvDir = informarAltura(this->dir);
    this->altura = 1 + max(altArvEsq, altArvDir); // Atualiza altura verificando qual sub árvore é maior
}

class avl {
    friend ostream& operator<<(ostream& output, avl& arvore);
    private:
        noh* raiz;
        // percorrimento em ordem da árvore
        void percorreEmOrdemAux(noh* atual, int nivel);
        void imprimeAutorizadosAux(noh* atual, bool impar);
        // funções auxiliares para remoção
        noh* encontraMenor(noh* raizSub);
        noh* removeMenor(noh* raizSub);
        // funções auxiliares para inserção e remoção usando método recursivo
        // retorna o nó para ajustar o pai ou o raiz
        noh* insereAux(noh* umNoh, const dado& umDado);
        noh* removeAux(noh* umNoh, tipoChave chave);
        // métodos para manutenção do balanceamento
        noh* rotacaoEsquerda(noh* umNoh);
        noh* rotacaoDireita(noh* umNoh);
        noh* arrumaBalanceamento(noh* umNoh);
        // busca, método iterativo
        noh* buscaAux(tipoChave chave);
        // função auxiliar do destrutor, usa percorrimento pós-ordem
        void destruirRecursivamente(noh* umNoh);
        void imprimirDir(const std::string& prefixo, const noh* node);
        void imprimirEsq(const std::string& prefixo, const noh* node, bool temIrmao);
    public:
        avl() { raiz = NULL; }
        ~avl();
        void imprimir();
        // inserção e remoção são recursivos
        void insere(const dado& umDado);
        void remove(tipoChave chave);
        // inserção e remoção, métodos recursivos
        // busca retorna uma cópia do objeto armazenado
        dado busca(tipoChave chave);
        void imprimeAutorizados(int dia);
        bool verificaAutorizado(tipoChave chave, int dia);
};

// destrutor
avl::~avl() {
    destruirRecursivamente(raiz);
}

// destrutor é recursivo, fazendo percorrimento pós-ordem
void avl::destruirRecursivamente(noh* umNoh) {
    if (umNoh->esq != NULL) { // Desaloca todos os filhos a esquerda
        destruirRecursivamente(umNoh->esq);
        delete umNoh->esq;
        umNoh->esq = NULL;
    }

    if (umNoh->dir != NULL) { // Desaloca todos os filhos a direita
        destruirRecursivamente(umNoh->dir);
        delete umNoh->dir;
        umNoh->dir = NULL;
    }
}

void avl::insere(const dado& umDado) {
    raiz = insereAux(raiz, umDado);
}

// inserção recursiva, devolve nó para atribuição de pai ou raiz
noh* avl::insereAux(noh* umNoh, const dado& umDado) {
    if (umNoh == NULL) {
		noh* novo = new noh(umDado); // cria um nó com o valor
		return novo;
	} else {  
		// não é folha nula, checa inserção à esquerda ou direita
		if (umDado.chave < umNoh->elemento.chave) {
			umNoh->esq = insereAux(umNoh->esq, umDado);
		} else {
			umNoh->dir = insereAux(umNoh->dir, umDado); 
		}
	}
	return arrumaBalanceamento(umNoh);
}

// checa e arruma, se necessário, o balanceamento em umNoh,
// fazendo as rotações e ajustes necessários
noh* avl::arrumaBalanceamento(noh* umNoh) {
    if (umNoh == NULL) { return umNoh; }
	// Inicialmente atualiza a altura de umNoh
	umNoh->atualizarAltura();
	// Checa o balanceamento no nó 
	int fatorBal = umNoh->fatorBalanceamento();
	// retorna o nó acima na árvore, caso esteja balanceado
	if ((fatorBal >= -1) and (fatorBal <= 1)) {
	  return umNoh;
	}
	
	// Caso o nó esteja desbalanceado, há 4 situações
	
	// 1. Desbalanceamento Esquerda Esquerda
	if ((fatorBal > 1) and (umNoh->esq->fatorBalanceamento() >= 0) ) {
		return rotacaoDireita(umNoh);
	}
	// 2. Desbalanceamento Esquerda Direita
	if ((fatorBal > 1) and (umNoh->esq->fatorBalanceamento() < 0) ) {
		umNoh->esq = rotacaoEsquerda(umNoh->esq);
		return rotacaoDireita(umNoh);
	}
	// 3. Desbalanceamento Direita Direita
	if ((fatorBal < -1) and (umNoh->dir->fatorBalanceamento() <= 0)) {
		return rotacaoEsquerda(umNoh);
	}
	// 4. Desbalanceamento Direita Esquerda
	if ((fatorBal < -1) and (umNoh->dir->fatorBalanceamento() > 0) ) {
		umNoh->dir = rotacaoDireita(umNoh->dir);
		return rotacaoEsquerda(umNoh);
	}    
}


// rotação à esquerda na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoEsquerda(noh* umNoh) {
	// acha filho à direita da raiz da subárvore
	noh* nohAux = umNoh->dir;

	// armazena subárvore à esquerda do nó auxiliar 
	// à direita da raiz atual
	umNoh->dir = nohAux->esq;
	// posiciona umNoh como filho à esquerda de nohAux
	nohAux->esq = umNoh;
	
	// atualiza alturas
	umNoh->atualizarAltura();
	nohAux->atualizarAltura();

	// atualiza a nova raiz da subárvore
	return nohAux;
}


// rotação à direita na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoDireita(noh* umNoh) {
	// acha filho à esquerda da raiz da subárvore
	noh* nohAux = umNoh->esq;

	// armazena subárvore à direita do nó auxiliar 
	// à esquerda da raiz atual
	umNoh->esq = nohAux->dir;
	// posiciona umNoh como filho à esquerda de nohAux
	nohAux->dir = umNoh;
	
	// atualiza alturas
	umNoh->atualizarAltura();
	nohAux->atualizarAltura();

	// atualiza a nova raiz da subárvore
	return nohAux;
}


// método de busca auxiliar (retorna o nó), iterativo
noh* avl::buscaAux(tipoChave chave) {
	// método retorna um nó, por isso é auxiliar (privado)
	noh* atual = raiz;
	while (atual != NULL) {
		if (atual->elemento.chave == chave) {
			return atual;
		} else if (atual->elemento.chave > chave) {
			atual = atual->esq;
		} else {
			atual = atual->dir;
		}
	}
	return atual; // retorna nulo quando não encontrado
}

// busca elemento com uma dada chave na árvore e retorna o registro completo
dado avl::busca(tipoChave chave) {
    noh* resultado = buscaAux(chave);
    if (resultado != NULL)
        return resultado->elemento;
    else
        throw runtime_error("Erro na busca: elemento não encontrado!");
}

// nó mínimo (sucessor) de subárvore com raiz em raizSub (folha mais à esquerda)
noh* avl::encontraMenor(noh* raizSub) {
    // Continua indo para o filho a esquerda até não ter filho esquerdo
    if (raizSub->esq == NULL) {
        return raizSub;
    } else {
        return encontraMenor(raizSub->esq); 
    }
}

// procedimento auxiliar para remover o sucessor substituíndo-o pelo
// seu filho à direita
noh* avl::removeMenor(noh* raizSub) {
    // procedimento auxiliar para remover o sucessor substituindo-o
	// pelo seu filho à direita
	if (raizSub->esq == NULL) {// encontrou o sucessor
		return raizSub->dir;
	} else { // não achou ainda, desce mais na subárvore
		raizSub->esq =  removeMenor(raizSub->esq);
		return arrumaBalanceamento(raizSub);
	} 
}

// remoção recursiva
void avl::remove(tipoChave chave) {
    raiz = removeAux(raiz, chave);
}

noh* avl::removeAux(noh* umNoh, tipoChave chave) {
    if (umNoh == NULL) {
		throw runtime_error("Nó não encontrado!");
	}
	noh* novaRaizSubArvore = umNoh;
	// valor é menor que nó atual, vai para subárvore esquerda
	if ( chave < umNoh->elemento.chave ) {
	  umNoh->esq = removeAux(umNoh->esq, chave);
	// valor é maior que nó atual, vai para subárvore direita
	} else if ( chave > umNoh->elemento.chave ) {
	  umNoh->dir = removeAux(umNoh->dir, chave);
	// valor igual ao do nó atual, que deve ser apagado
	} else {
		// nó não tem filhos à esquerda
		if (umNoh->esq == NULL) {
			novaRaizSubArvore = umNoh->dir;  
		// nó não tem filhos à direita
		} else if (umNoh->dir == NULL) {
			novaRaizSubArvore = umNoh->esq;
		} else { // nó tem dois filhos
			// trocando pelo sucessor
			novaRaizSubArvore = encontraMenor(umNoh->dir);
			// onde antes estava o sucessor fica agora seu filho 
			// à direita
			novaRaizSubArvore->dir = removeMenor(umNoh->dir);
			// filho à esquerda de umNoh torna-se filho à esquerda 
			// de sucessor
			novaRaizSubArvore->esq = umNoh->esq;
		}
		     
		// ponteiros ajustados, apagamos o nó
		delete umNoh;
	}
	// retorna o balanceamento na nova raiz da subárvore
	return arrumaBalanceamento(novaRaizSubArvore);
}

// utiliza o nó atual e seu nível na árvore (para facilitar visualização)
void avl::imprimeAutorizadosAux(noh* atual, bool impar) {
	if (atual != NULL) {
		imprimeAutorizadosAux(atual->esq, impar);
		if (!impar and ((atual->elemento.chave % 2) == 0)) {
			cout << "Nome: " << atual->elemento.nome << " | CPF: " << atual->elemento.cpf << " | Cod: " << atual->elemento.chave << endl;
		} else if (impar and ((atual->elemento.chave % 2) == 1)) {
			cout << "Nome: " << atual->elemento.nome << " | CPF: " << atual->elemento.cpf << " | Cod: " << atual->elemento.chave << endl;
		}
		imprimeAutorizadosAux(atual->dir, impar);
	}
}

// utiliza o nó atual e seu nível na árvore (para facilitar visualização)
void avl::imprimeAutorizados(int dia) {
    imprimeAutorizadosAux(this->raiz, dia % 2);
}

// utiliza o nó atual e seu nível na árvore (para facilitar visualização)
bool avl::verificaAutorizado(tipoChave chave, int dia) {
    dado Elemento = busca(chave);
    bool par = false;
    
    if ((dia % 2) == 0) {
		par = true;
	}
	
	if (par and ((Elemento.chave % 2) == 0)) {
		return true;
	} else if (!par and (Elemento.chave % 2) == 1) {
		return true;
	} else {
		return false;
	}
}

// utiliza o nó atual e seu nível na árvore (para facilitar visualização)
//void avl::percorreEmOrdemAux(noh* atual, int nivel) {
//}

ostream& operator<<(ostream& output, avl& arvore) {
    // arvore.percorreEmOrdemAux(arvore.raiz,0);
    arvore.imprimir();
    return output;
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirDir(const std::string& prefixo, const noh* node)
{
    if( node != nullptr )
    {
        std::cout << prefixo
                  << "└d─"
                  << "(" << node->elemento.chave << "," << node->elemento.nome << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "    " , node->esq , node->dir==nullptr );
        imprimirDir( prefixo + "    " , node->dir );
    }
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirEsq(const std::string& prefixo, const noh* node, bool temIrmao)
{
    if( node != nullptr )
    {
        std::cout << prefixo ;

        // A impressao da arvore esquerda depende da indicacao se existe o irmao a direita
        if (temIrmao)
            std::cout << "└e─" ;
        else
            std::cout << "├e─";

        std::cout << "(" << node->elemento.chave << "," << node->elemento.nome << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "│   " , node->esq, node->dir==nullptr );
        imprimirDir( prefixo + "│   " , node->dir );
    }
}

// imprime formatado seguindo o padrao tree uma avl
void avl::imprimir()
{
    if( this->raiz != nullptr )
    {
        std::cout << "(" << this->raiz->elemento.chave << "," << this->raiz->elemento.nome << ")" << std::endl;
        // apos imprimir a raiz, chama os respectivos metodos de impressao nas subarvore esquerda e direita
        // a chamada para a impressao da subarvore esquerda depende da existencia da subarvore direita
        imprimirEsq( " " , this->raiz->esq, this->raiz->dir==nullptr );
        imprimirDir( " " , this->raiz->dir );
    } else
        std::cout << "*arvore vazia*" << std::endl;
}

int main() {
    avl arvore;
    tipoChave chave;
    dado umDado;
    int dia = 0;

    char operacao;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // Inserir recursivamente
                    // objeto recebe id, nome, quantidade, valor
                    cin >> umDado;
                    arvore.insere(umDado);
                    break;
                case 'r': // Remover recursivamente
                    cin >> chave;
                    arvore.remove(chave);
                    break;
                case 'b': // Buscar
                    cin >> chave; // ler a chave
                    umDado = arvore.busca(chave); // escrever o valor
                    cout << umDado << endl;
                    break;
                case 'e': // Escrever arvore no formato tree
                    cout << arvore ;
                    break;
                case 'l': // lista os autorizados 
                    cin >> dia;
                    arvore.imprimeAutorizados(dia);
                    break;     
                case 'v': // Verifica se funcionario esta autorizado
                    cin >> chave >> dia;
                    if ( arvore.verificaAutorizado(chave, dia) )
                        cout << "Autorizado." << endl;
                    else
                        cout << "Não autorizado." << endl;
                    break;     
                case 'f': // Finalizar execução
                    break;
                default:
                    cout << "Comando invalido!\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (operacao != 'f');

    return 0;
}
