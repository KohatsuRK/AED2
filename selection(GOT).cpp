#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;


void selectionSort(vector<string> &ArrayN) {
    int tamanho = ArrayN.size();
    for(int i=0; i<tamanho; i++){
        int min = i;
        for(int j=i; j<tamanho; j++){
            if(ArrayN[j] < ArrayN[min])
                min = j;
        }
        if(min!=i)//se for igual nao troca
            swap(ArrayN[i],ArrayN[min]);
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
    clock_t tempoExe;
    string linha;
    vector<string> ArrayN;// Vamos ordenar o arquivo n.csv
    ifstream  arq;
    arq.open("GOT.csv");
    
    tempoExe = clock(); //incio do clock

    if (arq.is_open()) {
        while (getline(arq, linha)) {
            ArrayN.push_back(linha);
        }
    } else {
        cerr << "Erro ao abrir o arquivo" << endl;
        return 1;
    }
    arq.close();
    
    selectionSort(ArrayN);
    salvaOrdenacao(ArrayN, "sSortOrdenado(GOT).csv");
    

    tempoExe = clock() - tempoExe;//encerrmanteo do clock

    cout << "\nTamanho da Array/quantidade de dados ordenados: " << ArrayN.size() << "\n";
    cout << "Tempo de execucao (em segundos): " << ((float)tempoExe)/((CLOCKS_PER_SEC)) << "\n";//o clock esta sendo entregue em segundos 

    ArrayN.clear();//desaloca meu vetor
    return 0;
}