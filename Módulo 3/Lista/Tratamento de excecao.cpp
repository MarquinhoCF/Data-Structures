#include <iostream>
#include <sstream>

using namespace std;

enum tipoExcecao {caca1, caca2, caca3, caca4, divByZero};

class excecao {
    public:
        excecao(tipoExcecao t, int l);
        string msg();
    private:
        int linha;
        tipoExcecao tipo;
};

excecao::excecao(tipoExcecao t, int l) {
    linha = l;
    tipo = t;
}

string excecao::msg() {
    stringstream stream;

    stream << "Ih, deu ruim: ";
    switch (tipo) {
        case caca1:
            stream << "caca1";
            break;
        case caca2:
            stream << "caca2";
            break;
        case caca3:
            stream << "caca3";
            break;
        case caca4:
            stream << "caca4";
            break;
        case divByZero:
            stream << "dividiu por zero";
            break;
    }

    stream << " na linha " << linha << ".";

    return stream.str();
}

float minhaDivisao(int x, int y) {
    if (y == 0) {
        throw excecao(divByZero, __LINE__);
    } else {
        return (float) x/y;
    }
}

int main () {
    try {
        throw 20;
    } catch (int e) {
        cerr << "Deu Caca Nr. " << e << "\n";
        //exit(-1)
    }

    try {
        int n;
        cin >> n;

        switch (n) {
            case 1:
                throw excecao(caca1, __LINE__);
                break;
            case 2:
                throw excecao(caca2, __LINE__);
                break;
            case 3:
                throw excecao(caca3, __LINE__);
                break;
            case 4:
                throw excecao(caca4, __LINE__);
                break;
        }
    } catch (excecao e) {
        cerr << e.msg() << "\n";
        exit(EXIT_FAILURE);
    }

    //cout << minhaDivisao(6,0) << endl;

    try {
        int x, y;
        cin >> x >> y;
        cout << minhaDivisao(x, y) << endl;
    } catch (excecao e) {
        cerr << e.msg() << "\n";
        exit(EXIT_FAILURE);
    }
    
    exit(0);
}