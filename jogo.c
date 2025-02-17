#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#endif

#define linha 10
#define coluna 5
#define pontosNecessarios 10

// Protótipo da função
void exibirTabela(int tabela[linha][coluna]);
void exibirProximoNumero(int n1, int n2);
int tratarEntrada(int numeroAtual, int proximoNumero, int tabela[linha][coluna]);
void mesclarBlocos(int tabela[linha][coluna], int contadores[], int entrada, int numeroAtual, int proximoNumero);
void gravidade(int tabela[linha][coluna], int contadores[], int numeroAtual, int proximoNumero);
void reiniciarContadores(int tabela[linha][coluna], int contadores[]);
void limparTerminal();
#ifdef _WIN32
void setConsoleColor(int textColor, int bgColor);
void resetConsoleColor();
void escolherCor(int num);
int verificarGrid(int tabela[linha][coluna]);
void exibirPerdeu();
void exibirGanhou();
#endif

int pontos, martelos, acumulados;

int jogo()
{
    pontos = 0, martelos = 1, acumulados = 0;
    int numeroAtual, proximoNumero;
    // Abrindo arquivo com a sequencia de numeros que irão aparecer
    FILE *numeros;
    numeros = fopen("numeros.txt", "r");
    fscanf(numeros, "%d ", &proximoNumero);
    numeroAtual = proximoNumero;

    // Iniciando os contadores das linha
    int tabela[linha][coluna] = {0};
    int entrada;
    int contadores[5] = {linha - 1, linha - 1, linha - 1, linha - 1, linha - 1};

    while (1)
    {
        if (acumulados >= pontosNecessarios)
        {
            martelos++;
            acumulados -= pontosNecessarios;
        }

        int gridCheio = verificarGrid(tabela);
        limparTerminal();

        // Parte de exibição dos tabelas e do próximo numero
        if (fscanf(numeros, "%d ", &proximoNumero) == EOF)
        {
            exibirGanhou();
            break;
        }

        exibirProximoNumero(numeroAtual, proximoNumero);

        // Chama a função para imprimir a tabela
        exibirTabela(tabela);

        // tratando entradas
        entrada = tratarEntrada(numeroAtual, proximoNumero, tabela);
        if (entrada == 0)
        {
            break;
        }

        if (contadores[entrada - 1] == -1 && !gridCheio)
        {
            while (contadores[entrada - 1] == -1)
            {
                limparTerminal();
                exibirProximoNumero(numeroAtual, proximoNumero);
                exibirTabela(tabela);
                entrada = tratarEntrada(numeroAtual, proximoNumero, tabela);
            }
            if (entrada == 0)
            {
                break;
            }
        }

        tabela[contadores[entrada - 1]][entrada - 1] = numeroAtual;
        contadores[entrada - 1]--;
        mesclarBlocos(tabela, contadores, entrada, numeroAtual, proximoNumero);

        gravidade(tabela, contadores, numeroAtual, proximoNumero);

        // Condições pra perder
        gridCheio = verificarGrid(tabela);
        if (gridCheio)
        {
            int temIgual = 0;
            numeroAtual = proximoNumero;
            fscanf(numeros, "%d ", &proximoNumero);
            for (int i = 0; i < coluna; i++)
            {
                if (numeroAtual == tabela[0][i])
                {
                    temIgual = 1;
                }
            }
            if (temIgual == 0)
            {
                if (martelos == 0)
                {
                    exibirPerdeu();
                    break;
                }
                else
                {
                    int aux1, aux2;
                    while (1)
                    {
                        limparTerminal();
                        exibirProximoNumero(numeroAtual, proximoNumero);
                        exibirTabela(tabela);
                        printf("Digite a linha e a coluna que deseja usar o martelo. Ex: 1 2\n"
                                "As linhas se contam de cima para baixo\n");
                        scanf("%d %d", &aux1, &aux2);
                        if ((aux1 <= 10 && aux1 >= 1) && (aux2 <= 5 && aux2 >= 1))
                        {
                            break;
                        }
                    }

                    tabela[aux1 - 1][aux2 - 1] = 0;
                    martelos--;
                }
            }
            else
            {
                do
                {
                    limparTerminal();
                    exibirProximoNumero(numeroAtual, proximoNumero);
                    exibirTabela(tabela);
                    entrada = tratarEntrada(numeroAtual, proximoNumero, tabela);
                    printf("Numero atual = %d e proximo = %d\n", numeroAtual, proximoNumero);
                    sleep(2);
                } while (entrada != 0 && tabela[0][entrada - 1] != numeroAtual);                

                if (entrada == 0)
                {
                    break;
                }

                tabela[0][entrada - 1] *= 2;
                limparTerminal();
                exibirProximoNumero(numeroAtual, proximoNumero);
                exibirTabela(tabela);
            }
        }

        mesclarBlocos(tabela, contadores, entrada, numeroAtual, proximoNumero);
        gravidade(tabela, contadores, numeroAtual, proximoNumero);

        numeroAtual = proximoNumero;
    }

    fclose(numeros);
    return pontos;
}

void exibirTabela(int tabela[linha][coluna])
{
    printf(" -----------------------------------------\n");
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            if (j == 0)
            {
                printf(" ");
            }

            if (tabela[i][j] == 0)
            {
                printf("|");
                printf("       "); // Espaço vazio para valores 0
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
                printf("|");
#ifdef _WIN32
                escolherCor(num);
#endif
                printf("%*s%d%*s", espacoAntes, "", num, espacoDepois, ""); // Centraliza
            }
#ifdef _WIN32
            resetConsoleColor();
#endif
        }

        if (i == 1)
        {
            printf("| martelos: %d\n", martelos);
        }
        else if (i == 2)
        {
            printf("| pontuação atual: %d\n", pontos);
        }
        else
        {
            printf("|\n");
        }

        printf(" -----------------------------------------\n");
    }

    // Menu para informar as colunas da tabela
    printf("\n");
    printf(" -----------------------------------------\n"
           " |   1   |   2   |   3   |   4   |   5   |\n"
           " -----------------------------------------\n");
}

void exibirProximoNumero(int n1, int n2)
{

    int aux;
    int espacoAntes1, espacoDepois1;
    int espacoAntes2, espacoDepois2;

    printf("Digite 0 para voltar ao menu\n");

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

        limparTerminal();

        exibirProximoNumero(numeroAtual, proximoNumero);
        exibirTabela(tabela);
        printf("ENTRADA INVÁLIDA! Escolha um numero entre 0 e 5\n");
        getchar();
    }

    return entrada;
}

void mesclarBlocos(int tabela[linha][coluna], int contadores[], int entrada, int numeroAtual, int proximoNumero)
{
    int multiplicacao = 0;
    int linhaAtual = contadores[entrada - 1] + 1;
    int colunaAtual = entrada - 1;
    int aux = numeroAtual;

    if (linhaAtual != linha - 1 && tabela[linhaAtual + 1][colunaAtual] == numeroAtual)
    {
        tabela[linhaAtual + 1][colunaAtual] = 0;
        multiplicacao++;
    }
    if (colunaAtual != 0 && tabela[linhaAtual][colunaAtual - 1] == numeroAtual)
    {
        tabela[linhaAtual][colunaAtual - 1] = 0;
        multiplicacao++;
    }
    if (colunaAtual != coluna - 1 && tabela[linhaAtual][colunaAtual + 1] == numeroAtual)
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
        pontos += numeroAtual;
        acumulados += numeroAtual;
    }

    // Verificando se tem algum bloco igual ao novo bloco atual, se tiver mescla novamente
    if ((linhaAtual != linha - 1 && tabela[linhaAtual + 1][colunaAtual] == numeroAtual) || (colunaAtual != 0 && tabela[linhaAtual][colunaAtual - 1] == numeroAtual) || (colunaAtual != coluna - 1 && tabela[linhaAtual][colunaAtual + 1] == numeroAtual))
    {
        mesclarBlocos(tabela, contadores, entrada, numeroAtual, proximoNumero);
    }

    gravidade(tabela, contadores, numeroAtual, proximoNumero);
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
                mesclarBlocos(tabela, contadores, j + 1, tabela[i + 1][j], proximoNumero);
            }
        }
    }

    exibirProximoNumero(numeroAtual, proximoNumero);
    exibirTabela(tabela);
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

#ifdef _WIN32
// Função para configurar a cor do texto e do fundo no console
void setConsoleColor(int textColor, int bgColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor | (bgColor << 4));
}

// Função para resetar a cor do console
void resetConsoleColor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7); // Cor padrão: texto branco em fundo preto
}

void escolherCor(int num)
{
    if (num == 2)
    {
        setConsoleColor(0, 1); // azul
    }
    else if (num == 4)
    {
        setConsoleColor(0, 2); // verde
    }
    else if (num == 8)
    {
        setConsoleColor(0, 4); // vermelho
    }
    else if (num == 16)
    {
        setConsoleColor(0, 6); // amarelo
    }
    else if (num == 32)
    {
        setConsoleColor(0, 5); // roxo
    }
    else if (num == 64)
    {
        setConsoleColor(0, 8); // cinza escuro
    }
    else if (num == 128)
    {
        setConsoleColor(0, 4); // vermelho
    }
    else if (num == 256)
    {
        setConsoleColor(0, 9); // azul claro
    }
    else if (num == 512)
    {
        setConsoleColor(0, 6); // amarelo
    }
    else if (num == 1024)
    {
        setConsoleColor(0, 8); // cinza escuro
    }
    else if (num == 2048)
    {
        setConsoleColor(0, 10); // verde claro
    }
    else if (num == 4096)
    {
        setConsoleColor(0, 11); // aqua
    }
    else if (num == 8192)
    {
        setConsoleColor(0, 5); // roxo
    }
    else
    {
        resetConsoleColor(); // Cor padrão
    }
}
#endif

void limparTerminal()
{
    // Verifica se está no sistema Windows
#ifdef _WIN32
    system("cls");
// Caso esteja em um sistema Unix-like (Linux, macOS)
#else
    system("clear");
#endif
}

int verificarGrid(int tabela[linha][coluna])
{
    int gridCheio = 1;
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            if (tabela[i][j] == 0)
            {
                gridCheio = 0;
            }
        }
    }

    return gridCheio;
}

void exibirPerdeu()
{
    limparTerminal();
    printf(
        " ██████   █████  ███    ███ ███████      ██████  ██    ██ ███████ ██████\n"
        "██       ██   ██ ████  ████ ██          ██    ██ ██    ██ ██      ██   ██\n"
        "██   ███ ███████ ██ ████ ██ █████       ██    ██ ██    ██ █████   ██████\n"
        "██    ██ ██   ██ ██  ██  ██ ██          ██    ██  ██  ██  ██      ██   ██\n"
        " ██████  ██   ██ ██      ██ ███████      ██████    ████   ███████ ██   ██\n\n");
}

void exibirGanhou()
{
    limparTerminal();
    printf(
        "██  ██   ██████  ██    ██     ██     ██ ██ ███    ██\n"
        "██  ██  ██    ██ ██    ██     ██     ██ ██ ████   ██\n"
        " ████   ██    ██ ██    ██     ██  █  ██ ██ ██ ██  ██\n"
        "  ██    ██    ██ ██    ██     ██ ███ ██ ██ ██  ██ ██\n"
        "  ██     ██████   ██████       ███ ███  ██ ██   ████\n\n");
}