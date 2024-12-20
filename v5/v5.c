#include <stdio.h>
#include <locale.h>
#include <string.h>

#define LIGNES 6
#define COLONNES 7
#define VIDE 0
#define PION_J1 1
#define PION_J2 2

const char* PIONS[] = {"⚫", "\U0001F534", "\U0001F7E1", ""}; // vide, joueur 1, joueur 2
const char* barreVerticale = "║"; // |
const char* numero[] = {"\U0001D7CF", "\U0001D7D0", "\U0001D7D1", "\U0001D7D2", "\U0001D7D3", "\U0001D7D4", "\U0001D7D5"};

void init_board(int board[LIGNES][COLONNES]);
void print_board(int board[LIGNES][COLONNES]);
int jeter_pion(int board[LIGNES][COLONNES], int col, int pion);
int verif_gagnant(int board[LIGNES][COLONNES], int pion);
int board_rempli(int board[LIGNES][COLONNES]);

int main() {
    setlocale(LC_ALL, "");

    int board[LIGNES][COLONNES];
    int joueur_actuel = PION_J1;
    int col;
    int gagnant = 0;
    char pseudoJ1[50], pseudoJ2[50];

    printf("Entrez le pseudo du joueur 1: ");
    fgets(pseudoJ1, sizeof (pseudoJ1), stdin);
    pseudoJ1[strcspn(pseudoJ1, "\n")] = '\0'; // Retirer le saut de ligne

    printf("Entrez le pseudo du joueur 2: ");
    fgets(pseudoJ2, sizeof (pseudoJ2), stdin);
    pseudoJ2[strcspn(pseudoJ2, "\n")] = '\0'; // Retirer le saut de ligne

    init_board(board);

    while (!gagnant && !board_rempli(board)) {
        print_board(board);
        printf("%s [Entrer la colonne (1-7)]: ", joueur_actuel == PION_J1 ? pseudoJ1 : pseudoJ2);

        if (scanf("%d", &col) != 1) {
            printf("Entrée invalide. Essayez encore.\n");
            while (getchar() != '\n'); // Nettoyer le buffer
            continue;
        }

        if (col < 1 || col > 7) {
            printf("Mouvement invalide. Colonne hors plage (1-7). Essayez encore.\n");
            continue;
        }

        if (!jeter_pion(board, col - 1, joueur_actuel)) {
            printf("Mouvement invalide. La colonne est pleine. Essayez encore.\n");
            continue;
        }

        gagnant = verif_gagnant(board, joueur_actuel);
        if (gagnant || board_rempli(board)) {
            system("clear"); // Nettoyer l'écran uniquement avant l'affichage final
            print_board(board);
            if (gagnant) {
                printf("%s a gagné!\n", joueur_actuel == PION_J1 ? pseudoJ1 : pseudoJ2);
            } else {
                printf("Match nul! Aucun gagnant.\n");
            }
            break;
        }

        joueur_actuel = (joueur_actuel == PION_J1) ? PION_J2 : PION_J1;
        system("clear"); // Nettoyer l'écran ici après les vérifications
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
    printf("\n");
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            printf("%s%s", barreVerticale, PIONS[board[i][j]]);
        }
        printf("%s\n", barreVerticale);
    }
    for (int j = 0; j < COLONNES; j++) {
        printf("%s %s", barreVerticale, numero[j]);
    }
    printf("%s\n\n", barreVerticale);
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
                if (j <= COLONNES - 4 &&
                        board[i][j + 1] == pion &&
                        board[i][j + 2] == pion &&
                        board[i][j + 3] == pion) {
                    return 1;
                }
                if (i <= LIGNES - 4 &&
                        board[i + 1][j] == pion &&
                        board[i + 2][j] == pion &&
                        board[i + 3][j] == pion) {
                    return 1;
                }
                if (i <= LIGNES - 4 && j <= COLONNES - 4 &&
                        board[i + 1][j + 1] == pion &&
                        board[i + 2][j + 2] == pion &&
                        board[i + 3][j + 3] == pion) {
                    return 1;
                }
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

int board_rempli(int board[LIGNES][COLONNES]) {
    for (int j = 0; j < COLONNES; j++) {
        if (board[0][j] == VIDE) {
            return 0;
        }
    }
    return 1;
}