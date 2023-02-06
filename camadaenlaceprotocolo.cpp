#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "camadaenlace.h"
#include "camadafisica.h"


using namespace std;

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]){

	int size = 32;
	int bit = 0;
	// adiciona o novo bit no tamanho do quadro
	int aux[size + 1];
	int j = 0;
	
	for (int j = 0; j < size; j++){
		bit ^= quadro[j] & 1; //xor
		quadro[j] >>= 1;
		// Se o bit for 0 nada é alterado, se o bit for 1 altera entre 0 e 1
	}
	for (j = 0; j < size; j++){
		aux[j] = quadro[j];
	}
	aux[size] = bit;

	//chama a camada física
	CamadaFisicaTransmissora(quadro);
}

void CamadaEnlaceDadosTransmissoraControleDeErroCRC(int quadro[]){

	// usar polinomio CRC-32 (IEEE 802)
	int size = 4;
	int size_t = 8;
	int gerador[size];
	
	//definindo gerador para 1001
	gerador[0] = 1;
	gerador[1] = 0;
	gerador[2] = 0;
	gerador[3] = 1;
		
	int i;
	for (i = 5; i < size - 1; i++ ){
		gerador[i] = 0;
	}

	cout << "Quadro:" << endl;
	for (i = 1; i < size_t; i++){
		cout << quadro[i];
	}
	cout << "\n";
	cout << "Gerador:";
	for (i = 0; i < size; i++){
		cout << gerador[i];
	}

	cout << "\n";
	// Códificação CRC
	int j;
	int resto[size];
	for (j = 0; j < size; j++){
		if (resto[0] == 1){
			for (i = 0; i < size; i++){ 
				//xor
				resto[j] ^= gerador[i];
			}
		}
	}
	
	int quadro_n = quadro[i] && gerador[size];

	cout << "Mensagem Transmitida:" << endl;
	// Dobrar o tamanho do size para que não tenha problema na divisão
	//Soma 3 considerando que o CRC seja 0000
	for (i = 0; i < 2*size + 3; i ++){
		cout <<  quadro_n;

	}

	cout << "\n";
	//chama a camada física

	CamadaFisicaTransmissora(quadro);

}

void CamadaEnlaceDadosTransmissoraControleDeErroHamming(int quadro[]){
	// implementação  do código para Hamming (11,7)

	int size = 32;
	int size_bits = 11;
	int i;
	int aux[size_bits];
	std::vector<int> bit;
	cout << "Mensagem recebida:";
	cout << "\n";

	for (i = 0; i < size_bits; i++){
		//aux[size_bits] = quadro[i];
		cout << quadro[i];
	}

	int P1 = 0;
	int P2 = 0;
	int P4 = 0;
	int P8 = 0;

	for (i = 0; i < size_bits; i++){

		P1 = (aux[i] + aux [i + 3] + aux[i + 5] 
			+ aux[i + 7] + aux[i + 9 ] + aux[i + 11]) % 2 == 0;
		// verificar a paridade %2==0
		bit.push_back(P1);
		
		P2 = (aux [i]  + aux[i + 3] + aux [i + 6] +
			aux [i + 7] + aux [i + 10] + aux [i +11]) % 2 == 0;
		bit.push_back(P2);
		bit.push_back(aux[i]);

		P4 = (aux[i]  + aux[i + 5] + aux [i + 6] + aux[i + 7]) % 2 == 0;
		bit.push_back(P4);
		bit.push_back(aux[i + 1]);
		bit.push_back(aux[i + 2]);
		bit.push_back(aux[i + 3]);

		P8 = (aux[i] + aux [i + 9] + aux [i + 10] + aux [i + 11]) %2 == 0;
		bit.push_back(P8);
		bit.push_back(aux[i + 9]);
		bit.push_back(aux[i + 10]);
		bit.push_back(aux[i + 11]);

		}
	
	cout << endl;
	cout << "A mensagem transmitida eh:" << int(bit.size()) << endl;;
		
	
	//chama a camada física

	CamadaFisicaTransmissora(quadro);

	}
	 

void CamadaDeEnlaceTransmissoraControleDeErro(int quadro[]){
	int tipoDeControleDeErro;


		cout << "\n";
		cout << "\nTipo de Controle de Erro: \n 0 - Bit Paridade Par \n 1 - CRC\n 2 - Código de Hamming\n ";
		cin >> tipoDeControleDeErro;
	
	switch(tipoDeControleDeErro){
		case 0: CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
		break;
		case 1: CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
		break;
		case 2:CamadaEnlaceDadosTransmissoraControleDeErroHamming(quadro);
		break;
	}


}

/*Considerando size = 32*/

void CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(int quadro[]){

	int i;
	int quantidade;
	int size = 32;
	int new_size;
	quantidade = size/8;

	int quadro_invertido[8];

	new_size = size + 8;
	//Novo quadro recebe o tamanho no new_size;
	int novo_quadro[new_size];

	for (i = new_size-1; i > 1; i--){
		novo_quadro[i] = quadro[i - 8];
	}

	i = 0;

	while (quantidade > 0){
		quadro_invertido[i] = quantidade%2;
		quantidade = quantidade/2;
		i++;
	}

	if (i == 7){
		quadro_invertido[i] = 0;
		i++;
	}


	if (i == 6){
		for (i = 6; i < 8; i++)
		quadro_invertido[i] = 0;
	}


	if (i == 5){
		for (i = 5; i < 8; i++)
		quadro_invertido[i] = 0;
	}


	if (i == 4){
		for (i = 4; i < 8; i++)
		quadro_invertido[i] = 0;
	}


	if (i == 3){
		for (i = 3; i < 8; i++)
		quadro_invertido[i] = 0;
	}

	if (i == 2){
		for (i = 2; i < 8; i++)
			quadro_invertido[i] = 0;
	}

	if (i == 1){
		for (i = 1; i < 8; i++)
			quadro_invertido[i] = 0;
	}


	cout << endl;

	int j = 0;
	i = 7;

	while (j < 8){
		novo_quadro[j] = quadro_invertido[i];
		j++;
		i--;
		
	}	
	
	cout << "\nEnquadramento por contagem de caracter:" << endl;
	cout << "\n" << endl;

	for (i = 0; i < new_size; i++){
		cout << novo_quadro[i];
	}
	
	cout << "\n"<< endl;
	//próxima camada - controle de erro
	CamadaDeEnlaceTransmissoraControleDeErro(quadro);
	//chama a próxima camada
	CamadaEnlaceDadosReceptora(quadro);
}
void CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes(int quadro[]){
	// implmentação da inserção de bytes 
	int flag_bytes[] = {0,0,1,0,0,0,1,1}; // Considerando a flag == # -dec == 35 -bin== 00100011
	int flag_esc[] = {0,0,0,0,0,0,0,0,0}; // referente ao byte de escape
	//É necessário percorrer pelo quadro para encontrar a flag

	int i;
	int size = 32;
	int qtd_flag = 0;

	for ( i = 0; i < size - 8; i++ ){
		if (flag_bytes){
			qtd_flag++;
			i = i + 8;
		}
	}
	int new_size = size + 8*qtd_flag + 16;
	int novo_quadro[new_size];
	

	cout << "Inserção de bytes";
	cout << "\n";
	cout << "Flag:";
	cout << "\n";
	

	for (i = 0; i < 8; i++)
		cout << flag_bytes[i];
	cout << "\n";
	cout << "Quadro:";
	cout << "\n";
	for (i = 0; i < new_size; i++)
		cout << novo_quadro[i];
	cout << "\n";

	// próxima camada controle de erro
	CamadaDeEnlaceTransmissoraControleDeErro(quadro);
	//chama a próxima camada
	CamadaEnlaceDadosReceptora(quadro);

}



void CamadaEnlaceDadosTransmissora (int quadro[]){
	
	CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

	//próxima camada 

	//CamadaDeEnlaceTransmissoraControleDeErro(quadro);

	//próxima camada

	//CamadaFisicaTransmissora();
}

void CamadaEnlaceDadosTransmissoraEnquadramento(int quadro[]){
	int tipoDeEnquadramento;
	
		cout << "\n";
		cout << "\nTipo de Enquadramento: \n 0 - Contagem De Caracteres \n 1 - Inserção de Bytes\n ";
		cin >> tipoDeEnquadramento;
	
	switch (tipoDeEnquadramento){
		case 0: // contagem de caracteres
		CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(quadro);
		break;
		case 1:
		CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes(quadro);
		break;
		
	}
}
/*Desenquadramento*/

void CamadaEnlaceDadosReceptoraDesenquadramentoContagemDeCaracteres(int quadro[]){
	//implemente o código

	int i;
	int size = 32;
	int aux;
	int novo_quadro[size - 8];
	aux = novo_quadro[size - 8];
	cout <<"\n Quadro Desenquadrado:";
	cout << "\n";

	for (i = 1; i < size - 8; i++){
		aux = quadro[i + 7];
		cout << aux;
	}

	cout << "\n";

	//chama a próxima camada


}

void CamadaEnlaceDadosReceptoraDesenquadramentoInsercaoDebytes(int quadro[]){

	//para desenquadrar foi implementado o inverso do enquadramento

	int flag_bytes[] = {0,0,1,0,0,0,1,1}; // Considerando a flag == # -dec == 35 -bin== 00100011
	int flag_esc[] = {0,0,0,0,0,0,0,0,0}; // referente ao byte de escape

	int i;
	int size = 32;
	int qtd_flag = 0;

	for ( i = 0; i < size - 8 ; i++ ){
		if (flag_bytes){
			qtd_flag++;
			i = i + 8;
		}
	}
	int new_size = size  + 8*qtd_flag - 16;
	int novo_quadro[new_size];


	cout << "Inserção de bytes";
	cout << "\n";
	cout << "Flag:";
	cout << "\n";
	

	for (i = 0; i < 8; i++)
		cout << flag_bytes[i];
	cout << "\n";
	cout << "Quadro Desenquadrado:";
	cout << "\n";
	for (i = 0; i < new_size; i++)
		cout << novo_quadro[i];
	cout << "\n";

	// chama a próxima camada
}



void CamadaEnlaceDadosReceptoraEnquadramento(int quadro[]){
	/*Realiza a chamada para o tipo de desenquadramento*/
	int tipoDesenquadramento;
	
		cout << "\n";
		cout << "\nTipo de Enquadramento - Camada Receptora: \n 0 - Contagem De Caracteres \n 1 - Inserção de Bytes\n ";
		cin >> tipoDesenquadramento;
	
	switch (tipoDesenquadramento){
		case 0: // contagem de caracteres
		CamadaEnlaceDadosReceptoraDesenquadramentoContagemDeCaracteres(quadro);
		break;
		case 1:
		CamadaEnlaceDadosReceptoraDesenquadramentoInsercaoDebytes(quadro);
		break;
		

		}
}
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar (int quadro[]){
	cout << "Verificação se houve erro:" << endl;
	// Em 0 -> nada muda

	int bit;
	int size = 32;
	int aux[size -1];
	int i;
	int n = 0;

	for (i = 0; i < size ; i++){
		n ^= quadro[i];
	}

	if ( n == 0){
		cout << "Foi encontrado erro na transmissão do quadro." << endl;
	} else  {
		cout << "Não houve erro na transmissão do quadro." << endl;
	}

	for ( i = 0; i < size -1; i++){
		//Novo quadro - > aux é igual ao quadro original
		aux[i] =  quadro[i];
	}

	// Próxima camada

	CamadaEnlaceDadosReceptoraEnquadramento(quadro);
}

void CamadaEnlaceDadosReceptoraControleDeErroCRC (int quadro []){
	cout << "Verificação se houve erro:" << endl;
	/* Para esse controle de erro, pode ser utilizado o início da implementação
	que foi feita para a camada transmissora do CRC
	*/

	// usar polinomio CRC-32 (IEEE 802)
	int size = 4;
	int size_t = 8;
	int gerador[size];
	
	//definindo gerador para 1001
	gerador[0] = 1;
	gerador[1] = 0;
	gerador[2] = 0;
	gerador[3] = 1;
		
	int i;
	for (i = 5; i < size - 1; i++ ){
		gerador[i] = 0;
	}

	cout << "Quadro:" << endl;
	for (i = 1; i < size_t; i++){
		cout << quadro[i];
	}
	cout << "\n";
	cout << "Gerador:";
	for (i = 0; i < size; i++){
		cout << gerador[i];
	}

	// Implementação da decodificação do CRC
	int j;
	int resto[size];
	
	for ( j = 0; j < size + 3; j ++){
		if (resto[0] == 1){
			for (i = 0; i < size; i++){
				//xor igual da codificação, trocando apenas o parâmetro j por i
					resto[i] ^= gerador[i];
			
			}
		}

	// continuação da divisão
	
	if ( j < 2*size){
		for (i = 0; i < size -1; i++){
			resto[i] = resto[i];
		}
	}
}
	if (resto[size - 1] == 0)
		cout << "\nA Mensagem foi recebida sem erro." << endl;
	 else 
		cout << "\nA Mensagem foi recebida com erro." << endl;
	

	cout << "\nA Mensagem recebida foi:" << endl;

	for (i = 0; i < size + 4 ; i++){
		cout << quadro[i];
	}

	// próxima camada 
	CamadaEnlaceDadosReceptoraEnquadramento(quadro);
}

void  CamadaEnlaceDadosReceptoraControleDeErroDeHamming(int quadro[]){
	// implementar de decoficação

	int size = 32;
	int size_bits = 11;
	int i;
	int total = 0;
	int aux[size_bits];
	std::vector<int> bit;
	cout << "Mensagem recebida:";
	cout << "\n";

	for (i = 0; i < size_bits; i++){
		//aux[size_bits] = quadro[i];
		bit.push_back(quadro[i]);
	}
	for (i = 0; i < size; i++){
		int M3 = 0;
		int M5 = 0;
		int M7 = 0;
		int M9 = 0;
		int M11 = 0;
		
		// Os valores de M3 a M11 podem receber valores de 0 ou 1
		M3 = (bit[i + 0] ^ bit [i + 1]) == bit [i + 0];
		M5 = (bit[i + 3] ^ bit [i + 0]) == bit [i + 0];
		M7 = (bit[i + 3] ^ bit [i + 1]) == bit [i + 0];
		M9 = (bit[i + 7] ^ bit [i + 0]) == bit [i + 0];
		M11 = (bit[i + 7] ^ bit [i + 1]) == bit [i + 0];

		total = quadro[i] && quadro [i + 1] && quadro [i + 3] && quadro[i + 7];
	}

	if (total == 2){
		cout << "Houve erro na codificação de Hamming." << endl;

	} else {
		cout << "Não houve erro na codificação de Hamming." << endl;
	}

	cout << "Soma dos bits:" << total << endl;
	// próxima camada 
	CamadaEnlaceDadosReceptoraEnquadramento(quadro);
}
void CamadaEnlaceReceptoraControleDeErro(int quadro[]){

	int tipoDeControleDeErro;

		cout << "Camada Receptora" << endl;
		cout << "\n";
		cout << "\nTipo de Controle de Erro: \n 0 - Bit Paridade Par \n 1 - CRC\n 2 - Código de Hamming\n ";
		cin >> tipoDeControleDeErro;
	
	switch(tipoDeControleDeErro){
		case 0: CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
		break;
		case 1: CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
		break;
		case 2: CamadaEnlaceDadosReceptoraControleDeErroDeHamming(quadro);
		break;
	}
}


void CamadaEnlaceDadosReceptora(int quadro[]){
	//implemente o código
	//chama a próxima camada
	//CamadaEnlaceDadosReceptoraEnquadramento(quadro);
	//chama a próxima camada
	CamadaEnlaceReceptoraControleDeErro(quadro);
	//chama a próxima camada
	//CamadaDeAplicacaoReceptora();
}

