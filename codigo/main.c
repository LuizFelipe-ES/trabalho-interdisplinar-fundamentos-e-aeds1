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

    int codigoPassageiro;          // Codigo unico do passageiro
    char nomePassageiro[30];       // Nome completo do passageiro
    char enderecoPassageiro[50];   // Endereco completo do passageiro
    char telefone[15];             // Numero de telefone do passageiro, incluindo o DDD
    char fidelidade[4];            // Indica se o passageiro possui fidelidade ("sim" ou "nao")
    int pontosFidelidade;          // Quantidade de pontos acumulados pelo passageiro no programa de fidelidade

} passageiro;  // Estrutura que armazena os dados de um passageiro


typedef struct {
    int codigoIntegranteTripulacao;  // Codigo unico do integrante da tripulacao
    char nomeIntegranteTripulacao[30];  // Nome completo do integrante da tripulacao
    char telefoneIntegranteTripulacao[15];  // Numero de telefone do integrante da tripulacao
    char cargo[15];  // Cargo do integrante da tripulacao

} Tripulacao;  // Estrutura que armazena os dados de um integrante da tripulacao

typedef struct voo {

    int codigoVoo;  // Codigo unico do voo
    int diaVoo, mesVoo, anoVoo;  // Data do voo (dia, mes e ano)
    int horaVoo, minutosVoo;  // Hora e minutos de partida do voo
    char origemVoo[30];  // Origem do voo
    char destinoVoo[30];  // Destino do voo
    int codigoAviao;  // Codigo do aviao utilizado no voo
    int codigoPiloto;  // Codigo do piloto responsavel pelo voo
    int codigoCopiloto;  // Codigo do copiloto do voo
    int codigoComissario;  // Codigo do comissario de bordo
    char statusVoo[10];  // Status atual do voo (ex: "Em andamento", "Concluido")
    float tarifaVoo;  // Tarifa do voo

} voo;  // Estrutura que armazena os dados de um voo


typedef struct assento {

    int numeroDoAssento;  // Numero unico do assento
    int codigoDoVoo;  // Codigo do voo associado ao assento
    char statusDoAssento[10];  // Status do assento (ex: "ocupado" ou "livre")
    char nomePassageiro[30];  // Nome do passageiro caso o assento esteja ocupado

} assento;  // Estrutura que armazena os dados de um assento


typedef struct reserva {

    int codigoDoVoo;  // Codigo do voo associado a reserva
    int numeroDoAssento;  // Numero do assento reservado
    int codigoDoPassageiro;  // Codigo do passageiro que fez a reserva

} reserva;  // Estrutura que armazena os dados de uma reserva


Tripulacao *tripulantes = NULL;  // Ponteiro para armazenar os dados dos tripulantes, inicializado como NULL
int totalTripulantes = 0;  // Variavel que armazena o total de tripulantes

const char *ARQUIVO = "tripulantes.txt";  // Nome do arquivo que armazena os dados dos tripulantes


//***FUNCOES E PROCEDIMENTOS***

//Funcao para verificar se o codigo de passageiro ja existe
int codigoPassageiroJaExiste(int codigo) {
    FILE *arquivo = fopen("passageiros.txt", "r");  // Abre o arquivo "passageiros.txt" em modo leitura
    int codigoExistente;  // Variavel para armazenar o codigo do passageiro lido do arquivo
    passageiro novoPassageiro;  // Variavel para armazenar os dados do passageiro lido do arquivo

    if (arquivo == NULL) {  // Verifica se o arquivo nao foi aberto corretamente
        printf("\nArquivo nao encontrado.\n");  // Exibe mensagem de erro caso o arquivo nao exista
        return 0; // Arquivo nao existe, codigo nao existe
    }

    while (fscanf(arquivo, "%d;%29[^;];%49[^;];%14[^;];%3[^;];%d",  // Lê os dados do arquivo no formato especificado
    &novoPassageiro.codigoPassageiro, novoPassageiro.nomePassageiro, novoPassageiro.enderecoPassageiro, novoPassageiro.telefone,
    novoPassageiro.fidelidade, &novoPassageiro.pontosFidelidade) != EOF)  // Continua lendo até o fim do arquivo
        {
        if (novoPassageiro.codigoPassageiro == codigo) {  // Verifica se o codigo do passageiro lido é igual ao codigo informado
            fclose(arquivo);  // Fecha o arquivo após encontrar o codigo
            return 1; // Codigo ja existe
        }
    }

    fclose(arquivo);  // Fecha o arquivo quando o codigo nao for encontrado
    return 0; // Codigo nao encontrado
}


//Funcao para verificar se o passageiro existe
int passageiroExiste(char nomePassageiro[]){
    passageiro novoPassageiro;  // Variavel para armazenar os dados de um passageiro lido do arquivo
    int x=0;  // Variavel para contar se o passageiro foi encontrado

    FILE *arquivo;  // Ponteiro para o arquivo
    arquivo = fopen("passageiros.txt", "r");  // Abre o arquivo "passageiros.txt" em modo leitura

    if(arquivo == NULL){  // Verifica se o arquivo nao foi aberto corretamente
        printf("\nErro ao abrir arquivo!\n");  // Exibe mensagem de erro se o arquivo nao for encontrado
        return;  // Retorna sem fazer mais nada caso o arquivo nao tenha sido aberto
    }

    while (fscanf(arquivo, "%d;%29[^;];%49[^;];%14[^;];%3[^;];%d",  // Lê os dados do arquivo no formato especificado
                 &novoPassageiro.codigoPassageiro, novoPassageiro.nomePassageiro, novoPassageiro.enderecoPassageiro, novoPassageiro.telefone, novoPassageiro.fidelidade,
                 &novoPassageiro.pontosFidelidade) != EOF)  // Continua lendo até o final do arquivo
    {
        if(strcmp(novoPassageiro.nomePassageiro, nomePassageiro) == 0){  // Verifica se o nome do passageiro lido é igual ao nome informado
            x++;  // Se encontrado, incrementa a variavel 'x'
        }
    }

    fclose(arquivo);  // Fecha o arquivo após a leitura

    if(x==0){  // Verifica se nenhum passageiro foi encontrado
        printf("\nPassageiro nao encontrado.\n");  // Exibe mensagem caso o passageiro nao seja encontrado
        return 0;  // Retorna 0 indicando que o passageiro nao foi encontrado
    }
    else{  // Caso o passageiro tenha sido encontrado
        return 1;  // Retorna 1 indicando que o passageiro foi encontrado
    }
}

//Funcao para verificar se o codigo de voo existe
int codigoVooExiste(int codigo){
    voo novovoo;  // Variavel para armazenar os dados de um voo lido do arquivo

    FILE *arquivo;  // Ponteiro para o arquivo
    arquivo = fopen("voos.txt", "r");  // Abre o arquivo "voos.txt" em modo leitura

    if(arquivo == NULL){  // Verifica se o arquivo nao foi aberto corretamente
        printf("\nErro ao abrir 'voos.txt'!");  // Exibe mensagem de erro caso o arquivo nao exista
        return;  // Retorna sem fazer mais nada caso o arquivo nao tenha sido aberto
    }

    while(fscanf(arquivo, "%d - %29[^~]~ %29[^-]- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %9[^-]- R$ %f",  // Lê os dados do arquivo no formato especificado
        &novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, &novovoo.diaVoo, &novovoo.mesVoo, &novovoo.anoVoo, &novovoo.horaVoo, &novovoo.minutosVoo,
        &novovoo.codigoAviao, &novovoo.codigoPiloto, &novovoo.codigoCopiloto, &novovoo.codigoComissario,
        novovoo.statusVoo, &novovoo.tarifaVoo) != EOF)  // Continua lendo até o final do arquivo
        {
            if(codigo == novovoo.codigoVoo){  // Verifica se o codigo do voo lido é igual ao codigo informado
                return 1;  // Se o codigo for encontrado, retorna 1 indicando que o voo existe
            }
        }

        fclose(arquivo);  // Fecha o arquivo após a leitura

    printf("\nCodigo de voo inexistente, por favor, digite um codigo valido!");  // Exibe mensagem caso o codigo de voo nao seja encontrado
    return 0;  // Retorna 0 indicando que o codigo de voo nao foi encontrado
}

//Funcao para verificar se o assento esta livre
int verificaAssentoLivre(int codigo, int numeroAssento) {
    assento novoAssento;  // Variavel para armazenar os dados do assento lido do arquivo
    int x=0, y=0;  // Variaveis para contar o total de assentos e para verificar se o assento foi encontrado

    FILE *arquivo;  // Ponteiro para o arquivo
    arquivo = fopen("assentos.txt", "r");  // Abre o arquivo "assentos.txt" em modo leitura

    if(arquivo == NULL){  // Verifica se o arquivo nao foi aberto corretamente
        printf("\nErro ao abrir 'assentos.txt'!");  // Exibe mensagem de erro caso o arquivo nao exista
        return;  // Retorna sem fazer mais nada caso o arquivo nao tenha sido aberto
    }

    while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].",  // Lê os dados do arquivo no formato especificado
        &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro))
    {
        x++;  // Incrementa a variavel 'x' a cada assento lido
        if(codigo == novoAssento.codigoDoVoo && numeroAssento == novoAssento.numeroDoAssento){  // Verifica se o codigo do voo e numero do assento correspondem aos dados lidos
            if(strcmp(novoAssento.statusDoAssento, "livre ") == 0){  // Verifica se o status do assento é "livre"
                fclose(arquivo);  // Fecha o arquivo
                return 1;  // Retorna 1 indicando que o assento esta livre
            }
            else{
                fclose(arquivo);  // Fecha o arquivo
                printf("\nAssento ja ocupado! ");  // Exibe mensagem informando que o assento esta ocupado
                return 0;  // Retorna 0 indicando que o assento esta ocupado
            }
        }
        else{
            y++;  // Incrementa a variavel 'y' quando o assento lido nao corresponde ao codigo e numero informados
        }
    }

    fclose(arquivo);  // Fecha o arquivo após a leitura

    if(x == y){  // Verifica se o total de assentos lidos é igual ao número de assentos não correspondentes ao código e número
        printf("\nAssento nao cadastrado!");  // Exibe mensagem indicando que o assento nao foi cadastrado
        return 0;  // Retorna 0 indicando que o assento não foi encontrado
    }
}


// Funcao para cadastrar um passageiro
void cadastroDePassageiros() {
    passageiro novoPassageiro;  // Variavel para armazenar os dados do novo passageiro
    FILE *arquivo;  // Ponteiro para o arquivo onde os dados do passageiro serão gravados

    printf("Informe o codigo do passageiro: ");  // Solicita o codigo do passageiro
    scanf("%d", &novoPassageiro.codigoPassageiro);  // Lê o código do passageiro

    // Garantir unicidade do codigo
    while (codigoPassageiroJaExiste(novoPassageiro.codigoPassageiro) == 1) {  // Verifica se o código já existe
        printf("Codigo ja existe. Informe outro codigo: ");  // Solicita outro código caso o código já exista
        scanf("%d", &novoPassageiro.codigoPassageiro);  // Lê o novo código
    }

    // Ler os demais dados do passageiro
    getchar();  // Limpa o buffer do teclado para evitar problemas na leitura de strings
    printf("Informe o nome do passageiro: ");  // Solicita o nome do passageiro
    fgets(novoPassageiro.nomePassageiro, sizeof(novoPassageiro.nomePassageiro), stdin);  // Lê o nome do passageiro
    novoPassageiro.nomePassageiro[strcspn(novoPassageiro.nomePassageiro, "\n")] = '\0';  // Remove o caractere '\n' que vem com a leitura

    printf("Informe o endereco do passageiro: ");  // Solicita o endereço do passageiro
    fgets(novoPassageiro.enderecoPassageiro, sizeof(novoPassageiro.enderecoPassageiro), stdin);  // Lê o endereço do passageiro
    novoPassageiro.enderecoPassageiro[strcspn(novoPassageiro.enderecoPassageiro, "\n")] = '\0';  // Remove o caractere '\n' do endereço

    printf("Informe o telefone do passageiro: ");  // Solicita o telefone do passageiro
    fgets(novoPassageiro.telefone, sizeof(novoPassageiro.telefone), stdin);  // Lê o telefone do passageiro
    novoPassageiro.telefone[strcspn(novoPassageiro.telefone, "\n")] = '\0';  // Remove o caractere '\n' do telefone

    printf("O passageiro possui fidelidade? (sim/nao): ");  // Pergunta se o passageiro tem fidelidade
    fgets(novoPassageiro.fidelidade, sizeof(novoPassageiro.fidelidade), stdin);  // Lê a resposta sobre fidelidade
    novoPassageiro.fidelidade[strcspn(novoPassageiro.fidelidade, "\n")] = '\0';  // Remove o caractere '\n' da resposta

    if (strcmp(novoPassageiro.fidelidade, "sim") == 0) {  // Verifica se a resposta foi "sim"
        printf("Informe os pontos de fidelidade: ");  // Solicita os pontos de fidelidade
        scanf("%d", &novoPassageiro.pontosFidelidade);  // Lê os pontos de fidelidade
    } else {
        novoPassageiro.pontosFidelidade = 0;  // Caso não tenha fidelidade, os pontos são 0
    }

    // Gravar os dados no arquivo
    arquivo = fopen("passageiros.txt", "a");  // Abre o arquivo "passageiros.txt" no modo de anexação
    if (arquivo == NULL) {  // Verifica se houve erro ao abrir o arquivo
        printf("Erro ao abrir o arquivo.\n");  // Exibe mensagem de erro
        return 1;  // Retorna 1 caso haja erro na abertura do arquivo
    }

    fprintf(arquivo, "%d;%s;%s;%s;%s;%d\n",  // Grava os dados do novo passageiro no arquivo
            novoPassageiro.codigoPassageiro,
            novoPassageiro.nomePassageiro,
            novoPassageiro.enderecoPassageiro,
            novoPassageiro.telefone,
            novoPassageiro.fidelidade,
            novoPassageiro.pontosFidelidade);

    fclose(arquivo);  // Fecha o arquivo após gravar os dados
    printf("Passageiro cadastrado com sucesso!\n");  // Exibe mensagem de sucesso

    return 1;  // Retorna 1 indicando que o cadastro foi realizado com sucesso
}

// Função para listar passageiros
void listarPassageiros() {
    passageiro novoPassageiro;  // Declara uma variável para armazenar os dados de cada passageiro
    FILE *arquivo = fopen("passageiros.txt", "r");  // Abre o arquivo "passageiros.txt" no modo de leitura
    if (!arquivo) {  // Verifica se houve erro ao abrir o arquivo
        perror("Erro ao abrir o arquivo de passageiros");  // Exibe uma mensagem de erro se o arquivo não puder ser aberto
        return;  // Retorna da função se houver erro ao abrir o arquivo
    }

    printf("\nLista de Passageiros:\n");  // Exibe o título da lista de passageiros
    // Lê cada linha do arquivo e preenche a estrutura passageiro com os dados lidos
    while (fscanf(arquivo, "%d;%29[^;];%49[^;];%14[^;];%3[^;];%d",
    &novoPassageiro.codigoPassageiro, novoPassageiro.nomePassageiro, novoPassageiro.enderecoPassageiro, novoPassageiro.telefone,
    novoPassageiro.fidelidade, &novoPassageiro.pontosFidelidade) != EOF)  // Lê os dados do arquivo até o fim
    {
        // Exibe os dados do passageiro lido do arquivo
        printf("Codigo: %d\n", novoPassageiro.codigoPassageiro);  // Exibe o código do passageiro
        printf("Nome: %s\n", novoPassageiro.nomePassageiro);  // Exibe o nome do passageiro
        printf("Endereco: %s\n", novoPassageiro.enderecoPassageiro);  // Exibe o endereço do passageiro
        printf("Telefone: %s\n", novoPassageiro.telefone);  // Exibe o telefone do passageiro
        printf("--------------------------\n");  // Exibe uma linha para separar os dados dos passageiros
    }

    fclose(arquivo);  // Fecha o arquivo após a leitura
}


// Funcao para editar passageiro
void editarPassageiro() {
    FILE *arquivo = fopen("passageiros.txt", "r");  // Abre o arquivo "passageiros.txt" para leitura
    FILE *temp = fopen("temp.txt", "w");  // Cria um arquivo temporario "temp.txt" para escrita

    if (!arquivo || !temp) {  // Verifica se houve erro ao abrir os arquivos
        perror("Erro ao abrir os arquivos");  // Exibe mensagem de erro caso algum dos arquivos nao tenha sido aberto
        return;  // Retorna da funcao caso haja erro
    }

    int codigo;  // Declara a variavel para armazenar o codigo do passageiro
    int encontrado = 0;  // Declara e inicializa a variavel que ira verificar se o passageiro foi encontrado
    passageiro novoPassageiro;  // Declara a variavel para armazenar os dados do passageiro

    printf("\nDigite o codigo do passageiro a ser editado: ");  // Solicita o codigo do passageiro
    scanf("%d", &codigo);  // Lê o codigo do passageiro
    getchar();  // Limpa o buffer de entrada para evitar problemas com fgets

    // Lê o arquivo de passageiros e verifica se o codigo do passageiro corresponde ao fornecido
    while (fread(&novoPassageiro, sizeof(novoPassageiro), 1, arquivo)) {
        if (novoPassageiro.codigoPassageiro == codigo) {  // Verifica se o codigo do passageiro encontrado é o mesmo informado
            encontrado = 1;  // Marca como encontrado

            // Solicita novos dados para o passageiro
            printf("\nNovo Nome: ");
            fgets(novoPassageiro.nomePassageiro, sizeof(novoPassageiro.nomePassageiro), stdin);  // Lê o novo nome
            novoPassageiro.nomePassageiro[strcspn(novoPassageiro.nomePassageiro, "\n")] = 0;  // Remove o '\n' do nome

            printf("Novo Endereco: ");
            fgets(novoPassageiro.enderecoPassageiro, sizeof(novoPassageiro.enderecoPassageiro), stdin);  // Lê o novo endereço
            novoPassageiro.enderecoPassageiro[strcspn(novoPassageiro.enderecoPassageiro, "\n")] = 0;  // Remove o '\n' do endereço

            printf("Novo Telefone: ");
            fgets(novoPassageiro.telefone, sizeof(novoPassageiro.telefone), stdin);  // Lê o novo telefone
            novoPassageiro.telefone[strcspn(novoPassageiro.telefone, "\n")] = 0;  // Remove o '\n' do telefone
        }
        fwrite(&novoPassageiro, sizeof(novoPassageiro), 1, temp);  // Escreve os dados (editados ou não) no arquivo temporário
    }

    fclose(arquivo);  // Fecha o arquivo original
    fclose(temp);  // Fecha o arquivo temporário

    if (encontrado) {  // Verifica se o passageiro foi encontrado e editado
        remove("passageiros.dat");  // Remove o arquivo original
        rename("temp.dat", "passageiros.dat");  // Renomeia o arquivo temporário para o nome do arquivo original
        printf("\nPassageiro editado com sucesso!\n");  // Exibe mensagem de sucesso
    } else {  // Caso o passageiro não tenha sido encontrado
        remove("temp.dat");  // Remove o arquivo temporário
        printf("\nPassageiro nao encontrado.\n");  // Exibe mensagem de erro
    }
}

// Funcao para excluir passageiro
void excluirPassageiro() {
    passageiro novoPassageiro;  // Declara a estrutura para armazenar dados do passageiro
    FILE *arquivo;  // Declara o ponteiro para o arquivo de passageiros
    FILE *temp;  // Declara o ponteiro para o arquivo temporário

    arquivo = fopen("passageiros.txt", "r");  // Abre o arquivo de passageiros para leitura
    temp = fopen("temp.txt", "w");  // Cria um arquivo temporário para escrever

    // Verifica se houve erro ao abrir os arquivos
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");  // Exibe mensagem de erro
        return 1;  // Retorna da função em caso de erro
    }

    int codigo, encontrado = 0;  // Declara variáveis para o código do passageiro e flag de encontrado
    char nome[30];  // Declara a variável para armazenar o nome do passageiro

    // Solicita o código e o nome do passageiro a ser excluído
    printf("Digite o codigo do passageiro que deve ser excluido: ");
    scanf("%d", &codigo);  // Lê o código do passageiro
    getchar();  // Limpa o buffer de entrada
    printf("Digite o nome do passageiro que deve ser excluido: ");
    fgets(nome, sizeof(nome), stdin);  // Lê o nome do passageiro
    nome[strcspn(nome, "\n")] = '\0';  // Remove o '\n' do nome

    // Lê os dados do arquivo e escreve no arquivo temporário
    while (fscanf(arquivo, "%d;%29[^;];%49[^;];%14[^;];%3[^;];%d\n",
                  &novoPassageiro.codigoPassageiro,
                  novoPassageiro.nomePassageiro,
                  novoPassageiro.enderecoPassageiro,
                  novoPassageiro.telefone,
                  novoPassageiro.fidelidade,
                  &novoPassageiro.pontosFidelidade) != EOF) {
        // Verifica se o código e o nome coincidem
        if (novoPassageiro.codigoPassageiro == codigo && strcmp(novoPassageiro.nomePassageiro, nome) == 0) {
            encontrado = 1;  // Marca como encontrado
            printf("\nPassageiro %s (%d) excluido com sucesso!\n", nome, codigo);  // Exibe mensagem de sucesso
        } else {
            // Caso contrário, escreve o passageiro no arquivo temporário
            fprintf(temp, "%d;%s;%s;%s;%s;%d\n",
                    novoPassageiro.codigoPassageiro,
                    novoPassageiro.nomePassageiro,
                    novoPassageiro.enderecoPassageiro,
                    novoPassageiro.telefone,
                    novoPassageiro.fidelidade,
                    novoPassageiro.pontosFidelidade);
        }
    }

    fclose(arquivo);  // Fecha o arquivo original
    fclose(temp);  // Fecha o arquivo temporário

    // Se o passageiro foi encontrado, substitui o arquivo original pelo arquivo temporário
    if (encontrado == 1) {
        remove("passageiros.txt");  // Remove o arquivo original
        rename("temp.txt", "passageiros.txt");  // Renomeia o arquivo temporário para o nome do arquivo original
    } else {
        // Caso o passageiro não tenha sido encontrado, apaga o arquivo temporário
        remove("temp.txt");
        printf("Passageiro nao encontrado.\n");  // Exibe mensagem de erro
    }

    return 0;  // Retorna da função
}

// Função para buscar passageiro
void buscarPassageiro() {

    int esc;  // Declara a variável para armazenar a escolha do usuário

    do {
        // Exibe as opções para buscar o passageiro
        printf("\nComo voce deseja buscar o passageiro? \n1 - ID \n2 - Nome ");
        scanf("%d", &esc);  // Lê a escolha do usuário

        // Chama a função correspondente com base na escolha
        if (esc == 1) {
            buscaPassageiroID();  // Busca por ID
        } else if (esc == 2) {
            buscaPassageiroNome();  // Busca por Nome
        } else {
            // Caso a escolha seja inválida, não faz nada
        }
    } while (esc != 1 && esc != 2);  // Continua até que a escolha seja válida

    return;  // Retorna da função
}

// Função para buscar passageiro por ID
void buscaPassageiroID() {
    passageiro novoPassageiro;  // Declara a variável para armazenar os dados do passageiro

    int codigo, x = 0;  // Declara as variáveis para o código do passageiro e flag de encontrado

    FILE *arquivo;  // Declara o ponteiro para o arquivo de passageiros
    arquivo = fopen("passageiros.txt", "r");  // Abre o arquivo de passageiros para leitura

    printf("\nDigite o codigo do passageiro: ");
    scanf("%d", &codigo);  // Lê o código do passageiro

    // Lê os dados do arquivo e verifica se o código corresponde ao fornecido
    while (fscanf(arquivo, "%d;%29[^;];%49[^;];%14[^;];%3[^;];%d", &novoPassageiro.codigoPassageiro,
                  novoPassageiro.nomePassageiro, novoPassageiro.enderecoPassageiro, novoPassageiro.telefone,
                  novoPassageiro.fidelidade, &novoPassageiro.pontosFidelidade) != EOF) {
        if (codigo == novoPassageiro.codigoPassageiro) {  // Verifica se o código do passageiro é o mesmo
            x++;  // Marca como encontrado
            printf("\n%d %s\n", novoPassageiro.codigoPassageiro, novoPassageiro.nomePassageiro);  // Exibe os dados do passageiro
            return 1;  // Retorna se o passageiro foi encontrado
        }
    }

    // Se o passageiro não foi encontrado, exibe uma mensagem
    if (x == 0) {
        printf("\nPassageiro nao encontrado!");
        return 0;  // Retorna caso o passageiro não seja encontrado
    }
}


// Função para buscar passageiro por Nome
void buscaPassageiroNome(){
    passageiro novoPassageiro;  // Declara a variável para armazenar os dados do passageiro

    char nome[30];  // Declara a variável para armazenar o nome do passageiro
    int x=0;  // Declara a variável para contar os passageiros encontrados

    FILE *arquivo;  // Declara o ponteiro para o arquivo de passageiros
    arquivo = fopen("passageiros.txt", "r");  // Abre o arquivo de passageiros para leitura

    getchar();  // Limpa o buffer de entrada
    printf("\nDigite o nome do passageiro: ");
    fgets(nome, sizeof(nome), stdin);  // Lê o nome do passageiro
    nome[strcspn(nome, "\n")] = '\0';  // Remove o '\n' do nome

    // Lê os dados do arquivo e verifica se o nome corresponde ao fornecido
    while (fscanf(arquivo, "%d;%29[^;];%49[^;];%14[^;];%3[^;];%d", &novoPassageiro.codigoPassageiro,
                  novoPassageiro.nomePassageiro, novoPassageiro.enderecoPassageiro, novoPassageiro.telefone,
                  novoPassageiro.fidelidade, &novoPassageiro.pontosFidelidade) != EOF) {
        // Se o nome do passageiro corresponder ao nome buscado, exibe os dados do passageiro
        if (strcmp(nome, novoPassageiro.nomePassageiro) == 0) {
            x++;  // Marca que um passageiro foi encontrado
            printf("\n%d %s\n", novoPassageiro.codigoPassageiro, novoPassageiro.nomePassageiro);  // Exibe os dados
            return 1;  // Retorna ao encontrar o passageiro
        }
    }

    // Se o passageiro não foi encontrado, exibe uma mensagem
    if (x == 0) {
        printf("\nPassageiro nao encontrado!");
        return 0;  // Retorna caso o passageiro não seja encontrado
    }
}

// Função para cadastrar um voo
void cadastroDeVoo() {
    voo novovoo;  // Declara a estrutura para armazenar os dados do voo
    FILE *arquivo;  // Declara o ponteiro para o arquivo de voos

    arquivo = fopen("voos.txt", "a");  // Abre o arquivo de voos para append (adição no final)

    // Verifica se houve erro ao abrir o arquivo
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    // Solicita e lê as informações do voo
    printf("\nInforme o codigo do voo: ");
    scanf("%d", &novovoo.codigoVoo);

    // Solicita o código do piloto e verifica se o piloto existe
    printf("\nInforme o codigo do piloto: ");
    scanf("%d", &novovoo.codigoPiloto);
    if (!tripulanteExiste(novovoo.codigoPiloto)) {
        printf("Piloto não encontrado, cadastrando...\n");
        cadastroDeMembroTripulacao();  // Cadastra um novo membro da tripulação

        int codigo;
        printf("Digite o código do piloto recém-cadastrado para verificar: ");
        scanf("%d", &codigo);
        // Valida o código do piloto recém-cadastrado
        if (codigo != novovoo.codigoPiloto) {
            printf("Código incorreto. Cadastro não validado.\n");
            return;
        }
    }

    // Solicita o código do copiloto e realiza o mesmo procedimento
    printf("\nInforme o codigo do copiloto: ");
    scanf("%d", &novovoo.codigoCopiloto);
    if (!tripulanteExiste(novovoo.codigoCopiloto)) {
        printf("Copiloto não encontrado, cadastrando...\n");
        cadastroDeMembroTripulacao();  // Cadastra o copiloto

        int codigo;
        printf("Digite o código do copiloto recém-cadastrado para verificar: ");
        scanf("%d", &codigo);
        // Valida o código do copiloto recém-cadastrado
        if (codigo != novovoo.codigoCopiloto) {
            printf("Código incorreto. Cadastro não validado.\n");
            return;
        }
    }

    // Solicita o código do comissário e segue o mesmo procedimento
    printf("\nInforme o codigo do comissario: ");
    scanf("%d", &novovoo.codigoComissario);
    if (!tripulanteExiste(novovoo.codigoComissario)) {
        printf("Comissário não encontrado, cadastrando...\n");
        cadastroDeMembroTripulacao();  // Cadastra o comissário

        int codigo;
        printf("Digite o código do comissário recém-cadastrado para verificar: ");
        scanf("%d", &codigo);
        // Valida o código do comissário recém-cadastrado
        if (codigo != novovoo.codigoComissario) {
            printf("Código incorreto. Cadastro não validado.\n");
            return;
        }
    }

    // Solicita as demais informações do voo
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
    getchar();  // Consome o '\n' deixado pelo scanf
    printf("\nInforme a origem do voo: ");
    fgets(novovoo.origemVoo, sizeof(novovoo.origemVoo), stdin);
    novovoo.origemVoo[strcspn(novovoo.origemVoo, "\n")] = '\0';  // Remove o '\n'
    printf("\nInforme o destino do voo: ");
    fgets(novovoo.destinoVoo, sizeof(novovoo.destinoVoo), stdin);
    novovoo.destinoVoo[strcspn(novovoo.destinoVoo, "\n")] = '\0';  // Remove o '\n'
    printf("\nInforme o status do voo: ");
    fgets(novovoo.statusVoo, sizeof(novovoo.statusVoo), stdin);
    novovoo.statusVoo[strcspn(novovoo.statusVoo, "\n")] = '\0';  // Remove o '\n'
    printf("\nInforme a tarifa do voo: ");
    scanf("%f", &novovoo.tarifaVoo);

    // Escreve as informações no arquivo de voos
    fprintf(arquivo, "%d - %s ~ %s - %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %s - R$ %.2f\n",
            novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, novovoo.diaVoo, novovoo.mesVoo, novovoo.anoVoo, novovoo.horaVoo, novovoo.minutosVoo,
            novovoo.codigoAviao, novovoo.codigoPiloto, novovoo.codigoCopiloto, novovoo.codigoComissario, novovoo.statusVoo, novovoo.tarifaVoo);

    fclose(arquivo);  // Fecha o arquivo
    printf("Voo cadastrado com sucesso!\n");  // Exibe mensagem de sucesso
}

// Função para verificar se o tripulante existe
int tripulanteExiste(int codigo) {
    for (int i = 0; i < totalTripulantes; i++) {
        if (tripulantes[i].codigoIntegranteTripulacao == codigo) {
            return 1;  // Tripulante encontrado
        }
    }
    return 0;  // Tripulante não encontrado
}

// Função para listar todos os voos cadastrados
void listarVoos() {
    voo novovoo;  // Declara a estrutura para armazenar os dados do voo
    int x;  // Declara variável auxiliar para controle de loop

    FILE *arquivo;  // Declara o ponteiro para o arquivo de voos
    arquivo = fopen("voos.txt", "r");  // Abre o arquivo de voos para leitura

    // Verifica se houve erro ao abrir o arquivo
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    // Lê os dados do arquivo e exibe os voos cadastrados
    while (fscanf(arquivo, "%d - %29[^~]~ %29[^-]- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %9[^-]- R$ %f",
                  &novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, &novovoo.diaVoo, &novovoo.mesVoo, &novovoo.anoVoo, &novovoo.horaVoo, &novovoo.minutosVoo,
                  &novovoo.codigoAviao, &novovoo.codigoPiloto, &novovoo.codigoCopiloto, &novovoo.codigoComissario,
                  novovoo.statusVoo, &novovoo.tarifaVoo) != EOF) {
        // Exibe os dados do voo na tela
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

    // Abre o arquivo de voos em modo leitura e o arquivo temporário em modo escrita
    arquivo = fopen("voos.txt", "r"); //aberto como Read
    temp = fopen("temp.txt", "w"); //aberto como Write

    if(arquivo == NULL || temp == NULL){
        printf("Erro ao abrir o arquivo!");
        return 1; // Se algum dos arquivos não abrir, retorna erro
    }

    int id, encontrado=0;

    // Solicita o ID do voo que será alterado
    printf("\nQual o id do voo a ser alterado? ");
    scanf("%d", &id);
    getchar(); // Limpa o buffer do teclado

    // Escaneia o arquivo de voos para localizar o voo com o ID fornecido
    while(fscanf(arquivo, "%d - %29[^~]~ %29[^-]- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %9[^-]- R$ %f",
        &novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, &novovoo.diaVoo, &novovoo.mesVoo, &novovoo.anoVoo, &novovoo.horaVoo, &novovoo.minutosVoo,
        &novovoo.codigoAviao, &novovoo.codigoPiloto, &novovoo.codigoCopiloto, &novovoo.codigoComissario,
        novovoo.statusVoo, &novovoo.tarifaVoo) != EOF)
    {
        if(id == novovoo.codigoVoo){ // Se o voo foi encontrado, solicita os novos dados
            encontrado = 1;

            // Solicita ao usuário novos dados para atualizar o voo
            printf("\nInforme o codigo do voo: ");
            scanf("%d", &novovoo.codigoVoo);
            printf("\nInforme o codigo do avi o: ");
            scanf("%d", &novovoo.codigoAviao);
            // Repete o processo de entrada para todos os outros campos

            // Escreve as informações do voo alterado no arquivo temporário
            fprintf(temp, "%d - %s ~ %s - %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %s - R$ %.2f\n",
            novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, novovoo.diaVoo, novovoo.mesVoo, novovoo.anoVoo, novovoo.horaVoo, novovoo.minutosVoo,
            novovoo.codigoAviao, novovoo.codigoPiloto, novovoo.codigoCopiloto, novovoo.codigoComissario,
            novovoo.statusVoo, novovoo.tarifaVoo);
        }
        else{
            // Se o voo não for encontrado, simplesmente copia para o arquivo temporário
            fprintf(temp, "%d - %s~ %s- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %s- R$ %.2f\n",
            novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, novovoo.diaVoo, novovoo.mesVoo, novovoo.anoVoo, novovoo.horaVoo, novovoo.minutosVoo,
            novovoo.codigoAviao, novovoo.codigoPiloto, novovoo.codigoCopiloto, novovoo.codigoComissario,
            novovoo.statusVoo, novovoo.tarifaVoo);
        }
    }

    fclose(arquivo);
    fclose(temp);

    if(encontrado == 0){ // Se não encontrar o voo
        printf("\nCodigo de voo nao encontrado!\n\n");
        remove("temp.txt"); // Remove o arquivo temporário
    }
    else{
        // Se encontrado, substitui o arquivo de voos pelo arquivo temporário
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

    // Abre o arquivo de voos em modo leitura e o arquivo temporário em modo escrita
    arquivo = fopen("voos.txt", "r");
    temp = fopen("temp.txt", "w");

    if(arquivo == NULL || temp == NULL){
        printf("Erro ao abrir o arquivo!");
        return 1; // Se algum dos arquivos não abrir, retorna erro
    }

    int id, encontrado=0;

    // Solicita o ID do voo a ser excluído
    printf("\nDigite o codigo do voo que deve ser excluido: ");
    scanf("%d", &id);

    // Escaneia o arquivo de voos para procurar o voo a ser excluído
    while(fscanf(arquivo, "%d - %29[^~]~ %29[^-]- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %9[^-]- R$ %f",
    &novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, &novovoo.diaVoo, &novovoo.mesVoo, &novovoo.anoVoo, &novovoo.horaVoo, &novovoo.minutosVoo,
    &novovoo.codigoAviao, &novovoo.codigoPiloto, &novovoo.codigoCopiloto, &novovoo.codigoComissario,
    novovoo.statusVoo, &novovoo.tarifaVoo) != EOF)
    {
        if(id != novovoo.codigoVoo){ // Se o voo não for o que foi solicitado para exclusão
            // Escreve o voo no arquivo temporário
            fprintf(temp, "%d - %s~ %s- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %s- R$ %.2f\n",
            novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, novovoo.diaVoo, novovoo.mesVoo, novovoo.anoVoo, novovoo.horaVoo, novovoo.minutosVoo,
            novovoo.codigoAviao, novovoo.codigoPiloto, novovoo.codigoCopiloto, novovoo.codigoComissario,
            novovoo.statusVoo, novovoo.tarifaVoo);
        }
        else{
            encontrado++; // Incrementa se o voo for encontrado para exclusão
        }
    }

    fclose(arquivo);
    fclose(temp);

    if(encontrado == 1){ // Se o voo foi excluído
        remove("voos.txt");
        rename("temp.txt", "voos.txt");
        printf("\nVoo excluido!\n\n");
    }
    else{
        printf("\nCodigo de voo nao encontrado!\n\n");
        remove("temp.txt"); // Se não encontrado, remove o arquivo temporário
    }
}

void cadastroDeAssento () //FUNCIONAL
{
    assento novoAssento;

    FILE *arquivo;
    arquivo = fopen("assentos.txt", "a");

    // Abre o arquivo de assentos em modo append para adicionar novos assentos
    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo 'assentos.txt'!");
        return; // Se o arquivo não abrir, retorna erro
    }

    do{
        // Solicita o código do voo e verifica se ele existe
        printf("\nInsira o codigo do voo: ");
        scanf("%d", &novoAssento.codigoDoVoo);
    } while(codigoVooExiste(novoAssento.codigoDoVoo) == 0);

    // Solicita o número do assento
    printf("\nInforme o numero do assento: ");
    scanf("%d", &novoAssento.numeroDoAssento);

    // Define o status do assento como "livre" e o nome do passageiro como "n"
    strcpy(novoAssento.statusDoAssento, "livre");
    strcpy(novoAssento.nomePassageiro, "n");

    // Escreve os dados do assento no arquivo de assentos
    fprintf(arquivo, "%d - %s - %d %s.\n", novoAssento.codigoDoVoo, novoAssento.statusDoAssento, novoAssento.numeroDoAssento, novoAssento.nomePassageiro);

    fclose(arquivo);

    printf("\nAssento cadastrado e disponivel!\n");
}


// Função para listar os assentos de um voo
void listarAssentos() //FUNCIONAL
{
    assento novoAssento;
    int codigo, x=0;

    FILE *arquivo;
    arquivo = fopen("assentos.txt", "r"); // Abre o arquivo de assentos para leitura

    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo 'assentos.txt'!"); // Verifica se o arquivo foi aberto corretamente
        return;
    }

    do
    {
        printf("\nDigite o codigo do voo: ");
        scanf("%d", &codigo); // Solicita o código do voo
    }while(codigoVooExiste(codigo)==0); // Verifica se o voo existe

    // Lê o arquivo de assentos e imprime os assentos do voo solicitado
    while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].", &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro) != EOF)
    {
        if(codigo == novoAssento.codigoDoVoo){ // Se o código do voo for igual ao informado
            x++;
            // Verifica se o assento está livre ou ocupado e imprime as informações
            if(strcmp(novoAssento.statusDoAssento, "livre ") == 0){
                printf("\n%d - %s\n", novoAssento.numeroDoAssento, novoAssento.statusDoAssento);
            }
            else{
                printf("\n%d - %s- %s.\n", novoAssento.numeroDoAssento, novoAssento.statusDoAssento, novoAssento.nomePassageiro);
            }
        }
    }

    // Caso não encontre assentos para o voo, informa o usuário
    if(x==0){
        printf("\nNenhum assento cadastrado nesse voo.\n");
    }
}

// Função para excluir um assento
void excluirAssento() //FUNCIONAL
{
    assento novoAssento;
    int x=0, codigo, numeroAssento;

    FILE *arquivo;
    FILE *temp;
    arquivo = fopen("assentos.txt", "r"); // Abre o arquivo de assentos para leitura
    temp = fopen("temp.txt", "w"); // Cria um arquivo temporário para salvar as alterações

    if(arquivo == NULL || temp == NULL){
        printf("\nErro ao abrir arquivo!"); // Verifica se os arquivos foram abertos corretamente
        return;
    }

    do
    {
        printf("\nDigite o codigo do voo: ");
        scanf("%d", &codigo); // Solicita o código do voo
    }while(codigoVooExiste(codigo)==0); // Verifica se o voo existe

    // Lê o arquivo de assentos e verifica se existem assentos cadastrados para o voo
    while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].", &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro) != EOF)
    {
        if(codigo == novoAssento.codigoDoVoo){ // Se o código do voo for igual ao informado
            x++;
        }
    }

    rewind(arquivo); // Retorna ao início do arquivo para reprocessá-lo

    // Caso não encontre assentos para o voo, informa o usuário e encerra
    if(x==0){
        printf("\nNenhum assento cadastrado nesse voo.\n");
        fclose(arquivo);
        fclose(temp);
        return;
    }
    else{
        printf("\nDigite o numero do assento a ser excluido: ");
        scanf("%d", &numeroAssento); // Solicita o número do assento a ser excluído

        x = 0;

        // Lê novamente o arquivo e exclui o assento desejado
        while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].", &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro) != EOF)
        {
            if(numeroAssento == novoAssento.numeroDoAssento){ // Se o número do assento for encontrado
                x++;
            }
            else{
                // Se o assento não for o desejado, copia para o arquivo temporário
                fprintf(temp, "%d - %s- %d %s.\n", novoAssento.codigoDoVoo, novoAssento.statusDoAssento, novoAssento.numeroDoAssento, novoAssento.nomePassageiro);
            }
        }
    }

    fclose(arquivo);
    fclose(temp);

    // Caso o assento não tenha sido encontrado, informa o usuário
    if(x==0){
        printf("\nAssento nao cadastrado.\n");
        remove("temp.txt"); // Remove o arquivo temporário
    }
    else{
        // Caso o assento tenha sido excluído, atualiza o arquivo de assentos
        printf("\nAssento excluido!\n");
        remove("assentos.txt"); // Remove o arquivo original
        rename("temp.txt", "assentos.txt"); // Renomeia o arquivo temporário para o nome do arquivo original
    }
}

// Função para reservar um assento
void reservarAssento()
{
    assento novoAssento;
    int codigo, numeroAssento, x=0;

    FILE *arquivo;
    FILE *temp;
    arquivo = fopen("assentos.txt", "r"); // Abre o arquivo de assentos para leitura
    temp = fopen("temp.txt", "w"); // Cria um arquivo temporário para salvar as alterações

    if(arquivo == NULL || temp == NULL){
        printf("\nErro ao abrir arquivo!\n"); // Verifica se os arquivos foram abertos corretamente
        return;
    }

    do
    {
        printf("\nDigite o codigo do voo: ");
        scanf("%d", &codigo); // Solicita o código do voo
    }while(codigoVooExiste(codigo)==0); // Verifica se o voo existe

    do
    {
        printf("\nDigite o numero do assento: ");
        scanf("%d", &numeroAssento); // Solicita o número do assento
    }while(verificaAssentoLivre(codigo, numeroAssento)==0); // Verifica se o assento está livre
    getchar(); // Limpa o buffer de entrada

    // Lê o arquivo de assentos e realiza a reserva do assento
    while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].", &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro) != EOF)
    {
        if(codigo == novoAssento.codigoDoVoo && numeroAssento == novoAssento.numeroDoAssento){
            do
            {
                printf("\nDigite o nome do passageiro: ");
                fgets(novoAssento.nomePassageiro, sizeof(novoAssento.nomePassageiro), stdin); // Solicita o nome do passageiro
                novoAssento.nomePassageiro[strcspn(novoAssento.nomePassageiro, "\n")] = '\0'; // Remove a nova linha do nome
            }while(passageiroExiste(novoAssento.nomePassageiro) == 0); // Verifica se o passageiro já existe

            strcpy(novoAssento.statusDoAssento, "ocupado "); // Marca o assento como ocupado
        }
        // Escreve as informações no arquivo temporário
        fprintf(temp, "%d - %s- %d %s.\n", novoAssento.codigoDoVoo, novoAssento.statusDoAssento, novoAssento.numeroDoAssento, novoAssento.nomePassageiro);
    }

    fclose(arquivo);
    fclose(temp);

    // Substitui o arquivo original pelo arquivo temporário com as atualizações
    remove("assentos.txt");
    rename("temp.txt", "assentos.txt");

    printf("\nAssento reservado!\n");
}

// Função para liberar um assento
void baixaReservaAssento()
{
    assento novoAssento;
    int codigo, numeroAssento, x=0;

    FILE *arquivo;
    FILE *temp;
    arquivo = fopen("assentos.txt", "r"); // Abre o arquivo de assentos para leitura
    temp = fopen("temp.txt", "w"); // Cria um arquivo temporário para salvar as alterações

    if(arquivo == NULL || temp == NULL){
        printf("\nErro ao abrir arquivo!\n"); // Verifica se os arquivos foram abertos corretamente
        return;
    }

    do
    {
        printf("\nDigite o codigo do voo: ");
        scanf("%d", &codigo); // Solicita o código do voo
    }while(codigoVooExiste(codigo)==0); // Verifica se o voo existe

    do
    {
        printf("\nDigite o numero do assento: ");
        scanf("%d", &numeroAssento); // Solicita o número do assento
    }while(verificaAssentoLivre(codigo, numeroAssento)==1); // Verifica se o assento está livre

    // Lê o arquivo de assentos e realiza a liberação do assento
    while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].", &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro) != EOF)
    {
        if(codigo == novoAssento.codigoDoVoo && numeroAssento == novoAssento.numeroDoAssento){
            strcpy(novoAssento.nomePassageiro, "n"); // Limpa o nome do passageiro
            strcpy(novoAssento.statusDoAssento, "livre "); // Marca o assento como livre
        }
        // Escreve as informações no arquivo temporário
        fprintf(temp, "%d - %s- %d %s.\n", novoAssento.codigoDoVoo, novoAssento.statusDoAssento, novoAssento.numeroDoAssento, novoAssento.nomePassageiro);
    }

    fclose(arquivo);
    fclose(temp);

    // Substitui o arquivo original pelo arquivo temporário com as atualizações
    remove("assentos.txt");
    rename("temp.txt", "assentos.txt");

    printf("\nAssento livre!\n");
}


// Função para salvar os dados no arquivo
void salvarArquivo() {
    FILE *file = fopen(ARQUIVO, "w"); // Abre o arquivo para escrita
    if (!file) {
        perror("Erro ao abrir o arquivo para salvar"); // Verifica se o arquivo foi aberto corretamente
        return;
    }

    // Grava os dados de cada tripulante no arquivo
    for (int i = 0; i < totalTripulantes; i++) {
        fprintf(file, "%d;%s;%s;%s\n",
                tripulantes[i].codigoIntegranteTripulacao,
                tripulantes[i].nomeIntegranteTripulacao,
                tripulantes[i].telefoneIntegranteTripulacao,
                tripulantes[i].cargo);
    }

    fclose(file); // Fecha o arquivo
    printf("Dados salvos no arquivo.\n");
}

// Função para carregar os dados do arquivo
void carregarArquivo() {
    FILE *file = fopen(ARQUIVO, "r"); // Abre o arquivo para leitura
    if (!file) {
        printf("Nenhum dado encontrado para carregar.\n"); // Caso o arquivo não exista
        return;
    }

    totalTripulantes = 0;
    free(tripulantes); // Libera a memória alocada previamente
    tripulantes = NULL;

    Tripulacao temp;
    // Lê os dados do arquivo e os armazena na estrutura de tripulantes
    while (fscanf(file, "%d;%29[^;];%14[^;];%14[^\n]\n",
                  &temp.codigoIntegranteTripulacao,
                  temp.nomeIntegranteTripulacao,
                  temp.telefoneIntegranteTripulacao,
                  temp.cargo) == 4) {
        tripulantes = realloc(tripulantes, (totalTripulantes + 1) * sizeof(Tripulacao));
        tripulantes[totalTripulantes] = temp;
        totalTripulantes++;
    }

    fclose(file); // Fecha o arquivo
    printf("Dados carregados do arquivo.\n");
}

// Função para obter o próximo ID disponível para um membro da tripulação
int obterProximoId() {
    int proximoId = 1;
    for (int i = 0; i < totalTripulantes; i++) {
        if (tripulantes[i].codigoIntegranteTripulacao >= proximoId) {
            proximoId = tripulantes[i].codigoIntegranteTripulacao + 1; // Garante que o ID seja único e sequencial
        }
    }
    return proximoId;
}

// Função para cadastrar um novo membro da tripulação
void cadastroDeMembroTripulacao() {
    Tripulacao novoMembro;
    novoMembro.codigoIntegranteTripulacao = obterProximoId(); // Atribui o próximo ID disponível

    // Solicita os dados do novo membro da tripulação
    printf("Nome do integrante:   ");
    fgets(novoMembro.nomeIntegranteTripulacao, sizeof(novoMembro.nomeIntegranteTripulacao), stdin);
    novoMembro.nomeIntegranteTripulacao[strcspn(novoMembro.nomeIntegranteTripulacao, "\n")] = '\0';

    printf("Telefone do integrante:   ");
    fgets(novoMembro.telefoneIntegranteTripulacao, sizeof(novoMembro.telefoneIntegranteTripulacao), stdin);
    novoMembro.telefoneIntegranteTripulacao[strcspn(novoMembro.telefoneIntegranteTripulacao, "\n")] = '\0';

    printf("Cargo (piloto, copiloto, comissario):   ");
    fgets(novoMembro.cargo, sizeof(novoMembro.cargo), stdin);
    novoMembro.cargo[strcspn(novoMembro.cargo, "\n")] = '\0';

    // Adiciona o novo membro ao array de tripulantes
    tripulantes = realloc(tripulantes, (totalTripulantes + 1) * sizeof(Tripulacao));
    tripulantes[totalTripulantes] = novoMembro;
    totalTripulantes++;

    printf("Membro cadastrado com sucesso! Codigo: %d\n", novoMembro.codigoIntegranteTripulacao);

    salvarArquivo(); // Salva as alterações no arquivo
}

// Função para listar todos os membros da tripulação
void listarMembroTripulacao() {
    if (totalTripulantes == 0) {
        printf("Nenhum membro cadastrado.\n"); // Caso não haja membros cadastrados
        return;
    }

    // Exibe os dados de todos os membros
    printf("Lista de membros da tripulacao:\n");
    for (int i = 0; i < totalTripulantes; i++) {
        printf("Codigo: %d\n", tripulantes[i].codigoIntegranteTripulacao);
        printf("Nome: %s\n", tripulantes[i].nomeIntegranteTripulacao);
        printf("Telefone: %s\n", tripulantes[i].telefoneIntegranteTripulacao);
        printf("Cargo: %s\n\n", tripulantes[i].cargo);
    }
}

// Função para editar os dados de um membro da tripulação
void editarMembroTripulacao() {
    int codigo;
    printf("Digite o codigo do membro que deseja editar: ");
    scanf("%d", &codigo);
    getchar();

    // Procura o membro pelo código e permite editar seus dados
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
            salvarArquivo(); // Salva as alterações no arquivo
            return;
        }
    }

    printf("Codigo nao encontrado!\n"); // Caso o código não seja encontrado
}

// Função para excluir um membro da tripulação
void excluirMembroTripulacao() {
    int codigo;
    printf("Digite o codigo do membro que deseja excluir: ");
    scanf("%d", &codigo);
    getchar();

    // Procura o membro pelo código e o remove
    for (int i = 0; i < totalTripulantes; i++) {
        if (tripulantes[i].codigoIntegranteTripulacao == codigo) {
            // Realiza a exclusão deslocando os elementos do vetor
            for (int j = i; j < totalTripulantes - 1; j++) {
                tripulantes[j] = tripulantes[j + 1];
            }
            totalTripulantes--;
            tripulantes = realloc(tripulantes, totalTripulantes * sizeof(Tripulacao)); // Reajusta o tamanho do array
            printf("Membro excluido com sucesso!\n");
            salvarArquivo(); // Salva as alterações no arquivo
            return;
        }
    }

    printf("Codigo nao encontrado!\n"); // Caso o código não seja encontrado
}

// Função para listar os voos de um passageiro
void listarVoosPassageiro()
{
    // Declaração das variáveis necessárias
    assento novoAssento;
    voo novovoo;
    passageiro novoPassageiro;
    char nome[30];
    int esc, codigo;

    // Declaração dos ponteiros de arquivos
    FILE *arquivo;
    FILE *voos;
    FILE *passageiros;

    // Abre os arquivos necessários para leitura
    arquivo = fopen("assentos.txt", "r");
    voos = fopen("voos.txt", "r");
    passageiros = fopen("passageiros.txt", "r");

    // Verifica se o arquivo de assentos foi aberto corretamente
    if(arquivo == NULL){
        printf("\nErro ao abrir arquivo.");
        return;
    }

    // Solicita ao usuário a escolha do tipo de pesquisa
    do
    {
        printf("\nComo deseja pesquisar os voos? \n1 - ID \n2 - Nome");
        scanf("%d", &esc);
    }while(esc != 1 && esc != 2);  // Repete enquanto a opção não for 1 ou 2

    // Caso a pesquisa seja por nome do passageiro
    if(esc == 2){
        getchar();  // Limpa o buffer do teclado
        printf("\nDigite o nome do passageiro: ");
        fgets(nome, sizeof(nome), stdin);  // Lê o nome do passageiro
        nome[strcspn(nome, "\n")] = '\0';  // Remove o caractere de nova linha

        // Verifica todos os assentos para encontrar os relacionados ao passageiro
        while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].", &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro) != EOF)
        {
            // Verifica os voos correspondentes ao assento e passageiro
            while(fscanf(voos, "%d - %29[^~]~ %29[^-]- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %9[^-]- R$ %f",
            &novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, &novovoo.diaVoo, &novovoo.mesVoo, &novovoo.anoVoo, &novovoo.horaVoo, &novovoo.minutosVoo,
            &novovoo.codigoAviao, &novovoo.codigoPiloto, &novovoo.codigoCopiloto, &novovoo.codigoComissario,
            novovoo.statusVoo, &novovoo.tarifaVoo) != EOF)
            {
                // Se o nome do passageiro bater com o nome no arquivo de assentos
                if(strcmp(nome, novoAssento.nomePassageiro) == 0){
                    // Exibe o voo correspondente
                    if(novoAssento.codigoDoVoo == novovoo.codigoVoo){
                        printf("\nVoo: %d \n%s- %s\n Aviao: %d", novoAssento.codigoDoVoo, novovoo.origemVoo, novovoo.destinoVoo, novovoo.codigoAviao);
                    }
                }
            }

            // Retorna o ponteiro de leitura para o começo do arquivo de voos
            rewind(voos);
        }
        printf("\n------------------\n");
    }
    else{
        // Caso a pesquisa seja por código do passageiro
        printf("\nDigite o codigo do passageiro: ");
        scanf("%d", &codigo);

        // Verifica todos os assentos para encontrar o voo do passageiro
        while(fscanf(arquivo, "%d - %9[^-]- %d %29[^.].", &novoAssento.codigoDoVoo, novoAssento.statusDoAssento, &novoAssento.numeroDoAssento, novoAssento.nomePassageiro) != EOF)
        {
            // Verifica os voos no arquivo de voos
            while(fscanf(voos, "%d - %29[^~]~ %29[^-]- %d/%d/%d %d:%d - av %d; p %d; cop %d; com %d - %9[^-]- R$ %f",
            &novovoo.codigoVoo, novovoo.origemVoo, novovoo.destinoVoo, &novovoo.diaVoo, &novovoo.mesVoo, &novovoo.anoVoo, &novovoo.horaVoo, &novovoo.minutosVoo,
            &novovoo.codigoAviao, &novovoo.codigoPiloto, &novovoo.codigoCopiloto, &novovoo.codigoComissario,
            novovoo.statusVoo, &novovoo.tarifaVoo) != EOF)
            {
                // Verifica os passageiros no arquivo de passageiros
                while(fscanf(passageiros, "%d;%29[^;];%49[^;];%14[^;];%3[^;];%d", &novoPassageiro.codigoPassageiro,
                     novoPassageiro.nomePassageiro, novoPassageiro.enderecoPassageiro, novoPassageiro.telefone, novoPassageiro.fidelidade,
                     &novoPassageiro.pontosFidelidade) != EOF)
                {
                    // Se o código e nome do passageiro baterem, exibe o voo correspondente
                    if(codigo == novoPassageiro.codigoPassageiro){
                        if(strcmp(novoPassageiro.nomePassageiro, novoAssento.nomePassageiro) == 0){
                            if(novoAssento.codigoDoVoo == novovoo.codigoVoo){
                                printf("\nVoo: %d \n%s- %s\n Aviao: %d", novoAssento.codigoDoVoo, novovoo.origemVoo, novovoo.destinoVoo, novovoo.codigoAviao);
                            }
                        }
                    }
                }
                // Retorna o ponteiro de leitura para o começo do arquivo de passageiros
                rewind(passageiros);
            }

            // Retorna o ponteiro de leitura para o começo do arquivo de voos
            rewind(voos);
        }
        printf("\n------------------\n");
    }

    // Fecha os arquivos abertos
    fclose(arquivo);
    fclose(voos);
    fclose(passageiros);

}

// Funcao que busca pontos de fidelidade de um passageiro pelo codigo
void buscarPontosFidelidade(int codigoBuscado) {
    // Declaracao de variaveis
    FILE *arquivo; // Ponteiro para o arquivo
    passageiro p;  // Estrutura que armazena dados do passageiro
    char linha[300]; // Variavel para armazenar cada linha lida do arquivo
    int encontrado = 0; // Variavel que controla se o passageiro foi encontrado

    // Abre o arquivo "passageiros.txt" no modo de leitura
    arquivo = fopen("passageiros.txt", "r");

    // Verifica se houve erro ao abrir o arquivo
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return; // Encerra a funcao em caso de erro ao abrir o arquivo
    }

    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Lê os dados da linha e armazena na estrutura passageiro 'p'
        sscanf(linha, "%d;%[^;];%[^;];%[^;];%[^;];%d",
               &p.codigoPassageiro, // Lê o código do passageiro
               p.nomePassageiro,    // Lê o nome do passageiro
               p.enderecoPassageiro, // Lê o endereço do passageiro
               p.telefone,           // Lê o telefone do passageiro
               p.fidelidade,         // Lê o status de fidelidade
               &p.pontosFidelidade); // Lê os pontos de fidelidade

        // Verifica se o código do passageiro é igual ao código buscado
        if (p.codigoPassageiro == codigoBuscado) {
            // Se encontrado, exibe as informações do passageiro
            printf("Passageiro encontrado!\n");
            printf("Nome: %s\n", p.nomePassageiro);
            printf("Pontos de fidelidade: %d\n", p.pontosFidelidade);
            encontrado = 1; // Marca que o passageiro foi encontrado
            break; // Encerra o laço de repetição
        }
    }

    // Fecha o arquivo após a leitura
    fclose(arquivo);

    // Verifica se o passageiro foi encontrado
    if (!encontrado) {
        // Exibe mensagem caso o passageiro não tenha sido encontrado
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