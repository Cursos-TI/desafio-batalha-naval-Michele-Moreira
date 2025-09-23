#include <stdio.h>

#define TAM 10   // Tamanho do tabuleiro
#define TAM_NAVIO 3 // Tamanho dos navios

int main() {
    int tabuleiro[TAM][TAM]; // Matriz 10x10
    int navio1[TAM_NAVIO];   // Navio horizontal
    int navio2[TAM_NAVIO];   // Navio vertical

    // 1. Inicializar tabuleiro com 0 (água)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // 2. Definir posição do primeiro navio (horizontal)
    // Navio posicionado na linha 2, colunas 1 a 3
    int linha1 = 2;
    int col1 = 1;
    for (int i = 0; i < TAM_NAVIO; i++) {
        navio1[i] = 3;
        tabuleiro[linha1][col1 + i] = navio1[i];
    }

    // 3. Definir posição do segundo navio (vertical)
    // Navio posicionado na coluna 5, linhas 4 a 6
    int linha2 = 4;
    int col2 = 5;
    for (int i = 0; i < TAM_NAVIO; i++) {
        navio2[i] = 3;
        tabuleiro[linha2 + i][col2] = navio2[i];
    }

    // 4. Exibir tabuleiro
    printf("=== TABULEIRO BATALHA NAVAL ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
