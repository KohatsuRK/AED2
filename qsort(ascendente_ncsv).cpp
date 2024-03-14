#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

// int particiona(vector<int> &ArrayN, int inicio, int fim){
    
//     int i = inicio, j = fim;
//     int pivo = ArrayN[inicio];
//     int count = 0;

//     //conta quantos valores são menores ou iguais ao meu pivo
//     for (int i = inicio + 1; i <= fim ; i++) {
//         if (ArrayN[i] <= pivo)
//             count++;
//     }
 
//     int pivoIndice = inicio + count;
//     swap(ArrayN[pivoIndice], ArrayN[inicio]);
 
//     while (i < pivoIndice && j > pivoIndice) {
//         while (ArrayN[i] <= pivo) {
//             i++;
//         }
//         while (ArrayN[j] > pivo) {
//             j--;
//         }
//         if (i < pivoIndice && j > pivoIndice) {
//             swap(ArrayN[i++], ArrayN[j--]);
//         }
//     }

//     return pivoIndice;//retorna o indice
// }

int particiona(vector<int> &ArrayN, int inicio, int fim) {
    
    int i = inicio, j = fim;
    int pivo = ArrayN[inicio];
    int count = 0;

    // Conta quantos valores são maiores ou iguais ao meu pivo
    for (int i = inicio + 1; i <= fim; i++) {
        if (ArrayN[i] >= pivo)  // Alterado de <= para >=
            count++;
    }
 
    int pivoIndice = inicio + count;
    swap(ArrayN[pivoIndice], ArrayN[inicio]);
 
    while (i < pivoIndice && j > pivoIndice) {
        while (ArrayN[i] >= pivo) {  // Alterado de <= para >=
            i++;
        }
        while (ArrayN[j] < pivo) {  // Alterado de > para <
            j--;
        }
        if (i < pivoIndice && j > pivoIndice) {
            swap(ArrayN[i++], ArrayN[j--]);
        }
    }

    return pivoIndice; // Retorna o índice
}

void quickSort(vector<int> &ArrayN, int inicio, int fim) {
    int pivo;
    if(fim> inicio){
        pivo = particiona(ArrayN, inicio,fim);
        quickSort (ArrayN, inicio, pivo-1);
        quickSort (ArrayN, pivo+1, fim);
    }
}


void imprime(const vector<int> &ArrayN) {
   for (auto i = ArrayN.begin(); i != ArrayN.end(); i++)
    {
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


int main(){
    int tamanhoA,n;
    int fim, inicio;
    clock_t tempoExe;
    vector<int> ArrayN;// Vamos ordenar o arquivo n.csv
    ifstream  arq;
    arq.open("n.csv");
    //esse arquivo tem 1.000.000 de numeros inteiros
    
    
    tempoExe = clock(); //incio do clock
    
    if(arq.is_open()){
        while (arq.peek()!=EOF){
            arq >> n;
            ArrayN.push_back(n);
        }
        ArrayN.pop_back();//utilizei essa funcao pois por causa do eof, ele estava duplicando o ultimo vlaor, entao retiro o ultimo e agr ele funciona perfeitamente
        tamanhoA = ArrayN.size();
    }else
        cerr << "Erro ao abrir o arquivo" << endl; //caso nem abra o arquivo correntamente
    arq.close();
    
    inicio = 0;          //primeira posicao do vetor
    fim = tamanhoA-1;    //ultima posicao do vetor, -1 pois eu preciso do indice e não do tamanho total 

    quickSort(ArrayN, inicio, fim);
    //imprime(ArrayN);
    salvaOrdenacao(ArrayN, "qsort(ascendente).csv");//criei para comparar o reultado final dos codigos


    tempoExe = clock() - tempoExe;//encerrmanteo do clock
    cout << "\nTamanho da Array/quantidade de dados ordenados: " << tamanhoA << "\n";
    cout << "Tempo de execucao (em segundos): " << ((float)tempoExe)/((CLOCKS_PER_SEC)) << "\n";//o clock em segundos 

    ArrayN.clear();//desaloca meu vetor
    return 0;
}