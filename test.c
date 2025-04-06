#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TREE "\U0001F334"   // Tree emoji
#define PATH "\U0001F7EB"   // Brown square emoji (path)
#define MONKEY "\U0001F412" // Monkey emoji

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
    int x = 0, y = n/2; // Start at the top-left corner
    while (x < n && y < n) {
        forest[x][y] = 'P'; // Mark the path
        if (x == n - 1 && y == n - 1) break; // Stop when reaching the bottom-right corner

        // Randomly decide the next step (down or right)
        if (x < n - 1 && (y == n - 1 || rand() % 2 == 0)) {
            x++; // Move down
        } else {
            y++; // Move right
        }
    }
}

int main() {
    int n;
    printf("Enter the size of the forest (n): ");
    scanf("%d", &n);

    if (n > 100) {
        printf("Size too large! Please enter a value <= 100.\n");
        return 1;
    }

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