#include <iostream>
#include <fstream>

using namespace std;

class nohLista {
    friend class lista;
    private:
        int chave;
        nohLista* proximo;
    public:
        nohLista (int c){
            chave = c;
            proximo = NULL;
        }
};

class lista {
    private:
        nohLista* fim;
        nohLista* inicio;
        int tamanho;
    public:
        lista();
        ~lista(); 
        void insereFim (int c); 
        void imprimeLista();
};

lista::lista(){
    inicio = NULL;
    fim = NULL;
    tamanho = 0;
}
        
lista::~lista(){
    nohLista* aux = inicio;
    nohLista* temp;
	
    for (int i = 0; i < tamanho; i++) {
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    tamanho = 0;
    inicio = NULL;
    fim = NULL;
} 

void lista::insereFim (int c){
    nohLista* novo = new nohLista (c);
    if (tamanho == 0) {
        inicio = novo;
        fim = novo;
    }
    else {
        fim->proximo = novo;
        fim = novo;	
    }
    tamanho++;
}

void lista::imprimeLista(){
    nohLista* auxiliar = inicio;
    while (auxiliar->proximo != NULL){
        cout<<auxiliar->chave<<" ";
        auxiliar = auxiliar->proximo;
    }
    cout<<auxiliar->chave<<endl;
}

class noh {
    friend class abb;
    private:
        string palavra;
        noh* esq;
        noh* dir;
        lista numeros;
    public:
        noh(string umDado, int numero);
        ~noh();
};

noh::noh(string umDado, int numero) {
    palavra = umDado;
    esq = NULL;
    dir = NULL;
    numeros.insereFim(numero);
}

noh::~noh() {
    delete esq;
    delete dir;	
}

class abb {
    private:
        noh* raiz;
        noh* insereAux(noh* umNoh, string dado, int cont);
    public:
        abb();
        ~abb();
        void insere(string umDado, int cont);
        void busca(string busc);
};

abb::abb() {
    raiz = NULL;	
}

abb::~abb() {
    delete raiz;
}

void abb::insere(string umDado, int cont) {
    raiz = insereAux(raiz,umDado,cont);
}

noh* abb::insereAux(noh* umNoh, string umDado, int cont) {
    if (umNoh == NULL) {
        noh* novo = new noh(umDado,cont);
        return novo;	
    }
    else {
        if(umDado < umNoh->palavra) 
            umNoh->esq = insereAux(umNoh->esq,umDado,cont);
        else if (umDado > umNoh->palavra) 
            umNoh->dir = insereAux(umNoh->dir,umDado,cont);
        else 
            umNoh->numeros.insereFim(cont);
    }
    return umNoh;
}

void abb::busca(string busc) {
    noh* atual = raiz;
    bool encontrou = false;
    while (atual != NULL) {
        if (atual->palavra == busc) {
            atual->numeros.imprimeLista();
            encontrou = true;	
            atual = NULL;
        }
        else if(atual->palavra > busc) {
            atual = atual->esq;
        }
        else {
            atual = atual->dir;
        }
    }
    if (not encontrou) {
        cout << -1;	
    }
}

int main () {
    abb arvore;
    int cont = 0;
    ifstream arquivo("entrada.txt");
    string dados;
    
    if (arquivo) {
        while (arquivo >> dados) {
            cont++;
            arvore.insere(dados,cont);
        }
    }
	
    string busca;
    cin >> busca;
    arvore.busca(busca);
	
    arquivo.close();

    return 0;
}
