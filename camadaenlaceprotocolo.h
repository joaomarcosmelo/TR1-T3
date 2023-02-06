#ifndef camadaenlaceprotocolo.h
#define camadaenlaceprotocolo.h


void CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(int quadro[]);

void CamadaEnlaceDadosTransmissora (int quadro[]);

void CamadaEnlaceDadosTransmissoraEnquadramento(int quadro[]);

void CamadaEnlaceDadosReceptoraDesenquadramento(int quadro[]);

void CamadaEnlaceDadosReceptora(int quadro[]);

void CamadaEnlaceDadosReceptoraDesenquadramentoContagemDeCaracteres(int quadro[]);

void CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes(int quadro[]);

void CamadaEnlaceDadosReceptoraDesenquadramentoInsercaoDebytes(int quadro[]);

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]);

void CamadaEnlaceDadosTransmissoraControleDeErroCRC(int quadro[]);

void CamadaDeEnlaceTransmissoraControleDeErro(int quadro[]);

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar (int quadro[]);

void CamadaEnlaceDadosReceptoraControleDeErroCRC (int quadro []);

void CamadaEnlaceDadosTransmissoraControleDeErroHamming(int quadro[]);

void  CamadaEnlaceDadosReceptoraControleDeErroDeHamming(int quadro[]);





#endif //camadaenlaceprotocolo.h
