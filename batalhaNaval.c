#include <stdio.h>
#include <stdlib.h>

#define TAM 10       // tamanho do tabuleiro
#define TAM_NAVIO 3  // tamanho dos navios
#define SKILL 5      // dimensão das matrizes de habilidade (5x5)

// inicializa tabuleiro com água (0)
void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = 0;
}

// mostra tabuleiro com prioridade: navio(3) > area(5) > agua(0)
void mostrarTabuleiro(int tab[TAM][TAM], int efeito[TAM][TAM]) {
    printf("===  TABULEIRO  BATALHA  NAVAL  ===\n\n");
    printf("Legenda: 0=agua  3=navio  5=area-efeito\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == 3)                // navio tem prioridade visual
                printf("%d ", 3);
            else if (efeito[i][j] == 1)       // se há efeito e não há navio
                printf("%d ", 5);
            else
                printf("%d ", 0);
        }
        printf("\n");
    }
}

// funções para posicionar navios (assumem posição válida)
void colocarNavioHorizontal(int tab[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++)
        if (coluna + i >= 0 && coluna + i < TAM) // proteção simples
            tab[linha][coluna + i] = 3;
}
void colocarNavioVertical(int tab[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++)
        if (linha + i >= 0 && linha + i < TAM)
            tab[linha + i][coluna] = 3;
}
void colocarNavioDiagonalDireita(int tab[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++)
        if (linha + i >= 0 && linha + i < TAM && coluna + i >= 0 && coluna + i < TAM)
            tab[linha + i][coluna + i] = 3;
}
void colocarNavioDiagonalEsquerda(int tab[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++)
        if (linha + i >= 0 && linha + i < TAM && coluna - i >= 0 && coluna - i < TAM)
            tab[linha + i][coluna - i] = 3;
}

// construir matriz "cone" dinamicamente (aponta para baixo dentro da matriz)
void construirCone(int mat[SKILL][SKILL]) {
    int mid = SKILL / 2;
    for (int r = 0; r < SKILL; r++) {
        for (int c = 0; c < SKILL; c++) {
            // condicional que cria um "triângulo" com ápice na linha 0
            // nota: usamos r <= mid para limitar a altura do cone à metade superior
            if (r <= mid && abs(c - mid) <= r) mat[r][c] = 1;
            else mat[r][c] = 0;
        }
    }
}

// construir matriz "cruz" dinamicamente (centro)
void construirCruz(int mat[SKILL][SKILL]) {
    int mid = SKILL / 2;
    for (int r = 0; r < SKILL; r++) {
        for (int c = 0; c < SKILL; c++) {
            if (r == mid || c == mid) mat[r][c] = 1;
            else mat[r][c] = 0;
        }
    }
}

// construir matriz "octaedro" (vista frontal = losango/diamante)
void construirOctaedro(int mat[SKILL][SKILL]) {
    int mid = SKILL / 2;
    for (int r = 0; r < SKILL; r++) {
        for (int c = 0; c < SKILL; c++) {
            if (abs(r - mid) + abs(c - mid) <= mid) mat[r][c] = 1;
            else mat[r][c] = 0;
        }
    }
}

// aplica (sobrepõe) a matriz de habilidade no tabuleiro, centralizando em (origemL, origemC)
// escreve em 'efeito' (1 = afetado). Não sobrescreve diretamente tabuleiro para preservar navios.
void aplicarHabilidade(int efeito[TAM][TAM], int habilidade[SKILL][SKILL], int origemL, int origemC) {
    int mid = SKILL / 2;
    for (int i = 0; i < SKILL; i++) {
        for (int j = 0; j < SKILL; j++) {
            if (habilidade[i][j] == 1) {
                int r = origemL - mid + i; // centraliza a skill no ponto de origem
                int c = origemC - mid + j;
                if (r >= 0 && r < TAM && c >= 0 && c < TAM) {
                    efeito[r][c] = 1; // marca área de efeito
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int efeito[TAM][TAM]; // camada separada para efeitos (0/1)

    // inicializa tabuleiro e camada de efeito
    inicializarTabuleiro(tabuleiro);
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            efeito[i][j] = 0;

    // coloca 4 navios (posições seguras, sem sobreposição)
    colocarNavioHorizontal(tabuleiro, 0, 0);      // (0,0)-(0,2)
    colocarNavioVertical(tabuleiro, 2, 5);        // (2,5)-(4,5)
    colocarNavioDiagonalDireita(tabuleiro, 5, 0); // (5,0)-(7,2)
    colocarNavioDiagonalEsquerda(tabuleiro, 6, 9); // (6,9)-(8,7)

    // construir matrizes de habilidade dinamicamente
    int cone[SKILL][SKILL], cruz[SKILL][SKILL], octaedro[SKILL][SKILL];
    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    // definir pontos de origem (centro da habilidade) no tabuleiro
    // (escolhi exemplos; você pode alterar para testar)
    int origemConeL = 2, origemConeC = 2;   // o cone ficará no topo do tabuleiro
    int origemCruzL = 3, origemCruzC = 5;   // cruz próxima ao navio vertical
    int origemOctL  = 7, origemOctC  = 2;   // octaedro mais abaixo

    // aplicar habilidades (marca 'efeito' com 1 onde houver área)
    aplicarHabilidade(efeito, cone, origemConeL, origemConeC);
    aplicarHabilidade(efeito, cruz, origemCruzL, origemCruzC);
    aplicarHabilidade(efeito, octaedro, origemOctL, origemOctC);

    // exibir tabuleiro final
    mostrarTabuleiro(tabuleiro, efeito);

    return 0;
}
