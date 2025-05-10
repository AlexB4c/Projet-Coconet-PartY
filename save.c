#include "game.h"

void saveGame(char forest[][100], int n, int path[][2], int pathLength, Monkey monkeys[], int nbMonkeys, int *money, int *score, char *nomsauvegarde,int *vague) {
    FILE *file = fopen(nomsauvegarde, "w");
    if (file == NULL) {
        printf("Erreur lors de la sauvegarde.\n");
        return;
    }

    fprintf(file, "%d\n", n);  //size of forest
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

    fprintf(file, "%d\n", *score);

    fprintf(file, "%d\n", *vague);

    fprintf(file, "-1\n");

    fclose(file);
    printf("Partie sauvegardée !\n");
}

int loadGame(char forest[][100], int *n, int path[][2], int *pathLength, Monkey monkeys[], int *nbMonkeys, int *money, int *score,char *nomsauvegarde, int *vague) {
    FILE *file = fopen(nomsauvegarde, "r");
    if (!file) {
        printf("Aucune sauvegarde trouvée.\n");
        return 0;
    }

    fscanf(file, "%d", n);  // loading size of forest

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, " %c", &forest[i][j]);  // Caution to the space to ignore the gap line
        }
    }

    fscanf(file, "%d", pathLength);
    for (int i = 0; i < *pathLength; i++) {
        fscanf(file, "%d %d", &path[i][0], &path[i][1]);
    }

    fscanf(file, "%d", nbMonkeys);
    for (int i = 0; i < *nbMonkeys; i++) {
        fscanf(file, "%d %d %d %d %d %d", &monkeys[i].x, &monkeys[i].y, &monkeys[i].range, &monkeys[i].cooldownMax, &monkeys[i].cooldown, &monkeys[i].actif);
        forest[monkeys[i].x][monkeys[i].y] = 'M';  // Restore the monkeys on the forest
    }
    
    fscanf(file, "%d", money);
    
    fscanf(file, "%d", score);
    
    fscanf(file, "%d", vague);
    

    fclose(file);
    printf("Chargement terminé ! Forêt %dx%d, %d cases de chemin, %d singes chargés, vague: %d\n", *n, *n, *pathLength, *nbMonkeys, *vague);
    return 1;
}