#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>

using namespace std; 


int findMax(const vector<string>& vetor) {
    int tamanhoMax = 0;
    for (const string& str : vetor) {
        tamanhoMax = max(tamanhoMax, static_cast<int>(str.length()));
    }
    return tamanhoMax;
}

void countingSort(vector<string>& vetor, int exp) {
    const int n = vetor.size();
    const int alfabetoASCII = 256;

    vector<string> output(n);
    vector<int> count(alfabetoASCII, 0);

    for (int i = 0; i < n; i++) {
        int index = (exp < vetor[i].length()) ? static_cast<unsigned char>(vetor[i][exp]) : 0;
        count[index]++;
    }

    for (int i = 1; i < alfabetoASCII; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int index = (exp < vetor[i].length()) ? static_cast<unsigned char>(vetor[i][exp]) : 0;
        output[count[index] - 1] = vetor[i];
        count[index]--;
    }

    for (int i = 0; i < n; i++) {
        vetor[i] = output[i];
    }
}

void radixSort(vector<string>& vetor) {
    int tamanhoMax = findMax(vetor);

    for (int exp = tamanhoMax - 1; exp >= 0; exp--) {
        countingSort(vetor, exp);
    }
}

void print(const vector<string>& ArrayN) {
    for (const string& str : ArrayN) {
        cout << str << "\n";
    }
    cout << endl;
}

void salvaOrdenacao(const vector<string>& arr, const string& fileName) {
    ofstream sortedFile(fileName);
    if (sortedFile.is_open()) {
        for (const string& str : arr) {
            sortedFile << str << "\n";
        }
        sortedFile.close();
        cout << "\nOrdenação salva em " << fileName << endl;
    } else {
        cerr << "Erro ao criar o arquivo de saída" << endl;
    }
}

int main() {
    vector<string> ArrayN;
    string line;
    ifstream file;
    clock_t timeExe;
    string name;
    file.open("nomes.csv");

    timeExe = clock();

    if (file.is_open()) {
        while (file.peek() != EOF) {
            file >> name;
            ArrayN.push_back(name);
        }
        ArrayN.pop_back();
        cout << ArrayN[0] << "\n";
    } else {
        cerr << "Erro ao abrir o arquivo" << endl;
    }
    file.close();

    radixSort(ArrayN);
    salvaOrdenacao(ArrayN, "rsort(nomes).csv");

    timeExe = clock() - timeExe;

    cout << "\nTamanho da Array/quantidade de dados ordenados: " << ArrayN.size() << "\n";
    cout << "Tempo de execução (em segundos): " << ((float)timeExe)/ (CLOCKS_PER_SEC) << "\n";

    ArrayN.clear();
    return 0;
}
