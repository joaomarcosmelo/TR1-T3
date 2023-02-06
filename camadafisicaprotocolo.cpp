#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include "camadafisicaprotocolo.h"


using namespace std;


int CamadaFisicaReceptoraDecodificacaoBinaria() {
 
    cout << "Decodificao: " << endl;

    // Binario para decimal 

    int numero, digito;
    int posicao = 0;
    int resultado = 0;

    int vetor[] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    int tamanho_string;
    
    cout << "Tamanho da string: \n";
    cin >> tamanho_string;

    int i, j;

    for (i = 0; i < tamanho_string; i++){
    cout << "Digite o codigo binario que foi obtido  " << endl;
    scanf("%d", &numero);
       
      while (numero > 0) {
            digito = numero % 10;
            if (digito == 1)
                resultado = resultado + vetor[posicao];
            posicao++;
            numero = numero / 10;
            }        
    
        printf("O resultado em decimal eh : %d \n",resultado);
        printf("O resultado em ANSII eh : %c\n", char (resultado));
}

}

int BitXnor (int a, int b) {
      int resultante;
      resultante = !(a^b);
      return resultante;
}


int CamadaDeAplicacaoReceptoraDecodificacaoManchester(){

    int* manchester;
    int size_manchester;
    int size;

    int quadro[size_manchester/2];

    int i;

    string mensagem;
    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;

    // Passegm de clock 
    for (i = 0; i <size_manchester/2; i++){
        quadro[i] = BitXnor(manchester[2*i], 0);
    }

    cout << endl;

     for (i = 0; i < size_manchester/2; i++){
        cout << quadro[i];
     }
   
    cout << "A mensagem decofificada eh: \n" << quadro[i] << endl;

    cout << endl;
}

int CamadaDeAplicacaoReceptoraDecodificacaoBipolar(){

    string mensagem;

    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;

    int i;
    int nivelnegativo = -1;
    int aux0, aux1,aux2;
    int nivelneutro = 0;
    int nivelpositivo = 1;

    // Inicializar 
    for (i = 0; i < mensagem.length(); i++){
        mensagem[i] = 0;
        mensagem[i+1] = 1;
    }

    cout << "A mensagem decodifica eh: ";

    if (mensagem[i] < mensagem[nivelneutro]){
                nivelneutro = nivelpositivo;
                cout << "0";
                nivelneutro = 1;
                
              //else if (mensagem[i] == mensagem[i] || mensagem[i] == 0 || mensagem[i] == 1)  
            } else if ( mensagem[i] != mensagem[i]){

                 nivelneutro = nivelnegativo;
                 mensagem[i] >= (1 << i);
                 mensagem[i] = mensagem[i] - (1 << i);
                //cout << " ";   Strings 
                cout << "1";
                nivelneutro = 0;
            
                } 
            if (mensagem[i] ==  mensagem[i]  && mensagem[i] == 1 ){

                    //nivelnegativo  = nivelneutro;
                    cout << " ";
                    cout << "1";

                }
            
                cout << " ";
                cout << "\n";
            

     cout << "\nO valor tamanho da mensagem eh: " << mensagem.size() << endl;
    
}

void CamadaFisicaReceptora(){
   
    int fluxoBrutoDeBits;
    int tipoDeDeCodificacao;

    cout << "\nDigite qual a decodificacao voce escolhe:\n 0 - Binaria \n 1 - Manchester\n 2 - Bipolar\n";
    cin >> tipoDeDeCodificacao;
    

    switch (tipoDeDeCodificacao) {
        case 0: // codificacao binaria
          CamadaFisicaReceptoraDecodificacaoBinaria();
            break;
        case 1: // codificacao Manchester
           CamadaDeAplicacaoReceptoraDecodificacaoManchester();
            break;
        case 2: // codificacao bipolar
            CamadaDeAplicacaoReceptoraDecodificacaoBipolar();
            break;

    }

   // CamadaDeAplicacaoReceptora();
}



void MeioDeComunicacao (){
   
    int size = 8;
    int tipoDeCodificacao;

    int fluxoBrutoDeBits[size];
    int fluxoBrutoDeBitsPontoA[size];
    int fluxoBrutoDeBitsPontoB[size];
    int i;

    cout << "Fluxo de bits de A eh: \n";
    for (i = 0; i < size; i++){
        fluxoBrutoDeBitsPontoA[i] = fluxoBrutoDeBitsPontoB[i];
        cout << fluxoBrutoDeBitsPontoA[i];
    }
    cout << endl;
  
    fluxoBrutoDeBitsPontoA[size] = fluxoBrutoDeBits[size];
  
    srand(time(NULL)); 
    int porcentagemDeErros;
    int erro = 0;

    for (i = 0; i < size; i++){
        erro = rand()%100;

        if (erro < 10){
            cout << "Fluxo de bits:";
            cout << "\n";
            fluxoBrutoDeBits[i] ^=1;
            cout << fluxoBrutoDeBits[i];
        }
    }
    cout << "O fluxo de bits em B eh: \n";
    for (i = 0; i < size; i++){
        fluxoBrutoDeBitsPontoB[i] =  fluxoBrutoDeBits[i];
        cout << fluxoBrutoDeBitsPontoB[i];
        // Os bits sendo transferidos do Ponto A a B
    }

    cout << endl;
   
    // realizar a chamada da proxima camada
    CamadaFisicaReceptora();

}

void  CamadaFisicaTrasnmissoraCodificacaoBinaria(){
    string mensagem;
    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;
    cout << "A mensagem digitada em binario eh :\n";
    int i;

    for (i =0; i < mensagem[i]!= '\0'; i++){
        int aux;
        aux = mensagem[i];
        int j;
        for (j = 7; j + 1 > 0; j--){
            if (aux >=(1<< j)){
                aux = aux - (1 << j);
                cout << "1";
            } else {
                cout << "0";
            }

        }
        cout << " ";
    }
    cout << "\n";

    MeioDeComunicacao();
}

void CamadaDeAplicacaoTransmissoraCodificacaoManchester(){
 
   
    int i;
    int* quadro;
    int size;

    int manchester[2*size];
    
    string mensagem;
    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;

     // Passegem de clock considerando que ele comece em zero
    for (i = 0; i < size; i++){
        manchester[2*i] = BitXnor (0,quadro[i]);
        manchester[2* i +1] = BitXnor(1,quadro[i]);
    }

    // size foi definido como int mas nenhum valor especifico 
    
   for (i = 0; i < 2*size; i++){
        //cout << manchester[i];
        
    }
    cout << "A mensagem com a Codificacao Manchester eh :\n" << manchester[i] << endl;   
    cout << endl;

     MeioDeComunicacao();
}
void CamadaDeAplicacaoTransmissoraCodificacaoBipolar(){

    
    string mensagem;

    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;
   

    cout << "A mensagem digitada em bipolar eh :";
    int i;
    int nivelnegativo = -1;
    int nivelneutro = 0;
    int nivelpositivo = 1;

                       
            for (i = 0; i < mensagem.length(); i++)
            //mensagem[i] > mensagem[nivelneutro]
            if (mensagem[i] > mensagem[nivelneutro]){
                nivelneutro = nivelpositivo;
               // cout << " ";    
                cout << "1";
                nivelneutro = 1;
                
              //else if (mensagem[i] == mensagem[i] || mensagem[i] == 0 || mensagem[i] == 1)  
            } else if ( mensagem[i] == mensagem[i] || mensagem[i] == 0 || mensagem[i] == 1){

                 nivelneutro = nivelnegativo;
                 mensagem[i] >= (1 << i);
                 mensagem[i] = mensagem[i] - (1 << i);
                //cout << " ";    
                cout << "0";
                nivelneutro = 0;
                
                //mensagem[i] ==  mensagem[i]  && mensagem[i] == 1
                } 
            if (mensagem[i] ==  mensagem[i]  && mensagem[i] == 1 ){

                    //nivelnegativo  = nivelneutro;
                    cout << " ";
                    cout << "-1";

                }

            
                cout << " ";
                cout << "\n";
            

     cout << "\nO valor tamanho da mensagem eh: " << mensagem.size() << endl;
    
     MeioDeComunicacao();

}

void CamadaFisicaTransmissora( int quadro[]) {
    
    int tipoDeCodificacao;  
    int fluxoBrutoDeBits; 
    int size;

    cout << "\nDigite qual a codificacao voce escolhe:\n 0 - Binaria \n 1 - Manchester\n 2 - Bipolar\n";
    cin >> tipoDeCodificacao;

    while (tipoDeCodificacao != 0 && tipoDeCodificacao != 1 && tipoDeCodificacao != 2) {
        cout << "Selecione uma opcao valida." << endl;
        cout << "\nDigite qual a codificacao voce escolhe:\n 0 - Binaria \n 1 - Manchester\n 2 - Bipolar\n";
        cin >> tipoDeCodificacao;
    }

    switch (tipoDeCodificacao) {
        case 0: // codificacao binaria
            CamadaFisicaTrasnmissoraCodificacaoBinaria();
            break;
        case 1: // codificacao Manchester
            CamadaDeAplicacaoTransmissoraCodificacaoManchester();
            break;
        case 2: // codificacao bipolar
            CamadaDeAplicacaoTransmissoraCodificacaoBipolar();
            break;

    }
}


void CamadaDeAplicacaoTransmissora(int mensagem){
    
    int size = 32;
    int quadro[size];

    CamadaEnlaceDadosTransmissora(quadro);
   // CamadaFisicaTransmissora();
}

void AplicacaoTransmissora(void){
   int mensagem;
    // chama a proxima camada
    CamadaDeAplicacaoTransmissora(mensagem);

}

void AplicacaoReceptora(){
    int tipoDeCodificacao;

    cout << "Tipo de Decodificacao" << endl;
    cin >> tipoDeCodificacao;

    while (tipoDeCodificacao != 0 && tipoDeCodificacao != 1 && tipoDeCodificacao != 2) {
        cout << "Selecione uma opcao valida." << endl;
        cout << "\nDigite qual a codificacao voce escolhe:\n 0 - Binaria \n 1 - Manchester\n 2 - Bipolar\n";
        cin >> tipoDeCodificacao;
    }
     
    switch(tipoDeCodificacao){
         case 0: 
          CamadaFisicaReceptoraDecodificacaoBinaria();
         break;
         case 1:
          CamadaDeAplicacaoReceptoraDecodificacaoManchester();   
         break;  
         case 2:
         CamadaDeAplicacaoReceptoraDecodificacaoBipolar();
    }
   
}

void CamadaDeAplicacaoReceptora(){
       int fluxoBrutoDeBits;
       string mensagem;
    // chama a prox. camada
    AplicacaoReceptora();
}
