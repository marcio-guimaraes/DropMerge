#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "jogo.c"

#ifdef _WIN32
    #include <windows.h>
#endif

void printDropMerge();

int main()
{
    int entrada;



#ifdef _WIN32
    // Configura o Windows para UTF-8 (mas o CMD ainda pode ter problemas)
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    while (1)
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        printf("##############################\n");
        printf("###########  MENU  ###########\n");
        printf("##############################\n\n");

        printf("1 - Jogar\n");
        printf("2 - Ranking\n");
        printf("3 - Sobre\n");
        printf("0 - Sair\n\n");

        printf("Escolha uma opção: ");  // Agora a exibição está correta
        scanf("%d", &entrada);

        if (entrada == 0)
        {
            printf("Feito por Marcin :)\n\n");
            return 0;
        }
        if (entrada == 1)
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            printDropMerge();
            sleep(1);

            int pontos = jogo();
            printf("Pontuação final: %d\n", pontos);
            sleep(3);
        }
    }

    return 0;
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
