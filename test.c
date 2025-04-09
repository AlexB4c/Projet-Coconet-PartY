#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TREE "\U0001F334"   // Tree emoji
#define PATH "\U0001F7EB"   // Brown square emoji (path)
#define MONKEY "\U0001F412" // Monkey emoji
#define CROWN "\U0001F451" // couronne
#define FLAG "\U0001F6A9" // drapeau rouze

// Function to print the forest
void printForest(char forest[][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%s", forest[i][j] == 'T' ? TREE : (forest[i][j] == 'P' ? PATH : MONKEY));
        }
        printf("\n");
    }
}

// Function to generate a procedural path in the forest
void generatePath(char forest[][100], int n) {
    int x = n/2, y = 0; // Start middle left
    int up=0;
    int down=0;
    int i=0;
    while (x < n && y < n) {
        forest[x][y] = 'P'; // Mark the path
        if (y == n - 1) break; // Stop when reaching the bottom-right corner

        // Randomly decide the next step (down or right)
        if (x < n - 1 && (rand() % 2 == 0) && up==0) {
            x++; // down
            down=1;
            //path[i]="down";
            i++;
        }
        else if (x < n - 1 && (rand() % 2 == 0) && down==0){
            x--; // up
            up=1;
            //path[i]="up";
            i++;
        }
        else {
            y++;
            //path[i]="down";
            i++;
            forest[x][y] = 'P';
            y++; // Move right
            //path[i]="down";
            i++;
            up=0; // reset 
            down=0;

        }
    }
    forest[x][y] = 'C';

}

//void printPath(char* path[]){
//    int i=0;
//    while (i>=0 && i<200 ){
//        
//        printf("%s\n",path[i]);
//        i++;
//    }
//}

int main() {
    int n;
    printf("Enter the size of the forest (n): ");
    scanf("%d", &n);

    if (n > 100) {
        printf("Size too large! Please enter a value <= 100.\n");
        return 1;
    }
    //char path[200][10];
    char forest[100][100];

    // Initialize the forest with trees
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            forest[i][j] = 'T'; // 'T' represents a tree
        }
    }


    // Generate a procedural path
    srand(time(NULL)); // Seed the random number generator
    generatePath(forest, n);

    // Print the forest
    printForest(forest, n);
    return 0;
}