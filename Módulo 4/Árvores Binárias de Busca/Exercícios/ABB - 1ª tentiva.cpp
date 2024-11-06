/*
* Árcore Binária de Busca
* 
*/
#include <iostream>
#include <stdexcept>

using namespace std;

typedef int Dado; 

class noh {
    friend class abb;
    private:
        Dado dado;
        noh* esq;
        noh* dir;

    public:
        noh(const Dado& d):
            dado(d), esq(NULL), dir(NULL) { }
        ~noh() { }
};

class abb {
    private:
        noh* raiz;
        // percorrimento em ordem e em pre ordem da árvore
        void percorreEmOrdemAux(noh* atual, int nivel);
        void percorrePreOrdemAux(noh* atual, int nivel);
        // funções auxiliares para inserção
        // retorna o nó para ajustar o pai ou a raiz
        noh* insereAux(noh* umNoh, const Dado& d);
        // funções auxiliares para remoção
        noh* minimoAux(noh* raizSubArvore);
        noh* removeMenor(noh* raiSub);
        // função auxiliar do destrutor, usa percorrimento pós-ordem
        void destruirRecursivamente(noh* umNoh);

    public:
        abb() { raiz = NULL; }
        ~abb();
        // impressão recursiva
        void imprimeOrdem();
        void imprimePreOrdem();
        // inserção recursiva
        void insere(const Dado& d);
        // remoção recursiva
        void removerRecursivamente(Dado umValor);
        noh* removerRecAux(noh* umNoh, Dado umValor);
        
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

// Inserções:
void abb::insere(const Dado& d) {
    raiz = insereAux(raiz, d);
}

noh* abb::insereAux(noh* umNoh, const Dado& d) {
    if (umNoh == NULL)  {
        noh* novoNoh = new noh(d);
        return novoNoh;
    } else if (d < umNoh->dado) {
        umNoh->esq = insereAux(umNoh->esq, d);
        return umNoh;
    } else if (d > umNoh->dado) {
        umNoh->dir = insereAux(umNoh->dir, d);
        return umNoh;
    }
}

// Remoção:
void abb::removerRecursivamente(Dado umValor) {
    raiz = removerRecAux(raiz, umValor);
}

noh* abb::removerRecAux(noh* umNoh, Dado umValor) {
    if (umNoh == NULL) {
        throw runtime_error("ERRO");
    } 
   
    noh* novaRaizSubArvore = umNoh;
    // valor menor que nó atual, vai para subárvore esquerda
    if (umValor < umNoh->dado) {
        umNoh->esq = removerRecAux(umNoh->esq, umValor);
    // valor maior que nó atual, vai para subárvore direita
    } else if (umValor > umNoh->dado) {
        umNoh->dir = removerRecAux(umNoh->dir, umValor);
    // valor é igual ao armazenado no nó atual, 
    // que deve ser apagado
    } else { // umNoh é removido neste senão
        // nó não tem filhos à esquerda
        if (umNoh->esq == NULL) {
            novaRaizSubArvore = umNoh->dir;
        // nó não tem filhos à direita
        } else if (umNoh->dir == NULL) {
            novaRaizSubArvore = umNoh->esq;
        } else { // nó tem dois filhos  
            // podemos trocar pelo antecessor ou sucessor
            // troca o nó por seu sucessor
            novaRaizSubArvore = minimoAux(umNoh->dir);
            // troca o sucessor por seu filho à direita
            novaRaizSubArvore->dir = removeMenor(umNoh->dir);  
            // filho à esquerda de umNoh torna-se filho à esquerda do sucessor
            novaRaizSubArvore->esq = umNoh->esq;
        }
        // ponteiros ajustados, apagamos o nó
        delete umNoh;
        // fim do senão para remoção de umNoh
        // devolve a nova raiz
        return novaRaizSubArvore;
    }
}

// Auxiliares:
noh* abb::minimoAux(noh* raizSubArvore) {
    while (raizSubArvore->esq != NULL) {
        raizSubArvore = raizSubArvore->esq;
    }
    return raizSubArvore;
}

noh* abb::removeMenor(noh* raizSubArvore) {
    // procedimento auxiliar para remover o sucessor substituindo-o pelo seu filho à direita
    if (raizSubArvore->esq == NULL) { // encontrou o sucessor
        return raizSubArvore->dir;
    } else { // não achou ainda, desce mais na subárvore
        raizSubArvore->esq = removeMenor(raizSubArvore->esq);
        return raizSubArvore;
    }
} 

// Impressões:
void abb::imprimeOrdem() {
    percorreEmOrdemAux(raiz, 0);
    cout << endl;
}

void abb::percorreEmOrdemAux(noh* atual, int nivel) {
    if (atual) {
        percorreEmOrdemAux(atual->esq, nivel+1);
        cout << atual->dado << "/" << nivel << " ";
        percorreEmOrdemAux(atual->dir, nivel+1);
    }
}

void abb::imprimePreOrdem() {
    percorrePreOrdemAux(raiz, 0);
    cout << endl;
}

void abb::percorrePreOrdemAux(noh* atual, int nivel) {
    if (atual) {
        cout << atual->dado << "/" << nivel << " "; 
        percorrePreOrdemAux(atual->esq, nivel+1);
        percorrePreOrdemAux(atual->dir, nivel+1);
    }
}

int main() {
    abb arvore;
    Dado dado;
    char operacao;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // Inserir recursivamente
                    cin >> dado;
                    arvore.insere(dado);
                    break;

                case 'r': // Remover recursivamente
                    cin >> dado;
                    arvore.removerRecursivamente(dado);
                    break;
                
                case 'o': // Escrever tudo (em ordem)
                    arvore.imprimeOrdem();
                    break;
                
                case 'p': // Escrever tudo (em pre ordem)
                    arvore.imprimePreOrdem();
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