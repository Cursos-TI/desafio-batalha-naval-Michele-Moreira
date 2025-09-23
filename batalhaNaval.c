#include <stdio.h>

#define TAM 10       // Tamanho do tabuleiro
#define TAM_NAVIO 3  // Tamanho fixo dos navio

int main() {
    int tabuleiro[TAM][TAM]; // Matriz 10x10

    //  Inicializar tabuleiro com 0 (água)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Colocar navio diagonal ↙ (decrescente)
    int linha4 = 0, col4 = 9; // começa no canto superior direito
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (linha4 + i < TAM && col4 - i >= 0 && tabuleiro[linha4 + i][col4 - i] == 0) {
            tabuleiro[linha4 + i][col4 - i] = 3;
        }
    }

    // Definir posição do primeiro navio (horizontal)
    // Navio posicionado na linha 2, colunas 1 a 3
    int linha1 = 2, col1 = 1;
    int pode_posicionar = 1;
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (col1 + i >= TAM || tabuleiro[linha1][col1 + i] != 0) {
            pode_posicionar = 0;
            break;
        }
    }
    // Se puder posicionar, coloca o navio
    if (pode_posicionar) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha1][col1 + i] = 3;
        }
    }

    // Definir posição do terceiro navio (vertical)
    // Navio posicionado na coluna 4, linhas 4 a 6
    int linha2 = 4, col2 = 5;
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (linha2 + i < TAM && tabuleiro[linha2 + i][col2] == 0) {
            tabuleiro[linha2 + i][col2] = 3;
        }
    }

    // Colocar navio diagonal ↘ (crescente)
    int linha3 = 0, col3 = 0; // começa no canto superior esquerdo
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (linha3 + i < TAM && col3 + i < TAM && tabuleiro[linha3 + i][col3 + i] == 0) {
            tabuleiro[linha3 + i][col3 + i] = 3;
        }
    }

    // Imprimir o tabuleiro
    printf("=== TABULEIRO BATALHA NAVAL ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}