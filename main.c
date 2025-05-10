#include "game.h"


int main() {
    srand(time(NULL));
    int n, pathLength;
    char forest[100][100];
    int path[400][2];
    int crabs[100];
    for (int i = 0; i < 100; i++) crabs[i] = -1;
    Monkey monkeys[100];
    for (int i = 0; i < 100; i++) monkeys[i].actif = 0;
    int nbMonkeys = 0;
    int vague = 0;
    int money = 0;
    int score = 0;

    mainMenu(forest, n, path, pathLength, crabs, &nbMonkeys, monkeys, &money, &score, &vague);



    
    return 0;
}