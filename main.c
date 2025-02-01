#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "jogo.c"

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_NOME 50
#define MAX_JOGADORES 100

typedef struct
{
    char nome[MAX_NOME];
    int pontos;
} Jogador;

void printDropMerge();
void salvarPontuacao(const char *nome, int pontos);
void consultarRanking();
void ordenarRanking(Jogador jogadores[], int total);
void zerarRanking();

int main()
{
    int entrada;
    char nome[MAX_NOME];

#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    while (1)
    {
        limparTerminal();

        printf(

            "███╗░░░███╗███████╗███╗░░██╗██╗░░░██╗\n"
            "████╗░████║██╔════╝████╗░██║██║░░░██║\n"
            "██╔████╔██║█████╗░░██╔██╗██║██║░░░██║\n"
            "██║╚██╔╝██║██╔══╝░░██║╚████║██║░░░██║\n"
            "██║░╚═╝░██║███████╗██║░╚███║╚██████╔╝\n"
            "╚═╝░░░░░╚═╝╚══════╝╚═╝░░╚══╝░╚═════╝░\n");

        printf("1 - Jogar\n");
        printf("2 - Ranking\n");
        printf("3 - Zerar o ranking\n");
        printf("0 - Sair\n\n");

        printf("Escolha uma opção: ");
        scanf("%d", &entrada);
        getchar(); // Consumir ENTER deixado pelo scanf

        if (entrada == 0)
        {
            printf("Feito por Marcin :)\n\n");
            return 0;
        }
        else if (entrada == 1)
        {
            printf("Digite seu nome: ");
            fgets(nome, MAX_NOME, stdin);
            nome[strcspn(nome, "\n")] = 0; // Remover quebra de linha

            limparTerminal();

            printDropMerge();
            sleep(1);

            int pontos = jogo();
            printf("Pontuação final: %d\n", pontos);

            salvarPontuacao(nome, pontos);
            sleep(3);
        }
        else if (entrada == 2)
        {
            consultarRanking();
        }
        else if (entrada == 3)
        {
            zerarRanking();
        }
    }

    return 0;
}

// Função para salvar o nome e a pontuação no ranking
void salvarPontuacao(const char *nome, int pontos)
{
    FILE *arquivo = fopen("ranking.txt", "a");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de ranking!\n");
        return;
    }

    fprintf(arquivo, "%s - %d\n", nome, pontos);
    fclose(arquivo);
}

void printDropMerge()
{
#ifdef _WIN32
    setConsoleColor(0, 3);
#endif

    printf("       ____     ____       ___      ____         \n");
    printf("      |  _ \\   |  _ \\     / _ \\    |  _ \\        \n");
    printf("      | | | |  | |_) |   | | | |   | |_) |       \n");
    printf("      | |_| |  |  _ <    | | | |   |  __/        \n");
    printf("      |____/   |_| \\_\\    \\___/    |_|           \n");

#ifdef _WIN32
    resetConsoleColor();
    setConsoleColor(0, 2);
#endif

    printf("  __  __     _____     ____       ____     _____ \n");
    printf(" |  \\/  |   | _____   |  _ \\     / ___|   | ____|\n");
    printf(" | |\\/| |   |  _|     | |_) |   | |  _    |  _|  \n");
    printf(" | |  | |   | |___    |  _ <    | |_| |   | |___ \n");
    printf(" |_|  |_|   |_____|   |_| \\_\\    \\____|   |_____|\n");

#ifdef _WIN32
    resetConsoleColor();
#endif

    return;
}

// Função para ordenar o ranking em ordem decrescente
void ordenarRanking(Jogador jogadores[], int total)
{
    for (int i = 0; i < total - 1; i++)
    {
        for (int j = 0; j < total - i - 1; j++)
        {
            if (jogadores[j].pontos < jogadores[j + 1].pontos)
            {
                Jogador temp = jogadores[j];
                jogadores[j] = jogadores[j + 1];
                jogadores[j + 1] = temp;
            }
        }
    }
}

// Função para exibir o ranking ordenado
void consultarRanking()
{
    FILE *arquivo = fopen("ranking.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de ranking!\n");
        return;
    }

    Jogador jogadores[MAX_JOGADORES];
    int total = 0;

    while (fgets(jogadores[total].nome, MAX_NOME, arquivo) != NULL && total < MAX_JOGADORES)
    {
        char *sep = strrchr(jogadores[total].nome, '-');
        if (sep != NULL)
        {
            *sep = '\0'; // Substituir '-' por '\0' para separar nome e pontos
            sscanf(sep + 1, "%d", &jogadores[total].pontos);
            total++;
        }
    }

    fclose(arquivo);

    if (total == 0)
    {
        printf("Ranking vazio!\n");
        return;
    }

    ordenarRanking(jogadores, total);

    limparTerminal();

    printf("##############################\n");
    printf("########### RANKING ##########\n");
    printf("##############################\n\n");

    for (int i = 0; i < total; i++)
    {
        printf("%d. %s - %d\n", i + 1, jogadores[i].nome, jogadores[i].pontos);
    }

    printf("\nPressione ENTER para voltar ao menu\n");
    getchar();
}

// Função para zerar o ranking
void zerarRanking()
{
    FILE *arquivo = fopen("ranking.txt", "w");
    if (arquivo != NULL)
    {
        fclose(arquivo);
        printf("Ranking zerado!\n");
    }
    else
    {
        printf("Erro ao zerar o ranking!\n");
    }
    sleep(2);
}
