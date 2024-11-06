/**
    csv2bin, transforma arquivo csv em arquivo bin
    by Marcos & Willian, 2023
**/

#include <iostream>
#include <cstring>
#include <fstream>
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

int main()
{
    // ABRE OS ARQUIVOS CSV E CRIA BINÁRIO
    fstream arquivo("international-trade-june-2022-quarter-csv.csv", ios::in);
    cout << "********************************" << endl;
    cout << "\n****   Lendo o arquivo      ****" << endl; // Se tudo der certo
    cout << "\n********************************" << endl;

    if (arquivo)
    {
        fstream arqBin("arqBin.bin", ios::out | ios::binary); // cria e abre binário para salvamento dos registros
        string linha;
        string campo;
        string delimitador1 = ",\"";
        string delimitador2 = "\",\"";
        string delimitador3 = "\",";
        string delimitador4 = "\"";
        unsigned posFinalCampo;

        DadosCSV dado;

        getline(arquivo, linha); // ELIMINA O CABEÇALHO

        while (getline(arquivo, linha))
        {
            /*************************************************************************/

            // Extrai Time Ref
            posFinalCampo = linha.find(delimitador1);              // A partir do delimitador encontra a posição final do primeiro dado
            campo = linha.substr(0, posFinalCampo);                // Extrai o dado a partir dos limites encontrados
            linha.erase(0, posFinalCampo + delimitador1.length()); // Apaga-se o que foi extraído
            dado.Time_ref = stoul(campo);                          // Armazenamos o dado na struct DadosCSV

            /************************************************************************/

            // Extrai Account
            posFinalCampo = linha.find(delimitador2);
            campo = linha.substr(0, posFinalCampo);
            linha.erase(0, posFinalCampo + delimitador2.length());
            strcpy(dado.Account, campo.c_str());

            /************************************************************************/

            // Extrai Code
            posFinalCampo = linha.find(delimitador2);
            campo = linha.substr(0, posFinalCampo);
            linha.erase(0, posFinalCampo + delimitador2.length());
            strcpy(dado.Code, campo.c_str());

            /************************************************************************/

            // Extrai Country code
            posFinalCampo = linha.find(delimitador2);
            campo = linha.substr(0, posFinalCampo);
            linha.erase(0, posFinalCampo + delimitador2.length());
            strcpy(dado.Country_code, campo.c_str());

            /***********************************************************************/

            // Extrai Product type
            posFinalCampo = linha.find(delimitador3);
            campo = linha.substr(0, posFinalCampo);
            linha.erase(0, posFinalCampo + delimitador3.length());
            strcpy(dado.Product_type, campo.c_str());

            /********************************************************************/

            // Extrai value
            posFinalCampo = linha.find(delimitador1);
            campo = linha.substr(0, posFinalCampo);
            linha.erase(0, posFinalCampo + delimitador1.length());
            if (campo.length() == 0) // Caso não haja nenhum dado entre as "," assume-se 0
            {
                dado.Value = 0;
            }
            else
            {
                dado.Value = stof(campo);
            }

            /********************************************************************/

            // Extrai status
            posFinalCampo = linha.find(delimitador4);
            campo = linha.substr(0, posFinalCampo);
            linha.erase(0, posFinalCampo + delimitador4.length());
            strcpy(dado.Status, campo.c_str());

            /*********************************************************************/

            // SALVA REGISTRO NO BINÁRIO
            arqBin.write((char *)&dado, sizeof(DadosCSV)); // Escreve o arquivo binário, recebe o endereço de dado e tamanho do registro DadoCSV
        }
        cout << "*******************************" << endl;
        cout << "\n***   Escrito com sucesso   ***" << endl; // Se tudo der certo
        cout << "\n*******************************" << endl;
        arquivo.close(); // Fecha arquivo CSV
        arqBin.close();
    }
    else
    {
        cout << "**************************************" << endl;
        cout << "\n***   Arquivo não foi encontrado   ***" << endl; // Se tudo der eerado
        cout << "\n**************************************" << endl;
    }

    return 0;
}
