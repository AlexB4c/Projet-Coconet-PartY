#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TREE "\U0001F334"
#define PATH "\U0001F7EB"
#define MONKEY "\U0001F412"
#define CROWN "\U0001F451"
#define CRAB "\U0001F980"
#define FLAG "\U0001F6A9"
int money = 0;
int score = 0;

typedef struct {
    int x, y;
    int range;
    int cooldownMax;
    int cooldown;
    int actif;
} Monkey;

void printForest(char forest[][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            switch (forest[i][j]) {
                case 'T': printf("%s", TREE); break;
                case 'P': printf("%s", PATH); break;
                case 'M': printf("%s", MONKEY); break;
                case 'C': printf("%s", CROWN); break;
                case 'R': printf("%s", CRAB); break;
                case 'F': printf("%s", FLAG); break;
                default: printf(" "); break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

int generatePath(char forest[][100], int n, int path[][2]) {
    int x = n / 2, y = 0;
    int up = 0, down = 0;
    int pathLength = 0;

    forest[x][y] = 'F';

    while (y < n - 1) {
        path[pathLength][0] = x;
        path[pathLength][1] = y;
        pathLength++;

        if (x < n - 1 && rand() % 2 == 0 && up == 0) {
            x++; down = 1;
        } else if (x > 0 && rand() % 2 == 0 && down == 0) {
            x--; up = 1;
        } else {
            y++;
            forest[x][y] = 'P';
            path[pathLength][0] = x;
            path[pathLength][1] = y;
            pathLength++;
            y++; up = 0; down = 0;
        }

        if (y < n) forest[x][y] = 'P';
    }

    path[pathLength][0] = x;
    path[pathLength][1] = y;
    pathLength++;
    if (y - 1 >= 0) forest[x][y - 1] = 'C';

    return pathLength;
}

void crabDelete(char forest[][100], int path[][2], int crabIndex, int crabs[], int *money, int *score) {
    if (crabs[crabIndex] == -1) return;
    int x = path[crabs[crabIndex]][0];
    int y = path[crabs[crabIndex]][1];
    forest[x][y] = 'P';
    *money += 10; // Gain de 10 unités d'argent
    *score += 200; // Gain de 200
    printf("Crabe éliminé ! Argent total : %d, Score : %d\n", *money, *score);
    for(int i= crabIndex; i< 99 && crabs[i] != -1; i++) {
        crabs[i] = crabs[i + 1];
    }
    crabs[99] = -1;
}

void moveCrab(char forest[][100], int n, int path[][2], int pathLength, int crabIndex, int crabs[]) {
    if (crabIndex < 0 || crabIndex >= 100 || crabs[crabIndex] == -1 || crabs[crabIndex] >= pathLength) return;

    int oldX = path[crabs[crabIndex]][0];
    int oldY = path[crabs[crabIndex]][1];
    forest[oldX][oldY] = 'P';

    crabs[crabIndex]++;
    if (crabs[crabIndex] >= pathLength) return;

    int newX = path[crabs[crabIndex]][0];
    int newY = path[crabs[crabIndex]][1];
    forest[newX][newY] = 'R';

    if (crabs[crabIndex] == pathLength - 1) {
        printf("Le crabe a atteint la couronne ! Victoire des crustacés !\n");
        exit(0);
    }
}

void monkeyTurn(Monkey monkeys[], int nbMonkeys, char forest[][100], int n, int path[][2], int crabs[]) {
    for (int i = 0; i < nbMonkeys; i++) {
        if (monkeys[i].actif != 1) continue;

        if (monkeys[i].cooldown > 0) {
            monkeys[i].cooldown--;
            continue;
        }

        int x = monkeys[i].x;
        int y = monkeys[i].y;
        int attacked = 0;

        for (int dx = -monkeys[i].range; dx <= monkeys[i].range; dx++) {
            for (int dy = -monkeys[i].range; dy <= monkeys[i].range; dy++) {
                int nx = x + dx, ny = y + dy;
                if ((dx == 0 && dy == 0) || nx < 0 || ny < 0 || nx >= n || ny >= n) continue;

                if (forest[nx][ny] == 'R') {
                    for (int k = 0; k < 100 && crabs[k] != -1; k++) {
                        if (crabs[k] < 0 || crabs[k] >= 400) continue;
                        if (path[crabs[k]][0] == nx && path[crabs[k]][1] == ny) {
                            crabDelete(forest, path, k, crabs, &money, &score);
                            monkeys[i].cooldown = monkeys[i].cooldownMax;
                            attacked = 1;
                            break;
                        }
                    }
                }
                if (attacked) break;
            }
            if (attacked) break;
        }
    }
}

void monkeyGenerator(char forest[][100], int n, Monkey monkeys[], int nb, int x, int y) {
    if (nb >= 100) return;
    monkeys[nb] = (Monkey){x, y, 1, 3, 0, 1};
    forest[x][y] = 'M';
}

void crabGenerator(char forest[][100], int path[][2], int crabs[]) {
    int i = 0;
    while (i < 100 && crabs[i] != -1) i++;
    if (i >= 100) return;
    crabs[i] = 1;
    forest[path[1][0]][path[1][1]] = 'R';
}

void crabTurn(char forest[][100], int n, int path[][2], int pathLength, int crabs[]) {
    for (int i = 0; i < 100 && crabs[i] != -1; i++) {
        moveCrab(forest, n, path, pathLength, i, crabs);
    }
}


void crabWave(char forest[][100], int crabNumber, int n, int path[][2], int pathLength, int crabs[], int nbMonkeys, Monkey monkeys[],int *money, int *score) {
    int count = 0;
    crabGenerator(forest, path, crabs);
    printForest(forest, n);

    while (count < crabNumber || crabs[0] != -1) {
        if (rand() % 3 == 0 && count < crabNumber) {
            crabGenerator(forest, path, crabs);
            count++;
        }
        sleep(1);
        crabTurn(forest, n, path, pathLength, crabs);
        printForest(forest, n);
        monkeyTurn(monkeys, nbMonkeys, forest, n, path, crabs);

        int crabalive = 0;
        for (int i = 0; i < 100; i++) {
            if (crabs[i] != -1) {
                crabalive = 1;
                break;
            }
        }
        if (!crabalive && count >= crabNumber) break;
    }

}

void saveGame(char forest[][100], int n, int path[][2], int pathLength, Monkey monkeys[], int nbMonkeys, int *money, int *score) {
    FILE *file = fopen("save.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de la sauvegarde.\n");
        return;
    }

    fprintf(file, "%d\n", n);  // Taille de la forêt
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fputc(forest[i][j], file);
        }
        fputc('\n', file);
    }

    fprintf(file, "%d\n", pathLength);
    for (int i = 0; i < pathLength; i++) {
        fprintf(file, "%d %d\n", path[i][0], path[i][1]);
    }

    fprintf(file, "%d\n", nbMonkeys);
    for (int i = 0; i < nbMonkeys; i++) {
        fprintf(file, "%d %d %d %d %d %d\n", monkeys[i].x, monkeys[i].y, monkeys[i].range, monkeys[i].cooldownMax, monkeys[i].cooldown, monkeys[i].actif);
    }

    fprintf(file, "%d\n", *money);
    for (int i = 0; i < *money; i++) {
        fprintf(file, "%d ", i);
    }

    fprintf(file, "%d\n", *score);
    for (int i = 0; i < *score; i++) {
        fprintf(file, "%d ", i);
    }
    fprintf(file, "-1\n");

    fclose(file);
    printf("Partie sauvegardée !\n");
}

int loadGame(char forest[][100], int *n, int path[][2], int *pathLength, Monkey monkeys[], int *nbMonkeys, int *money, int *score) {
    FILE *file = fopen("save.txt", "r");
    if (!file) {
        printf("Aucune sauvegarde trouvée.\n");
        return 0;
    }

    fscanf(file, "%d", n);  // Charger taille forêt

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, " %c", &forest[i][j]);  // Attention à l'espace pour ignorer les sauts de ligne
        }
    }

    fscanf(file, "%d", pathLength);
    for (int i = 0; i < *pathLength; i++) {
        fscanf(file, "%d %d", &path[i][0], &path[i][1]);
    }

    fscanf(file, "%d", nbMonkeys);
    for (int i = 0; i < *nbMonkeys; i++) {
        fscanf(file, "%d %d %d %d %d %d", &monkeys[i].x, &monkeys[i].y, &monkeys[i].range, &monkeys[i].cooldownMax, &monkeys[i].cooldown, &monkeys[i].actif);
        forest[monkeys[i].x][monkeys[i].y] = 'M';  // Restaurer le singe sur la carte
    }
    
    fscanf(file, "%d", money);
    for (int i = 0; i < *money; i++) {
        fscanf(file, "%d", &i);
    }
    fscanf(file, "%d", score);
    for (int i = 0; i < *score; i++) {
        fscanf(file, "%d", &i);
    }

    fclose(file);
    printf("Chargement terminé ! Forêt %dx%d, %d cases de chemin, %d singes chargés.\n", *n, *n, *pathLength, *nbMonkeys);
    return 1;
}

void magasin(int *money, int *nbMonkeys, Monkey monkeys[], char forest[][100], int n) {
    printf("\n--- Magasin ---\n");
    printf("Votre solde: %d bananes écrasées\n", *money);
    printf("Que voulez-vous faire ?\n");
    printf("1. Acheter un singe (30 bananes écrasées)\n");
    printf("2. Quitter le magasin\n");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        if (*money < 30) {
            printf("Vous n'avez pas assez de bananes écrasées pour acheter un singe.\n");
            return;
        }

        int x, y;
        printf("Entrez les coordonnées du singe (x y) : ");
        scanf("%d %d", &x, &y);

        if (x >= 0 && x < n && y >= 0 && y < n && forest[x][y] != 'P' && forest[x][y] != 'M') {
            monkeyGenerator(forest, n, monkeys, *nbMonkeys, x, y);
            (*nbMonkeys)++;
            *money -= 50; // Déduire le coût du singe
            printf("Singe acheté avec succès !\n");
        } else {
            printf("Emplacement invalide (occupé ou hors limites).\n");
        }

    } else if (choice == 2) {
        printf("Vous avez quitté le magasin.\n");
    } else {
        printf("Choix invalide.\n");
    }
}


int main() {
    srand(time(NULL));
    int n, pathLength;
    char forest[100][100];
    int path[400][2];

    int crabs[100];
    for (int i = 0; i < 100; i++) crabs[i] = -1;

    Monkey monkeys[100];
    int nbMonkeys = 0;
    // Demander si on veut charger une sauvegarde
    int charger;
    printf("Charger une sauvegarde ? (1 = oui / 0 = non) : ");
    scanf("%d", &charger);

    if (charger == 1) {
        if (!loadGame(forest, &n, path, &pathLength, monkeys, &nbMonkeys, &money, &score)) {
            printf("Échec du chargement. Création d'une nouvelle partie...\n");
            charger = 0;
        } else {
            printForest(forest, n);
        }
    }

    if (charger == 0) {
        n = rand() % 40 + 10;  // Taille de la forêt entre 10 et 50

        // Initialiser la forêt avec des arbres
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                forest[i][j] = 'T';

         pathLength = generatePath(forest, n, path);
         printf("Carte générée :\n");
         printForest(forest, n);

         printf("Combien de singes ? (max 100) : ");
         scanf("%d", &nbMonkeys);

         for (int i = 0; i < nbMonkeys; i++) {
            int x, y;
            printf("Singe %d (x y) : ", i + 1);
            scanf("%d %d", &x, &y);
            if (x >= 0 && x < n && y >= 0 && y < n && forest[x][y] != 'P') {
                monkeyGenerator(forest, n, monkeys, i, x, y);
            } else {
                printf("Invalide. Réessaye.\n");
                i--;
            }
          printForest(forest, n);
       }
    }
    printf("\nVoici la carte finale avant sauvegarde :\n");
    printForest(forest, n);

    int crabCount;
    printf("Combien de crabes voulez-vous générer ? : ");
    scanf("%d", &crabCount);
    crabWave(forest, crabCount, n, path, pathLength, crabs, nbMonkeys, monkeys, &money, &score);
    magasin(&money, &nbMonkeys, monkeys, forest, n);
    printf("Voulez-vous sauvegarder la partie ? (1 = oui / 0 = non) : ");
    int save;
    scanf("%d", &save);
    if (save == 1)
    saveGame(forest, n, path, pathLength, monkeys, nbMonkeys, &money, &score);
    printf("Partie terminée ! Score final : %d | Argent restant : %d\n", score, money);
    
    return 0;
}
