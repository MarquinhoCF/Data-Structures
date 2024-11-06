#include <iostream>
#include <string>

using namespace std;

class elemento{
    friend class lista;
    private:
        int chave;
        elemento *proximo;
        elemento *anterior;
    public:
        elemento (int c){
            chave = c;
            proximo = NULL;
            anterior = NULL;
        }
};

class lista{
    private:
        elemento *inicio;
        elemento *fim;
    public:
        lista();
        ~lista();        
        void insereInicio(int c);
        void insereFim (int c);
        int removeRepetidos();//retorna a quantidade de elementos restantes na lista
        void removeValor(int c);
        bool vazia();
        void imprimeLista();
};
    
lista::lista(){
    inicio = NULL;
    fim = NULL;
}
        
lista::~lista(){
    elemento* aux = inicio;
	elemento* temp = NULL;

	while (aux != NULL) {
		temp = aux;
		aux = aux->proximo;
		delete temp;
	}

	//redirecionamento de ponteiros
	inicio = NULL;
	fim = NULL;
}  

void lista::insereInicio (int c){
    // * primeiro criamos um nó
	elemento* novo = new elemento(c);

	// * agora inserimos o nó na lista
	// se a lista estiver vazia, inserimos o primeiro nó
	if (vazia()) { // ou (primeiro == NULL) ou (tamanho == 0)
		inicio = novo;
		fim = novo;
	} else { // já tem elementos na lista insere no início
		novo->proximo = inicio;
		inicio->anterior = novo;
		inicio = novo;
	}
}
        
void lista::insereFim (int c){
    // * primeiro criamos um nó
	elemento* novo = new elemento(c);

	// * agora inserimos o nó na lista
	// se a lista estiver vazia, inserimos o primeiro nó
	if (vazia()) { // ou (primeiro == NULL) ou (tamanho == 0)
		inicio = novo;
		fim = novo;
	} else { // já tem elementos na lista insere no final
		fim->proximo = novo;
		novo->anterior = fim;
		fim = novo;
	}
}
        
int lista::removeRepetidos(){
    int cont;
    elemento* auxiliar1 = inicio;
    elemento* auxiliar2;
    while (auxiliar1 != NULL){
        cont = 0;
        auxiliar2 = inicio;
        while (auxiliar2 != NULL){
            cout << auxiliar1->chave << " <--> " << auxiliar2->chave << endl;

            if (auxiliar1->chave == auxiliar2->chave) {
                cont++;
            }
            if (cont > 1) {
                removeValor(auxiliar2->chave);
            } else {
                auxiliar2 = auxiliar2->proximo;
            }
        }

        auxiliar1 = auxiliar1->proximo;
    }

    cont = 1;
    auxiliar1 = inicio;
    while (auxiliar1 != NULL){
        cont++;
        auxiliar1 = auxiliar1->proximo;
    }

    return cont;
}

void lista::removeValor(int c) {
	elemento* aux = inicio;

    cout << c << endl;

	while ((aux != NULL) && (aux->chave != c)) {
		aux = aux->proximo;
	}

	if (aux == NULL) {
		cerr << "Erro: remocao de valor não encontrado!!" << endl;
		exit(EXIT_FAILURE);
	} else {
		elemento* anterior = aux->anterior;
		elemento* proximo = aux->proximo;
		if (anterior != NULL) {
			anterior->proximo = proximo;
		} else {
			inicio = aux->proximo;
		}
		if (proximo != NULL) {
			proximo->anterior = anterior;
		} else {
			fim = aux->anterior;
		}
		delete aux;
	}

	if (vazia()) {
		inicio = NULL;
		fim = NULL;
	}
}
        
void lista::imprimeLista(){
    if (inicio != NULL){
        elemento *auxiliar = inicio;
        while (auxiliar->proximo != NULL){
            cout<<"("<<auxiliar->chave<<") ";
            auxiliar =  auxiliar->proximo;
        }
        cout<<"("<<auxiliar->chave<<")"<<endl;
    } else {
        cout<<"VAZIA";
    }
}

bool lista::vazia(){
    return (inicio == NULL);
}
    
int main(){
    
    lista listaD;
    
    int chave;
    string dado;
    
    cin>>chave;
    
    while (chave != -1){
        listaD.insereFim(chave);        
        cin>>chave;  
    }
    cout<<listaD.removeRepetidos()<<endl;
    listaD.imprimeLista();
    
    return 0;
}