#include <stdio.h>
#include "jogo.c"

void printDropMerge();

int main()
{
    int entrada;
    while (1)
    {

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        printf("##############################\n###########  MENU  ###########\n##############################\n\n");

        printf("1 - Jogar\n");
        printf("2 - Ranking\n");
        printf("3 - Sobre\n");
        printf("0 - Sair\n\n");

        scanf("%d", &entrada);

        if (entrada == 0)
        {
            printf("Feito por marcin :)\n\n");
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

            jogo();
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
    printf(" |  \\/  |   | ____|   |  _ \\     / ___|   | ____|\n");
    printf(" | |\\/| |   |  _|     | |_) |   | |  _    |  _|  \n");
    printf(" | |  | |   | |___    |  _ <    | |_| |   | |___ \n");
    printf(" |_|  |_|   |_____|   |_| \\_\\    \\____|   |_____|\n");
#ifdef _WIN32
    resetConsoleColor();
#endif

    return;
}