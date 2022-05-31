/* 
    Atividade de  GCC216 - Estruturas de Dados, 2021

    Solução de: Guilherme Grego Santos
*/

#include <iostream>

using namespace std;

class noh {
    friend class pilha;
    private:
        char dado;
        noh *proximo;
    public:
        noh (char caractere);
};

noh :: noh (char caractere) {
    dado = caractere;
    proximo = NULL;
}

class pilha {
    private:
        int tamanho;
        noh *topo;
    public:
        pilha ();
        ~pilha();
        int tam();
        void empilha(char caractere);
        void limpar();
        int desempilha();
        bool vazia();
};

pilha::pilha() {
    topo =  NULL;
    tamanho = 0;	
}

pilha::~pilha() {
    limpar();
}

void pilha :: limpar() {
    while (tamanho > 0)
        desempilha();
}

int pilha::tam() {
    return tamanho;
}

void pilha::empilha(char caractere) {
    noh *novo = new noh(caractere);
    novo->proximo = topo;
    topo = novo;
    tamanho++;
}

int pilha::desempilha () {
    char aux1 = topo->dado;
    noh *aux2 = topo;
    topo = topo->proximo;
    delete [] aux2;
    tamanho--;
    return aux1;
}

bool pilha::vazia() {
    return (tamanho == 0);
}

int main () {
    pilha pilhaAs, pilhaCs;
    char caractere;
    cin >> caractere;
    
    string resposta = "nao";
    
    int aux = 0;
    while (caractere != 'X') {
        if (caractere == 'A')
            pilhaAs.empilha('A');
        else if (caractere == 'C')
            pilhaCs.empilha('C');
        else if (caractere == 'B')
            aux++;
        cin >> caractere;
    }
    
    bool auxiliar = (aux == 1 and (pilhaCs.tam() / 2) == pilhaAs.tam());
    if (auxiliar and (not (pilhaAs.vazia() and pilhaCs.vazia())))
        resposta = "sim";
		
    while (not (pilhaAs.vazia() or pilhaCs.vazia()) and pilhaCs.tam() > 1) {
        pilhaAs.desempilha();
        pilhaCs.desempilha();
        pilhaCs.desempilha();
    }    
    
    cout << resposta << " " << pilhaAs.tam() << " " << pilhaCs.tam();
	
    return 0;
}
