#include "game.h"

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

