#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

int particiona(vector<string> &ArrayN, int inicio, int fim){
    int i = inicio, j = fim;
    string pivo = ArrayN[inicio];
    int count = 0;

    //conta quantos valores são menores ou iguais ao meu pivo
    for (int i = inicio + 1; i <= fim ; i++) {
        if (ArrayN[i] <= pivo)
            count++;
    }
 
    int pivoIndice = inicio + count;
    swap(ArrayN[pivoIndice], ArrayN[inicio]);
 
    while (i < pivoIndice && j > pivoIndice) {
        while (ArrayN[i] <= pivo) {
            i++;
        }
        while (ArrayN[j] > pivo) {
            j--;
        }
        if (i < pivoIndice && j > pivoIndice) {
            swap(ArrayN[i++], ArrayN[j--]);
        }
    }

    return pivoIndice;//retorna o indice
}


void quickSort(vector<string> &ArrayN, int inicio, int fim) {
    int pivo;
    if(fim> inicio){
        pivo = particiona(ArrayN, inicio,fim);
        quickSort (ArrayN, inicio, pivo-1);
        quickSort (ArrayN, pivo+1, fim);
    }
}


void imprime(const vector<string> &ArrayN) {
   for (auto i = ArrayN.begin(); i != ArrayN.end(); i++)
    {
        cout << *i << "\n";
    }
    cout << endl;
}


void salvaOrdenacao(const vector<string> &ArrayN, const string &nomeArquivo) {
    ofstream arquivoOrdenado(nomeArquivo);
    if (arquivoOrdenado.is_open()) {
        for (const string &str : ArrayN) { // Usar const string &str para evitar cópias
            arquivoOrdenado << str << "\n";
        }
        arquivoOrdenado.close();
        cout << "\nOrdenação salva em " << nomeArquivo << endl;
    } else {
        cerr << "Erro ao criar o arquivo de saída" << endl;
    }
}


int main(){
    int tamanhoA;
    int fim, inicio;
    clock_t tempoExe;
    vector<string> ArrayN;
    string n;
    ifstream arq;
    arq.open("nomes.csv");
    
    tempoExe = clock();
    
    if(arq.is_open()){
        while (arq.peek()!=EOF){
            arq >> n;
            ArrayN.push_back(n);
        }
        ArrayN.pop_back();
        tamanhoA = ArrayN.size();
        cout<< ArrayN[0] << "\n";
    }else
        cerr << "Erro ao abrir o arquivo" << endl; 
    arq.close();
    
    inicio = 0;          
    fim = tamanhoA-1;   


    quickSort(ArrayN, inicio, fim);
    salvaOrdenacao(ArrayN, "qsortOrdenado(nomes).csv");

    tempoExe = clock() - tempoExe;
    cout << "\nTamanho da Array/quantidade de dados ordenados: " << tamanhoA << "\n";

    cout << "Tempo de execucao (em milissegundo): " << ((int)tempoExe)/((CLOCKS_PER_SEC)/1000) << " ms\n";


    ArrayN.clear();
    return 0;
}