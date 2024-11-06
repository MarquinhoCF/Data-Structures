## Projeto Prático - Etapa 1

# Tratamento de Arquivos e Ordenação em Memória Secundária

Grupo 1 - Alunos:

Nome: Marcos Carvalho Ferreira -- Turma: 14B -- Matrícula: 202010203
Nome: Willian Brandão de Souza -- Turma: 14A -- Matrícula: 202220233

### Objetivo

Este projeto prático tem como objetivo implementar um sistema capaz de converter um arquivo CSV em um formato binário.

Na etapa 1 do projeto foi necessário implementar o sistema que converte de CSV para binário e um sistema para realizar o tratamento e manipulação dos dados do arquivo binário.

### Funcionalidades

- csv2bin.cpp: Este código é responsável por realizar a conversão de um arquivo CSV para um arquivo binário. Ele lê o arquivo CSV, processa os dados e os armazena em um formato binário eficiente. Não é necessário digitar o nome da base de dados, porem garanta que o arquivo esteja na mesma pasta do executável do código. Na base de dados "international-trade-june-2022-quarter-csv.csv" alguns do valores de "Value" estão vazios, nesses casos o sistema considera como valor 0.

- manipulaArqBin.cpp: Este código é responsável por realizar a leitura e o tratamento do arquivo binário gerado pela conversão do arquivo CSV. Ele permite que os dados sejam manipulados e analisados de acordo com as necessidades do usuário. Não é necessário digitar o nome da base de dados binária, porem garanta que o arquivo esteja na mesma pasta do executável do código. Este código foi tratado para a maioria dos erros que algum usuário pudesse cometer ao submeter os dados ao sistema, porém ao digitar um valor muito grande que supere a memória de um inteiro/unsigned int/float (quando solicitado) o programa irá terminar a execução.

### Como usar o projeto

Siga as instruções abaixo para utilizar o projeto em seu ambiente de desenvolvimento:

1 - Não é necessário passar nada como argumento (inclusive o nome dos arquivo), tanto da base de dados em CSV quanto no arquivo binário (.bin). Porém não modifique a nomenclatura de nenhum arquivo, caso contrário os arquivos não serão encontrados pelo sistema.

2 - Compile e execute o código "csv2bin.cpp" utilizando o compilador C++ de sua preferência ou IDE.

3 - Após a execução bem-sucedida do csv2bin, será gerado um arquivo binário com o nome "arqBin.bin".

4 - Compile e execute o código "manipulaArqBin.cpp" utilizando o compilador C++ de sua preferência ou IDE.

5 - Durante a execução do código "manipulaArqBin.cpp" selecione a opção desejado e siga o passo a passo indicado pelas saídas de texto do terminal.

### Requisitos do Sistema

- Compilador C++ compatível com o padrão C++11 ou superior.
- Sistema operacional compatível (Windows, Linux, macOS).
