# DropMerge 2048 - Jogo em C

## 📌 Sobre o Jogo

DropMerge 2048 é um jogo inspirado no clássico 2048, com mecânicas de queda de blocos semelhantes ao jogo DropMerge. O objetivo é combinar blocos de mesmo valor para obter a maior pontuação possível antes que o tabuleiro fique cheio.

## 🎮 Como Jogar

1. Escolha um nível de dificuldade.
2. Digite o número da coluna onde deseja que o bloco caia.
3. Blocos com o mesmo valor se fundem ao se encontrarem, dobrando o valor.
4. Continue jogando até não haver mais espaço para blocos.
5. Utilize o martelo estrategicamente para destruir blocos quando necessário.

## 🔥 Níveis de Dificuldade

- **Fácil**: 5 colunas, primeiro martelo obtido com 128 pontos.
- **Médio**: 4 colunas, primeiro martelo obtido com 512 pontos.
- **Difícil**: 3 colunas, primeiro martelo obtido com 1024 pontos.
- O jogador pode alterar o nível de dificuldade a qualquer momento no menu de configurações.

## 🔨 Uso do Martelo

Se o tabuleiro estiver cheio e o jogador tiver um martelo, ele pode ser usado para remover um bloco específico:
1. Escolha a linha (1 a 10).
2. Escolha a coluna (dependendo do nível de dificuldade).
3. O jogo continuará normalmente após a remoção do bloco.

**Observação:** O número de pontos necessários para conseguir um martelo dobra a cada vez que um é obtido.

## ⚙️ Configurações

No menu de configurações, o jogador pode:
- Alterar o nível de dificuldade.
- Zerar o ranking e redefinir as pontuações.

## 💡 Dicas

- Planeje onde os blocos vão cair para evitar que o tabuleiro fique cheio rapidamente.
- Use o martelo com estratégia para remover blocos que atrapalham combinações.

## 🛠️ Como Compilar e Executar

Para compilar o jogo, utilize um compilador C como `gcc`:

```sh
gcc main.c -o dropmerge
```

Para rodar o jogo:

```sh
./dropmerge
```

## 📜 Licença

Este projeto é de uso livre. Sinta-se à vontade para modificar e compartilhar!

---

Divirta-se jogando DropMerge!
