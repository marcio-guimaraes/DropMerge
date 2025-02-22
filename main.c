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
void configuracoes();
void instrucoes();
void escolherDificuldade();

int main()
{
    int entrada;
    char nome[MAX_NOME];

#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    // comandos iniciais
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

        switch (entrada)
        {
        case 5:
            limparTerminal();
            printf("Feito por Marcin :)\n\n");
            return 0;

        case 1:
            limparTerminal();
            sleep(1);

            int pontos = jogo();
            printf("Pontuação final: %d\n", pontos);

            salvarPontuacao(nome, pontos);
            sleep(3);
            break;

        case 2:
            limparTerminal();
            configuracoes();
            break;

        case 3:
            limparTerminal();
            instrucoes();
            break;

        case 4:
            consultarRanking();
            break;

        default:
            break;
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
        "██████   █████  ███    ██ ██   ██ ██ ███    ██  ██████\n"
        "██   ██ ██   ██ ████   ██ ██  ██  ██ ████   ██ ██     \n"
        "██████  ███████ ██ ██  ██ █████   ██ ██ ██  ██ ██   ███\n"
        "██   ██ ██   ██ ██  ██ ██ ██  ██  ██ ██  ██ ██ ██    ██ \n"
        "██   ██ ██   ██ ██   ████ ██   ██ ██ ██   ████  ██████\n\n");

    printf(" ========================================\n");
    printf("| %-10s | %-10s | %-15s |\n", "Posição", "Pontos", "Nickname");
    printf(" ========================================\n");

    for (int i = 0; i < total; i++)
    {
        printf("| %-8d | %-10d | %-15s |\n", i + 1, jogadores[i].pontos, jogadores[i].nome);
    }

    printf(" ========================================\n");

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

void configuracoes()
{

    printf("##########CONFIGURAÇÕES##########\n\n");

    printf("1 - Zerar ranking\n"
           "2 - Modo de dificuldade\n"
           "3 - Voltar ao menu principal\n\n"
           "Digite a opção desejada: ");

    int num;
    while (1)
    {
        scanf("%d", &num);
        if (num >= 1 && num <= 3)
        {
            break;
        }
    }

    switch (num)
    {
    case 1:
        zerarRanking();
        break;

    case 2:
        escolherDificuldade();

    case 3:
        return;

    default:
        break;
    }

    return;
}

void instrucoes()
{
    printf("INSTRUÇÕES SOBRE O JOGO\n\n");

    printf("Objetivo:\nO objetivo do jogo é combinar blocos de mesmo valor para obter a maior pontuação possível antes que o tabuleiro fique cheio.\n\n"

           "Regras:\n"
           "O jogo acontece em um grid com um número de colunas que varia conforme o nível de dificuldade.\n"
           "O jogador deve digitar um número correspondente à coluna para escolher onde um novo bloco irá cair.\n"
           "Se dois blocos com o mesmo valor se encontrarem, eles se combinam em um único bloco com o valor dobrado.\n"
           "O jogo termina quando não houver mais espaço para blocos.\n\n"

           "Níveis de Dificuldade:\n"
           "- Fácil: 5 colunas, o primeiro martelo pode ser obtido com 128 pontos.\n"
           "- Médio: 4 colunas, o primeiro martelo pode ser obtido com 512 pontos.\n"
           "- Difícil: 3 colunas, o primeiro martelo pode ser obtido com 1024 pontos.\n"
           "O jogador pode alterar o nível de dificuldade a qualquer momento no menu de configurações.\n\n"

           "Uso do Martelo:\n"
           "Se o tabuleiro estiver cheio e o jogador tiver um martelo, ele pode usá-lo para destruir um bloco específico.\n"
           "Para isso, o jogador deve escolher:\n"
           "Linha (1 a 10)\n"
           "Coluna (de acordo com o nível de dificuldade)\n"
           "Após remover um bloco, o jogo continua normalmente.\n\n"
           "O número de pontos necessários para conseguir um martelo dobra a cada vez que o jogador obtém um.\n\n"

           "Configurações:\n"
           "No menu de configurações, o jogador pode:\n"
           "- Alterar o nível de dificuldade.\n"
           "- Zerar o ranking e redefinir as pontuações.\n\n"

           "Dicas:\n"
           "Escolha bem onde os blocos vão cair para evitar que o tabuleiro fique cheio rapidamente.\n"
           "Use o martelo com estratégia para remover blocos que atrapalham combinações.\n\n");

    printf("Tecle ENTER para retornar ao menu principal\n");
    getchar();

    return;
}

void escolherDificuldade()
{
    limparTerminal();
    printf("Por padrão a dificuldade do jogo vem em \"fácil\", mas você pode escolher entre fácil, médio e difícil\n"
           "Escolha uma das dificuldades abaixo:\n"
           "1 - Fácil\n"
           "2 - Médio\n"
           "3 - Difícil\n"
           "0 - Voltar ao menu de configurações\n\n");
    int dificuldade;
    scanf("%d", &dificuldade);

    switch (dificuldade)
    {
    case 1:
        linha = 10;
        coluna = 5;
        pontosNecessarios = 10000;
        break;

    case 2:
        linha = 10;
        coluna = 4;
        pontosNecessarios = 12000;
        break;

    case 3:
        linha = 10;
        coluna = 3;
        pontosNecessarios = 14000;
        break;

    default:
        break;
    }
    return;
}
