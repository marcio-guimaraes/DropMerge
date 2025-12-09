#ifndef JOGO_H
#define JOGO_H

// Declaração das funções de jogo.c que são usadas em main.c
int jogo();
void limparTerminal();

/*
 Declaração das variáveis globais como 'extern'.
 Isso informa ao compilador que essas variáveis existem
 e serão definidas em outro arquivo (neste caso, jogo.c).
*/
extern int linha;
extern int coluna;
extern int pontosNecessarios;

#endif // JOGO_H