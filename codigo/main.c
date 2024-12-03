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

 int cadastroDePassageiros ()
 {

 }

 int cadastroIntegranteTripulacao ()
 {

 }

 int cadastroDeVoo ()
 {

 }

 int cadastroDeAssentos ()
 {

 }

 int reservaDeAssento ( )
 {

 }

 int baixaReservaAssento ()
 {

 }

 int buscarPassageiroOuMembroDaTripulacao ()
 {

 }

 int listarVoosPassageiro ()
 {

 }

 int programaDeFidelidade ()
 {

 }

//Função Principal
int main ( void )
{
 int x = 1;
 int quantidadeAvioes = 10;
 int quantidadePadraoDeAssentos[8][10];


 do
 {
  printf("___________________________________________________________________________________________________________");
  printf("\nTRABALHO PRATICO INTERDISCIPLINAR ALGORITMOS E ESTRUTURAS DE DADOS / FUNDAMENTOS DE ENGENHARIA DE SOFTWARE");
  printf("\n\nMenu de opcoes : \n\n1 - Cadastrar Passageiro \n2 - Cadastrar Membro da Tripulacao \n3 - Cadastrar um Voo \n4 - Cadastrar um Assento \n5 - Reservar um Assento \n6 - Cancelar Minha Viagem \n7 - Pesquisar Membros da Tripulacao ou Passageiro \n8 - Listar os Meus Voos \n9 - Programa de Fidelidade \n0 - Sair do Menu");
  printf("\n\nEscolha uma Opcao : ");
  scanf("%d", &x);

  switch ( x )
  {
    case 0: ; break;
    case 1: cadastroDePassageiros() ; break;
    case 2: cadastroIntegranteTripulacao() ; break;
    case 3: cadastroDeVoo() ; break;
    case 4: cadastroDeAssentos() ; break;
    case 5: reservaDeAssento(); break;
    case 6: baixaReservaAssento(); break;
    case 7: buscarPassageiroOuMembroDaTripulacao; break;
    case 8: listarVoosPassageiro; break;
    case 9: programaDeFidelidade; break;
    default: printf("\nOpção Invalida");
  }

 } while ( x != 0 );


 return 0;
}
