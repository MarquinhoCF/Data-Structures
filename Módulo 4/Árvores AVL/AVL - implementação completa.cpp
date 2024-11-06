/*
* Árvore de Adelson-Velskii e Landis (AVL)
* 
* código base: by professores de Estrutura de Dados, 2023/01
* implementação das funções: by Marcos, em 2023
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <queue>

typedef std::string TChave; // chave da árvore
typedef float TValor; // valor da árvore

// === Declarações das classes ===================================================
class NohAVL; // declaração avançada

class AVL {
    public:
        AVL();
        ~AVL();
        TValor& Valor(TChave chave);
        void EscreverEmOrdem();
        void EscreverNivelANivel(std::ostream& saida);
        void Inserir(TChave chave, const TValor& valor);
        bool ConferirLigacoes();
        void Remover(TChave chave);
    private:
        NohAVL* mPtRaiz;
};

class NohAVL {
    friend std::ostream& operator<<(std::ostream& saida, NohAVL* ptNoh);
    friend void AVL::EscreverNivelANivel(std::ostream& saida);
    public:
        NohAVL (TChave c, const TValor& v);
        ~NohAVL();
        void DesalocarFilhosRecursivo();
        NohAVL* InserirRecursivo(NohAVL* ptNoh);
        NohAVL* MenorRecursivo();
        NohAVL* RemoverRecursivo(TChave chave);
        bool ConferirLigacoesRecursivo();
        TValor& Valor(TChave chave);
    private:
        NohAVL* ArrumarBalanceamento();
        int InformarAltura(NohAVL* umNoh);
        void AtualizarAltura();
        int FatorBalanceamento();
        NohAVL* Remover();
        NohAVL* RotacionarEsquerda();
        NohAVL* RotacionarDireita();
        void SubstitutirPor(NohAVL* ptNoh);
        void Transplantar(NohAVL* ptFilho);
        void TrocarFilho(NohAVL* ptAntigo, NohAVL* ptNovo);
        TChave mChave;
        TValor mValor;
        NohAVL* mPtEsq;
        NohAVL* mPtDir;
        NohAVL* mPtPai;
        unsigned int mAltura; // folhas têm altura 1
};

// === Implementações das classes ================================================

using namespace std;

// === Classe NohAVL =============================================================

NohAVL::NohAVL(TChave c, const TValor& v)
    : mChave(c), mValor(v), mPtEsq(NULL), mPtDir(NULL), mPtPai(NULL), mAltura(1) {
}

NohAVL::~NohAVL() {
}

// Faz as rotações e ajustes necessários inclusive do nó pai. Atualiza a altura.
// Retorna o ponteiro para o nó que ficar na posição dele após os ajustes.
NohAVL* NohAVL::ArrumarBalanceamento() {
    AtualizarAltura(); // Atualiza a altura do Noh atual
    int fatorBal = FatorBalanceamento(); // Obtemos o fator de balanceamento do noh atual
    if (fatorBal > 1) { // Rotação direita
        if (mPtEsq->FatorBalanceamento() < 0) { // Verifica se será necessário rotação dupla
            mPtEsq = mPtEsq->RotacionarEsquerda(); // Rotação esquerda-direita
        }
        return RotacionarDireita();
    }
    else if (fatorBal < -1) { // Rotação esquerda
        if (mPtDir->FatorBalanceamento() > 0) { // Verifica se será necessário rotação dupla
            mPtDir = mPtDir->RotacionarDireita(); // Rotação direita-esquerda
        }
        return RotacionarEsquerda();
    }
    return this;
}

int NohAVL::InformarAltura(NohAVL* umNoh) {
    if (umNoh == NULL) { // Verifica se o noh é nulo
        return 0; 
    } else {
        return umNoh->mAltura; // Retorna altura do noh
    }
}


// Calcula e atualiza a altura de um nó.
void NohAVL::AtualizarAltura() {
    int altArvEsq = InformarAltura(this->mPtEsq);
    int altArvDir = InformarAltura(this->mPtDir);
    this->mAltura = 1 + max(altArvEsq, altArvDir); // Atualiza altura verificando qual sub árvore é maior
}

// Desaloca todos os descendentes.
void NohAVL::DesalocarFilhosRecursivo() {
    if (mPtEsq != NULL) { // Desaloca todos os filhos a esquerda
        mPtEsq->DesalocarFilhosRecursivo();
        delete mPtEsq;
        mPtEsq = NULL;
    }

    if (mPtDir != NULL) { // Desaloca todos os filhos a direita
        mPtDir->DesalocarFilhosRecursivo();
        delete mPtDir;
        mPtDir = NULL;
    }
}

// Calcula e retorna o fator de balanceamento do nó.
int NohAVL::FatorBalanceamento() {
    int altArvEsq = InformarAltura(this->mPtEsq);
    int altArvDir = InformarAltura(this->mPtDir);
    return altArvEsq - altArvDir;
}

// Insere um nó numa subárvore. Retorna o ponteiro para o nó que ficou no lugar do que recebeu
// a mensagem.
NohAVL* NohAVL::InserirRecursivo(NohAVL* ptNoh) {
    // Não insere nohs com chaves repetidas
    if (ptNoh->mChave < mChave) { // Chave do novo noh é menor 
        if (mPtEsq == NULL) { // Se não tem filho esquerdo adiciona
            mPtEsq = ptNoh;
            ptNoh->mPtPai = this;
        } else { // Tenta inserir de novo
            mPtEsq = mPtEsq->InserirRecursivo(ptNoh);
        }
    } else { // Chave do novo noh é maior
        if (mPtDir == NULL) { // Se não tem filho direito adiciona
            mPtDir = ptNoh;
            ptNoh->mPtPai = this;
        } else { // Tenta inserir de novo
            mPtDir = mPtDir->InserirRecursivo(ptNoh);
        }
    }
    return ArrumarBalanceamento();
}

// Busca o nó que tem a menor chave. Retorna o ponteiro para ele.
NohAVL* NohAVL::MenorRecursivo() {
    // Continua indo para o filho a esquerda até não ter filho esquerdo
    if (mPtEsq == NULL) {
        return this;
    } else {
        return mPtEsq->MenorRecursivo(); 
    }
}

// Remove o nó. Retorna o ponteiro para o nó que ficou no lugar dele.
// Confira com RemoverRecursivo(TChave).
NohAVL* NohAVL::Remover() {
    NohAVL *aux;

    if (mPtEsq == NULL) { // Não tem filho a esquerda
        aux = mPtDir;
        Transplantar(mPtDir); // tenta transplantar o filho direito
    } else if (mPtDir == NULL) { // Não tem filho a direita
        aux = mPtEsq;
        Transplantar(mPtEsq); // tenta transplantar o filho esquerdo
    } else { // Possui os 2 filhos
        NohAVL *sucessor = mPtDir->MenorRecursivo(); // Encontra o sucessor
        aux = sucessor;

        // Procedimento para remoção do noh e sua troca pelo sucessor
        // Juntamente com os ajustes necessários para o seu balanceamento

        if (sucessor->mPtPai != this) { // Verifica se o pai do sucessor não é ele mesmo
            sucessor->Transplantar(sucessor->mPtDir);
            sucessor->mPtDir = mPtDir;
            sucessor->mPtDir->mPtPai = sucessor;
        }
        Transplantar(sucessor);
        sucessor->mPtEsq = mPtEsq;
        sucessor->mPtEsq->mPtPai = sucessor;
        sucessor->ArrumarBalanceamento(); // Verifica balanceamento
    }
    return aux; // Retorna o ponteiro do noh que ficou no lugar
}

// Busca recursivamente um nó com dada chave e o remove. Retorna o ponteiro para o nó que ficou
// no lugar do nó que recebeu a mensagem.
// Confira com Remover().
NohAVL* NohAVL::RemoverRecursivo(TChave chave) {
    // Realiza a busca do noh com a chave passada como parâmetro 
    if (chave < mChave) { 
        if (mPtEsq == NULL) {
            throw runtime_error("Erro ao remover: chave não encontrada!");
        } else {
            mPtEsq = mPtEsq->RemoverRecursivo(chave);
        }
    } else if (chave > mChave) {
        if (mPtDir == NULL) {
            throw runtime_error("Erro ao remover: chave não encontrada!");
        } else {
            mPtDir = mPtDir->RemoverRecursivo(chave);
        }
    } else { // Encontrou o noh
        NohAVL *resultado = Remover();
        delete this; // Deleta o próprio noh
        return resultado; // E retorna o ponteiro para ficar no lugar
    }
    return ArrumarBalanceamento();
}

// Rotaciona à direita a subárvore. Retorna a nova raiz da subárvore.
NohAVL* NohAVL::RotacionarDireita() {
    // Procedimento para rotacionar a direita

    // Encontra o filho a esquerda
    NohAVL *ptFilho = mPtEsq;
    // Descolca o filho direito
    mPtEsq = ptFilho->mPtDir;
    if (ptFilho->mPtDir != NULL) {
        ptFilho->mPtDir->mPtPai = this;
    }
    
    // Atualiza o pai do filho
    ptFilho->mPtPai = mPtPai;

    // Verifica se é necessário a tualizar o pai de um dos filhos
    if (mPtPai == NULL) {
        // não faz nada
    } else if (this == mPtPai->mPtEsq) {
        mPtPai->mPtEsq = ptFilho;
    } else {
        mPtPai->mPtDir = ptFilho;
    }

    // Finalização da rotação
    ptFilho->mPtDir = this;
    mPtPai = ptFilho;
    AtualizarAltura(); // Atualiza a altura do próprio noh
    ptFilho->AtualizarAltura(); // Atualiza a altura do noh filho
    return ptFilho; // Retorna o noh filho
}

// Rotaciona à esquerda a subárvore. Retorna a nova raiz da subárvore.
NohAVL* NohAVL::RotacionarEsquerda() {
    // Procedimento para rotacionar a esquerda

    // Encontra o filho a direita
    NohAVL *ptFilho = mPtDir;
    // Descolca o filho direito
    mPtDir = ptFilho->mPtEsq;
    if (ptFilho->mPtEsq != NULL) {
        ptFilho->mPtEsq->mPtPai = this;
    }

    // Atualiza o pai do filho
    ptFilho->mPtPai = mPtPai;

     // Verifica se é necessário a tualizar o pai de um dos filhos
    if (mPtPai == NULL) {
        // não faz nada
    } else if (this == mPtPai->mPtEsq) {
        mPtPai->mPtEsq = ptFilho;
    } else {
        mPtPai->mPtDir = ptFilho;
    }

    // Finalização da rotação
    ptFilho->mPtEsq = this;
    mPtPai = ptFilho;
    AtualizarAltura(); // Atualiza a altura do próprio noh
    ptFilho->AtualizarAltura(); // Atualiza a altura do noh filho
    return ptFilho; // Retorna o noh filho
}

// Atualiza todas as ligações, para que ptNoh, fique no lugar deste nó.
// Usado na remoção com dois filhos.
void NohAVL::SubstitutirPor(NohAVL* ptNoh) {
    if (mPtPai != NULL) {
        if (this == mPtPai->mPtEsq) { 
            mPtPai->mPtEsq = ptNoh;
        } else {
            mPtPai->mPtDir = ptNoh;
        }
    }

    if (ptNoh != NULL) {
        ptNoh->mPtPai = mPtPai;
    }
}

// Muda as ligações do pai e do filho para desligar o nó atual.
// Usado para remoção na situação em que não existem os dois filhos.
void NohAVL::Transplantar(NohAVL* ptFilho) {
    if (mPtPai == NULL) {
        // não faz nada
    } else if (this == mPtPai->mPtEsq) {
        mPtPai->mPtEsq = ptFilho;
    } else {
        mPtPai->mPtDir = ptFilho;
    }

    if (ptFilho != NULL) {
        ptFilho->mPtPai = mPtPai;
    }
}

// Substitui um dos filhos por um novo nó.
void NohAVL::TrocarFilho(NohAVL* ptAntigo, NohAVL* ptNovo) {
    if (mPtEsq == ptAntigo) {
        mPtEsq = ptNovo;
    } else if (mPtDir == ptAntigo) {
        mPtDir = ptNovo;
    } else {
        throw runtime_error("Erro ao trocar filho: filho não encontrado!");
    }

    if (ptNovo != NULL) {
        ptNovo->mPtPai = this;
    }
}

// Busca recursivamente uma dada chave e retorna o valor associado a ela.
// Levanta exceção se não encontrar a chave.
TValor& NohAVL::Valor(TChave chave) {
    // Realiza a busca recursiva na AVL
    if (chave == mChave) {
        return mValor;
    } else if (chave < mChave) {
        if (mPtEsq == NULL) {
            throw runtime_error("Erro ao buscar valor: chave não encontrada!");
        } else {
            return mPtEsq->Valor(chave);
        }
    } else {
        if (mPtDir == NULL) {
            throw runtime_error("Erro ao buscar valor: chave não encontrada!");
        } else {
            return mPtDir->Valor(chave);
        }
    }
}

// Escreve o conteúdo de um nó no formato [altura:chave/valor].
// Escreve "[]" se o ponteiro recebido for NULL.
ostream& operator<<(ostream& saida, NohAVL* ptNoh) {
    if (ptNoh == NULL)
        saida << "[]";
    else
        saida << '[' << ptNoh->mAltura << ':' << ptNoh->mChave << '/' << ptNoh->mValor << ']';
    return saida;
}

// === Classe AVL =================================================================================
AVL::AVL() : mPtRaiz(NULL) {
}

AVL::~AVL() {
    if (mPtRaiz != NULL) {
        mPtRaiz->DesalocarFilhosRecursivo();
        delete mPtRaiz;
    }
}

// Retorna o valor associado a uma dada chave.
TValor& AVL::Valor(TChave chave) {
    if (mPtRaiz == NULL) {
        throw runtime_error("Tentativa de buscar valor numa arvore vazia.");
    } else {
        return mPtRaiz->Valor(chave);
    }
}

// verificar se as ligações entre os nós da árvore AVL estão corretas
bool AVL::ConferirLigacoes() {
    if (mPtRaiz == NULL) {
        return true;
    } else {
        return mPtRaiz->ConferirLigacoesRecursivo();
    }
}

bool NohAVL::ConferirLigacoesRecursivo() {
    bool resultado = true;
    if (mPtEsq != NULL) {
        if (mPtEsq->mPtPai != this) {
            cerr << "Erro: filho a esquerda com pai errado!" << endl;
            resultado = false;
        }
        resultado = mPtEsq->ConferirLigacoesRecursivo();
    }
    if (mPtDir != NULL)
    {
        if (mPtDir->mPtPai != this) {
            cerr << "Erro: filho a direita com pai errado!" << endl;
            resultado = false;
        }
        resultado = mPtDir->ConferirLigacoesRecursivo();
    }
    return resultado;
}

// Escreve o conteúdo da árvore nível a nível, na saída de dados informada.
// Usado para conferir se a estrutra da árvore está correta.
void AVL::EscreverNivelANivel(ostream& saida) {
    queue<NohAVL*> filhos;
    NohAVL* fimDeNivel = new NohAVL(TChave(), TValor()); // nó especial para marcar fim de um nível
    filhos.push(mPtRaiz);
    filhos.push(fimDeNivel);
    while (!(filhos.empty())) {
        NohAVL* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (!(filhos.empty()))
                filhos.push(fimDeNivel);
        }
        else {
            saida << ptNoh << ' ';
            if (ptNoh != NULL) {
                filhos.push(ptNoh->mPtEsq);
                filhos.push(ptNoh->mPtDir);
            }
        }
    }
    delete fimDeNivel;
}

// Insere um par chave/valor na árvore.
void AVL::Inserir(TChave chave, const TValor& valor) {
    NohAVL *ptNoh = new NohAVL(chave, valor);
    if (mPtRaiz == NULL) {
        mPtRaiz = ptNoh;
    } else {
        mPtRaiz = mPtRaiz->InserirRecursivo(ptNoh);
    }
}

// Remove da árvore o nó que tiver uma dada chave.
void AVL::Remover(TChave chave) {
    if (mPtRaiz == NULL){
        throw runtime_error("Tentativa de remover elemento de uma árvore vazia.");
    } else {
        mPtRaiz = mPtRaiz->RemoverRecursivo(chave);
    }
}

// === Programa ===================================================================================
int main() {
    AVL minhaArvore;
    char opcao;
    TChave chave;
    TValor valor;
    do {
        cin >> opcao;
        switch (opcao) {
            case 'i': // Inserir
                cin >> chave >> valor;
                minhaArvore.Inserir(chave, valor);
                break;
            case 'r': // Remover
                try {
                    cin >> chave;
                    minhaArvore.Remover(chave);
                }
                catch (runtime_error& erro) {
                    cerr << erro.what() << endl;
                }
                break;
            case 'b': // Buscar
                try {
                    cin >> chave;
                    valor = minhaArvore.Valor(chave);
                    cout << valor << endl;
                }
                catch (runtime_error& erro) {
                    cerr << erro.what() << endl;
                }
                break;
            case 'e': // Escrever nós nível a nível
                minhaArvore.EscreverNivelANivel(cout);
                break;
            case 'f': // Finalizar o programa
                // vai verificar depois
                break;
            default:
                cerr << "Opção inválida\n";
        }
    } while (opcao != 'f');
    return 0;
}