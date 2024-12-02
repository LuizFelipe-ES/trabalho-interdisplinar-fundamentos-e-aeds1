/********************************************************
* FILENAME : main.c
* DESCRIPTION : File compression and decompression
*               routines related to airline tickets.
*
* AUTHORS : 1 - Luiz Felipe Alves da Silva
*           2 - Mirna dos Reis Arcanjo
* START DATE : 02 Dez 2024
*
* AUTHOR 1 - Matricula: [874345]
* AUTHOR 1 - Codigo de Pessoa: [1484339]
* AUTHOR 2 - Matricula: [MATRICULA_MIRNA]
* AUTHOR 2 - Codigo de Pessoa: [CÓDIGO_MIRNA]
********************************************************/

//Bibliotecas Utilizadas no Trabalho
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//Estruturas de Dados
typedef struct passageiro{

 int codigoPassageiro;
 char nomePassageiro[30];
 char enderecoPassageiro[50];
 int pontosFidelidade;

}passageiro;

typedef struct triupulacao{

 int codigoIntegranteTripulacao;
 char nomeIntegranteTripulacao[30];
 int telefoneIntegranteTripulacao;
 int cargoPiloto;
 int cargoCopiloto;
 int cargoComissario;

}tripulacao;

typedef struct voo{

 int codigoVoo;
 int diaVoo, mesVoo, anoVoo;
 int horaVoo, minutosVoo;
 char origemVoo[30];
 char destinoVoo[30];
 int codigoAviao;
 int codigoPiloto;
 int codigoCopiloto;
 int codigoComissario;
 char statusVoo[8];
 float tarifaVoo;

}voo;

typedef struct assento {

 int quantidadeDeAssentos[8][10];
 int numeroDoAssento;
 int codigoDoVoo;
 char statusDoAssento[8];

}assento;

typedef struct reserva {

 int codigoDoVoo;
 int numeroDoAssento;
 int codigoDoPassageiro;

}reserva;

//Funções e Procedimentos



//Função Principal
int main ( void )
{




 return 0;
}