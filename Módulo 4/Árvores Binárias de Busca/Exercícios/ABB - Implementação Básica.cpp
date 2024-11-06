/*
* Árvore Binária de Busca
* 
* by Marcos, em 2023
*/

#include <iostream>
#include <stdexcept>

using namespace std;

typedef int dado;

class noh {
    friend class abb;
private:
    dado myDado;
    noh *esq;
    noh *dir;

public:
    noh(const dado &umDado) {
        myDado = umDado;
        esq = NULL;
        dir = NULL;
    }
    ~noh() {}
};

class abb {
    private:
        noh *raiz;
        void percorrerEmOrdemAux(noh *atual, int nivel);    // percorre em ordem da arvore.
        void percorrerEmPreOrdemAux(noh *atual, int nivel); // percorre em pre ordem da arvore.
        // funcao auxiliar do destrutor, usa percorrimento em pós-ordem
        void destruirRecursivamente(noh *umNoh);
        // funcoes auxiliares de insercao
        // retorna o no para ajustar o pai ou raiz
        noh* insereAux(noh *umNoh, const dado &umDado);
        // funcoes auxiliares de remocao
        noh* menorValor(noh *umNoh);
        noh* removeAux(noh *umNoh, dado valor);
        // busca método iterativo
        //noh* buscaAux(noh* umNoh, int valor);

    public:
        abb();
        ~abb();
        void imprimeEmOrdem();
        void imprimeEmPreOrdem();
        void remove(dado valor);
        // insercao recursiva
        void insere(const dado &umDado);
        // busca retorna uma copia do objeto armazenado
        //dado busca(int valor);
};

// CONSTRUTORES E DESTRUTORES:
abb::abb() {
    raiz = NULL;
}

abb::~abb() {
    destruirRecursivamente(raiz);
}

void abb::destruirRecursivamente(noh *umNoh) {
    if (umNoh) {
        destruirRecursivamente(umNoh->esq);
        destruirRecursivamente(umNoh->dir);
        delete umNoh;
    }
}

// INSERÇÃO:
void abb::insere(const dado &umDado) {
    raiz = insereAux(raiz, umDado);
}

noh* abb::insereAux(noh *umNoh, const dado &umDado) {
    if (umNoh == NULL) {
        noh *novoNoh = new noh(umDado);
        return novoNoh;
    } else if (umDado < umNoh->myDado) { // insere filho a esquerda, valor menor que o no
        umNoh->esq = insereAux(umNoh->esq, umDado);
        return umNoh;
    } else { // valor igual ao no ou maior
        umNoh->dir = insereAux(umNoh->dir, umDado);
        return umNoh;
    }
}

// REMOÇÃO:
noh* abb::menorValor(noh *umNoh) {
    noh *atual = umNoh;
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

void abb::remove(dado valor)
{
    raiz = removeAux(raiz, valor);
    if (raiz == NULL) {
        throw runtime_error("ERRO");
    }
}

noh* abb::removeAux(noh *umNoh, dado valor)
{
    if (umNoh == NULL) {
        return umNoh;
    }

    if (valor < umNoh->myDado) {
        umNoh->esq = removeAux(umNoh->esq, valor);
    } else if (valor > umNoh->myDado) {
        umNoh->dir = removeAux(umNoh->dir, valor);
    } else {
        if ((umNoh->esq == NULL) || (umNoh->dir == NULL)) {
            noh *aux;
            if (umNoh->esq != NULL) {
                aux = umNoh->esq;
            } else {
                aux = umNoh->dir;
            } 
            
            if (aux == NULL) {
                aux = umNoh;
                umNoh = NULL;
            } else {
                *umNoh = *aux;
            } 
            delete aux;
        } else {
            noh *aux = menorValor(umNoh->dir);
            umNoh->myDado = aux->myDado;
            umNoh->dir = removeAux(umNoh->dir, aux->myDado);
        }
    }
    return umNoh;
}

// IMPRESSÕES:
void abb::imprimeEmOrdem() {
    if (raiz == NULL) {
        throw runtime_error("ERRO");
    }
    percorrerEmOrdemAux(raiz, 0);
    cout << endl;
}

void abb::percorrerEmOrdemAux(noh *atual, int nivel) {
    if (atual != NULL) {
        percorrerEmOrdemAux(atual->esq, nivel + 1);
        cout << atual->myDado << "/" << nivel << " ";
        percorrerEmOrdemAux(atual->dir, nivel + 1);
    }
}

void abb::imprimeEmPreOrdem() {
    if (raiz == NULL) {
        throw runtime_error("ERRO");
    }
    percorrerEmPreOrdemAux(raiz, 0);
    cout << endl;
}

void abb::percorrerEmPreOrdemAux(noh *atual, int nivel) {
    if (atual != NULL) {
        cout << atual->myDado << "/" << nivel << " ";
        percorrerEmPreOrdemAux(atual->esq, nivel + 1);
        percorrerEmPreOrdemAux(atual->dir, nivel + 1);
    }
}

// BUSCA:
/*dado abb::busca(int valor) {
    noh *aux = buscaAux(raiz, valor);
    if (aux == NULL) {
        throw runtime_error("ERRO");
    } else {
        return aux->myDado;
    }
}

noh* abb::buscaAux(noh *umNoh, int valor) {
    if (umNoh == NULL) {
        return NULL;
    } else if (valor < umNoh->myDado) { // insere filho a esquerda, valor menor que o no
        return buscaAux(umNoh->esq, valor);
    } else if (valor > umNoh->myDado) {// insere filho a direita, valor maior que o no
        return buscaAux(umNoh->dir, valor);
    } else { // valor igual ao no ou maior
        return umNoh;
    }
}*/

int main() {
    abb minhaAbb;
    dado info;
    char comando;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info;
                    minhaAbb.insere(info);
                    break;
                case 'r': // remover
                    cin >> info;
                    minhaAbb.remove(info);
                    break;
                case 'o': // inserir
                    minhaAbb.imprimeEmOrdem();
                    break;
                case 'p': // limpar tudo
                    minhaAbb.imprimeEmPreOrdem();
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando invalido\n";
            }
        } catch (runtime_error &e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    return 0;
}