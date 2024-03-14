#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

int particiona(vector<string> &ArrayN, int inicio, int fim) {
    string pivo = ArrayN[inicio];
    int i = inicio;
    for (int j = inicio + 1; j <= fim; j++) {
        if (ArrayN[j] < pivo) {
            i++;
            swap(ArrayN[i], ArrayN[j]);
        }
    }
    swap(ArrayN[i], ArrayN[inicio]);
    return i;
}

void quickSort(vector<string> &ArrayN, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particiona(ArrayN, inicio, fim);
        quickSort(ArrayN, inicio, pivo - 1);
        quickSort(ArrayN, pivo + 1, fim);
    }
}

void imprime(const vector<string> &ArrayN) {
    for (const string &str : ArrayN) {
        cout << str << "\n";
    }
    cout << endl;
}

void salvaOrdenacao(const vector<string> &ArrayN, const string &nomeArquivo) {
    ofstream arquivoOrdenado(nomeArquivo);
    if (arquivoOrdenado.is_open()) {
        for (const string &str : ArrayN) {
            arquivoOrdenado << str << "\n";
        }
        arquivoOrdenado.close();
        cout << "\nOrdenação salva em " << nomeArquivo << endl;
    } else {
        cerr << "Erro ao criar o arquivo de saída" << endl;
    }
}

int main() {
    clock_t tempoExe;
    vector<string> ArrayN;
    string linha;
    int tamanhoA;
    tempoExe = clock();
    
    ifstream arq("GOT.csv");

    if (arq.is_open()) {
        while (getline(arq, linha)) {
            ArrayN.push_back(linha);
        }
        tamanhoA = ArrayN.size();
        cout << "Primeira linha: " << ArrayN[0] << "\n";
    } else {
        cerr << "Erro ao abrir o arquivo" << endl;
        return 1;
    }

    arq.close();

    int inicio = 0;
    int fim = tamanhoA - 1;

    quickSort(ArrayN, inicio, fim);
    salvaOrdenacao(ArrayN, "qsortOrdenado(GOT).csv");

    tempoExe = clock() - tempoExe;
    cout << "\nTamanho da Array/quantidade de dados ordenados: " << tamanhoA << "\n";
    cout << "Tempo de execução (em milissegundos): " << ((int)tempoExe) / (CLOCKS_PER_SEC / 1000) << " ms\n";

    return 0;
}
