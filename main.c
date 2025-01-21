#include <stdio.h>
#define linha 7
#define coluna 5

// Protótipo da função
void printTabela(int tabela[linha][coluna]);

int main()
{
    int tabela[linha][coluna] = {
        {2, 4, 0, 0, 0},
        {16, 32, 128, 0, 0},
        {0, 256, 512, 0, 0},
        {1024, 0, 0, 2048, 0},
        {0, 0, 64, 8, 0},
        {0, 2, 4, 16, 0},
        {0, 0, 0, 0, 0}
    }; // Inicializando a tabela com valores aleatórios pra testar

    // Chama a função para imprimir a tabela
    printTabela(tabela);

    // Menu para informar as colunas da tabela
    printf("\n");
    printf(" ----------------------------------------------\n"
           " |    1   |    2   |    3   |    4   |    5   |\n"
           " ----------------------------------------------\n");

    return 0;
}

void printTabela(int tabela[linha][coluna])
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
                if (num < 10) { // 1 dígito
                    espacoAntes = 3;
                    espacoDepois = 3;
                } else if (num < 100) { // 2 dígitos
                    espacoAntes = 2;
                    espacoDepois = 3;
                } else if (num < 1000) { // 3 dígitos
                    espacoAntes = 2;
                    espacoDepois = 2;
                } else { // 4 dígitos
                    espacoAntes = 1;
                    espacoDepois = 2;
                }
                printf(" |%*s%d%*s", espacoAntes, "", num, espacoDepois, ""); // Centraliza
            }
        }
        printf(" |\n");
        printf(" ----------------------------------------------\n");
    }
}
