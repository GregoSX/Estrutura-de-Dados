/* 
    Atividade de  GCC216 - Estruturas de Dados, 2021

    Solução de: Guilherme Grego Santos
*/

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

class torneio {
    private:
        int *heap;
        int capacidade;
        int tamanho;
        int inicioDados;
        inline int pai(int i);
        inline int esquerdo(int i);
        inline int direito(int i);
        void arruma();
        void copiaMaiorOuMenor(int i, string aux);
	public:
        torneio(int vetor[], int tam);
        ~torneio();
        int raiz();
};

torneio::torneio (int vetor[], int tam) {
    capacidade = 1;
    while (capacidade < tam)
        capacidade *= 2;

    capacidade = capacidade - 1 + tam;
    
    heap = new int [capacidade];
    inicioDados = capacidade - tam;
    
    memcpy (&heap[inicioDados], vetor, sizeof(int)*tam);
    
    tamanho = tam;
    arruma();
}


torneio::~torneio (){
    delete [] heap;
}

int torneio::pai (int i) {
    return (i-1)/2;
}

int torneio::esquerdo (int i) {
    return 2*i+1;
}

int torneio::direito (int i) {
    return 2*i+2;
}

int torneio::raiz() {
    return heap[0];
}

void torneio::arruma () {
    string aux;
    int aux1 = ceil(tamanho / 2.0);
    int k = 0;
	
    for (int i = inicioDados-1; i >= 0; i--)  {
        if (i < (aux1 - 1)) {
            aux1 = ceil(aux1 / 2.0);
            k++;
        }
		
        if (k % 2 == 0) {
            aux = "maior";
        }
        else {
            aux = "menor";
        }  
        copiaMaiorOuMenor(i,aux);
    }
}

void torneio::copiaMaiorOuMenor(int i, string aux) {
    int esq = esquerdo(i);
    int dir = direito(i);
    int maior = -1;
    int menor = -1;
 
    if (esq < capacidade) {
        if (aux == "maior" ) {
            if ((dir < capacidade) and (heap[dir] > heap[esq])) {
                maior = dir;
            }
            else {
                maior = esq;
            }
            heap[i] = heap[maior];
        }
        else {
            if ((dir < capacidade) and (heap[dir] < heap[esq]) and heap[dir] >= 0) {
                menor = dir;
            }
            else {
                menor = esq;
            }
            heap[i] = heap[menor];	
        }
    }
    else {
        heap[i] = -1;	
    }
}

int main () {
    int quantPart;
    cin >> quantPart;
	
    if (quantPart > 0) {
        int vetor[quantPart];
		
        for (int i = 0; i < quantPart; i++)
            cin >> vetor[i];
            		
        torneio *torneioAlternado =  new torneio (vetor,quantPart);
	
        cout << torneioAlternado->raiz() << endl;
	
        delete torneioAlternado;
    }

    return 0;
}
