#include "game.h"

int main() {
    srand(time(NULL));
    int n, pathLength;
    char forest[100][100];
    int path[400][2];

    int crabs[100];
    for (int i = 0; i < 100; i++) crabs[i] = -1;

    Monkey monkeys[100];
    int nbMonkeys = 0;

    n = rand() % 40 + 10;

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

    int crabCount;
    printf("Combien de crabes ? : ");
    scanf("%d", &crabCount);

    crabWave(forest, crabCount, n, path, pathLength, crabs, nbMonkeys, monkeys);

    return 0;
}
    



    int crabCount;
    Monkey monkeys[100];
    for (int i = 0; i < 100; i++) {
        monkeys[i].actif = -1; // Initialiser tous les singes avec un statut actif à -1
    }
    int nbMonkeys;

    printForest(forest, n);

    printf("Combien de singes voulez-vous placer ? (max 100) : ");
    scanf("%d", &nbMonkeys);

    for (int i = 0; i < nbMonkeys; i++) {
        int x, y;
        printf("Entrez les coordonnées du singe %d (x y) : ", i + 1);
        scanf("%d %d", &x, &y);

        if (x >= 0 && x < n && y >= 0 && y < n && forest[x][y] != 'P') {
        monkeyGenerator(forest, n, monkeys, i, x, y);
        forest[x][y] = 'M'; // Place le singe sur la carte
        } else {
        printf("Coordonnées invalides ou emplacement non disponible. Réessayez.\n");
        i--; // Reprendre la saisie pour ce singe
        }
        printForest(forest, n);
    }
    printf("\nVoici la carte après avoir placé les singes :\n");
    printForest(forest, n);

    printf("Combien de crabes voulez-vous générer ? : ");
    scanf("%d", &crabCount);
    crabWave(forest, crabCount, n, path, pathLength, crabs, nbMonkeys, monkeys); // on lance une vague de crabes

    return 0;
}