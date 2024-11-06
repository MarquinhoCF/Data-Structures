## Projeto Prático - Etapa 2

# Tratamento de Arquivos e Ordenação em Memória Secundária

Grupo 1 - Alunos:

Nome: Marcos Carvalho Ferreira -- Turma: 14B -- Matrícula: 202010203
Nome: Willian Brandão de Souza -- Turma: 14A -- Matrícula: 202220233


### Objetivo

Este projeto prático tem como objetivo implementar um sistema capaz de converter um arquivo CSV em um formato binário.

Na etapa 1 do projeto foi necessário implementar o sistema que converte de CSV para binário e um sistema para realizar o tratamento e manipulação dos dados do arquivo binário.

Na etapa 2 em utilizar o arquivo binário criado a partir do sistema da primeira etapa e ordená-lo a partir do método de ordenação externa. Os dados do arquivo e o processo de armazenamento e ordenação deverão utilizar arquivos em formato binário. A estratégia de ordenação utilizada foi Mergesort Multiway.


### Funcionalidades

- csv2bin.cpp: Este código é responsável por realizar a conversão de um arquivo CSV para um arquivo binário. Ele lê o arquivo CSV, processa os dados e os armazena em um formato binário eficiente. Não é necessário digitar o nome da base de dados, porém garanta que o arquivo esteja na mesma pasta do executável do código, o arquivo será salvo automaticamente com o nome "arqBin.bin". Na base de dados "international-trade-june-2022-quarter-csv.csv" alguns do valores de "Value" estão vazios, nesses casos o sistema considera como valor 0.

- manipulaArqBin.cpp: Este código é responsável por realizar a leitura e o tratamento do arquivo binário gerado pela conversão do arquivo CSV. Ele permite que os dados sejam manipulados e analisados de acordo com as necessidades do usuário. Não é necessário digitar o nome da base de dados binária, porem garanta que o arquivo esteja na mesma pasta do executável do código. Este código foi tratado para a maioria dos erros que algum usuário pudesse cometer ao submeter os dados ao sistema, porém ao digitar um valor muito grande que supere a memória de um inteiro/unsigned int/float (quando solicitado) o programa irá terminar a execução.

- sortFile.cpp: Este código é responsável por realizar a ordenação externa do arquivo binário resultante dos códigos anteriores "arqBin.bin", transformando-o em um arquivo binário ordenado final. Foi atribuído que a ordenação fosse em ordem decrescente e utilizasse os seguintes atributos-chave para comparação: "Product_type" e "Value", sendo o primeiro atributo considerado o ordenador primário e o segundo o secundário em caso de empates. A estratégia implementada é o Multiway MergeSort, que envolve a criação de arquivos temporários, ordenação dos registros nesses arquivos e, em seguida, a mesclagem dos arquivos temporários para obter o arquivo final ordenado. Não é necessário digitar o nome do arquivo ordenado a ser criado, ele será salvo automaticamente com o nome "arqBinOrdenado.bin"

- manipulaArqBinOrdenado.cpp: A aplicação “manipulaArqBinOrdenado.cpp” é uma adaptação da aplicação “manipulaArqBin.cpp”. Ela é uma cópia da aplicação da etapa passada, possuindo as mesmas funções implementadas anteriormente. Sua única modificação é que ela abrirá por padrão o arquivo binário “arqBinOrdenado.bin” (linha de código 13) e possibilitará avaliar o resultado da ordenação pelo método Multiway MergeSort. 


### Como usar o projeto

Siga as instruções abaixo para utilizar o projeto em seu ambiente de desenvolvimento:

1 - Para o "csv2bin.cpp" não é necessário passar nada como argumento (inclusive o nome do arquivo), tanto da base de dados em CSV quanto no arquivo binário (.bin). Porém não modifique a nomenclatura de nenhum arquivo, caso contrário os arquivos não serão encontrados pelo sistema.

2 - Compile e execute o código "csv2bin.cpp" utilizando o compilador C++ de sua preferência ou IDE.

3 - Após a execução bem-sucedida do csv2bin, será gerado um arquivo binário com o nome "arqBin.bin".

4 - Compile e execute o código "manipulaArqBin.cpp" utilizando o compilador C++ de sua preferência ou IDE.

5 - Durante a execução do código "manipulaArqBin.cpp" selecione a opção desejada e siga o passo a passo indicado pelas saídas de texto do terminal.

6 - Para o "sortFile.cpp" não é necessário passar nada como argumento (inclusive o nome do arquivo binário). Não modifique a nomenclatura do arquivo binário "arqBin.bin", caso contrário ele não será encontrado pelo sistema.

7 - Compile e execute o código "sortFile.cpp" utilizando o compilador C++ de sua preferência ou IDE, e aguarde a ordenação ser executada.

8 - Após a execução bem-sucedida do sortFile, será gerado um novo arquivo binário com o nome "arqBinOrdenado.bin".

9 - Compile e execute o código "manipulaArqBinOrdenado.cpp" utilizando o compilador C++ de sua preferência ou IDE.

5 - Durante a execução do código "manipulaArqBin.cpp" selecione a opção desejada e siga o passo a passo indicado pelas saídas de texto do terminal.


### Requisitos do Sistema

- Compilador C++ compatível com o padrão C++11 ou superior.
- Sistema operacional compatível (Windows, Linux, macOS).
