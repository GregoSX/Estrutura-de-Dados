/* 
    Atividade de  GCC216 - Estruturas de Dados, 2021

    Solução de: Guilherme Grego Santos
*/

#include <iostream>

using namespace std;

class noh {
    friend class fila;
    private:
        int dado;
        noh *proximo;
    public:
        noh (int valor);
};

noh::noh (int valor) {
    proximo = NULL;
    dado = valor;	
}

class fila {
    private:
        int tamanho;
        noh *inicio;
        noh *fim;
    public:
        fila ();
        ~fila();
        void enfileira(int valor);
        int desenfileira();
        int tam();
        bool filaVazia();
        void limpaFila();
};

bool fila::filaVazia() {
    return (tamanho == 0);
}

fila::fila() {
    inicio = NULL;
    fim = NULL;
    tamanho = 0;	
}

fila::~fila() {
    limpaFila();
}

void fila::limpaFila() {
    while (tamanho > 0)
        desenfileira();
}

void fila::enfileira(int valor) {
    noh *novo = new noh (valor);
    if (filaVazia())
        inicio = novo;
    else
        fim->proximo = novo;
    fim = novo;
    tamanho++;
}

int fila::desenfileira() {
    int aux1 = inicio->dado;
    noh *aux2 = inicio;
    inicio = inicio->proximo;
    delete [] aux2;
    tamanho--;
    if (tamanho == 0)
        fim = NULL;
    return aux1;
}

int fila::tam() {
    return tamanho;
}

int main () {
    int valor;
    fila fila1;
    int totalElementos;
    cin >> totalElementos;
	
	if (totalElementos > 0) {
        for (int i = 0; i < totalElementos; i++) {
            cin >> valor;
            fila1.enfileira(valor);
        }
        
        int k, num;
        cin >> k;
        
        while (fila1.tam() >= k) {
            int cont = 0;
            num = fila1.desenfileira();
            for (int i = 0; i < k; i++) {
                if (i > 0){
                    num = fila1.desenfileira();
                    fila1.enfileira(num);
                    cont++;
                }
                if (num < 0 or (i == k - 1 and num >= 0)) {
                    if (num < 0) {
                        cout << num << " ";
                        i = k;
                    }
                    else {
                        cout << " inexistente ";
                    }
                    for (int j = 0; j < fila1.tam()-cont; j++) {
                        num = fila1.desenfileira();
                        fila1.enfileira(num);
                    }
                }
            }
        }
    }
	
    return 0;
}
