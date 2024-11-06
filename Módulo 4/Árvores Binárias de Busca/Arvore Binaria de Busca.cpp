/*
* Árcore Binária de Busca
* 
*/
#include <iostream>
#include <stdexcept>

using namespace std;

struct contato {
    string nome; // esta sera a chave utilizada
    string telefone; // primeiro dado
    string descricao; // segundo dado
};

class noh {
    friend class abb;
    private:
        contato dadosDoContato;
        noh* esq;
        noh* dir;

    public:
        noh(const contato& umContato):
            dadosDoContato(umContato), esq(NULL), dir(NULL) { }
        ~noh() { }
};

class abb {
    private:
        noh* raiz;
        // percorrimento em ordem da árvore
        void percorreEmOrdemAux(noh* atual, int nivel);
        // funções auxiliares para inserção
        // retorna o nó para ajustar o pai ou a raiz
        noh* insereAux(noh* umNoh, const contato& umContato);
        // busca método iterativo
        noh* buscaAux(noh* umNoh, string chave);
        // função auxiliar do destrutor, usa percorrimento pós-ordem
        void destruirRecursivamente(noh* umNoh);

    public:
        abb() { raiz = NULL; }
        ~abb();
        void imprime();
        // inserção recursiva
        void insere(const contato& umContato);
        // busca retorna uma cópia do objeto armazenado
        contato busca(string chave);
};

abb::~abb() {
    destruirRecursivamente(raiz);
}

void abb::destruirRecursivamente(noh* umNoh) {
    if (umNoh == NULL){
        destruirRecursivamente(umNoh->esq);
        destruirRecursivamente(umNoh->dir);
        delete umNoh;
    }
}

void abb::insere(const contato& umContato) {
    raiz = insereAux(raiz, umContato);
}

noh* abb::insereAux(noh* umNoh, const contato& umContato){
    if (umNoh == NULL)  {
        noh* novoNoh = new noh(umContato);
        return novoNoh;
    } else if (umContato.nome < umNoh->dadosDoContato.nome) {
        umNoh->esq = insereAux(umNoh->esq, umContato);
        return umNoh;
    } else if (umContato.nome > umNoh->dadosDoContato.nome) {
        umNoh->dir = insereAux(umNoh->dir, umContato);
        return umNoh;
    } else {
        throw runtime_error("chave repetida na inserção");
    }
}

void abb::imprime() {
    percorreEmOrdemAux(raiz, 0);
        cout << endl;
}

void abb::percorreEmOrdemAux(noh* atual, int nivel) {
    if (atual) {
        percorreEmOrdemAux(atual->esq, nivel+1);
        cout << atual->dadosDoContato.nome << "/" << nivel << "     ";
        percorreEmOrdemAux(atual->dir, nivel+1);
    }
}

contato abb::busca(string chave) {
    noh* nohComDados = buscaAux(raiz, chave);

    if (nohComDados == NULL) {
        throw runtime_error("nome buscado não foi encontrado!");
    } else {
        return nohComDados->dadosDoContato;
    }
}

noh* abb::buscaAux(noh* umNoh, string chave) {
    if (umNoh == NULL)  {
        return NULL;
    } else if (chave < umNoh->dadosDoContato.nome) {
        return buscaAux(umNoh->esq, chave);
    } else if (chave > umNoh->dadosDoContato.nome) {
        return buscaAux(umNoh->dir, chave);
    } else {
        return umNoh;
    }
}

int main() {
    abb arvore;
    string chave;
    contato umContato;

    char operacao;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // Inserir recursivamente
                    // objeto recebe nome, telefone, descricao
                    cin >> umContato.nome
                        >> umContato.telefone
                        >> umContato.descricao;
                    arvore.insere(umContato);
                    break;

                case 'b': // Buscar
                    cin >> chave; // ler a chave
                    umContato = arvore.busca(chave); // escrever valor
                    cout << "Elemento buscado: "
                         << umContato.nome << " / "
                         << umContato.telefone << " / "
                         << umContato.descricao << " / "
                         << endl;
                    break;

                case 'p': // Escrever tudo (em ordem)
                    arvore.imprime();
                    break;

                case 'f': // Finaliza operacao
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cerr << e.what() << endl;
        }
    } while (operacao != 'f');

    return 0;
}