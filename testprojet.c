#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define TREE "\U0001F334"   // Tree emoji
#define PATH "\U0001F7EB"   // Brown square emoji (path)
#define MONKEY "\U0001F412" // Monkey emoji
#define CROWN "\U0001F451"  // Crown emoji
#define CRAB "\U0001F980"  // Crabe emoji
#define FLAG "\U0001F6A9"   // Drapeau rouge emoji 🚩


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



void placeMonkeys(char forest[][100], int n) {
    int monkeys;
    printf("Combien de singes voulez-vous placer ? ");
    scanf("%d", &monkeys);

    for (int i = 0; i < monkeys; i++) {
        int x, y;
        printf("Position du singe #%d (ligne colonne): ", i + 1);
        scanf("%d %d", &x, &y);

        if (x >= 0 && x < n && y >= 0 && y < n) {
            if (forest[x][y] == 'T') {
                forest[x][y] = 'M';
            } else {
                printf(" Emplacement non valide (occupé ou sur un chemin), essayez encore.\n");
                i--; // Refaire cette itération
            }
        } else {
            printf(" Coordonnées hors limites. Essayez encore.\n");
            i--;
        }
    }
}



void moveCrab(char forest[][100], int n, int path[][2], int pathLength) {
    for (int i = 0; i < pathLength; i++) {
        int x = path[i][0];
        int y = path[i][1];

        // Vérifie s'il est attaqué par un singe
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && ny >= 0 && nx < n && ny < n && forest[nx][ny] == 'M') {
                    printf("Le crabe a été attaqué à (%d, %d) !\n", x, y);
                    forest[x][y] = 'P';
                    return;
                }
            }
        }

        // Affiche l'état
        forest[x][y] = 'R';
        printForest(forest, n);
        sleep(1);
        if ((forest[x][y] != 'C')  && !(x==n/2 && y==0)) forest[x][y] = 'P'; // remettre la route
        if ((forest[x][y] != 'C') && (x==n/2 && y==0))  forest[x][y] = 'F'; // remettre le drapeau
        if ((forest[x][y] == 'C') && (x==n/2 && y==0))  forest[x][y] = 'C'; // laisser la couronne

    }

    printf("Le crabe a atteint la couronne ! Victoire des crustacés !\n");
}



int main() {
        int n;
        srand(time(NULL));
        n=rand() % 40 + 10; // Taille de la forêt entre 10 et 50
        char forest[100][100];
    
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                forest[i][j] = 'T';
    
        srand(time(NULL));
        int path[10000][2]; // Coordonnées du chemin
        int pathLength=generatePath(forest, n,path);
    
        printf("\nVoici la carte avant de placer les singes :\n");
        printForest(forest, n);
    
        placeMonkeys(forest, n);
        moveCrab(forest, n, path, pathLength);  // Le crabe se déplace avant toute attaque
        printForest(forest, n);
    
        return 0;
 }
