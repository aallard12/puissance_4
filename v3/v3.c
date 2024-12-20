/* File:   main.c
 * Author: aallard
 *
 * Created on 13 décembre 2024, 08:19 */

#include <stdio.h>
#include <locale.h>

#define LIGNES 6
#define COLONNES 7
#define VIDE 0
#define PION_J1 1
#define PION_J2 2

const char* PIONS[] = {"\u26AB", "\U0001F534", "\U0001F7E1", ""}; // vide, joueur 1, joueur 2
const char* barreVerticale = "\u2551"; // |
const char* numero[] = {"\U0001D7CF", "\U0001D7D0", "\U0001D7D1", "\U0001D7D2", "\U0001D7D3", "\U0001D7D4", "\U0001D7D5"};
// 1, 2, 3, 4, 5, 6, 7

void init_board(int board[LIGNES][COLONNES]);
void print_board(int board[LIGNES][COLONNES]);
int jeter_pion(int board[LIGNES][COLONNES], int col, int pion);
int verif_gagnant(int board[LIGNES][COLONNES], int pion);

int main() {
    setlocale(LC_ALL, "");

    int board[LIGNES][COLONNES];
    int joueur_actuel = PION_J1;
    int col;
    int gagnant = 0;
    
    init_board(board);

    while (!gagnant) {
        print_board(board);
        printf("Joueur %d [Entrer la colonne (1-7)]: ", joueur_actuel);
        scanf("%d", &col);
        system("clear");

        if (col < 1 || col > 7 || !jeter_pion(board, col - 1, joueur_actuel)) {
            printf("Mouvement invalide. Essayez encore.\n");
        } else {
            gagnant = verif_gagnant(board, joueur_actuel);
            if (gagnant) {
                system("clear");
                print_board(board);
                printf("Joueur %d a gagné!\n", joueur_actuel == PION_J1 ? 1 : 2);
            }
            joueur_actuel = (joueur_actuel == PION_J1) ? PION_J2 : PION_J1;
        }
    }
    return 0;
}

void init_board(int board[LIGNES][COLONNES]) {
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            board[i][j] = VIDE;
        }
    }
}

void print_board(int board[LIGNES][COLONNES]) {
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            printf("%s%s", barreVerticale, PIONS[board[i][j]]);
        }
        printf("%s\n", barreVerticale);
    }
    for (int j = 0; j < COLONNES; j++) {
        printf("%s %s", barreVerticale, numero[j]);
    }
    printf("%s\n", barreVerticale);
}

int jeter_pion(int board[LIGNES][COLONNES], int col, int pion) {
    for (int i = LIGNES - 1; i >= 0; i--) {
        if (board[i][col] == VIDE) {
            board[i][col] = pion;
            return 1;
        }
    }
    return 0;
}

int verif_gagnant(int board[LIGNES][COLONNES], int pion) {
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            if (board[i][j] == pion) {
                // Vérification horizontale
                if (j <= COLONNES - 4 && 
                    board[i][j + 1] == pion && 
                    board[i][j + 2] == pion && 
                    board[i][j + 3] == pion) {
                    return 1;
                }
                // Vérification verticale
                if (i <= LIGNES - 4 && 
                    board[i + 1][j] == pion && 
                    board[i + 2][j] == pion && 
                    board[i + 3][j] == pion) {
                    return 1;
                }
                // Vérification diagonale (bas-droite)
                if (i <= LIGNES - 4 && j <= COLONNES - 4 && 
                    board[i + 1][j + 1] == pion && 
                    board[i + 2][j + 2] == pion && 
                    board[i + 3][j + 3] == pion) {
                    return 1;
                }
                // Vérification diagonale (haut-droite)
                if (i >= 3 && j <= COLONNES - 4 && 
                    board[i - 1][j + 1] == pion && 
                    board[i - 2][j + 2] == pion && 
                    board[i - 3][j + 3] == pion) {
                    return 1;
                }
            }
        }
    }
    return 0;
}