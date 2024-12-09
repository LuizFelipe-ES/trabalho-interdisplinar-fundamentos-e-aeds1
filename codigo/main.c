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
* AUTHOR 2 - Codigo de Pessoa: [C�DIGO_MIRNA]
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

typedef struct tripulacao{

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
 char statusVoo[10];
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

//Fun��es e Procedimentos

 int cadastroDePassageiros ()
 {

 }

 int cadastroIntegranteTripulacao ()
 {

 }

 void cadastroDeVoo () //FUNCIONAL
 {
    voo novovoo;

    FILE *arquivo;

    arquivo = fopen("voos.txt","a"); //aberto como Append

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return 1;
    }

    //LER dados
    printf("\nInforme o codigo do voo: ");
    scanf("%d", &novovoo.codigoVoo);
    printf("\nInforme o codigo do avi�o: ");
    scanf("%d", &novovoo.codigoAviao);
    printf("\nInforme o codigo do piloto: ");
    scanf("%d", &novovoo.codigoPiloto);
    printf("\nInforme o codigo do copiloto: ");
    scanf("%d", &novovoo.codigoCopiloto);
    printf("\nInforme o codigo do comissario: ");
    scanf("%d", &novovoo.codigoComissario);
    printf("\nInforme o dia do voo: ");
    scanf("%d", &novovoo.diaVoo);
    printf("\nInforme o mes do voo: ");
    scanf("%d", &novovoo.mesVoo);
    printf("\nInforme o ano do voo: ");
    scanf("%d", &novovoo.anoVoo);
    printf("\nInforme a hora do voo: ");
    scanf("%d", &novovoo.horaVoo);
    printf("\nInforme os minutos do voo: ");
    scanf("%d", &novovoo.minutosVoo);
    getchar();
    printf("\nInforme a origem do voo: ");
    fgets(novovoo.origemVoo, sizeof(novovoo.origemVoo), stdin);
    novovoo.origemVoo[strcspn(novovoo.origemVoo, "\n")] = '\0';
    printf("\nInforme o destino do voo: ");
    fgets(novovoo.destinoVoo, sizeof(novovoo.destinoVoo), stdin);
    novovoo.destinoVoo[strcspn(novovoo.destinoVoo, "\n")] = '\0';
    printf("\nInforme o status do voo: ");
    fgets(novovoo.statusVoo, sizeof(novovoo.statusVoo), stdin);
    novovoo.statusVoo[strcspn(novovoo.statusVoo, "\n")] = '\0';
    printf("\nInforme a tarifa do voo: ");
    scanf("%f", &novovoo.tarifaVoo);


    //ESCREVER no arquivo
    fprintf(arquivo ,"%d - %s ~ %s - %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %s - R$ %.2f\n",
            novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, novovoo.diaVoo, novovoo.mesVoo, novovoo.anoVoo, novovoo.horaVoo, novovoo.minutosVoo,
            novovoo.codigoAviao, novovoo.codigoPiloto, novovoo.codigoCopiloto, novovoo.codigoComissario, novovoo.statusVoo, novovoo.tarifaVoo);


    fclose(arquivo);


 }

 void listarVoos() //FUNCIONAL
 {
        voo novovoo;
        int x;

        FILE *arquivo;
        arquivo = fopen("voos.txt","r"); //aberto como Read

        if(arquivo==NULL){
        printf("Erro ao criar o arquivo.\n");
        return 1;
        }


        while(fscanf(arquivo, "%d - %29[^~]~ %29[^-]- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %9[^-]- R$ %f",
        &novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, &novovoo.diaVoo, &novovoo.mesVoo, &novovoo.anoVoo, &novovoo.horaVoo, &novovoo.minutosVoo,
        &novovoo.codigoAviao, &novovoo.codigoPiloto, &novovoo.codigoCopiloto, &novovoo.codigoComissario,
        novovoo.statusVoo, &novovoo.tarifaVoo) != EOF)
        {
                //PRINTA os dados na tela
                printf("\n%d - %s~ %s- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %s- R$ %.2f\n",
                novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, novovoo.diaVoo, novovoo.mesVoo, novovoo.anoVoo, novovoo.horaVoo, novovoo.minutosVoo,
                novovoo.codigoAviao, novovoo.codigoPiloto, novovoo.codigoCopiloto, novovoo.codigoComissario,
                novovoo.statusVoo, novovoo.tarifaVoo);

        }

 }

 void editarVoo() //FUNCIONAL
 {
     voo novovoo;

     FILE *arquivo;
     FILE *temp;

     arquivo = fopen("voos.txt", "r"); //aberto como Read
     temp = fopen("temp.txt", "w"); //aberto como Write

     if(arquivo == NULL || temp == NULL){
        printf("Erro ao abrir o arquivo!");
        return 1;
     }

     int id, encontrado=0;

     //Id de pesquisa
     printf("\nQual o id do voo a ser alterado? ");
     scanf("%d", &id);
     getchar();

     //ESCANEIA o arquivo
     while(fscanf(arquivo, "%d - %29[^~]~ %29[^-]- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %9[^-]- R$ %f",
        &novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, &novovoo.diaVoo, &novovoo.mesVoo, &novovoo.anoVoo, &novovoo.horaVoo, &novovoo.minutosVoo,
        &novovoo.codigoAviao, &novovoo.codigoPiloto, &novovoo.codigoCopiloto, &novovoo.codigoComissario,
        novovoo.statusVoo, &novovoo.tarifaVoo) != EOF)
        {

                //ID de voo encontrado
                if(id == novovoo.codigoVoo){
                    //LER novos dados
                    encontrado = 1;
                    printf("\nInforme o codigo do voo: ");
                    scanf("%d", &novovoo.codigoVoo);
                    printf("\nInforme o codigo do avi�o: ");
                    scanf("%d", &novovoo.codigoAviao);
                    printf("\nInforme o codigo do piloto: ");
                    scanf("%d", &novovoo.codigoPiloto);
                    printf("\nInforme o codigo do copiloto: ");
                    scanf("%d", &novovoo.codigoCopiloto);
                    printf("\nInforme o codigo do comissario: ");
                    scanf("%d", &novovoo.codigoComissario);
                    printf("\nInforme o dia do voo: ");
                    scanf("%d", &novovoo.diaVoo);
                    printf("\nInforme o mes do voo: ");
                    scanf("%d", &novovoo.mesVoo);
                    printf("\nInforme o ano do voo: ");
                    scanf("%d", &novovoo.anoVoo);
                    printf("\nInforme a hora do voo: ");
                    scanf("%d", &novovoo.horaVoo);
                    printf("\nInforme os minutos do voo: ");
                    scanf("%d", &novovoo.minutosVoo);
                    getchar();
                    printf("\nInforme a origem do voo: ");
                    fgets(novovoo.origemVoo, sizeof(novovoo.origemVoo), stdin);
                    novovoo.origemVoo[strcspn(novovoo.origemVoo, "\n")] = '\0';
                    printf("\nInforme o destino do voo: ");
                    fgets(novovoo.destinoVoo, sizeof(novovoo.destinoVoo), stdin);
                    novovoo.destinoVoo[strcspn(novovoo.destinoVoo, "\n")] = '\0';
                    printf("\nInforme o status do voo: ");
                    fgets(novovoo.statusVoo, sizeof(novovoo.statusVoo), stdin);
                    novovoo.statusVoo[strcspn(novovoo.statusVoo, "\n")] = '\0';
                    printf("\nInforme a tarifa do voo: ");
                    scanf("%f", &novovoo.tarifaVoo);

                    //ESCREVE no arquivo temp
                    fprintf(temp, "%d - %s ~ %s - %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %s - R$ %.2f\n",
                    novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, novovoo.diaVoo, novovoo.mesVoo, novovoo.anoVoo, novovoo.horaVoo, novovoo.minutosVoo,
                    novovoo.codigoAviao, novovoo.codigoPiloto, novovoo.codigoCopiloto, novovoo.codigoComissario,
                    novovoo.statusVoo, novovoo.tarifaVoo);
                }
                else{
                    //ESCREVE no arquivo temp
                    fprintf(temp, "%d - %s~ %s- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %s- R$ %.2f\n",
                    novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, novovoo.diaVoo, novovoo.mesVoo, novovoo.anoVoo, novovoo.horaVoo, novovoo.minutosVoo,
                    novovoo.codigoAviao, novovoo.codigoPiloto, novovoo.codigoCopiloto, novovoo.codigoComissario,
                    novovoo.statusVoo, novovoo.tarifaVoo);
                }

        }

        fclose(arquivo);
        fclose(temp);

        if(encontrado == 0){
            printf("\nCodigo de voo nao encontrado!\n\n");

            //REMOVE arquivo temporario
            remove("temp.txt");
        }
        else{
            //REMOVE voos.txt e substitui por temp.txt
            remove("voos.txt");
            rename("temp.txt", "voos.txt");
            printf("\nVoo atualizado!\n\n");
        }

 }

void excluirVoo()
{
    voo novovoo;

    FILE *arquivo;
    FILE *temp;

    arquivo = fopen("voos.txt", "r");
    temp = fopen("temp.txt", "w");

    if(arquivo == NULL || temp == NULL){
        printf("Erro ao abrir o arquivo!");
        return 1;
    }

    int id, encontrado=0;

    //ID de pesquisa
    printf("\nDigite o codigo do voo que deve ser excluido: ");
    scanf("%d", &id);

    //ESCANEIA o arquivo
    while(fscanf(arquivo, "%d - %29[^~]~ %29[^-]- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %9[^-]- R$ %f",
    &novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, &novovoo.diaVoo, &novovoo.mesVoo, &novovoo.anoVoo, &novovoo.horaVoo, &novovoo.minutosVoo,
    &novovoo.codigoAviao, &novovoo.codigoPiloto, &novovoo.codigoCopiloto, &novovoo.codigoComissario,
    novovoo.statusVoo, &novovoo.tarifaVoo) != EOF)
    {
        if(id != novovoo.codigoVoo){
            //ESCREVE no arquivo temp
            fprintf(temp, "%d - %s~ %s- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %s- R$ %.2f\n",
            novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, novovoo.diaVoo, novovoo.mesVoo, novovoo.anoVoo, novovoo.horaVoo, novovoo.minutosVoo,
            novovoo.codigoAviao, novovoo.codigoPiloto, novovoo.codigoCopiloto, novovoo.codigoComissario,
            novovoo.statusVoo, novovoo.tarifaVoo);
        }
        else{
            encontrado++;
        }
    }

    fclose(arquivo);
    fclose(temp);

    if(encontrado == 1){
        remove("voos.txt");
        rename("temp.txt", "voos.txt");
        printf("\nVoo excluido!\n\n");
    }
    else{
        printf("\nCodigo de voo nao encontrado!\n\n");
        remove("temp.txt");
    }
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

//Fun��o Principal
int main ( void )
{
 int x = 1;
 int quantidadeAvioes = 10;
 int quantidadePadraoDeAssentos[8][10];


 do
 {
  printf("___________________________________________________________________________________________________________");
  printf("\nTRABALHO PRATICO INTERDISCIPLINAR ALGORITMOS E ESTRUTURAS DE DADOS / FUNDAMENTOS DE ENGENHARIA DE SOFTWARE");
  printf("\n\nMenu de opcoes : \n\n1 - Passageiros \n2 - Membros da Tripulacao \n3 - Voos \n4 - Assentos \n5 - Reservas \n0 - Sair do Menu");
  printf("\n\nEscolha uma Opcao : ");
  scanf("%d", &x);

  switch ( x )
  {
    case 0: ; break;
    case 1:
            printf("\n\nMenu de opcoes : \n\n1 - Cadastrar Passageiro \n2 - Editar passageiro \n3 - Listar passageiros \n4 - Excluir passageiro");
            scanf("%d", &x);
            switch( x )
            {
            case 1: cadastroDePassageiros(); break;
            //case 2: editarPassageiros(); break;
            //case 3: listarPassageiros(); break;
            //case 4: excluirPassageiros(); break;
            default: printf("\nOpcao invalida!"); break;
            }
            break;
    case 2:
            /*printf("\n\nMenu de opcoes : \n\n1 - Cadastrar membro da tripulacao \n2 - Editar membro da tripulacao \n3 - Listar membros da tripulacao \n4 - Excluir membro da tripulacao");
            scanf("%d", &x);
            switch( x )
            {
            case 1: cadastroDeMembroTripulacao(); break;
            case 2: editarMembroTripulacao(); break;
            case 3: listarMembroTripulacao(); break;
            case 4: excluirMembroTripulacao(); break;
            default: printf("\nOpcao invalida!"); break;
            }*/
            break;
    case 3:
            printf("\n\nMenu de opcoes : \n\n1 - Cadastrar voo \n2 - Editar voo \n3 - Listar voos \n4 - Excluir voo");
            scanf("%d", &x);
            switch( x )
            {
            case 1: cadastroDeVoo(); break;
            case 2: editarVoo(); break;
            case 3: listarVoos(); break;
            case 4: excluirVoo(); break;
            default: printf("\nOpcao invalida!"); break;
            }
            break;
    case 4:
            /*printf("\n\nMenu de opcoes : \n\n1 - Cadastrar assento \n2 - Editar assento \n3 - Listar assentos \n4 - Excluir assento");
            scanf("%d", &x);
            switch( x )
            {
            case 1: cadastroDeAssento(); break;
            case 2: editarAssento(); break;
            case 3: listarAssentos(); break;
            case 4: excluirAssento(); break;
            default: printf("\nOpcao invalida!"); break;
            }
            break;
    case 5:
            printf("\n\nMenu de opcoes : \n\n1 - Cadastrar reserva \n2 - Editar reserva \n3 - Listar reservas \n4 - Excluir reserva");
            scanf("%d", &x);
            switch( x )
            {
            case 1: cadastroDeReserva(); break;
            case 2: editarReserva(); break;
            case 3: listarReserva(); break;
            case 4: excluirReserva(); break;
            default: printf("\nOpcao invalida!"); break;
            }
            break;*/
    default: printf("\nOp��o Invalida");
  }

 } while ( x != 0 );


 return 0;
}
