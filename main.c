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
#define ARQUIVO_RANKING "ranking.bin"

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

    //comandos iniciais
    limparTerminal();
    printDropMerge();
    printf("\nNICKNAME: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = 0; // Remover quebra de linha

    while (1)
    {
        limparTerminal();

        printf(
            "███╗   ███╗███████╗███╗  ██╗██╗   ██╗\n"
            "████╗ ████║██╔════╝████╗ ██║██║   ██║\n"
            "██╔████╔██║█████╗  ██╔██╗██║██║   ██║\n"
            "██║╚██╔╝██║██╔══╝  ██║╚████║██║   ██║\n"
            "██║ ╚═╝ ██║███████╗██║ ╚███║╚██████╔╝\n"
            "╚═╝     ╚═╝╚══════╝╚═╝  ╚══╝ ╚═════╝\n\n");

        printf("1 - JOGAR\n"
               "2 - CONFIGURAÇÕES\n"
               "3 - INSTRUÇÕES\n"
               "4 - RANKING\n"
               "5 - SAIR\n\n");

        printf("Digite a opção desejada: ");
        scanf("%d", &entrada);
        getchar(); // Consumir ENTER deixado pelo scanf

        if (entrada == 5)
        {
            limparTerminal();
            printf("Feito por Marcin :)\n\n");
            return 0;
        }
        else if (entrada == 1)
        {

            limparTerminal();
            sleep(1);

            int pontos = jogo();
            printf("Pontuação final: %d\n", pontos);

            salvarPontuacao(nome, pontos);
            sleep(3);
        }
        else if (entrada == 4)
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

// Função para salvar a pontuação no arquivo binário
void salvarPontuacao(const char *nome, int pontos)
{
    FILE *arquivo = fopen(ARQUIVO_RANKING, "ab"); // "ab" = append binário

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de ranking!\n");
        return;
    }

    Jogador jogador;
    strncpy(jogador.nome, nome, MAX_NOME);
    jogador.nome[MAX_NOME - 1] = '\0'; // Garantir que o nome não ultrapasse o limite
    jogador.pontos = pontos;

    fwrite(&jogador, sizeof(Jogador), 1, arquivo);
    fclose(arquivo);
}

// Função para exibir o ranking ordenado
void consultarRanking()
{
    FILE *arquivo = fopen(ARQUIVO_RANKING, "rb");

    if (arquivo == NULL)
    {
        printf("Ranking vazio\n");
        sleep(1);
        return;
    }

    Jogador jogadores[MAX_JOGADORES];
    int total = 0;

    while (fread(&jogadores[total], sizeof(Jogador), 1, arquivo) == 1 && total < MAX_JOGADORES)
    {
        total++;
    }

    fclose(arquivo);

    if (total == 0)
    {
        printf("Ranking vazio!\n");
        sleep(1);
        return;
    }

    ordenarRanking(jogadores, total);

    limparTerminal();

    printf(
        " _____             _    _             \n"
        "|  __ \\           | |  (_)            \n"
        "| |__) |__ _ _ __ | | ___ _ __   __ _ \n"
        "|  _  // _` | '_ \\| |/ / | '_ \\ / _` |\n"
        "| | \\ \\ (_| | | | |   <| | | | | (_| |\n"
        "|_|  \\_\\__,_|_| |_|_|\\_\\_|_| |_|\\__, |\n"
        "                                 __/ |\n"
        "                                |___/ \n\n"
           "  || xp  ||  nome\n\n");

    for (int i = 0; i < total; i++)
    {
        printf("%d.   %d   -   %s\n", i + 1, jogadores[i].pontos, jogadores[i].nome);
    }

    printf("\nPressione ENTER para voltar ao menu\n");
    getchar();
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

// Função para zerar o ranking
void zerarRanking()
{
    FILE *arquivo = fopen(ARQUIVO_RANKING, "wb"); // "wb" = escrever binário (apaga tudo)
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

// Exibir o nome do jogo
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
}
