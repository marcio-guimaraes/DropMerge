#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define linha 7
#define coluna 5

// Protótipo da função
void exibirTabela(int tabela[linha][coluna]);
void exibirProximoNumero(int n1, int n2);
int tratarEntrada(int numeroAtual, int proximoNumero, int tabela[linha][coluna]);
void mesclarBlocos(int tabela[linha][coluna], int contadores[], int entrada, int numeroAtual);
void gravidade(int tabela[linha][coluna], int contadores[], int numeroAtual, int proximoNumero);
// void exibindocontadores(int contadores[]);
void reiniciarContadores(int tabela[linha][coluna], int contadores[]);

int main()
{
    int numeroAtual = 2, proximoNumero;
    // Abrindo arquivo com a sequencia de numeros que irão aparecer
    FILE *numeros;
    numeros = fopen("numeros.txt", "r");

    // Iniciando os contadores das linha
    int tabela[linha][coluna] = {0};
    int entrada;
    int contadores[5] = {6, 6, 6, 6, 6};

    while (1)
    {
        // Verifica se está no sistema Windows
#ifdef _WIN32
        system("cls");
// Caso esteja em um sistema Unix-like (Linux, macOS)
#else
        system("clear");
#endif

        // Parte de exibição dos tabelas e do próximo numero
        fscanf(numeros, "%d ", &proximoNumero);
        exibirProximoNumero(numeroAtual, proximoNumero);

        // Chama a função para imprimir a tabela
        exibirTabela(tabela);

        // tratando entradas
        entrada = tratarEntrada(numeroAtual, proximoNumero, tabela);
        if (entrada == 0)
        {
            printf("Feito por marcin :)\n\n");
            return 0;
        }

        tabela[contadores[entrada - 1]][entrada - 1] = numeroAtual;
        contadores[entrada - 1]--;
        mesclarBlocos(tabela, contadores, entrada, numeroAtual);

        gravidade(tabela, contadores, numeroAtual, proximoNumero);

        numeroAtual = proximoNumero;

        // exibindocontadores(contadores);
    }

    fclose(numeros);
    return 0;
}

void exibirTabela(int tabela[linha][coluna])
{
    printf(" ----------------------------------------------\n");
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            if (tabela[i][j] == 0)
            {
                printf(" |       "); // Espaço vazio para valores 0
            }
            else
            {
                // Calcula o número de espaços para centralizar o número
                int num = tabela[i][j];
                int espacoAntes, espacoDepois;
                if (num < 10)
                { // 1 dígito
                    espacoAntes = 3;
                    espacoDepois = 3;
                }
                else if (num < 100)
                { // 2 dígitos
                    espacoAntes = 3;
                    espacoDepois = 2;
                }
                else if (num < 1000)
                { // 3 dígitos
                    espacoAntes = 2;
                    espacoDepois = 2;
                }
                else
                { // 4 dígitos
                    espacoAntes = 2;
                    espacoDepois = 1;
                }
                printf(" |%*s%d%*s", espacoAntes, "", num, espacoDepois, ""); // Centraliza
            }
        }
        printf(" |\n");
        printf(" ----------------------------------------------\n");
    }

    // Menu para informar as colunas da tabela
    printf("\n");
    printf(" ----------------------------------------------\n"
           " |    1   |    2   |    3   |    4   |    5   |\n"
           " ----------------------------------------------\n");
}

void exibirProximoNumero(int n1, int n2)
{

    int aux;
    int espacoAntes1, espacoDepois1;
    int espacoAntes2, espacoDepois2;

    printf("Digite 0 para sair\n");

    if (n1 < 10)
    { // 1 dígito
        espacoAntes1 = 3;
        espacoDepois1 = 4;
        aux = 4;
    }
    else if (n1 < 100)
    { // 2 dígitos
        espacoAntes1 = 3;
        espacoDepois1 = 3;
        aux = 4;
    }
    else if (n1 < 1000)
    { // 3 dígitos
        espacoAntes1 = 2;
        espacoDepois1 = 3;
        aux = 4;
    }
    else
    { // 4 dígitos
        espacoAntes1 = 2;
        espacoDepois1 = 1;
        aux = 4;
    }

    if (n2 < 10)
    { // 1 dígito
        espacoAntes2 = 3;
        espacoDepois2 = 4;
    }
    else if (n2 < 100)
    { // 2 dígitos
        espacoAntes2 = 3;
        espacoDepois2 = 3;
    }
    else if (n2 < 1000)
    { // 3 dígitos
        espacoAntes2 = 2;
        espacoDepois2 = 3;
    }
    else
    { // 4 dígitos
        espacoAntes2 = 2;
        espacoDepois2 = 1;
    }

    printf("                                      ---------     --------\n");
    printf("                                      |%*s%d%*s", espacoAntes1, "", n1, espacoDepois1, " |");
    printf(" %*s|%*s%d%*s", aux, "", espacoAntes2, "", n2, espacoDepois2, " |\n");
    printf("                                      ---------     --------\n\n");
}

int tratarEntrada(int numeroAtual, int proximoNumero, int tabela[linha][coluna])
{
    int entrada;
    while (1)
    {
        scanf("%d", &entrada);
        if (entrada >= 0 && entrada <= 5)
        {
            break;
        }
        // Verifica se está no sistema Windows
#ifdef _WIN32
        system("cls");
// Caso esteja em um sistema Unix-like (Linux, macOS)
#else
        system("clear");
#endif
        exibirProximoNumero(numeroAtual, proximoNumero);
        exibirTabela(tabela);
        printf("ENTRADA INVÁLIDA! Escolha um numero entre 0 e 5\n");
    }

    return entrada;
}

void mesclarBlocos(int tabela[linha][coluna], int contadores[], int entrada, int numeroAtual)
{

    // tabela[contadores[entrada - 1]][entrada - 1] = numeroAtual;
    int multiplicacao = 0;
    int linhaAtual = contadores[entrada - 1] + 1;
    int colunaAtual = entrada - 1;
    int aux = numeroAtual;

    if (linhaAtual != 6 && tabela[linhaAtual + 1][colunaAtual] == numeroAtual)
    {
        tabela[linhaAtual + 1][colunaAtual] = 0;
        multiplicacao++;
    }
    if (colunaAtual != 0 && tabela[linhaAtual][colunaAtual - 1] == numeroAtual)
    {
        tabela[linhaAtual][colunaAtual - 1] = 0;
        multiplicacao++;
    }
    if (colunaAtual != 4 && tabela[linhaAtual][colunaAtual + 1] == numeroAtual)
    {
        tabela[linhaAtual][colunaAtual + 1] = 0;
        multiplicacao++;
    }

    for (int i = 0; i < multiplicacao; i++)
    {
        numeroAtual *= 2;
    }

    if (numeroAtual != aux)
    {
        tabela[contadores[entrada - 1] + 1][entrada - 1] = numeroAtual;
    }

    // Verificando se tem algum bloco igual ao novo bloco atual, se tiver mescla novamente
    if ((linhaAtual != 6 && tabela[linhaAtual + 1][colunaAtual] == numeroAtual) || (colunaAtual != 0 && tabela[linhaAtual][colunaAtual - 1] == numeroAtual) || (colunaAtual != 4 && tabela[linhaAtual][colunaAtual + 1] == numeroAtual))
    {
        mesclarBlocos(tabela, contadores, entrada, numeroAtual);
    }
}

void gravidade(int tabela[linha][coluna], int contadores[], int numeroAtual, int proximoNumero)
{

    // Fazendo os blocos descerem
    for (int i = 0; i < linha - 1; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            // verifica se o bloco atual é diferente de 0 e o bloco de baixo é igual a 0
            if (tabela[i][j] != 0 && tabela[i + 1][j] == 0)
            {
                tabela[i + 1][j] = tabela[i][j];
                tabela[i][j] = 0;
                reiniciarContadores(tabela, contadores);
                mesclarBlocos(tabela, contadores, j + 1, tabela[i + 1][j]);
            }
        }
    }

    /*for (int i = linha-1; i > 0; i--)
    {
        for (int j = coluna-1; j >= 0; j--)
        {
            if (tabela[i][j] == tabela[i-1][j] && tabela[i][j] != 0)
            {
                tabela[i][j] *= 2;
                tabela[i-1][j] = 0;

            }
        }
    }*/

    // Reinicio dos contadores para a coluna com 0

    exibirProximoNumero(numeroAtual, proximoNumero);
    exibirTabela(tabela);
}

void exibindocontadores(int contadores[])
{
    for (int i = 0; i < coluna; i++)
    {
        printf("Contador %d: %d\n", i, contadores[i]);
        sleep(0.5);
    }
}

void reiniciarContadores(int tabela[linha][coluna], int contadores[])
{
    for (int i = 0; i < coluna; i++)
    {
        for (int j = linha - 1; j >= 0; j--)
        {
            if (tabela[j][i] == 0)
            {
                contadores[i] = j;
                break;
            }
        }
    }
}