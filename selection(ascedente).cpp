#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;


void selectionSort(vector<int> &ArrayN) {
    int tamanho = ArrayN.size();
    for(int i=0; i<tamanho; i++){
        int max = i;
        for(int j=i; j<tamanho; j++){
            if(ArrayN[j] > ArrayN[max])
                max = j;
        }
        if(max!=i)//se for igual nao troca
            swap(ArrayN[i],ArrayN[max]);
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
        cout << "Ordenação salva em " << nomeArquivo << endl;
    } else {
        cerr << "Erro ao criar o arquivo de saída" << endl;
    }
}

int main(){
    int tamanhoA,n;
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
        ArrayN.pop_back();
        tamanhoA = ArrayN.size();
   
    }else
        cerr << "Erro ao abrir o arquivo" << endl; 
    arq.close();
    
    selectionSort(ArrayN);
    salvaOrdenacao(ArrayN, "sSortOrdenado(decrecente_n).csv");
    

    tempoExe = clock() - tempoExe;

    cout << "\nTamanho da Array/quantidade de dados ordenados: " << tamanhoA << "\n";
    cout << "Tempo de execucao (em segundos): " << ((float)tempoExe)/((CLOCKS_PER_SEC)) << "\n";

    ArrayN.clear();
    return 0;
}