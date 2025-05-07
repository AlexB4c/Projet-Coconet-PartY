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





void printForest(char forest[][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            switch(forest[i][j]) {
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
    int x = n / 2, y = 0;  // Départ au milieu de la première colonne
    int up = 0, down = 0;
    int pathLength = 0;

    forest[x][y] = 'F'; // Drapeau de départ


    // Boucle jusqu'à ce qu'on atteigne la dernière ligne ou colonne
    while (y < n - 1) {  // Continue tant que y n'a pas atteint la fin
        // Ajout des coordonnées du chemin dans path
        path[pathLength][0] = x;
        path[pathLength][1] = y;
        pathLength++;

        if (x < n - 1 && rand() % 2 == 0 && up == 0) {
            x++;  // Descendre
            down = 1;
        } else if (x > 0 && rand() % 2 == 0 && down == 0) {
            x--;  // Monter
            up = 1;
        } else {
            y++;  // Avancer d'une case à droite
            forest [x][y] = 'P';  // Marque la case comme faisant partie du chemin
            path[pathLength][0] = x;
            path[pathLength][1] = y;
            pathLength++;
            y++;
            up = 0;
            down = 0;
        }

        forest[x][y] = 'P';  // Marque la case comme faisant partie du chemin
    }

    // Ajoute la dernière case avec la couronne
    path[pathLength][0] = x;
    path[pathLength][1] = y;
    pathLength++;
    forest[x][y-1] = 'C';  // Placer la couronne (dernière case)

    return pathLength;  // Retourne la longueur du chemin
}

void crabDelete(char forest[][100], int path[][2],int crabindex, int crabs[]){
    int x = path[crabs[crabindex]][0];
    int y = path[crabs[crabindex]][1];
    forest[x][y] = 'P'; // Remettre la case à la route
    int i=1;
    while ((crabindex+i) != -1)
    {
        crabs[crabindex+i-1] = crabs[crabindex+i]; // Décaler les crabes
        i++;
    }
    crabs[crabindex+i-1] = -1;
}

void moveCrab(char forest[][100], int n, int path[][2], int pathLength, int crabindex, int crabs[]) {
    int x = path[crabs[crabindex]][0];
    int y = path[crabs[crabindex]][1];

    
    crabs[crabindex] +=1 ; // Le crabe avance d'une case
    forest[x][y] = 'P'; // Remettre la case à la route
    
    x = path[crabs[crabindex]][0];
    y = path[crabs[crabindex]][1];
    forest[x][y] = 'R'; // Marque la case suivante comme occupée par le crabe

    // Vérifie si le crabe a atteint la fin du chemin
    if (crabindex == pathLength ) {
        printf("Le crabe a atteint la couronne ! Victoire des crustacés !\n");
        exit(0);
    }

}

void monkeyTurn(Monkey monkeys[], int nbmonkeys, char forest[][100], int n, int path[][2], int crabs[]){
    for (int i = 0; i < nbmonkeys; i++) {
        if (monkeys[i].actif == 1) { // Si le singe est actif


            if (monkeys[i].cooldown > 0) {
                monkeys[i].cooldown--; // Réduire le cooldown
                continue; // Passer au prochain singe
            }

            int x = monkeys[i].x;
            int y = monkeys[i].y;

            // Vérifie si un crabe est dans la portée d'attaque
            int attacked = 0; // Variable pour s'assurer qu'un singe n'attaque qu'un seul crabe
            for (int dx = -monkeys[i].range; dx <= monkeys[i].range; dx++) {
                for (int dy = -monkeys[i].range; dy <= monkeys[i].range; dy++) {
                    if (dx == 0 && dy == 0) continue; // Ignore la case actuelle
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && ny >= 0 && nx < n && ny < n) { // Vérifie les limites
                        
                        if (forest[nx][ny] == 'R' && attacked == 0 ) { // Si un crabe est trouvé
                            for (int k = 0; crabs[k] != -1; k++) {
                                if (path[crabs[k]][0] == nx && path[crabs[k]][1] == ny) { // on cherche l'indice du crabe
                                    crabDelete(forest, path, k, crabs);
                                    monkeys[i].cooldown = monkeys[i].cooldownMax; // Réinitialiser le cooldown
                                    attacked = 1; // Marquer que le singe a attaqué un crabe
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void monkeyGenerator(char forest[][100], int n, Monkey monkeys[], int nbmonkeys, int x, int y){
    Monkey newMonkey;
    newMonkey.x = x;
    newMonkey.y = y;
    newMonkey.range = 1; // Portée d'attaque par défaut
    newMonkey.cooldownMax = 3; // Cooldown par défaut
    newMonkey.cooldown = 0; // Cooldown initialisé à 0
    newMonkey.actif = 1; // set le singe comme actif
    monkeys[nbmonkeys] = newMonkey; // Ajoute le singe au tableau
}

void crabGenerator(char forest[][100], int path[][2], int crabs[]){
    int i=0;
    while (crabs[i] != -1){
        i++;
    } // Trouver le premier indice vide
    crabs[i] = 1; // Ajoute un crabe à la position de départ
    forest[path[1][0]][path[1][1]] = 'R'; // Marque la première case comme occupée par le crabe
}
    

void crabTurn(char forest[][100], int n, int path[][2], int pathLength, int crabs[]){
    int i=0;
        while(crabs[i] != -1){
            moveCrab(forest, n, path, pathLength,crabs[i], crabs);
            printf("Crabe %d a avancé\n", i);
            i++;
        }

}


void crabWave(char forest[][100], int crabNumber, int n, int path[][2], int pathLength, int crabs[], int nbMonkeys, Monkey monkeys[]){
    int crabalive = 1; // Variable pour vérifier si au moins un crabe est vivant
    crabGenerator(forest, path, crabs); // on génère un premier crabe
    printf("premier crabe posé\n");
    printForest(forest, n);
    int count=1;
    crabTurn(forest, n, path, pathLength, crabs);
    printf("crabeturn\n");
    monkeyTurn(monkeys, nbMonkeys, forest, n, path, crabs); // on fait jouer les singes
    printf("monkeyturn\n");

    while (count < crabNumber || crabalive) {
            if ((rand() % 3 == 0) && (count < crabNumber)) {
                crabGenerator(forest, path, crabs);
                count++;
            } // on espace les crabes de façon aléatoire
        sleep(1);
        crabTurn(forest, n, path, pathLength, crabs); // on fait avancer les crabes
        printForest(forest, n);
        monkeyTurn(monkeys, nbMonkeys, forest, n, path, crabs); // on fait jouer les singes
            if (crabs[0] == -1){
                crabalive = 0;
            }
    }
}



int main() {
        int n;
        srand(time(NULL));
        n = rand() % 40 + 10; // Taille de la forêt entre 10 et 50
        char forest[100][100];
    
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                forest[i][j] = 'T';
    
        srand(time(NULL));
        int path[10000][2]; // Coordonnées du chemin
        int pathLength=generatePath(forest, n,path);
    
        printf("\nVoici la carte avant de placer les singes :\n");
        printForest(forest, n);
    

        int crabs[100]; // Tableau pour suivre les positions des crabes, initialisé à -1
        for (int i=0; i<100; i++){
            crabs[i] = -1; // Initialiser tous les crabes à -1
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
