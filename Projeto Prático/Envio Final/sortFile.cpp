/**
    sortFile, recebe um arquivo binario e cria um arquivo binario ordenado com os dados do arquivo passado
    by Marcos & Willian, 2023

    Ordenaçao: Decrescente
    -> Primario: Product_type   -> Secundario: Value

**/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

// Tamanho dos vetores de char do registro
const int ACCOUNT_QTD = 8;
const int CODE_QTD = 8;
const int COUNTRY_CODE_QTD = 26;
const int PRODUCT_TYPE_QTD = 10;
const int STATUS_QTD = 1;

/*
Registro para os dados do arquivo CSV.
Os atributos tem o nome do cabecalho do arquivo csv.
 */
struct DadosCSV
{
    int Time_ref;
    float Value;
    char Account[ACCOUNT_QTD], Code[CODE_QTD], Country_code[COUNTRY_CODE_QTD],
        Product_type[PRODUCT_TYPE_QTD], Status[STATUS_QTD];
};

// Sobrecarda do operador ">", a comparacao primaria sera a partir de Product_Type,
// caso o resultado primario seja igual, a comparaçao sera feita a partir de Value
bool operator>(const DadosCSV &d1, const DadosCSV &d2)
{
    bool status;
    int comparacao = strcmp(d1.Product_type, d2.Product_type);

    if (comparacao == 0) // A comparacao entre os Product_type resultou em empate
    {
        status = (d1.Value > d2.Value);
    }
    else if (comparacao > 0) // d1 é maior que d2
    {
        status = true;
    }
    else // d2 é maior que d1
    {
        status = false;
    }
    return status;
}

// ================== Implementação de uma Max Heap característica ========================

// Registro para ordenacao dos DadosCSV
struct noh
{
    // Dado a ser ordenado
    DadosCSV dado;

    // indice no vetor de arquivos que representa de qual arquivo o dado veio
    int indice;
};

// maxHeap para identificar o maior dado e realizar a ordenacao dos dados
class maxHeap
{
private:
    // Atributos da Heap:
    noh *heap;
    int capacidade;
    int tamanho;
    // Métodos auxiliares:
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i);
    void arruma();
    void corrigeDescendo(int i);
    void corrigeSubindo(int i);

public:
    maxHeap(int cap);
    ~maxHeap();
    noh retiraRaiz();
    void insere(noh d);
};

maxHeap::maxHeap(int cap)
{
    capacidade = cap;
    heap = new noh[cap];
    tamanho = 0;
}

maxHeap::~maxHeap()
{
    delete[] heap;
}

void maxHeap::arruma()
{
    // Arruma inicará da metade do vetor "heap" e ate que chegue a raiz ele decrementa chamando corrigeDescendo
    // Como nossa heap começa em 0 temos q subtrair 1
    for (int i = (tamanho / 2 - 1); i >= 0; i--)
    {
        corrigeDescendo(i);
    }
}

int maxHeap::pai(int i)
{
    return (i - 1) / 2;
}

int maxHeap::esquerdo(int i)
{
    return (2 * i) + 1;
}

int maxHeap::direito(int i)
{
    return (2 * i) + 2;
}

void maxHeap::corrigeDescendo(int i)
{
    int esq = esquerdo(i);
    int dir = direito(i);
    int maior = i;

    // se a posição de "esq" não for inválida, comparo "esq" com maior e se for necessário atualizo maior
    if ((esq < tamanho) && (operator>(heap[esq].dado, heap[maior].dado)))
    {
        maior = esq;
    }

    // se a posição de "dir" não for inválida, comparo "dir" com maior e se for necessário atualizo maior
    if ((dir < tamanho) && (operator>(heap[dir].dado, heap[maior].dado)))
    {
        maior = dir;
    }

    // se maior não for i mais, é preciso trocar e chamar recursivamente corrigeDescendo novamente
    // note que se maior for trocado ele sempre terá profundidade maior que anteriormente
    if (maior != i)
    {
        swap(heap[i], heap[maior]);
        corrigeDescendo(maior);
    }
}

void maxHeap::corrigeSubindo(int i)
{
    int p = pai(i);

    // Se o valor de i for maior que o valor que estiver em pai, é necessário trocar
    if (operator>(heap[i].dado, heap[p].dado))
    {
        swap(heap[i], heap[p]);
        corrigeSubindo(p);
    }
}

void maxHeap::insere(noh d)
{
    if (tamanho == capacidade)
    {
        cout << "Impossivel inserir em heap cheio." << endl;
        return;
    }
    heap[tamanho] = d;
    corrigeSubindo(tamanho);
    tamanho++;
}

noh maxHeap::retiraRaiz()
{
    if (tamanho == 0)
    {
        cerr << "Impossivel retirar de heap vazia." << endl;
        exit(EXIT_FAILURE);
    }
    noh aux = heap[0];
    swap(heap[0], heap[tamanho - 1]);
    tamanho--;
    corrigeDescendo(0);
    return aux;
}

// ===================== Método de Ordenação: MergeSort =====================

// Metodo auxiliar para mergesort
void merge(DadosCSV *vet, int inicio, int meio, int fim)
{
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // Cria vetores temporarios para ordenacao
    DadosCSV *L = new DadosCSV[n1];
    DadosCSV *R = new DadosCSV[n2];

    // Copia os dados para os vetores temporarios L[] e R[]
    for (i = 0; i < n1; i++)
    {
        L[i] = vet[inicio + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = vet[meio + 1 + j];
    }
    // Merge os vetores temporarios de volta para o vetor original
    i = 0;      // Indice inicial do primeiro subvetor
    j = 0;      // Indice inicial do segundo subvetor
    k = inicio; // Indice inicial do subvetor ordenaddo
    // Compara os subvetores e faz a ordenacao
    while (i < n1 && j < n2)
    {
        if (L[i] > R[j])
        {
            vet[k] = L[i];
            i++;
        }
        else
        {
            vet[k] = R[j];
            j++;
        }
        k++;
    }
    // Aqui apenas um dos vetores tem elementos ordenados
    //  Copia os elementos restantes de L[], se houver algum,
    while (i < n1)
    {
        vet[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver algum
    while (j < n2)
    {
        vet[k] = R[j];
        j++;
        k++;
    }
}

// ordena o vetor de Registros - Ordenaçao recursica Merge Sort
void mergesort(DadosCSV *vet, int inicio, int fim)
{
    if (inicio < fim)
    {
        // Encontra o meio do vetor
        int meio = inicio + (fim - inicio) / 2;

        // Ordena a primeira e a segunda metade
        mergesort(vet, inicio, meio);
        mergesort(vet, meio + 1, fim);

        // Junta as duas metades
        merge(vet, inicio, meio, fim);
    }
}

// ========================== Implementação da estratégia de Ordenação Externa ============================

// cria um arquivo ordenado a partir dos arquivos temporarios criados em criarArqsTemp()
void multiwayMergeSort(string arq_saida, int qtdArqTemp)
{
    fstream arqSaida(arq_saida, ios::out | ios::binary);
    fstream arqEntrada[qtdArqTemp]; // Vetor de arquivos temporarios ja ordenados para leitura

    for (int i = 0; i < qtdArqTemp; i++)
    {
        string nome = "arqTemp";
        nome += to_string(i);
        nome += ".txt";
        arqEntrada[i].open(nome, ios::in | ios::binary);
    }

    // O vetor "vetNohs" permite gerenciar a entrada de registros a medida que vao sendo ordenados
    // ja que cada noh guarda o índice do arquivo de origem em seu registro
    noh vetNohs[qtdArqTemp];
    maxHeap maxheap(qtdArqTemp);

    int i;
    // adiciona o primeiro dado de cada arquivo no maxHeap
    for (i = 0; i < qtdArqTemp; i++)
    {
        arqEntrada[i].read((char *)&vetNohs[i].dado, sizeof(DadosCSV));
        vetNohs[i].indice = i;
        maxheap.insere(vetNohs[i]);
    }
    int contador = 0;

    // Arquivos sao lidos e armazenados na maxheap ate a acabar a leitura de todos os arquivos
    while (contador != i)
    {

        noh raiz = maxheap.retiraRaiz();                      // obtem-se a raiz
        arqSaida.write((char *)&raiz.dado, sizeof(DadosCSV)); // escreve-se o registro da raiz obtida no arquivo de Saída

        // Reposiciona-se os ponteiros nos arquivos temporarios de entrada atual
        int atual = (int)arqEntrada[raiz.indice].tellg();
        arqEntrada[raiz.indice].seekg(0, arqEntrada[raiz.indice].end);
        int tam = (int)arqEntrada[raiz.indice].tellg();
        arqEntrada[raiz.indice].seekg(0, arqEntrada[raiz.indice].beg);
        arqEntrada[raiz.indice].seekg(atual);

        // Adiciona um novo dado a heap enquanto o arquivo de entrada ainda possuir dados
        if (arqEntrada[raiz.indice].tellg() != tam)
        {
            arqEntrada[raiz.indice].read((char *)&raiz.dado, sizeof(DadosCSV));
            maxheap.insere(raiz);
        }
        else // Conta-se mais um arquivo lido quando antinge o tamanho maximo
        {
            contador++;
        }
    }

    // Fecha e exlui todos os arquivos temporários
    for (int i = 0; i < qtdArqTemp; i++)
    {
        arqEntrada[i].close();
        string nome = "arqTemp";
        nome += to_string(i);
        nome += ".txt";
        const char *arq = nome.c_str();
        remove(arq);
    }
    arqSaida.close();
}

// Usado para criaçao de varios arquivos temporarios ordenados com o quicksort a partir do arquivo binario de entrada desordenado
int criarArqsTemp(fstream &arquivo, int nRegPorArq)
{
    DadosCSV *vetor = new DadosCSV[nRegPorArq];

    int total = 0;      // Total de dados no vetor
    int numArqTemp = 0; // Conta o numero de arquivos temporarios criados

    arquivo.seekg(0, arquivo.end);
    int tamanho = (int)arquivo.tellg(); // Obtem-se o tamanho do arquivo
    arquivo.seekg(0, arquivo.beg);

    // Enquanto existe dados no arquivo
    while (arquivo.tellg() != tamanho)
    {
        // Le um registro do arquivo e armazena na posiçao do vetor
        arquivo.read((char *)&vetor[total], sizeof(DadosCSV));
        total++;

        // Enquanto nao atingir o tamanho max por arquivo (definido no main),
        // o vetor e ordenado de registros e ordenado e salvo em um arquivo temporario
        if (total == nRegPorArq)
        {
            mergesort(vetor, 0, nRegPorArq - 1);

            // Criação dos nomes dos arquivos de acordo com a quantidade:
            string nome = "arqTemp";
            nome += to_string(numArqTemp);
            nome += ".txt";

            // Cria o arquivo temporario
            fstream arqsTemp(nome, ios::out | ios::binary);

            // Adiciona os registros de cada posicao do vetor no arquivo recem criado
            for (int j = 0; j < nRegPorArq; j++)
            {
                arqsTemp.write((char *)&vetor[j], sizeof(DadosCSV));
            }

            // Conta mais 1 arquivo e prepara para o próximo
            numArqTemp++;
            total = 0;
            arqsTemp.close();
        }
    }

    // Mais um arquivo e criado caso o vetor ainda tenha conteudo e nao tenha atingido o tamanho maximo do arquivo.
    if (total > 0)
    {
        mergesort(vetor, 0, total - 1);

        // Repetição do mesmo trecho acima para realizar o salvamento dos dados
        string nome = "arqTemp";
        nome += to_string(numArqTemp);
        nome += ".txt";
        fstream arqsTemp(nome, ios::out | ios::binary);
        for (int j = 0; j < total; j++)
        {
            arqsTemp.write((char *)&vetor[j], sizeof(DadosCSV));
        }
        numArqTemp++;
        arqsTemp.close();
    }

    delete vetor;
    return numArqTemp;
}
// ================================== Função Principal ========================================

int main()
{
    cout << "**********************************" << endl;
    cout << "\n****   Ordenacao Externa      ****" << endl;
    cout << "\n**********************************" << endl;

    fstream arquivo("arqBin.bin", ios::in | ios::out | ios::binary);

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo)
    {
        cout << "\n\n*********************************" << endl;
        cout << "\n***    Arquivo Aberto    ***" << endl;
        cout << "\n********************************" << endl;

        cout << "\n\nCriando os Arquivos Temporarios... Aguarde..." << endl;
        int nRegPorArq = 5000; // quantidade de registros em cada arquivo temp
        int totalArqTemp = criarArqsTemp(arquivo, nRegPorArq);
        arquivo.close();

        cout << "\n\nOrdenando o Arquivo por Multi-Way Mergesort... Aguarde mais um pouco..." << endl;
        multiwayMergeSort("arqBinOrdenado.bin", totalArqTemp);

        cout << "\n**************************************" << endl;
        cout << "\n*****   Ordenado com Sucesso!!   *****" << endl; // Se tudo der certo
        cout << "\n**************************************" << endl;
    }
    else
    {
        cout << "**************************************" << endl;
        cout << "\n***   Arquivo nao foi encontrado   ***" << endl; // Se tudo der errado
        cout << "\n**************************************" << endl;
    }
    return 0;
}