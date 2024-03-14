#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <time.h>
using namespace std;

int getMax(const vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
}

void countSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(19, 0); //temos 19 elementos para acomodar números negativos e positivos

    for (int i = 0; i < n; i++) {
        int digit = 9 - (arr[i] / exp) % 10; 
        count[digit]++;
    }

    for (int i = 1; i < 19; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int digit = 9 - (arr[i] / exp) % 10; 
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(vector<int>& arr) {
    int max = abs(getMax(arr));
    int exp = 1;

    while (max / exp > 0) {
        countSort(arr, exp);
        exp *= 10;
    }
}

void imprime(const vector<int> &ArrayN) {
    for (auto i = ArrayN.begin(); i != ArrayN.end(); i++) {
        cout << *i << "\n";
    }
    cout << endl;
}

void salvaOrdenacao(const vector<int> &ArrayN, const string &nomeArquivo) {
    ofstream arquivoOrdenado(nomeArquivo);
    if (arquivoOrdenado.is_open()) {
        for (int i : ArrayN) {
            arquivoOrdenado << i << "\n";
        }
        arquivoOrdenado.close();
        cout << "\nOrdenação salva em " << nomeArquivo << endl;
    } else {
        cerr << "Erro ao criar o arquivo de saída" << endl;
    }
}

int main() {
    vector<int> ArrayN;
    int n;
    ifstream arq;
    clock_t tempoExe;
    arq.open("n.csv");
    
    tempoExe = clock(); // Início do clock
    if (arq.is_open()) {
        while (arq.peek() != EOF) {
            arq >> n;
            ArrayN.push_back(n); // Inserindo na array
        }
        ArrayN.pop_back(); // Remove duplicação do último valor devido ao EOF
    } else
        cerr << "Erro ao abrir o arquivo" << endl; 
    arq.close();
 
    radixSort(ArrayN);
    salvaOrdenacao(ArrayN, "rsort(decrescente).csv");

    tempoExe = clock() - tempoExe;
    cout << "\nTamanho da Array/quantidade de dados ordenados: " << ArrayN.size() << "\n";
    cout << "Tempo de execução (em segundos): " << ((float)tempoExe) / CLOCKS_PER_SEC << "\n";

    ArrayN.clear();
    return 0;
}
