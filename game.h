#ifndef GAME_H
#include GAME_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define TREE "\U0001F334"   // Tree emoji
#define PATH "\U0001F7EB"   // Brown square emoji (path)
#define MONKEY "\U0001F412" // Monkey emoji
#define CROWN "\U0001F451"  // Crown emoji
#define CRAB "\U0001F980"  // Crabe emoji
#define FLAG "\U0001F6A9"   // Drapeau rouge emoji 

typedef struct{
    int x;
    int y; // position du singe
    int range; // portée d'attaque
    int cooldownMax; // cooldown max
    int cooldown; // cooldown actuel
    int actif ; // 1 si actif, 0 sinon
}Monkey;

// Fonctions de path.c
void printForest(char forest[][100], int n);
int generatePath(char forest[][100], int n, int path[][2]);

// Fonctions de monkey.c
void monkeyGenerator(char forest[][100], int n, Monkey monkeys[], int nbmonkeys, int x, int y);
void monkeyTurn(Monkey monkeys[], int nbmonkeys, char forest[][100], int n, int path[][2], int crabs[]);

// Fonctions de crab.c
void crabGenerator(char forest[][100], int path[][2], int crabs[]);
void crabDelete(char forest[][100], int path[][2], int crabindex, int crabs[]);
void moveCrab(char forest[][100], int n, int path[][2], int pathLength, int crabindex, int crabs[]);
void crabTurn(char forest[][100], int n, int path[][2], int pathLength, int crabs[]);
void crabWave(char forest[][100], int crabNumber, int n, int path[][2], int pathLength, int crabs[], int nbMonkeys, Monkey monkeys[]);

#endif