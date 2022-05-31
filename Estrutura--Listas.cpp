#include <iostream>

using namespace std;

class elemento{
    friend class lista;
    private:
        int chave;
        elemento *proximo;
        elemento *anterior;
    public:
        elemento (int c){
            chave = c;
            proximo = NULL;
            anterior = NULL;
        }
};

class lista{
    private:
        int tamanho;
        elemento *inicio;
        elemento *fim;
    public:
        lista();
        ~lista();      
        void insereFim (int c);
        void removeRepetidos();
        bool vazia();
        void imprimeLista();
        void imprimeReverso();
};
    
lista::lista(){
    inicio = NULL;
    fim = NULL;
    tamanho = 0;
}
        
lista::~lista(){
    elemento *aux = inicio;
    elemento *temp;
	
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
    elemento *novo = new elemento (c);
    if (vazia()) {
        inicio = novo;
        fim = novo;
    }
    else {
        fim->proximo = novo;
        novo->anterior = fim;
        fim = novo;	
    }
    tamanho++;
}

void lista::removeRepetidos() {
    elemento *auxiliar = inicio;
    elemento *aux;

    while (auxiliar != NULL) {
        aux = auxiliar->proximo;	
        while (aux != NULL) {
            if (auxiliar->chave == aux->chave) {	
			    if (aux->anterior != NULL)
                    aux->anterior->proximo = aux->proximo;
                else
                    inicio = aux->proximo;
			    
                if (aux->proximo != NULL) 
                    aux->proximo->anterior = aux->anterior;  
                else 
                    fim = aux->anterior;
                       
                delete aux;
                tamanho--;
		
                if (vazia()) {
                    inicio = NULL;
                    fim = NULL;
                }
            }
            aux = aux->proximo;
        }	  
        auxiliar = auxiliar->proximo;
    }
}

void lista::imprimeReverso(){
    elemento *auxiliar = fim;
    while (auxiliar->anterior != NULL){
        cout<<auxiliar->chave<<" ";
        auxiliar = auxiliar->anterior;
    }
    cout<<auxiliar->chave<<endl;
}
           
void lista::imprimeLista(){
    elemento *auxiliar = inicio;
    while (auxiliar->proximo != NULL){
        cout<<auxiliar->chave<<" ";
        auxiliar = auxiliar->proximo;
    }
    cout<<auxiliar->chave<<endl;
}

bool lista::vazia() {
    return (tamanho == 0);	
}
    
int main(){
    lista L1;
    
    int quant,chave;
    
    cin>>quant;
    
    for (int i = 0; i < quant; i++){
        cin >> chave;
        L1.insereFim(chave);          
    }

    L1.removeRepetidos();
    L1.imprimeLista();
    L1.imprimeReverso();
    
    return 0;
}
