#include <stdio.h>
#include <stdlib.h>

#define linha 7
#define coluna 5

// Protótipo da função
void exibirTabela(int tabela[linha][coluna]);
void exibirProximoNumero(int n1, int n2);

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
        system("clear");
        // Parte de exibição dos tabelas e do próximo numero
        fscanf(numeros, "%d ", &proximoNumero);

        exibirProximoNumero(numeroAtual, proximoNumero);

        // Chama a função para imprimir a tabela
        exibirTabela(tabela);

        //tratando entradas
        while (1)
        {
           scanf("%d", &entrada);
           if (entrada >= 0 && entrada <= 5)
           {
            break;
           }
           system("clear");
           exibirProximoNumero(numeroAtual, proximoNumero);
           exibirTabela(tabela);
           printf("ENTRADA INVÁLIDA! Escolha um numero entre 0 e 5\n");
        }
        
        if (entrada == 0)
        {
            break;
        }
        tabela[contadores[entrada - 1]][entrada - 1] = numeroAtual;
        contadores[entrada - 1]--;
        numeroAtual = proximoNumero;
        
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