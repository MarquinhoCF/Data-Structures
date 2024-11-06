/**
    manipulaArBin, permite manipulacao de algumas operacoes no arquivo binario gerado pelo csv2bin
    by Marcos & Willian, 2023
**/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

fstream arquivo("arqBinOrdenado.bin", ios::in | ios::out | ios::binary);

// Tamanho dos vetores de char do registro
const int ACCOUNT_QTD = 8;
const int CODE_QTD = 8;
const int COUNTRY_CODE_QTD = 26;
const int PRODUCT_TYPE_QTD = 10;
const int STATUS_QTD = 1;

/*
Registro para os dados do arquivo CSV.
 */
struct DadosCSV
{
    int Time_ref;
    float Value;
    char Account[ACCOUNT_QTD], Code[CODE_QTD], Country_code[COUNTRY_CODE_QTD],
        Product_type[PRODUCT_TYPE_QTD], Status[STATUS_QTD];
};

DadosCSV dado; // Variavel para executar as operacoes com os dados do arquivo.
unsigned int nPosicoes;

///------------------------------- FUNCOES AUXILIARES -------------------------------///

/*
Atualiza a variável global "nPosicoes" q indica a quantidade de posicoes ocupadas
Usado em:
main()
 */
unsigned int calculaNPosicoes()
{
    arquivo.seekg(0, arquivo.end);
    int tam = (int)arquivo.tellg();
    arquivo.seekg(0, arquivo.beg);
    nPosicoes = tam / sizeof(DadosCSV);
    return nPosicoes;
}

/*
Verifica se uma sequencia de caracteres eh numerica, além disso ela diferencia valores int e ponto flutuante.
A variável booleana "ehFloat" faz com que os "." sejam ignorados, e assim aceita esses valores como numéricos.
Usado em:
verificadorErro()
*/
bool ehNumerico(const string &texto, bool ehFloat)
{
    bool ok = true;
    for (char const &c : texto)
    {
        if ((isdigit(c) == 0))
        {
            if ((ehFloat) && (c == '.')) // ignora a virgula
            {
                ok = true;
            }
            else // retorna falso logo na primeira vez em que achar um caractere que nao e um digito
            {
                return false;
            }
        }
    }
    return ok;
}

/*
Funcao para verificar se os dados de entrada estao de acordo com o esperado pelo registro
n = 1 para valores inteiros, n =2 para valores ponto flutuante e 3 para textos.
Usada em:
leDadosUsuario()
*/
bool verificadorErro(unsigned int n, const string &linha, unsigned int tamanhoVetor = 0)
{
    bool ok = true;

    if (linha.size() == 0)
    { // Verifica se enquadra em um erro comum
        n = 4;
    }
    switch (n)
    {       // Cada opção chama sua função e pede seus parâmetros
    case 1: // Verifica se os valores são inteiros
        ok = ehNumerico(linha, false);
        break;
    case 2: // Verifica se os valores são ponto flutuante
        ok = ehNumerico(linha, true);
        break;
    case 3: // Verifica erro pelo tamanho da string
        if ((linha.size() == 1) && (tamanhoVetor == 1))
        { // Caso único de tipo char
            ok = true;
        }
        else if (linha.size() >= tamanhoVetor)
        {
            ok = false;
            if (tamanhoVetor == 1)
            {
                cout << "A string que voce digitou superou o tamanho esperado!\nDigite um texto de " << tamanhoVetor << " caracteres" << endl;
            }
            else
            {
                cout << "A string que voce digitou superou o tamanho esperado!\nDigite um texto de " << tamanhoVetor - 1 << " caractere" << endl;
            }
        }
        break;
    case 4: // Tratamento de erro comum: O usuário não digitou nenhum caracter
        cout << "Voce nao digitou nada!" << endl;
        ok = false;
        break;
    default:
        cout << "VERIFICA ERRO SEM VALOR" << endl;
        break;
    }
    return ok;
}
/*
Funcao usada para os imprimir atributos do registro.
Usado nas funçoes:
lerFaixaRegistros()
imprimirTodos()
 */
void imprimir()
{
    cout << endl
         << "*********************************************" << endl;
    cout << "Time_ref           : " << dado.Time_ref << endl;
    cout << "Account            : " << dado.Account << endl;
    cout << "Code               : " << dado.Code << endl;
    cout << "Country_code       : " << dado.Country_code << endl;
    cout << "Product_type       : " << dado.Product_type << endl;
    cout << "Value              : " << dado.Value << endl;
    cout << "Status             : " << dado.Status << endl;
}

/*
Inserir dados do novo registro.
Usado em:
insereNaPosicao()
alterarDados()
 */
void leDadosUsuario()
{
    string linha = "";
    ////*******************************************////
    cout << "Time_ref: ";
    getline(cin, linha);
    while (!verificadorErro(1, linha))
    {
        cout << "Digite um valor tipo int!" << endl;
        cout << "Time_ref: ";
        getline(cin, linha);
    }
    cout << linha << endl;
    dado.Time_ref = atoi(linha.c_str());
    /***********************************************/
    cout << "Account: ";
    getline(cin, linha);
    while (!verificadorErro(3, linha, ACCOUNT_QTD))
    {
        cout << "Digite uma string!" << endl;
        cout << "Account: ";
        getline(cin, linha);
    }
    strcpy(dado.Account, linha.c_str());

    /*********************************************/

    cout << "Code: ";
    getline(cin, linha);
    while (!verificadorErro(3, linha, CODE_QTD))
    {
        cout << "Digite uma string!" << endl;
        cout << "Code: ";
        getline(cin, linha);
    }
    strcpy(dado.Code, linha.c_str());

    /*************************************************/

    cout << "Country_code: ";
    getline(cin, linha);
    while (!verificadorErro(3, linha, COUNTRY_CODE_QTD))
    {
        cout << "Digite uma string!" << endl;
        cout << "Country_code: ";
        getline(cin, linha);
    }
    strcpy(dado.Country_code, linha.c_str());

    /******************************************************/
    cout << "Product_type: ";
    getline(cin, linha);
    while (!verificadorErro(3, linha, PRODUCT_TYPE_QTD))
    {
        cout << "Digite uma string!" << endl;
        cout << "Product_type: ";
        getline(cin, linha);
    }
    strcpy(dado.Product_type, linha.c_str());

    /******************************************************/
    cout << "Value: ";
    getline(cin, linha);
    while (!verificadorErro(2, linha))
    {
        cout << "Digite um valor tipo float!" << endl;
        cout << "Value: ";
        getline(cin, linha);
    }
    dado.Value = stof(linha.c_str());

    /*****************************************************/
    cout << "Status: ";
    getline(cin, linha);
    while (!verificadorErro(3, linha, STATUS_QTD))
    {
        cout << "Status: ";
        getline(cin, linha);
    }
    strcpy(dado.Status, linha.c_str());

    /***************************************************/
    cout << "\n\n\n... ...AGUARDE A INSERCAO DOS DADOS... ..." << endl;
}

///------------------------------- FUNCOES PARA OPERACOES -------------------------------///

/*
Troca 2 registros de posicao, criacao de um registro temporario que le os atributos de uma posicao enquanto o registro 'dado' le
da outra posicao, o ponteiro e reposicionado e invertem a escrita.
Primiera posicao = pos1.
Segunda posicao = pos2.
 */
void trocarPosicao(unsigned int pos1, unsigned int pos2)
{
    DadosCSV temp;
    arquivo.seekg((pos1 - 1) * sizeof(DadosCSV));  // posicionamento do ponteiro
    arquivo.read((char *)&dado, sizeof(DadosCSV)); // Le o registro do arquivo e manda para 'dado'
    arquivo.seekg((pos2 - 1) * sizeof(DadosCSV));  // posicionamento do ponteiro
    arquivo.read((char *)&temp, sizeof(DadosCSV)); // Le o registro do arquivo e manda para 'temp'
    arquivo.seekg((pos2 - 1) * sizeof(DadosCSV));
    arquivo.write((char *)&dado, sizeof(DadosCSV)); // Escreve o conteúdo de dado no arquivo na posição definida
    arquivo.seekg((pos1 - 1) * sizeof(DadosCSV));
    arquivo.write((char *)&temp, sizeof(DadosCSV));
}

/*
Cria um novo registro no final do arquivo atraves da chamada da funcao 'leDadosUsuario'
Realiza a chamada da funcao 'trocarPosicao' para ir substituindo os arquivos ate chegar na posicao selecionada
 */

void insereNaPosicao(unsigned int pos)
{
    arquivo.seekg(0, arquivo.end);                               // Posiciona no fim
    leDadosUsuario();                                            // leDadosUsuario os atributos
    arquivo.write((char *)&dado, sizeof(DadosCSV));              // Escreve no final
    arquivo.seekg(0, arquivo.end);                               // Posiciona no fim
    int totalArq = int(arquivo.tellg()) / int(sizeof(DadosCSV)); // Encontra o total de registros
    for (unsigned int i = 0; i < (totalArq - pos); i++)
    { // Chama a funcao 'trocarPosicao' que troca os valores da posicao final ate a selecionada pelo usuario
        trocarPosicao(totalArq - i - 1, totalArq - i);
    }
}
/*
Recebe as posicoes que o usuario deseja e chama a funcao 'imprimir' e imprime todo os registros entre essas posicoes.
 */

void lerFaixaRegistros(int pos1, int pos2)
{
    arquivo.seekg((pos1 - 1) * sizeof(DadosCSV));
    for (int i = 0; i <= (pos2 - pos1); i++)
    {
        arquivo.read((char *)&dado, sizeof(DadosCSV));
        imprimir();
    }
}

/*
Recebe a posicao que o usuario deseja preencher e chama a funcao 'leDadosUsuario' para que o usuario possa digitar os valores desejados.
 */
void alterarDadosCSV(int pos)
{
    arquivo.seekg((pos - 1) * sizeof(DadosCSV));
    leDadosUsuario();
    arquivo.write((char *)&dado, sizeof(DadosCSV));
}

/*
Imprime todos os os dados.
Chama a funcao 'imprimir'
 */
void imprimirTodos()
{
    arquivo.seekg(0, arquivo.end);
    int tam = (int)arquivo.tellg();
    arquivo.seekg(0, arquivo.beg);
    while (arquivo.tellg() != tam)
    {
        arquivo.read((char *)&dado, sizeof(DadosCSV));
        imprimir();
    }
}

///------------------------------- Selecao do usuario ----------------------------------///

/*
Permite a selecao que o usuario deseja executar
 */
unsigned int selecao()
{
    cout << "\n>>>>>>>>>>>>>>>>>>>>> SELECIONE A OPCAO DESEJADA <<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "Selecione \"1\" para adicionar elemento em posicao especifica" << endl;
    cout << "Selecione \"2\" para visualizar uma faixa de registros" << endl;
    cout << "Selecione \"3\" para alterar os dados de um registro em uma posicao especifica" << endl;
    cout << "Selecione \"4\" para trocar dois registros de posicao" << endl;
    cout << "Selecione \"5\" para imprimir todos os registros" << endl;
    cout << "Selecione \"6\" para saber o total de registros" << endl;
    cout << "Selecione \"7\" para sair" << endl;
    cout << "\nPara selecionar uma opcao digite apenas o numero desejado " << endl;
    cout << "Selecione a opcao desejada: ";
    string linha;
    getline(cin, linha);
    while (!verificadorErro(1, linha)) // verifica se valor e inteiro valido
    {
        cout << "Digite um valor tipo int!" << endl;
        cout << "Selecione a opcao desejada: ";
        getline(cin, linha);
    }
    int opc = atoi(linha.c_str());
    cout << "\n>>>>>>>>>>>>>>>>>>>>> OPCAO " << opc << " SELECIONADA <<<<<<<<<<<<<<<<<<<<<" << endl;
    return opc;
}

///------------------------------- main ----------------------------------///

int main()
{
    int n = 0;
    unsigned int pos, pos2;
    bool errado;
    string resposta;
    if (arquivo)
    { // Se abrir corretamente
        cout << "\n\n*********************************" << endl;
        cout << "\n***    Arquivo Aberto    ***" << endl;
        cout << "\n********************************" << endl;
        nPosicoes = calculaNPosicoes();
        while (n != 7)
        {
            n = selecao();
            // Cada opção da funcao 'selecao' retorna um valor que é usado como parametro do switch case
            switch (n)
            {
            case 1: // Adiciona um registro na posicao definida pelo usuario
                cout << "Em qual posicao adicionar?: ";
                getline(cin, resposta);
                errado = true;
                // inicio do tratamento de erros da entrada do usuário para inteiros válidos ( maiores que 0 e igual ao tamanho maximo do registro)
                while (errado)
                {
                    while (!verificadorErro(1, resposta))
                    {
                        cout << "Digite um valor tipo int!" << endl;
                        cout << "Em qual posicao adicionar?: ";
                        getline(cin, resposta);
                    }

                    pos = stoi(resposta.c_str());

                    if (pos == 0)
                    {
                        cout << "A posicao 0 e invalida!" << endl;
                    }
                    else if (pos > (nPosicoes + 1))
                    {
                        cout << "A posicao maxima que voce pode adicionar e " << nPosicoes + 1 << "!" << endl;
                    }
                    else
                    {
                        errado = false;
                    }

                    if (errado)
                    {
                        cout << "Em qual posicao adicionar?: ";
                        getline(cin, resposta);
                    }
                }
                // fim do tratamento de erros da entrada do usuário para inteiros válidos
                insereNaPosicao(pos); // Chama a funcao para inserir registro na posicao selecionada pelo usuario
                calculaNPosicoes();   // atualiza tamanho do registro
                break;

            case 2: // Seleciona um intervalo para impressao dos registros
                cout << "Entre quais posicoes visualizar?" << endl;
                cout << "DICA: selecione a mesma posicao 2 vezes para visualiza-la\n-> Menor posicao: ";
                getline(cin, resposta);
                // inicio do tratamento de erros da entrada do usuário para inteiros válidos ( maiores que 0 e igual ao tamanho maximo do registro)
                errado = true;
                while (errado)
                {
                    while (!verificadorErro(1, resposta))
                    {
                        cout << "Digite um valor tipo int!" << endl;
                        cout << "-> Menor posicao: ";
                        getline(cin, resposta);
                    }

                    pos = stoi(resposta.c_str());

                    if (pos == 0)
                    {
                        cout << "A posicao 0 e invalida!" << endl;
                    }
                    else if (pos > (nPosicoes))
                    {
                        cout << "A menor posicao para visualizacao nao aceita valores maiores que " << nPosicoes << "!" << endl;
                    }
                    else
                    {
                        errado = false;
                    }

                    if (errado)
                    {
                        cout << "-> Menor posicao: ";
                        getline(cin, resposta);
                    }
                }

                cout << "-> Maior posicao: ";
                getline(cin, resposta);
                errado = true;
                while (errado)
                {
                    while (!verificadorErro(1, resposta))
                    {
                        cout << "Digite um valor tipo int!" << endl;
                        cout << "-> Maior posicao: ";
                        getline(cin, resposta);
                    }

                    pos2 = stoi(resposta.c_str());

                    if (pos2 == 0)
                    {
                        cout << "A posicao 0 e invalida!" << endl;
                    }
                    else if (pos2 > (nPosicoes))
                    {
                        cout << "A maior posicao para visualizacao nao aceita valores maiores que " << nPosicoes << "!" << endl;
                    }
                    else if (pos2 < pos)
                    {
                        cout << "O valor digitado e menor que o primeiro!" << endl;
                    }
                    else
                    {
                        errado = false;
                    }

                    if (errado)
                    {
                        cout << "-> Maior posicao: ";
                        getline(cin, resposta);
                    }
                }
                // fim do tratamento de erros da entrada do usuário para inteiros válidos

                lerFaixaRegistros(pos, pos2);
                break;

            case 3: //
                cout << "Em qual posicao alterar os dados?: ";
                getline(cin, resposta);
                // inicio do tratamento de erros da entrada do usuário para inteiros válidos ( maiores que 0 e igual ao tamanho maximo do registro)
                errado = true;
                while (errado)
                {
                    while (!verificadorErro(1, resposta))
                    {
                        cout << "Digite um valor tipo int!" << endl;
                        cout << "Em qual posicao adicionar?: ";
                        getline(cin, resposta);
                    }

                    pos = stoi(resposta.c_str());

                    if (pos == 0)
                    {
                        cout << "A posicao 0 e invalida!" << endl;
                    }
                    else if (pos > nPosicoes)
                    {
                        cout << "A posicao maxima que voce pode alterar e " << nPosicoes << "!" << endl;
                    }
                    else
                    {
                        errado = false;
                    }

                    if (errado)
                    {
                        cout << "Em qual posicao adicionar?: ";
                        getline(cin, resposta);
                    }
                }
                // fim do tratamento de erros da entrada do usuário para inteiros válidos

                alterarDadosCSV(pos);
                break;

            case 4: // Troca posicoes definidas pelo usuario
                cout << "Quais posicoes trocar?\n-> Primeira posicao: ";
                getline(cin, resposta);
                // inicio do tratamento de erros da entrada do usuário para inteiros válidos ( maiores que 0 e igual ao tamanho maximo do registro, além do valor pos < pos1)
                errado = true;
                while (errado)
                {
                    while (!verificadorErro(1, resposta))
                    {
                        cout << "Digite um valor tipo int!" << endl;
                        cout << "-> Primeira posicao: ";
                        getline(cin, resposta);
                    }

                    pos = stoi(resposta.c_str());

                    if (pos == 0)
                    {
                        cout << "A posicao 0 e invalida!" << endl;
                    }
                    else if (pos > nPosicoes - 2)
                    {
                        cout << "A primeira posicao para troca nao aceita valores maiores que " << nPosicoes - 2 << "!" << endl;
                    }
                    else
                    {
                        errado = false;
                    }

                    if (errado)
                    {
                        cout << "-> Primeira posicao: ";
                        getline(cin, resposta);
                    }
                }

                cout << "-> Segunda posicao: ";
                getline(cin, resposta);
                errado = true;
                while (errado)
                {
                    while (!verificadorErro(1, resposta))
                    {
                        cout << "Digite um valor tipo int!" << endl;
                        cout << "-> Segunda posicao: ";
                        getline(cin, resposta);
                    }

                    pos2 = stoi(resposta.c_str());

                    if (pos2 == 0)
                    {
                        cout << "A posicao 0 e invalida!" << endl;
                    }
                    else if (pos2 == pos)
                    {
                        cout << "O valor digitado e igual ao primeiro!" << endl;
                    }
                    else if (pos2 > (nPosicoes))
                    {
                        cout << "A segunda posicao para troca nao aceita valores maiores que " << nPosicoes << "!" << endl;
                    }
                    else
                    {
                        errado = false;
                    }

                    if (errado)
                    {
                        cout << "-> Segunda posicao: ";
                        getline(cin, resposta);
                    }
                }
                // fim do tratamento de erros da entrada do usuário para inteiros válidos

                trocarPosicao(pos, pos2);
                break;

            case 5: // impressao de todos os dados
                imprimirTodos();
                break;

            case 6: // verifica tamanho do resgistro
                cout << "O arquivo tem " << nPosicoes << " registros." << endl;
                break;

            case 7: // encerra o programa
                cout << "Ate mais";
                break;

            default:
                cout << "Opcao invalida!\n\nEscolha uma das opcoes da selecao abaixo.\n";
                break;
            }
        }
        arquivo.close(); // fecha o arquivo
    }
    else
    {
        cout << "\n\n******************************************" << endl;
        cout << "\n***    Não foi encontrado o arquivo    ***" << endl;
        cout << "\n******************************************" << endl;
    }

    return 0;
}
