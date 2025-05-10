#ifndef GAME_H
#define GAME_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define TREE "\U0001F334"   // Tree emoji
#define PATH "\U0001F7EB"   // Brown square emoji (path)
#define MONKEY "\U0001F412" // Monkey emoji
#define CROWN "\U0001F451"  // Crown emoji
#define CRAB "\U0001F980"  // Crab emoji
#define FLAG "\U0001F6A9"   // Red flag emoji 

typedef struct{
    int x;
    int y; 
    int range; // range attack
    int cooldownMax; // cooldown max
    int cooldown; // curent cooldown 
    int actif ; // 1 if active, else 0
}Monkey;

// Functions of map.c
void printForest(char forest[][100], int n);
int generatePath(char forest[][100], int n, int path[][2]);

// Functions of monkey.c
void monkeyGenerator(char forest[][100], int n, Monkey monkeys[], int* nbmonkeys, int x, int y);
void monkeyTurn(Monkey monkeys[], int nbMonkeys, char forest[][100], int n, int path[][2], int crabs[],int* money, int* score);

// Functions of crab.c
void crabGenerator(char forest[][100], int path[][2], int crabs[]);
void crabDelete(char forest[][100], int path[][2], int crabIndex, int crabs[], int *money, int *score) ;
void moveCrab(char forest[][100], int n, int path[][2], int pathLength, int crabindex, int crabs[]);
void crabTurn(char forest[][100], int n, int path[][2], int pathLength, int crabs[]);
void crabWave(char forest[][100], int n, int path[][2], int pathLength, int crabs[], int* nbMonkeys, Monkey monkeys[],int *money, int *score,int *vague);

// Functions of save.c
void saveGame(char forest[][100], int n, int path[][2], int pathLength, Monkey monkeys[], int nbMonkeys, int *money, int *score,  char *nomsauvegarde, int *vague);
int loadGame(char forest[][100], int *n, int path[][2], int *pathLength, Monkey monkeys[], int *nbMonkeys, int *money, int *score,  char *nomsauvegarde, int *vague);


// Functions of menus.c
void mainMenu(char forest[][100], int n, int path[][2], int pathLength, int crabs[], int* nbMonkeys, Monkey monkeys[],int *money, int *score, int *vague);
void explainMenu();
void menuVague(char forest[][100], int n, int path[][2], int pathLength, int crabs[], int* nbMonkeys, Monkey monkeys[],int *money, int *score, int *vague);
void magasin(int *money, int *nbMonkeys, Monkey monkeys[], char forest[][100], int n);
void printMenu(const char *filename);
void choixTaille(int *n);
void menuFin();


#endif