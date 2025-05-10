#include "game.h"

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

void crabWave(char forest[][100], int n, int path[][2], int pathLength, int crabs[], int* nbMonkeys, Monkey monkeys[],int *money, int *score,int *vague) {
    int crabtab[10] = {1, 2, 3, 4, 6, 8, 10, 14, 18, 24};
    int crabNumber = crabtab[*vague];
    int count = 1;
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
        monkeyTurn(monkeys, *nbMonkeys, forest, n, path, crabs,money, score);

        int crabalive = 0;
        for (int i = 0; i < 100; i++) {
            if (crabs[i] != -1) {
                crabalive = 1;
                break;
            }
        }
        if (!crabalive && count >= crabNumber) break;
    }
    *vague += 1;
    system("clear");
    printf("bravo ! vous avez terminé la vague %d\n", *vague);
    sleep(2);
    menuVague(forest, n, path, pathLength, crabs, nbMonkeys, monkeys, money, score, vague);
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