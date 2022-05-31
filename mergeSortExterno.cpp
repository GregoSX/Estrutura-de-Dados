#include <iostream>
#include <fstream>
#include <cstdio> // para remover arquivos
#include <cstdlib>
#include <cstring>

using namespace std;

//estrutura a ser lida do arquivo
class Registro 
{
    private:
        unsigned int indice;
        float tempo;
        char origem[40];
        char destino[40];
        char protocolo[18];
        unsigned int tamanho;
        char informacao[100];
    public:
        void imprime();
        void mergeexterno (ifstream &arqEntrada, fstream &arqSaida, int escolha_ordenacao);
        bool intercalaBloco (ifstream auxE[2], ofstream auxS[2], int passo, int saida, int escolha_ordenacao);

};

void Registro :: imprime() 
{
    std::cout << indice << "; ";
    std::cout << tempo << "; ";
    std::cout << origem << "; ";
    std::cout << destino << "; ";
    std::cout << protocolo << "; ";
    std::cout << tamanho << "; ";
    std::cout << informacao << std::endl;
}

bool Registro::intercalaBloco (ifstream auxE[2], ofstream auxS[2], int passo, int saida, int escolha_ordenacao) {
    // consideramos incialmente que naão irá fazer nenhuma intercalação 
    bool intercalou = false;
    Registro dados[2];
    // posição relativa de leitura em cada um dos arquivos 
    int pos[2] = {0,0};
    
    /* variavél para informar se od dados do arquivo são válidos (se foram lidos do arquivo de entrada e ainda não gravados no arquivo de saída)*/

    bool valido[2] = {false, false};
    int cont = 0;
    /*em cada passo de tamanho n lemos n dados de cada arquivo e fazemos a intercalação parcial em um novo bloco de 2*n no arquivo de saída ultilizado*/

    while (((pos[0] + pos[1] )) < (2*passo)) {
		cont++;
        // incialmente verificamos se há dados para ser lidos
        if ((pos[0] < passo) && (!valido[0])) {
            /*tentamos ler o arquivo verific&&o se a leitura foi válida */
            //leitura inválida -> final do arquivo
            if (auxE[0].read((char *) &dados[0] , sizeof(Registro))) {
                // cout << "leu arq1: " << auxE[0].tellg() << endl;
                valido[0] = true;
            }
            else {
                // para encerrar o while e não entrar no if novamente 
                pos[0] = passo;
                // cout << "arq1 terminou" << endl;
            }
        }

        //repetimos o processo para o segundo arquivo
        if ((pos[1] < passo) && (!valido[1])) {
            /*tentamos ler o arquivo verific&&o se a leitura foi válida */
            //leitura inválida -> final do arquivo
            if (auxE[1].read((char *) &dados[1] , sizeof(Registro))) {
                // cout << "leu arq1: " << auxE[0].tellg() << endl;
                valido[1] = true;
            }
            else {
                // para encerrar o while e não entrar no if novamente 
                pos[1] = passo;
                // cout << "arq1 terminou" << endl;
            }
        }

        /* nesse momento temos dados lidos dos dois arquivos a 
        não ser que um (ou ambos) tenham chegado a o fim*/
            
        //1° caso, os dois dados são válidos 
        if (valido[0] && valido[1]) {
            // marca que intercalou
            intercalou = true;
            // gravamos o menor valor no arquivo de saída 
            if (dados[0].indice >= dados[1].indice && escolha_ordenacao == 1) {
                auxS[saida].write((const char *) (&dados[0]), sizeof(Registro));
                // dado utilizado não é mais válido, avança posição
                valido[0] = false;
                pos[0]++;
            }
            else if ((strcmp(dados[0].informacao,dados[1].informacao) < 0) && escolha_ordenacao == 2) {
				auxS[saida].write((const char *) (&dados[0]), sizeof(Registro));
                // dado utilizado não é mais válido, avança posição
                valido[0] = false;
                pos[0]++;
			}
            else {
                auxS[saida].write((const char *) (&dados[1].indice), sizeof(Registro));
                // dado ultilizado não é mais válido, avança posição 
                valido[1] = false;
                pos[1]++;
            }          
        }
        //2° caso, apenas o primeiro dado é válido
        else if (valido[0]) {
        // marca que intercalou 
            intercalou = true;
            auxS[saida].write((const char *) (&dados[0].indice), sizeof(Registro));
            // dado ultilizado não é mais válido, avança posição 
            valido[0] = false;
            pos[0]++;
        }
        // 3° caso, apenas o segundo dado é válido
        else if (valido[1]) {
            // marca que intercalou 
            intercalou = true;
            auxS[saida].write((const char *) (&dados[1].indice), sizeof(Registro));
            // dado ultilizado não é mais válido, avança posição 
            valido[1] = false;
            pos[1]++;
        }
    }
    return intercalou;
}

void Registro::mergeexterno (ifstream &arqEntrada, fstream &arqSaida, int escolha_ordenacao){
    ofstream arqB1("arqB1.bin",ios::binary);
    ofstream arqB2("arqB2.bin",ios::binary);

    if ((!arqB1) | (!arqB2)){
        cerr << "Arquivos auxiliares não puderam ser aberto" << endl;
        exit(EXIT_FAILURE);
    }

    Registro umDado;

    //posicion&&o ponteiro de leitura no final do arquivo
    arqEntrada.seekg(0,ios::end);
    //obtendo a posicao final do arquivo
    int tamanho = arqEntrada.tellg();
    //dado o tamanho do arquivo, sabe-se quantos registros no arquivo
    int num_registros = tamanho / sizeof(Registro);
    //metade do numero de registro (arredondado pra cima)
    int metade = (num_registros / 2) + 0.5;
    
    //posicionado ponteiro de leitura no inicio do arquivo
    arqEntrada.seekg(0,ios::beg);

    //copia os dados para os dois arquivo auxiliares
    for (int i = 0; i < metade; i++) {
        arqEntrada.read((char*) &umDado, sizeof(Registro));
        arqB1.write((char*) &umDado, sizeof(Registro));
    }
    for (int i = metade; i < num_registros; i++) {
        arqEntrada.read((char*) &umDado, sizeof(Registro));
        arqB2.write((char*) &umDado, sizeof(Registro));
    }

    //finalizaçao da primeira etapa
    arqB1.close();
    arqB2.close();
    arqEntrada.close();

    //arquivos auxiliares
    ifstream auxEntrada[2];
    ofstream auxSaida[2];

    //variaveis de controle
    int passo = 1;
    bool ida = true;
    bool ultimo[2];

    //laço principal
    while (passo <= num_registros){
        if(ida){
            auxEntrada[0].open("arqB1.bin",ios::binary);
            auxEntrada[1].open("arqB2.bin",ios::binary);
            auxSaida[0].open("arqC1.bin",ios::binary);
            auxSaida[1].open("arqC2.bin",ios::binary);
        }
        else {
            auxEntrada[0].open("arqC1.bin",ios::binary);
            auxEntrada[1].open("arqC2.bin",ios::binary);
            auxSaida[0].open("arqB1.bin",ios::binary);
            auxSaida[1].open("arqB2.bin",ios::binary);
        }
        if ((! auxEntrada[0]) | (! auxEntrada[1]) | (! auxSaida[0]) | (! auxSaida[1])) {
            cerr << "Arquivos auxiliares não puderam abertos" << endl;
            exit(EXIT_FAILURE);
        }
        //enquanto não chegar ao final dos arquivos de entrada, vai intercal&&o os blocos
        while ((! auxEntrada[0].eof()) && (! auxEntrada[1].eof())){
            ultimo[0] = intercalaBloco(auxEntrada,auxSaida,passo,0,escolha_ordenacao);
            ultimo[1] = intercalaBloco(auxEntrada,auxSaida,passo,1,escolha_ordenacao);
        }
        
        //fecha os arquivos para permitir troca (escrita<->leitura) na próxima interação
        auxEntrada[0].close();
        auxEntrada[1].close();
        auxSaida[0].close();
        auxSaida[1].close();
        
        //prepara próxima interação, invertendo arquivos e dobr&&o tamanho do passo
        ida = !(ida);
        passo *= 2;
    }

    //merge termin&&o, agora lemos do arquivo auxiliar para arquivo de saida
    ifstream auxEnt;

    //identifica o arquivo auxiliar com dados ordenados
    if (ida) {
        if (ultimo[0]) {
            auxEnt.open ("arqB1.bin", ios::binary);
        }
        else {
            auxEnt.open ("arqB2.bin", ios::binary);
        }
    }
    else {
        if (ultimo[0]) {
            auxEnt.open ("arqC1.bin", ios::binary);
        }
        else {
            auxEnt.open ("arqC2.bin", ios::binary);
        }
    }

    if (! auxEnt) {
        cerr <<"Arquivo auxiliar não poder ser aberto" << endl;
        exit(EXIT_FAILURE);
    }

    while (auxEnt.read((char*)(&umDado),sizeof(Registro))) {
        arqSaida.write((const char*)(&umDado),sizeof(Registro));
    }

    auxEnt.close();

    //cereja do bolo, apagar arquivos auxiliares
    remove("arqB1.bin");
    remove("arqB2.bin");
    remove("arqC1.bin");
    remove("arqC2.bin");
    
}

void copiaRegistros (fstream &arquivo, Registro umRegistro[], int posicao_bytes)
{
    arquivo.seekg(posicao_bytes); // Posiciona a cabeça de leitura
	
    for (int i = 0; i < 100000; i++) //copi&&o regitros para vetor o de objetos
        arquivo.read((char*) &umRegistro[i], sizeof(umRegistro[i]));
}

int main () {
    ifstream entrada("captura_pacotes.bin",ios::binary);
    fstream saida("saida.bin",ios::binary | ios::in |ios::out);
   
    Registro *umRegistro = new Registro[100000];

    if (! entrada) {
        cerr <<"Arquivo de entrada não pode ser aberto" << endl;
        exit(EXIT_FAILURE);
    }
    if (! saida) {
        cerr <<"Arquivo de saida não pode ser aberto" << endl;
        exit(EXIT_FAILURE);
    }
    
    int escolha_ordenacao;
    
    cout <<"Digite o metodo : " << endl;
    
    cin >> escolha_ordenacao;

    umRegistro->mergeexterno(entrada,saida,escolha_ordenacao);

    copiaRegistros(saida, umRegistro, 0);
    
    for (int i = 0; i < 5; i++) // teste
			umRegistro[i].imprime();
			
    umRegistro[25000].imprime();
    umRegistro[25000+1].imprime();
    umRegistro[50000].imprime();
    umRegistro[100000-1].imprime();
			
    entrada.close();
    saida.close();
    
    return 0;
    
}
