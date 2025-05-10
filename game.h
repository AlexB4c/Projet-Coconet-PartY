#ifndef GAME_H
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

// Fonctions de map.c
void printForest(char forest[][100], int n);
int generatePath(char forest[][100], int n, int path[][2]);

// Fonctions de monkey.c
void monkeyGenerator(char forest[][100], int n, Monkey monkeys[], int* nbmonkeys, int x, int y);
void monkeyTurn(Monkey monkeys[], int nbMonkeys, char forest[][100], int n, int path[][2], int crabs[],int* money, int* score);

// Fonctions de crab.c
void crabGenerator(char forest[][100], int path[][2], int crabs[]);
void crabDelete(char forest[][100], int path[][2], int crabIndex, int crabs[], int *money, int *score) ;
void moveCrab(char forest[][100], int n, int path[][2], int pathLength, int crabindex, int crabs[]);
void crabTurn(char forest[][100], int n, int path[][2], int pathLength, int crabs[]);
void crabWave(char forest[][100], int n, int path[][2], int pathLength, int crabs[], int* nbMonkeys, Monkey monkeys[],int *money, int *score,int *vague);

// Fonctions de save.c
void saveGame(char forest[][100], int n, int path[][2], int pathLength, Monkey monkeys[], int nbMonkeys, int *money, int *score,  char *nomsauvegarde, int *vague);
int loadGame(char forest[][100], int *n, int path[][2], int *pathLength, Monkey monkeys[], int *nbMonkeys, int *money, int *score,  char *nomsauvegarde, int *vague);


// Fonctions de menus.c
void mainMenu(char forest[][100], int n, int path[][2], int pathLength, int crabs[], int* nbMonkeys, Monkey monkeys[],int *money, int *score, int *vague);
void explainMenu();
void menuVague(char forest[][100], int n, int path[][2], int pathLength, int crabs[], int* nbMonkeys, Monkey monkeys[],int *money, int *score, int *vague);
void magasin(int *money, int *nbMonkeys, Monkey monkeys[], char forest[][100], int n);
void printMenu(const char *filename);
void choixTaille(int *n);
void menuFin();





#endif