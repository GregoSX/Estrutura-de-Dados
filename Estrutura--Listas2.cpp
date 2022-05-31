#include <iostream>
#include <string>

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
        void insereInicio(int c);
        void insereFim (int c);
        int removeRepetidos();//retorna a quantidade de elementos restantes na lista
        bool vazia();
        void imprimeLista();
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

void lista::insereInicio (int c){
    elemento *novo = new elemento (c);
    if (vazia()) { 
        inicio = novo;
        fim = novo;
    }
    else {
        novo->proximo = inicio;
        inicio->anterior = novo;
        inicio = novo;
    }
    tamanho++;
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

int lista::removeRepetidos() {
    elemento *auxiliar = inicio;
    elemento *aux;

    while (auxiliar != NULL) {
        aux = auxiliar->proximo;	
        while (aux != NULL) {
            if (auxiliar->chave == aux->chave) {
                aux->anterior->proximo = aux->proximo;
			    
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
    return tamanho;
}
           
void lista::imprimeLista(){
    if (inicio != NULL){
        elemento *auxiliar = inicio;
        while (auxiliar->proximo != NULL){
            cout<<"("<<auxiliar->chave<<") ";
            auxiliar =  auxiliar->proximo;
        }
        cout<<"("<<auxiliar->chave<<")"<<endl;
    } else {
            cout<<"VAZIA";
    }
}

bool lista::vazia() {
    return (tamanho == 0);	
}
    
int main(){
    
    lista listaD;
    
    int chave;
    
    cin>>chave;
    
    while (chave >= 0){
        listaD.insereFim(chave);        
        cin>>chave;  
    }

    cout << listaD.removeRepetidos() << endl;
    listaD.imprimeLista();
    
    return 0;
}
