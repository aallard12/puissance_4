/* File:   main.c
 * Author: aallard
 *
 * Created on 13 décembre 2024, 08:19*/

#include <stdio.h>
#include <locale.h>

#define LIGNES 6
#define COLONNES 7
#define VIDE ' '

void init_board(char board[LIGNES][COLONNES]);
void print_board(char board[LIGNES][COLONNES]);
int jeter_pion(char board[LIGNES][COLONNES], int col, char pion);
int verif_gagnant(char board[LIGNES][COLONNES], char pion);

int main() {
    
    setlocale(LC_ALL, "");
    
    char board[LIGNES][COLONNES];
    int joueur_actuel = 1;
    int col;
    int gagnant = 0;

    init_board(board);

    while (!gagnant) {
        print_board(board);
        printf("Joueur %d [Entrer la colonne (1-7)]: ", joueur_actuel);
        scanf("%d", &col);
        if (col < 1 || col > 7 || !jeter_pion(board, col - 1, joueur_actuel == 1 ? '\U0001F534' : '\U0001F7E1')) {
            printf("Mouvement invalide. Essayez encore.\n");
        } else {
            gagnant = verif_gagnant(board, joueur_actuel == 1 ? '\U0001F534' : '\U0001F7E1');
            if (gagnant) {
                print_board(board);
                printf("Joueur %d a gagné!\n", joueur_actuel);
            }
            joueur_actuel = 3 - joueur_actuel; // CHANGEMENT DU JOUEUR
        }
    }
    return 0;
}

void init_board(char board[LIGNES][COLONNES]) {
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            board[i][j] = VIDE;
        }
    }
}

void print_board(char board[LIGNES][COLONNES]) {
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
    for (int j = 0; j < COLONNES; j++) {
        printf("  %d ", j + 1);
    }
    printf("\n");
}

int jeter_pion(char board[LIGNES][COLONNES], int col, char pion) {
    for (int i = LIGNES - 1; i >= 0; i--) {
        if (board[i][col] == VIDE) {
            board[i][col] = pion;
            return 1;
        }
    }
    return 0;
}

int verif_gagnant(char board[LIGNES][COLONNES], char pion) {
    
    // Vérification des directions horizontale, verticale et diagonale pour savoir si il a gagné.
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            if (board[i][j] == pion) {
                
                // Vérification horizontale
                if (j <= COLONNES - 4 && board[i][j + 1] == pion && board[i][j + 2] == pion && board[i][j + 3] == pion) {
                    return 1;
                }
                // Vérification verticale
                if (i <= LIGNES - 4 && board[i + 1][j] == pion && board[i + 2][j] == pion && board[i + 3][j] == pion) {
                    return 1;
                }
                // Vérification diagonale (bas-droite)
                if (i <= LIGNES - 4 && j <= COLONNES - 4 && board[i + 1][j + 1] == pion && board[i + 2][j + 2] == pion && board[i + 3][j + 3] == pion) {
                    return 1;
                }
                // Vérification diagonale (haut-droite)
                if (i >= 3 && j <= COLONNES - 4 && board[i - 1][j + 1] == pion && board[i - 2][j + 2] == pion && board[i - 3][j + 3] == pion) {
                    return 1;
                }
            }
        }
    }
    return 0;
}