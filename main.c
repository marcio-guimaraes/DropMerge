#include <stdio.h>
#define linha 7
#define coluna 5

// Protótipo da função
void exibirTabela(int tabela[linha][coluna]);
void exibirProximoNumero();

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

    exibirProximoNumero();
    printf("\n");

    // Chama a função para imprimir a tabela
    exibirTabela(tabela);

    // Menu para informar as colunas da tabela
    printf("\n");
    printf(" ----------------------------------------------\n"
           " |    1   |    2   |    3   |    4   |    5   |\n"
           " ----------------------------------------------\n");

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
                if (num < 10) { // 1 dígito
                    espacoAntes = 3;
                    espacoDepois = 3;
                } else if (num < 100) { // 2 dígitos
                    espacoAntes = 3;
                    espacoDepois = 2;
                } else if (num < 1000) { // 3 dígitos
                    espacoAntes = 2;
                    espacoDepois = 2;
                } else { // 4 dígitos
                    espacoAntes = 2;
                    espacoDepois = 1;
                }
                printf(" |%*s%d%*s", espacoAntes, "", num, espacoDepois, ""); // Centraliza
            }
        }
        printf(" |\n");
        printf(" ----------------------------------------------\n");
    }
}

void exibirProximoNumero(){

    int n1 = 1, n2 = 1, aux;
    int espacoAntes1, espacoDepois1;
    int espacoAntes2, espacoDepois2;

                if (n1 < 10) { // 1 dígito
                    espacoAntes1 = 3;
                    espacoDepois1 = 4;
                    aux = 4;
                } else if (n1 < 100) { // 2 dígitos
                    espacoAntes1 = 3;
                    espacoDepois1 = 3;
                    aux = 4;
                } else if (n1 < 1000) { // 3 dígitos
                    espacoAntes1 = 2;
                    espacoDepois1 = 3;
                    aux = 4;
                } else { // 4 dígitos
                    espacoAntes1 = 2;
                    espacoDepois1 = 1;
                    aux = 4;
                }
                

                if (n2 < 10) { // 1 dígito
                    espacoAntes2 = 3;
                    espacoDepois2 = 4;
                } else if (n2 < 100) { // 2 dígitos
                    espacoAntes2 = 3;
                    espacoDepois2 = 3;
                } else if (n2 < 1000) { // 3 dígitos
                    espacoAntes2 = 2;
                    espacoDepois2 = 3;
                } else { // 4 dígitos
                    espacoAntes2 = 2;
                    espacoDepois2 = 1;
                }

                printf(" ---------     --------\n");
                      printf(" |%*s%d%*s", espacoAntes1, "", n1, espacoDepois1, " |");
                      printf(" %*s|%*s%d%*s",aux,"", espacoAntes2, "", n2, espacoDepois2, " |\n");
                      printf(" ---------     --------\n");
                      
                    
                
}