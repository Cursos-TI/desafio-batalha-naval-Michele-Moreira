#include <stdio.h>
#define TAM 10   // tamanho do tabuleiro
#define TAM_NAVIO 3  // tamanho dos navios

void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void mostrarTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("===  TABULEIRO  BATALHA  NAVAL  ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// coloca um navio horizontal
void colocarNavioHorizontal(int tabuleiro[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = 3;
    }
}

// coloca um navio vertical
void colocarNavioVertical(int tabuleiro[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = 3;
    }
}

// coloca um navio diagonal ↘
void colocarNavioDiagonalDireita(int tabuleiro[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = 3;
    }
}

// coloca um navio diagonal ↙
void colocarNavioDiagonalEsquerda(int tabuleiro[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = 3;
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // posições fixas e seguras
    colocarNavioHorizontal(tabuleiro, 0, 0);     // horizontal (linha 0, colunas 0–2)
    colocarNavioVertical(tabuleiro, 2, 5);       // vertical (coluna 5, linhas 2–4)
    colocarNavioDiagonalDireita(tabuleiro, 5, 0); // diagonal ↘ (começa em 5,0)
    colocarNavioDiagonalEsquerda(tabuleiro, 6, 9); // diagonal ↙ (começa em 6,9)

    mostrarTabuleiro(tabuleiro);

    return 0;
}
