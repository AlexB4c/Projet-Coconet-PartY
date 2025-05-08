#include "game.h"

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