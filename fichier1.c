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

void crabDelete(char forest[][100], int path[][2], int crabIndex, int crabs[]) {
    if (crabs[crabIndex] == -1) return;
    int x = path[crabs[crabIndex]][0];
    int y = path[crabs[crabIndex]][1];
    forest[x][y] = 'P';
    for (int i = crabIndex; i < 99 && crabs[i] != -1; i++) {
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
                            crabDelete(forest, path, k, crabs);
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

void crabWave(char forest[][100], int crabNumber, int n, int path[][2], int pathLength, int crabs[], int nbMonkeys, Monkey monkeys[]) {
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
