/* 
    turma.cpp - aplicação para desenvolvimento de atividade
    de Tipo Abstrado de Dados

    Atividade de  GCC216 - Estruturas de Dados, 2020

    Solução de: Marcos Carvalho Ferreira - 202010203
*/

#include <iostream>
#include <math.h>

using namespace std;

struct aluno {
    string nomeDoAluno;
    float notas[3];
    aluno();       
};

aluno::aluno() {
    nomeDoAluno.clear();
    notas[0] = 0;
    notas[1] = 0;
    notas[2] = 0;
}


class turma {
    private:
        // *** AVISO: Não altere os atributos privados da classe *** 
        aluno* listaDeAlunos;
        int quantidadeDeAlunos;
        int capacidadeMaxima;
    public:
        turma(int capacidade);
        turma(const turma& umaTurma);
        ~turma();
        void inserirNovoAluno(const aluno& umAluno);
        bool buscarAluno(const string& nome, aluno& umAluno);
        void redimensionarCapacidade();
        friend void simularNotaFinal(turma umaTurma, float bonificacao);
};

turma::turma(int capacidade) {
    quantidadeDeAlunos = 0;
    capacidadeMaxima = capacidade;
    listaDeAlunos = new aluno[capacidadeMaxima];
}

// Construtor de cópia implementado para corrigir o problema de "falha de segmentação"
turma::turma(const turma& umaTurma) {
	// Todos os atributos são copiados
	quantidadeDeAlunos = umaTurma.quantidadeDeAlunos;
	capacidadeMaxima = umaTurma.capacidadeMaxima;
	// Crio outro vetor alocao dinamicamente
	listaDeAlunos = new aluno[capacidadeMaxima];
	// Cada item da lista é copiado
	for (int i = 0; i < quantidadeDeAlunos; i++) {
		listaDeAlunos[i] = umaTurma.listaDeAlunos[i];
	}
}

turma::~turma() {
    delete [] listaDeAlunos;
}

void turma::inserirNovoAluno(const aluno& umAluno) {
    if (quantidadeDeAlunos == capacidadeMaxima) { // vetor cheio, precisa redimensionar
        redimensionarCapacidade();
    }
    listaDeAlunos[quantidadeDeAlunos] = umAluno;
    quantidadeDeAlunos++;
}

bool turma::buscarAluno(const string& nome, aluno& umAluno) {
    int posicaoAtual = 0;

    while (posicaoAtual < quantidadeDeAlunos and 
           listaDeAlunos[posicaoAtual].nomeDoAluno != nome) 
        posicaoAtual++;

    // se posicaoAtual não for menor que quantidade de produtos, é porque não encontrou
    if (posicaoAtual < quantidadeDeAlunos) {
        umAluno = listaDeAlunos[posicaoAtual];
        return true;
    }

    return false;
}

void turma::redimensionarCapacidade() {
	// Primeiramente atualizo a capacidade máxima para 20% a mais (usando arredondamento para cima)
	capacidadeMaxima = ceil(capacidadeMaxima*1.2);
	// Crio outro vetor alocado dinamicamente com a capacidade máxima atualizada
    aluno *listaSuporte = new aluno[capacidadeMaxima];
    // Copio cada item do vetor antigo para o novo
    for(int i = 0; i < quantidadeDeAlunos; i++) {
        listaSuporte[i] = listaDeAlunos[i];
	}
	// Deleto o vetor antigo
    delete [] listaDeAlunos;
    // Utilizo do ponteiro do vetor antigo e recebo o novo
    listaDeAlunos = listaSuporte;
}

void simularNotaFinal(turma umaTurma, float bonificacao) {
    // *** AVISO: Não altere esta função *** 
    int notaFinalTemporaria;
    for (int i = 0; i < umaTurma.quantidadeDeAlunos; i++) {
        notaFinalTemporaria = bonificacao + (umaTurma.listaDeAlunos[i].notas[0] 
            + umaTurma.listaDeAlunos[i].notas[1] + umaTurma.listaDeAlunos[i].notas[2]) / 3;
        notaFinalTemporaria = min(notaFinalTemporaria,100);
        cout << umaTurma.listaDeAlunos[i].nomeDoAluno << " " << notaFinalTemporaria << endl;
    }
    cout << endl;
}


int main() {
    // *** AVISO: Não altere a função principal, o main() *** 
    int capacidadeInicial;

    cout << "Turma - Aplicativo para Calcular Média Final\n" 
         << "Entre com capacidade máxima inicial da turma: ";
    cin >> capacidadeInicial;

    turma minhaTurma(capacidadeInicial);

    cout << "Turma - Escolha a Opção:\n"
         << "i - inserir novo aluno\n"
         << "b - buscar por dados de um aluno a partir do nome\n"
         << "c - simular nota final de todos os alunos\n"
         << "s - para sair do programa" << endl;

    char opcaoDoMenu;
    aluno umAluno;
    string nome;
    float bonificacao;

    cin >> opcaoDoMenu;

    while (opcaoDoMenu != 's') {
        switch(opcaoDoMenu) {
            case 'i' : 
                cout << "Entre com dados do aluno (nome e três notas):" << endl;
                cin >> umAluno.nomeDoAluno 
                    >> umAluno.notas[0] >> umAluno.notas[1] >> umAluno.notas[2];
                minhaTurma.inserirNovoAluno(umAluno);
                break;

            case 'b' :
                cout << "Entre com nome do aluno para busca: ";
                cin >> nome;
                
                if (minhaTurma.buscarAluno(nome, umAluno)) 
                    cout << umAluno.nomeDoAluno << " "
                         << umAluno.notas[0] << " " <<  umAluno.notas[1] << " "
                         << umAluno.notas[2] << endl << endl;
                else 
                    cout << "Aluno não encontrado!" << endl << endl;
                break;

            case 'c' : 
                cout << "Entre com valor da bonificacao: ";
                cin >> bonificacao;
                simularNotaFinal(minhaTurma,bonificacao);
                break;

            case 's' : // não faz nada, espera retorno ao while para sair 
                break;

            default:
                cout << "Opção inválida!" << endl;
                break;

        }
        cout << "Turma - Escolha a Opção:\n"
            << "i - inserir novo aluno\n"
            << "b - buscar por dados de um aluno a partir do nome\n"
            << "c - simular nota final de todos os alunos\n"
            << "s - para sair do programa" << endl;
        cin >> opcaoDoMenu;
    }

    return 0;
}
