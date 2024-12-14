/********************
* FILENAME : main.c
* DESCRIPTION : File compression and decompression
*               routines related to airline tickets.
*
* AUTHORS :
*           1 - Arthur Henrique de Lima Santos
*           2 - Karen Joilly Araújo Gregório de Almeida
*           3 - Luiz Felipe Alves da Silva
*           4 - Mirna dos Reis Arcanjo
*
* START DATE : 02 Dez 2024
*
* AUTHOR 1 - Matricula: [829748]
* AUTHOR 1 - Codigo de Pessoa: [1486435]
* AUTHOR 2 - Matricula: [874309]
* AUTHOR 2 - Codigo de Pessoa: [1568690]
* AUTHOR 3 - Matricula: [874345]
* AUTHOR 3 - Codigo de Pessoa: [1484339]
* AUTHOR 4 - Matricula: [83320]
* AUTHOR 4 - Codigo de Pessoa: [148975]
********************/

//Bibliotecas Utilizadas no Trabalho
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//Estruturas de Dados
typedef struct passageiro {

	int codigoPassageiro;
	char nomePassageiro[30];
	char enderecoPassageiro[50];
	char telefone[15];
	char fidelidade[4]; //"sim ou nao"
	int pontosFidelidade;

} passageiro;

typedef struct {
    int codigoIntegranteTripulacao;
    char nomeIntegranteTripulacao[30];
    char telefoneIntegranteTripulacao[15];
    char cargo[15];
} Tripulacao;

typedef struct voo {

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

} voo;

typedef struct assento {

	int numeroDoAssento;
	int codigoDoVoo;
	char statusDoAssento[10]; // ocupado/livre
	char nomePassageiro[30]; //caso esteja ocupado

} assento;

typedef struct reserva {

	int codigoDoVoo;
	int numeroDoAssento;
	int codigoDoPassageiro;

} reserva;

Tripulacao *tripulantes = NULL;
int totalTripulantes = 0;

const char *ARQUIVO = "tripulantes.txt";

//***FUNÇÕES E PROCEDIMENTOS***

//Função para verificar se o codigo de passageiro já existe
int codigoPassageiroJaExiste(int codigo) {
    FILE *arquivo = fopen("passageiros.txt", "r");
    int codigoExistente;
    passageiro novoPassageiro;

    if (arquivo == NULL) {
        printf("\nArquivo não encontrado.\n");
        return 0; // Arquivo não existe, código não existe
    }

    while (fscanf(arquivo, "%d;%29[^;];%49[^;];%14[^;];%3[^;];%d",
    &novoPassageiro.codigoPassageiro, novoPassageiro.nomePassageiro, novoPassageiro.enderecoPassageiro, novoPassageiro.telefone,
    novoPassageiro.fidelidade, &novoPassageiro.pontosFidelidade) != EOF)
        {
        if (novoPassageiro.codigoPassageiro == codigo) {
            fclose(arquivo);
            return 1; // Código já existe
        }
    }

    fclose(arquivo);
    return 0; // Código não encontrado
}

//Função para verificar se o passageiro existe
int passageiroExiste(char nomePassageiro[]){
    passageiro novoPassageiro;
    int x=0;

    FILE *arquivo;
    arquivo = fopen("passageiros.txt", "r");

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo!\n");
        return;
    }

    while (fscanf(arquivo, "%d;%29[^;];%49[^;];%14[^;];%3[^;];%d", &novoPassageiro.codigoPassageiro,
                 novoPassageiro.nomePassageiro, novoPassageiro.enderecoPassageiro, novoPassageiro.telefone, novoPassageiro.fidelidade,
                 &novoPassageiro.pontosFidelidade) != EOF)
    {
        if(strcmp(novoPassageiro.nomePassageiro, nomePassageiro) == 0){
            x++; //Passageiro encontrado
        }
    }

    fclose(arquivo);

    if(x==0){
        printf("\nPassageiro nao encontrado.\n");
        return 0;
    }
    else{
        return 1;
    }
}

//Função para verificar se o codigo de voo existe
int codigoVooExiste(int codigo){
    voo novovoo;

    FILE *arquivo;
    arquivo = fopen("voos.txt", "r");

    if(arquivo == NULL){
        printf("\nErro ao abrir 'voos.txt'!");
        return;
    }

    while(fscanf(arquivo, "%d - %29[^~]~ %29[^-]- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %9[^-]- R$ %f",
        &novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, &novovoo.diaVoo, &novovoo.mesVoo, &novovoo.anoVoo, &novovoo.horaVoo, &novovoo.minutosVoo,
        &novovoo.codigoAviao, &novovoo.codigoPiloto, &novovoo.codigoCopiloto, &novovoo.codigoComissario,
        novovoo.statusVoo, &novovoo.tarifaVoo) != EOF)
        {
            if(codigo == novovoo.codigoVoo){ //Voo existe
                return 1;
            }
        }

        fclose(arquivo);

    printf("\nCodigo de voo inexistente, por favor, digite um codigo valido!");
    return 0;
}

//Função para verificar se o assento está livre
int verificaAssentoLivre(int codigo, int numeroAssento) {
    assento novoAssento;
    int x=0, y=0;

    FILE *arquivo;
    arquivo = fopen("assentos.txt", "r");

    if(arquivo == NULL){
        printf("\nErro ao abrir 'assentos.txt'!");
        return;
    }

    while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].", &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro))
    {
        x++;
        if(codigo == novoAssento.codigoDoVoo && numeroAssento == novoAssento.numeroDoAssento){
            if(strcmp(novoAssento.statusDoAssento, "livre ") == 0){
                fclose(arquivo);
                return 1;
            }
            else{
                fclose(arquivo);
                printf("\nAssento já ocupado! ");
                return 0;
            }
        }
        else{
            y++;
        }
    }

    fclose(arquivo);

    if(x == y){
        printf("\nAssento não cadastrado!");
        return 0;
    }

}

// Funcao para cadastrar um passageiro
void cadastroDePassageiros() {
	passageiro novoPassageiro;
	FILE *arquivo;

	printf("Informe o codigo do passageiro: ");
	scanf("%d", &novoPassageiro.codigoPassageiro);

	// Garantir unicidade do cC3digo
	while (codigoPassageiroJaExiste(novoPassageiro.codigoPassageiro) == 1) {
		printf("Codigo ja existe. Informe outro codigo: ");
		scanf("%d", &novoPassageiro.codigoPassageiro);
	}

	// Ler os demais dados do passageiro
	getchar(); // Limpar buffer
	printf("Informe o nome do passageiro: ");
	fgets(novoPassageiro.nomePassageiro, sizeof(novoPassageiro.nomePassageiro), stdin);
	novoPassageiro.nomePassageiro[strcspn(novoPassageiro.nomePassageiro, "\n")] = '\0'; // Remover o '\n'

	printf("Informe o endereco do passageiro: ");
	fgets(novoPassageiro.enderecoPassageiro, sizeof(novoPassageiro.enderecoPassageiro), stdin);
	novoPassageiro.enderecoPassageiro[strcspn(novoPassageiro.enderecoPassageiro, "\n")] = '\0'; // Remover o '\n'

	printf("Informe o telefone do passageiro: ");
	fgets(novoPassageiro.telefone, sizeof(novoPassageiro.telefone), stdin);
	novoPassageiro.telefone[strcspn(novoPassageiro.telefone, "\n")] = '\0'; // Remover o '\n'

	printf("O passageiro possui fidelidade? (sim/nao): ");
	fgets(novoPassageiro.fidelidade, sizeof(novoPassageiro.fidelidade), stdin);
	novoPassageiro.fidelidade[strcspn(novoPassageiro.fidelidade, "\n")] = '\0'; // Remover o '\n'

	if (strcmp(novoPassageiro.fidelidade, "sim") == 0) {
		printf("Informe os pontos de fidelidade: ");
		scanf("%d", &novoPassageiro.pontosFidelidade);
	} else {
		novoPassageiro.pontosFidelidade = 0; // Sem pontos caso nC#o tenha fidelidade
	}

	// Gravar os dados no arquivo
	arquivo = fopen("passageiros.txt", "a");
	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		return 1;
	}

	fprintf(arquivo, "%d;%s;%s;%s;%s;%d\n",
	        novoPassageiro.codigoPassageiro,
	        novoPassageiro.nomePassageiro,
	        novoPassageiro.enderecoPassageiro,
	        novoPassageiro.telefone,
	        novoPassageiro.fidelidade,
	        novoPassageiro.pontosFidelidade);

	fclose(arquivo);
	printf("Passageiro cadastrado com sucesso!\n");

	return 1;
}

// Função para listar passageiros
void listarPassageiros() {
    passageiro novoPassageiro;
    FILE *arquivo = fopen("passageiros.txt", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de passageiros");
        return;
    }


    printf("\nLista de Passageiros:\n");
    while (fscanf(arquivo, "%d;%29[^;];%49[^;];%14[^;];%3[^;];%d",
    &novoPassageiro.codigoPassageiro, novoPassageiro.nomePassageiro, novoPassageiro.enderecoPassageiro, novoPassageiro.telefone,
    novoPassageiro.fidelidade, &novoPassageiro.pontosFidelidade) != EOF)
        {
        printf("Codigo: %d\n", novoPassageiro.codigoPassageiro);
        printf("Nome: %s\n", novoPassageiro.nomePassageiro);
        printf("Endereco: %s\n", novoPassageiro.enderecoPassageiro);
        printf("Telefone: %s\n", novoPassageiro.telefone);
        printf("--------------------------\n");
    }

    fclose(arquivo);
}

// Função para editar passageiro
void editarPassageiro() {
    FILE *arquivo = fopen("passageiros.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!arquivo || !temp) {
        perror("Erro ao abrir os arquivos");
        return;
    }

    int codigo;
    int encontrado = 0;
    passageiro novoPassageiro;

    printf("\nDigite o código do passageiro a ser editado: ");
    scanf("%d", &codigo);
    getchar();

    while (fread(&novoPassageiro, sizeof(novoPassageiro), 1, arquivo)) {
        if (novoPassageiro.codigoPassageiro == codigo) {
            encontrado = 1;

            printf("\nNovo Nome: ");
            fgets(novoPassageiro.nomePassageiro, sizeof(novoPassageiro.nomePassageiro), stdin);
            novoPassageiro.nomePassageiro[strcspn(novoPassageiro.nomePassageiro, "\n")] = 0;

            printf("Novo Endereço: ");
            fgets(novoPassageiro.enderecoPassageiro, sizeof(novoPassageiro.enderecoPassageiro), stdin);
            novoPassageiro.enderecoPassageiro[strcspn(novoPassageiro.enderecoPassageiro, "\n")] = 0;

            printf("Novo Telefone: ");
            fgets(novoPassageiro.telefone, sizeof(novoPassageiro.telefone), stdin);
            novoPassageiro.telefone[strcspn(novoPassageiro.telefone, "\n")] = 0;
        }
        fwrite(&novoPassageiro, sizeof(novoPassageiro), 1, temp);
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("passageiros.dat");
        rename("temp.dat", "passageiros.dat");
        printf("\nPassageiro editado com sucesso!\n");
    } else {
        remove("temp.dat");
        printf("\nPassageiro não encontrado.\n");
    }
}

// Função para excluir passageiro
void excluirPassageiro() {
    passageiro novoPassageiro;
    FILE *arquivo;
    FILE *temp;

    arquivo = fopen("passageiros.txt", "r");
    temp = fopen("temp.txt", "w");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    int codigo, encontrado = 0;
    char nome[30];

    // Solicitar código e nome do passageiro
    printf("Digite o código do passageiro que deve ser excluído: ");
    scanf("%d", &codigo);
    getchar();  // Limpar buffer
    printf("Digite o nome do passageiro que deve ser excluído: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';  // Remover o '\n'

    // Processar o arquivo e gravar no arquivo temporário
    while (fscanf(arquivo, "%d;%29[^;];%49[^;];%14[^;];%3[^;];%d\n",
                  &novoPassageiro.codigoPassageiro,
                  novoPassageiro.nomePassageiro,
                  novoPassageiro.enderecoPassageiro,
                  novoPassageiro.telefone,
                  novoPassageiro.fidelidade,
                  &novoPassageiro.pontosFidelidade) != EOF) {
        // Verificar se o código e o nome coincidem
        if (novoPassageiro.codigoPassageiro == codigo && strcmp(novoPassageiro.nomePassageiro, nome) == 0) {
            encontrado = 1;
            printf("\nPassageiro %s (%d) excluído com sucesso!\n", nome, codigo);
        } else {
            // Caso contrário, escreva o passageiro no arquivo temporário
            fprintf(temp, "%d;%s;%s;%s;%s;%d\n",
                    novoPassageiro.codigoPassageiro,
                    novoPassageiro.nomePassageiro,
                    novoPassageiro.enderecoPassageiro,
                    novoPassageiro.telefone,
                    novoPassageiro.fidelidade,
                    novoPassageiro.pontosFidelidade);
        }
    }

    fclose(arquivo);
    fclose(temp);

    // Se o passageiro foi encontrado, substitui o arquivo original pelo arquivo temporário
    if (encontrado == 1) {
        remove("passageiros.txt");
        rename("temp.txt", "passageiros.txt");
    } else {
        // Caso não tenha sido encontrado, apaga o arquivo temporário
        remove("temp.txt");
        printf("Passageiro não encontrado.\n");
    }

    return 0;
}

// Função para buscar passageiro
void buscarPassageiro() {

    int esc;

    do
    {
        printf("\nComo voce deseja buscar o passageiro? \n1 - ID \n2 - Nome ");
        scanf("%d", &esc);

        if(esc == 1){
            buscaPassageiroID();
        }
        else if(esc == 2){
            buscaPassageiroNome();
        }
        else{

        }
    }while(esc != 1 && esc != 2);

    return;

}

// Função para buscar passageiro por ID
void buscaPassageiroID(){
    passageiro novoPassageiro;

    int codigo, x=0;

    FILE *arquivo;
    arquivo = fopen("passageiros.txt", "r");

    printf("\nDigite o codigo do passageiro: ");
    scanf("%d", &codigo);

    while (fscanf(arquivo, "%d;%29[^;];%49[^;];%14[^;];%3[^;];%d", &novoPassageiro.codigoPassageiro,
            novoPassageiro.nomePassageiro, novoPassageiro.enderecoPassageiro, novoPassageiro.telefone, novoPassageiro.fidelidade,
            &novoPassageiro.pontosFidelidade) != EOF)
    {
        if(codigo == novoPassageiro.codigoPassageiro){
        x++;
        printf("\n%d %s\n", novoPassageiro.codigoPassageiro, novoPassageiro.nomePassageiro);
        return 1;
        }
    }

    if(x==0){
        printf("\nPassageiro não encontrado!");
        return 0;
    }

}

// Função para buscar passageiro por Nome
void buscaPassageiroNome(){
    passageiro novoPassageiro;

    char nome[30];
    int x=0;

    FILE *arquivo;
    arquivo = fopen("passageiros.txt", "r");

    getchar();
    printf("\nDigite o nome do passageiro: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    while (fscanf(arquivo, "%d;%29[^;];%49[^;];%14[^;];%3[^;];%d", &novoPassageiro.codigoPassageiro,
            novoPassageiro.nomePassageiro, novoPassageiro.enderecoPassageiro, novoPassageiro.telefone, novoPassageiro.fidelidade,
            &novoPassageiro.pontosFidelidade) != EOF)
    {
        if(strcmp(nome, novoPassageiro.nomePassageiro) == 0){
        x++;
        printf("\n%d %s\n", novoPassageiro.codigoPassageiro, novoPassageiro.nomePassageiro);
        return 1;
        }
    }

    if(x==0){
        printf("\nPassageiro não encontrado!");
        return 0;
    }
}

void cadastroDeVoo() {
    voo novovoo;
    FILE *arquivo;

    arquivo = fopen("voos.txt", "a"); // Abre o arquivo em modo append

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    printf("\nInforme o codigo do voo: ");
    scanf("%d", &novovoo.codigoVoo);


    printf("\nInforme o codigo do piloto: ");
    scanf("%d", &novovoo.codigoPiloto);
    if (!tripulanteExiste(novovoo.codigoPiloto)) {
        printf("Piloto não encontrado, cadastrando...\n");
        cadastroDeMembroTripulacao();

        int codigo;
        printf("Digite o código do piloto recém-cadastrado para verificar: ");
        scanf("%d", &codigo);
        if (codigo != novovoo.codigoPiloto) {
            printf("Código incorreto. Cadastro não validado.\n");
            return;
        }
    }


    printf("\nInforme o codigo do copiloto: ");
    scanf("%d", &novovoo.codigoCopiloto);
    if (!tripulanteExiste(novovoo.codigoCopiloto)) {
        printf("Copiloto não encontrado, cadastrando...\n");
        cadastroDeMembroTripulacao();

        int codigo;
        printf("Digite o código do copiloto recém-cadastrado para verificar: ");
        scanf("%d", &codigo);
        if (codigo != novovoo.codigoCopiloto) {
            printf("Código incorreto. Cadastro não validado.\n");
            return;
        }
    }

    // Verifica se o comissário existe
    printf("\nInforme o codigo do comissario: ");
    scanf("%d", &novovoo.codigoComissario);
    if (!tripulanteExiste(novovoo.codigoComissario)) {
        printf("Comissário não encontrado, cadastrando...\n");
        cadastroDeMembroTripulacao();

        int codigo;
        printf("Digite o código do comissário recém-cadastrado para verificar: ");
        scanf("%d", &codigo);
        if (codigo != novovoo.codigoComissario) {
            printf("Código incorreto. Cadastro não validado.\n");
            return;
        }
    }

    // Lê as demais informações do voo
    printf("\nInforme o codigo do aviao: ");
    scanf("%d", &novovoo.codigoAviao);
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
    getchar(); // Para consumir o '\n' deixado por scanf
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

    // Escreve as informações no arquivo
    fprintf(arquivo, "%d - %s ~ %s - %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %s - R$ %.2f\n",
            novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, novovoo.diaVoo, novovoo.mesVoo, novovoo.anoVoo, novovoo.horaVoo, novovoo.minutosVoo,
            novovoo.codigoAviao, novovoo.codigoPiloto, novovoo.codigoCopiloto, novovoo.codigoComissario, novovoo.statusVoo, novovoo.tarifaVoo);

    fclose(arquivo);
    printf("Voo cadastrado com sucesso!\n");
}

int tripulanteExiste(int codigo) {
    for (int i = 0; i < totalTripulantes; i++) {
        if (tripulantes[i].codigoIntegranteTripulacao == codigo) {
            return 1; // Tripulante encontrado
        }
    }
    return 0; // Tripulante não encontrado
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
                    printf("\nInforme o codigo do avi o: ");
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

void excluirVoo() //FUNCIONAL
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

void cadastroDeAssento () //FUNCIONAL
{
    assento novoAssento;

    FILE *arquivo;
    arquivo = fopen("assentos.txt", "a");

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo 'assentos.txt'!");
        return;
    }

    do{
        printf("\nInsira o codigo do voo: ");
        scanf("%d", &novoAssento.codigoDoVoo);
    } while(codigoVooExiste(novoAssento.codigoDoVoo) == 0);

    printf("\nInforme o numero do assento: ");
    scanf("%d", &novoAssento.numeroDoAssento);

    strcpy(novoAssento.statusDoAssento, "livre");
    strcpy(novoAssento.nomePassageiro, "n");

    fprintf(arquivo, "%d - %s - %d %s.\n", novoAssento.codigoDoVoo, novoAssento.statusDoAssento, novoAssento.numeroDoAssento, novoAssento.nomePassageiro);

    fclose(arquivo);

    printf("\nAssento cadastrado e disponivel!\n");

}

void listarAssentos() //FUNCIONAL
{
    assento novoAssento;
    int codigo, x=0;

    FILE *arquivo;
    arquivo = fopen("assentos.txt", "r");

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo 'assentos.txt'!");
        return;
    }

    do
    {
        printf("\nDigite o codigo do voo: ");
        scanf("%d", &codigo);
    }while(codigoVooExiste(codigo)==0);

    while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].", &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro) != EOF)
    {
        if(codigo == novoAssento.codigoDoVoo){
            x++;
            if(strcmp(novoAssento.statusDoAssento, "livre ") == 0){
                printf("\n%d - %s\n", novoAssento.numeroDoAssento, novoAssento.statusDoAssento);
            }
            else{
                printf("\n%d - %s- %s.\n", novoAssento.numeroDoAssento, novoAssento.statusDoAssento, novoAssento.nomePassageiro);
            }
        }
    }

    if(x==0){
        printf("\nNenhum assento cadastrado nesse voo.\n");
    }
}

void excluirAssento() //FUNCIONAL
{
    assento novoAssento;
    int x=0, codigo, numeroAssento;

    FILE *arquivo;
    FILE *temp;
    arquivo = fopen("assentos.txt", "r");
    temp = fopen("temp.txt", "w");

    if(arquivo == NULL || temp == NULL){
        printf("\nErro ao abrir arquivo!");
        return;
    }

    do
    {
        printf("\nDigite o codigo do voo: ");
        scanf("%d", &codigo);
    }while(codigoVooExiste(codigo)==0);

    while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].", &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro) != EOF)
    {
        if(codigo == novoAssento.codigoDoVoo){
            x++;
        }
    }

    rewind(arquivo);

    if(x==0){
        printf("\nNenhum assento cadastrado nesse voo.\n");
        fclose(arquivo);
        fclose(temp);
        return;
    }
    else{
        printf("\nDigite o numero do assento a ser excluido: ");
        scanf("%d", &numeroAssento);

        x = 0;

        while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].", &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro) != EOF)
        {
            if(numeroAssento == novoAssento.numeroDoAssento){
                x++;
            }
            else{
                fprintf(temp, "%d - %s- %d %s.\n", novoAssento.codigoDoVoo, novoAssento.statusDoAssento, novoAssento.numeroDoAssento, novoAssento.nomePassageiro);
            }
        }
    }

    fclose(arquivo);
    fclose(temp);

    if(x==0){
        printf("\nAssento nao cadastrado.\n");
        remove("temp.txt");
    }
    else{
        printf("\nAssento excluido!\n");
        remove("assentos.txt");
        rename("temp.txt", "assentos.txt");
    }
}

void reservarAssento()
{
    assento novoAssento;
    int codigo, numeroAssento, x=0;

    FILE *arquivo;
    FILE *temp;
    arquivo = fopen("assentos.txt", "r");
    temp = fopen("temp.txt", "w");

    if(arquivo == NULL || temp == NULL){
        printf("\nErro ao abrir arquivo!\n");
        return;
    }

    do
    {
        printf("\nDigite o codigo do voo: ");
        scanf("%d", &codigo);
    }while(codigoVooExiste(codigo)==0);

    do
    {
        printf("\nDigite o numero do assento: ");
        scanf("%d", &numeroAssento);
    }while(verificaAssentoLivre(codigo, numeroAssento)==0);
    getchar();

    while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].", &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro) != EOF)
    {
        if(codigo == novoAssento.codigoDoVoo && numeroAssento == novoAssento.numeroDoAssento){
            do
            {
                printf("\nDigite o nome do passageiro: ");
                fgets(novoAssento.nomePassageiro, sizeof(novoAssento.nomePassageiro), stdin);
                novoAssento.nomePassageiro[strcspn(novoAssento.nomePassageiro, "\n")] = '\0';
            }while(passageiroExiste(novoAssento.nomePassageiro) == 0);

            strcpy(novoAssento.statusDoAssento, "ocupado ");
        }
        fprintf(temp, "%d - %s- %d %s.\n", novoAssento.codigoDoVoo, novoAssento.statusDoAssento, novoAssento.numeroDoAssento, novoAssento.nomePassageiro);
    }

    fclose(arquivo);
    fclose(temp);

    remove("assentos.txt");
    rename("temp.txt", "assentos.txt");

    printf("\nAssento reservado!\n");

}

void baixaReservaAssento ()
{
    assento novoAssento;
    int codigo, numeroAssento, x=0;

    FILE *arquivo;
    FILE *temp;
    arquivo = fopen("assentos.txt", "r");
    temp = fopen("temp.txt", "w");

    if(arquivo == NULL || temp == NULL){
        printf("\nErro ao abrir arquivo!\n");
        return;
    }

    do
    {
        printf("\nDigite o codigo do voo: ");
        scanf("%d", &codigo);
    }while(codigoVooExiste(codigo)==0);

    do
    {
        printf("\nDigite o numero do assento: ");
        scanf("%d", &numeroAssento);
    }while(verificaAssentoLivre(codigo, numeroAssento)==1);

    while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].", &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro) != EOF)
    {
        if(codigo == novoAssento.codigoDoVoo && numeroAssento == novoAssento.numeroDoAssento){

            strcpy(novoAssento.nomePassageiro, "n");
            strcpy(novoAssento.statusDoAssento, "livre ");
        }
        fprintf(temp, "%d - %s- %d %s.\n", novoAssento.codigoDoVoo, novoAssento.statusDoAssento, novoAssento.numeroDoAssento, novoAssento.nomePassageiro);
    }

    fclose(arquivo);
    fclose(temp);

    remove("assentos.txt");
    rename("temp.txt", "assentos.txt");

    printf("\nAssento livre!\n");
}


void salvarArquivo() {
    FILE *file = fopen(ARQUIVO, "w");
    if (!file) {
        perror("Erro ao abrir o arquivo para salvar");
        return;
    }

    for (int i = 0; i < totalTripulantes; i++) {
        fprintf(file, "%d;%s;%s;%s\n",
                tripulantes[i].codigoIntegranteTripulacao,
                tripulantes[i].nomeIntegranteTripulacao,
                tripulantes[i].telefoneIntegranteTripulacao,
                tripulantes[i].cargo);
    }

    fclose(file);
    printf("Dados salvos no arquivo.\n");
}

void carregarArquivo() {
    FILE *file = fopen(ARQUIVO, "r");
    if (!file) {
        printf("Nenhum dado encontrado para carregar.\n");
        return;
    }

    totalTripulantes = 0;
    free(tripulantes);
    tripulantes = NULL;

    Tripulacao temp;
    while (fscanf(file, "%d;%29[^;];%14[^;];%14[^\n]\n",
                  &temp.codigoIntegranteTripulacao,
                  temp.nomeIntegranteTripulacao,
                  temp.telefoneIntegranteTripulacao,
                  temp.cargo) == 4) {
        tripulantes = realloc(tripulantes, (totalTripulantes + 1) * sizeof(Tripulacao));
        tripulantes[totalTripulantes] = temp;
        totalTripulantes++;
    }

    fclose(file);
    printf("Dados carregados do arquivo.\n");
}

int obterProximoId() {
    int proximoId = 1;
    for (int i = 0; i < totalTripulantes; i++) {
        if (tripulantes[i].codigoIntegranteTripulacao >= proximoId) {
            proximoId = tripulantes[i].codigoIntegranteTripulacao + 1;
        }
    }
    return proximoId;
}

void cadastroDeMembroTripulacao() {
    Tripulacao novoMembro;
    novoMembro.codigoIntegranteTripulacao = obterProximoId();

    printf("Nome do integrante:   ");
    fgets(novoMembro.nomeIntegranteTripulacao, sizeof(novoMembro.nomeIntegranteTripulacao), stdin);
    novoMembro.nomeIntegranteTripulacao[strcspn(novoMembro.nomeIntegranteTripulacao, "\n")] = '\0';

    printf("Telefone do integrante:   ");
    fgets(novoMembro.telefoneIntegranteTripulacao, sizeof(novoMembro.telefoneIntegranteTripulacao), stdin);
    novoMembro.telefoneIntegranteTripulacao[strcspn(novoMembro.telefoneIntegranteTripulacao, "\n")] = '\0';

    printf("Cargo (piloto, copiloto, comissario):   ");
    fgets(novoMembro.cargo, sizeof(novoMembro.cargo), stdin);
    novoMembro.cargo[strcspn(novoMembro.cargo, "\n")] = '\0';

    tripulantes = realloc(tripulantes, (totalTripulantes + 1) * sizeof(Tripulacao));
    tripulantes[totalTripulantes] = novoMembro;
    totalTripulantes++;

    printf("Membro cadastrado com sucesso! Codigo: %d\n", novoMembro.codigoIntegranteTripulacao);

    salvarArquivo();
}

void listarMembroTripulacao() {
    if (totalTripulantes == 0) {
        printf("Nenhum membro cadastrado.\n");
        return;
    }

    printf("Lista de membros da tripulacao:\n");
    for (int i = 0; i < totalTripulantes; i++) {
        printf("Codigo: %d\n", tripulantes[i].codigoIntegranteTripulacao);
        printf("Nome: %s\n", tripulantes[i].nomeIntegranteTripulacao);
        printf("Telefone: %s\n", tripulantes[i].telefoneIntegranteTripulacao);
        printf("Cargo: %s\n\n", tripulantes[i].cargo);
    }
}

void editarMembroTripulacao() {
    int codigo;
    printf("Digite o codigo do membro que deseja editar: ");
    scanf("%d", &codigo);
    getchar();

    for (int i = 0; i < totalTripulantes; i++) {
        if (tripulantes[i].codigoIntegranteTripulacao == codigo) {
            printf("Novo nome: ");
            fgets(tripulantes[i].nomeIntegranteTripulacao, sizeof(tripulantes[i].nomeIntegranteTripulacao), stdin);
            tripulantes[i].nomeIntegranteTripulacao[strcspn(tripulantes[i].nomeIntegranteTripulacao, "\n")] = '\0';

            printf("Novo telefone: ");
            fgets(tripulantes[i].telefoneIntegranteTripulacao, sizeof(tripulantes[i].telefoneIntegranteTripulacao), stdin);
            tripulantes[i].telefoneIntegranteTripulacao[strcspn(tripulantes[i].telefoneIntegranteTripulacao, "\n")] = '\0';

            printf("Novo cargo: ");
            fgets(tripulantes[i].cargo, sizeof(tripulantes[i].cargo), stdin);
            tripulantes[i].cargo[strcspn(tripulantes[i].cargo, "\n")] = '\0';

            printf("Membro atualizado com sucesso!\n");
            salvarArquivo();
            return;
        }
    }

    printf("Codigo nao encontrado!\n");
}

void excluirMembroTripulacao() {
    int codigo;
    printf("Digite o codigo do membro que deseja excluir: ");
    scanf("%d", &codigo);
    getchar();

    for (int i = 0; i < totalTripulantes; i++) {
        if (tripulantes[i].codigoIntegranteTripulacao == codigo) {
            for (int j = i; j < totalTripulantes - 1; j++) {
                tripulantes[j] = tripulantes[j + 1];
            }
            totalTripulantes--;
            tripulantes = realloc(tripulantes, totalTripulantes * sizeof(Tripulacao));
            printf("Membro excluido com sucesso!\n");
            salvarArquivo();
            return;
        }
    }

    printf("Codigo nao encontrado!\n");
}
void listarVoosPassageiro()
{
    assento novoAssento;
    voo novovoo;
    passageiro novoPassageiro;
    char nome[30];
    int esc, codigo;

    FILE *arquivo;
    FILE *voos;
    FILE *passageiros;
    arquivo = fopen("assentos.txt", "r");
    voos = fopen("voos.txt", "r");
    passageiros = fopen("passageiros.txt", "r");

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo.");
        return;
    }

    do
    {
        printf("\nComo deseja pesquisar os voos? \n1 - ID \n2 - Nome");
        scanf("%d", &esc);
    }while(esc != 1 && esc != 2);

    if(esc == 2){
        getchar();
        printf("\nDigite o nome do passageiro: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0';

        while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].", &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro) != EOF)
        {
            while(fscanf(voos, "%d - %29[^~]~ %29[^-]- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %9[^-]- R$ %f",
            &novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, &novovoo.diaVoo, &novovoo.mesVoo, &novovoo.anoVoo, &novovoo.horaVoo, &novovoo.minutosVoo,
            &novovoo.codigoAviao, &novovoo.codigoPiloto, &novovoo.codigoCopiloto, &novovoo.codigoComissario,
            novovoo.statusVoo, &novovoo.tarifaVoo) != EOF)
            {
                if(strcmp(nome, novoAssento.nomePassageiro) == 0){
                    if(novoAssento.codigoDoVoo == novovoo.codigoVoo){
                        printf("\nVoo: %d \n%s- %s\n Aviao: %d", novoAssento.codigoDoVoo, novovoo.origemVoo, novovoo.destinoVoo, novovoo.codigoAviao);
                    }
                }
            }

            rewind(voos);


        }
        printf("\n------------------\n");
    }
    else{
        printf("\nDigite o codigo do passageiro: ");
        scanf("%d", &codigo);

        while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].", &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro) != EOF)
        {
            while(fscanf(voos, "%d - %29[^~]~ %29[^-]- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %9[^-]- R$ %f",
            &novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, &novovoo.diaVoo, &novovoo.mesVoo, &novovoo.anoVoo, &novovoo.horaVoo, &novovoo.minutosVoo,
            &novovoo.codigoAviao, &novovoo.codigoPiloto, &novovoo.codigoCopiloto, &novovoo.codigoComissario,
            novovoo.statusVoo, &novovoo.tarifaVoo) != EOF)
            {
                while(fscanf(passageiros, "%d;%29[^;];%49[^;];%14[^;];%3[^;];%d", &novoPassageiro.codigoPassageiro,
                     novoPassageiro.nomePassageiro, novoPassageiro.enderecoPassageiro, novoPassageiro.telefone, novoPassageiro.fidelidade,
                     &novoPassageiro.pontosFidelidade) != EOF)
                {
                    if(codigo == novoPassageiro.codigoPassageiro){
                        if(strcmp(novoPassageiro.nomePassageiro, novoAssento.nomePassageiro) == 0){
                            if(novoAssento.codigoDoVoo == novovoo.codigoVoo){
                                printf("\nVoo: %d \n%s- %s\n Aviao: %d", novoAssento.codigoDoVoo, novovoo.origemVoo, novovoo.destinoVoo, novovoo.codigoAviao);
                            }
                        }
                    }
                }
                rewind(passageiros);
            }

            rewind(voos);
        }
        printf("\n------------------\n");
    }

    fclose(arquivo);
    fclose(voos);
    fclose(passageiros);

}

void buscarPontosFidelidade(int codigoBuscado) {
    FILE *arquivo;
    passageiro p;
    char linha[300];
    int encontrado = 0;


    arquivo = fopen("passageiros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }


    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

        sscanf(linha, "%d;%[^;];%[^;];%[^;];%[^;];%d",
               &p.codigoPassageiro,
               p.nomePassageiro,
               p.enderecoPassageiro,
               p.telefone,
               p.fidelidade,
               &p.pontosFidelidade);


        if (p.codigoPassageiro == codigoBuscado) {
            printf("Passageiro encontrado!\n");
            printf("Nome: %s\n", p.nomePassageiro);
            printf("Pontos de fidelidade: %d\n", p.pontosFidelidade);
            encontrado = 1;
            break;
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Nenhum passageiro encontrado com o codigo %d.\n", codigoBuscado);
    }
}

//Funcao Principal
int main ( void )
{
 int codigo;
 int x = 1;
 int quantidadeAvioes = 10;
 int quantidadePadraoDeAssentos[8][10];


 do
 {
  printf("___________________________________________________________________________________________________________");
  printf("\nTRABALHO PRATICO INTERDISCIPLINAR ALGORITMOS E ESTRUTURAS DE DADOS / FUNDAMENTOS DE ENGENHARIA DE SOFTWARE");
  printf("\n\nMenu de opcoes : \n\n1 - Passageiros \n2 - Membros da Tripulacao \n3 - Voos \n4 - Assentos \n5 - Consulta de Fidelidade \n0 - Sair do Menu");
  printf("\n\nEscolha uma Opcao : ");
  scanf("%d", &x);

  switch ( x )
  {
    case 0: ; break;
    case 1:
            printf("\n\nMenu de opcoes : \n\n1 - Cadastrar Passageiro \n2 - Editar passageiro \n3 - Listar passageiros \n4 - Excluir passageiro \n5 - Buscar passageiro \n6 - Listar voos do passageiro ");
            printf("\n\nEscolha uma Opcao : ");
            scanf("%d", &x);
            switch( x )
            {
            case 1: cadastroDePassageiros(); break;
            case 2: editarPassageiro(); break;
            case 3: listarPassageiros(); break;
            case 4: excluirPassageiro(); break;
            case 5: buscarPassageiro(); break;
            case 6: listarVoosPassageiro(); break;
            default: printf("\nOpcao invalida!"); break;
            }
            break;
    case 2:
            printf("\n\nMenu de opcoes : \n\n1 - Cadastrar membro da tripulacao \n2 - Editar membro da tripulacao \n3 - Listar membros da tripulacao \n4 - Excluir membro da tripulacao");
            printf("\n\nEscolha uma Opcao : ");
            scanf("%d", &x);
            switch( x )
            {
            case 1: cadastroDeMembroTripulacao(); break;
            case 2: editarMembroTripulacao(); break;
            case 3: listarMembroTripulacao(); break;
            case 4: excluirMembroTripulacao(); break;
            default: printf("\nOpcao invalida!"); break;
            }
            break;
    case 3:
            printf("\n\nMenu de opcoes : \n\n1 - Cadastrar voo \n2 - Editar voo \n3 - Listar voos \n4 - Excluir voo");
            printf("\n\nEscolha uma Opcao : ");
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
            printf("\n\nMenu de opcoes : \n\n1 - Cadastrar assento \n2 - Reservar assento \n3 - Listar assentos \n4 - Excluir assento \n5 - Excluir reserva de assento");
            printf("\n\nEscolha uma Opcao : ");
            scanf("%d", &x);
            switch( x )
            {
            case 1: cadastroDeAssento(); break;
            case 2: reservarAssento(); break;
            case 3: listarAssentos(); break;
            case 4: excluirAssento(); break;
            case 5: baixaReservaAssento(); break;
            default: printf("\nOpcao invalida!"); break;
            }

            break;

    case 5:
            printf("\n\nDigite o codigo do passageiro para consultar os pontos de fidelidade : ");
            scanf("%d", &codigo);
            buscarPontosFidelidade(codigo);

            break;
    default: printf("\nOpcao Invalida");
  }

 } while ( x != 0 );


 return 0;
}

