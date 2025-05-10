#include "game.h"

void printMenu(const char *filename) {
    FILE *file = fopen(filename, "r"); // Open the file in read mode
    if (file == NULL) {
        perror("Error opening file"); // Print an error message if the file cannot be opened
        return;
    }

    char line[256]; // Buffer to store each line of the file
    while (fgets(line, sizeof(line), file)) { // Read the file line by line
        printf("%s", line); // Print each line to the console
    }

    fclose(file); // Close the file
}

void menuVague(char forest[][100], int n, int path[][2], int pathLength, int crabs[], int* nbMonkeys, Monkey monkeys[],int *money, int *score, int *vague) {
    int choice;
    do{
        system("clear"); // Clear the terminal screen
        if (*vague > 9) {
            menuFin(); //game over
        }
        printForest(forest, n); // Print the forest
        printMenu("menuVague.txt"); // Print the menu from the file
        printf("\n--- Vague actuelle %d ---\n", *vague + 1);

        printf("\n entrez votre choix: ");
        scanf("%d", &choice); // Get user input

        switch (choice) {
            case 1: // continue
                crabWave(forest, n, path, pathLength, crabs, nbMonkeys, monkeys, money, score, vague);
                break;
            case 2: // shop
                magasin(money, nbMonkeys, monkeys, forest, n);
                menuVague(forest, n, path, pathLength, crabs, nbMonkeys, monkeys, money, score, vague);
                break;
            case 3: // save game
                char saveName[256];
                printf("Entrez le nom de la sauvegarde(ex: maSauvegarde.txt): ");
                scanf("%s", saveName);
                saveGame(forest, n, path, pathLength, monkeys, *nbMonkeys, money, score, saveName, vague);
                printf("Partie sauvegardée sous le nom %s\n", saveName);
                exit(0); // Exit the program
                break;
            case 4: //quit without saving
                exit(0); // Exit the program
                break;
            default:
                printf("choix invalide réessayer\n");
                break;
        }
    }while(choice != 1 && choice != 2 && choice != 3 && choice != 4);
    
    
        
    
}

void choixTaille(int *n) {
    system("clear"); // Clear the terminal screen
    int choice;
    printMenu("choixTaille.txt"); // Print the menu from the file

    printf("\nEntrez votre choix (1 à 3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            *n = (rand() % 5) + 6; // Generate a random number between 6 and 10
            printf("Taille de la forêt définie à %d.\n", *n);
            break;
        case 2:
            *n = (rand() % 11) + 10; // Generate a random number between 10 and 20
            printf("Taille de la forêt définie à %d.\n", *n);
            break;
        case 3:
            *n = (rand() % 11) + 20; // Generate a random number between 20 and 30
            printf("Taille de la forêt définie à %d.\n", *n);
            break;
        default:
            printf("Choix invalide. Veuillez réessayer.\n");
            choixTaille(n); // Recurse until a valid choice is made
            break;
    }
}

void mainMenu(char forest[][100], int n, int path[][2], int pathLength, int crabs[], int* nbMonkeys, Monkey monkeys[],int *money, int *score, int *vague) {
    system("clear"); // Clear the terminal screen
    int choice;

    printMenu("menuPrincipal.txt"); // Print the menu from the file
    do{
        printf("\n Enter your choice: ");
        scanf("%d", &choice); // Get user input
    }while(!(choice >= 1 && choice <= 5));

    switch (choice) {
        case 1: // new game
            choixTaille(&n); // Obtenir la taille de la forêt
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    forest[i][j] = 'T';
                }
            }
            pathLength = generatePath(forest, n, path);
            printf("Carte générée :\n");
            printForest(forest, n);
            int x=-1; int y=-1;
            int valide = 0;
            do{
                int x, y; 
                printf("placez votre premier singe (ligne colonne):\n");
                scanf("%d %d", &x, &y);
                if (x >= 0 && x < n && y >= 0 && y < n) {
                    if (forest[x][y] != 'P') {
                        valide = 1;
                        printf("Singe %d %d\n", x, y);
                        monkeyGenerator(forest, n, monkeys, nbMonkeys, x, y);
                        printf("Singe placé avec succès !\n");
                    } else {
                        printf("Invalide. Réessaye.\n");
                    }
                } else {
                    printf("Invalide. Réessaye.\n");
                }
            }while (!valide);
            system("clear");
            printForest(forest, n);
            printf("Voici la carte avant le début de la partie :\n");
            
            crabWave(forest, n, path, pathLength, crabs, nbMonkeys, monkeys, money, score, vague);
            break;



        case 2: // load game
            char saveName[256];
            printf("Entrez le nom de la sauvegarde (extension comprise) : ");
            scanf("%s", saveName);
            if (!loadGame(forest, &n, path, &pathLength, monkeys, nbMonkeys, money, score, saveName, vague)) {
                printf("Échec du chargement. Retour au menu principal...\n");
                mainMenu(forest, n, path, pathLength, crabs, nbMonkeys, monkeys, money, score, vague);
            }else{
                menuVague(forest, n, path, pathLength, crabs, nbMonkeys, monkeys, money, score, vague);
            }
                
            break;
        case 3: // explain menu
            explainMenu();
            mainMenu(forest, n, path, pathLength, crabs, nbMonkeys, monkeys, money, score, vague);
            break;
        case 4:
            exit(0); // Exit the program
            break;
        case 5:
            printf("😡 Arrêtez de chercher des bugs !\n"); // Exit the program
            break;
        default:
            printf("choix invalide réessayer\n");
            break;
    }
}

void explainMenu() {
    system("clear"); // Clear the terminal screen
    printMenu("explain.txt"); // Print the explanation from the file


    printf("\nappuyer sur entrer pour continuer...\n");
    getchar(); // Wait for user input
    getchar(); // To handle the newline left by previous scanf

}

void menuFin() {
    system("clear"); // Clear the terminal screen
    printMenu("fin.txt"); // Print the explanation from the file
    exit (0); // Exit the program
}

void magasin(int *money, int *nbMonkeys, Monkey monkeys[], char forest[][100], int n) {
    printForest(forest, n); // Print the forest
    printf("\n voici l'état de la forêt :\n");
    printf("\n--- Magasin ---\n");
    printf("Votre solde: %d bananes écrasées\n", *money);
    printf("Que voulez-vous faire ?\n");
    printf("1. Acheter un singe (30 bananes écrasées)\n");
    printf("2. Quitter le magasin\n");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        if (*money < 30) {
            printf("Vous n'avez pas assez de bananes écrasées pour acheter un singe.\n");
            return;
        }

        int x, y;
        int valide = 0;
        do{
            printf("Entrez les coordonnées du singe (ligne colonne) : ");
            scanf("%d %d", &x, &y);
            if(x >= 0 && x < n && y >= 0 && y < n) {
                if (forest[x][y] != 'P' && forest[x][y] != 'M') {
                    valide = 1;
                    monkeyGenerator(forest, n, monkeys, nbMonkeys, x, y);
                    *money -= 50; 
                    printf("Singe acheté avec succès !\n");
                }else {
                    printf("Emplacement invalide (occupé ou hors limites).\n");
                }
            }else {
            printf("Emplacement invalide (occupé ou hors limites).\n");
            }
        }while (valide == 0);}
     
        
    else if (choice == 2) {
        printf("Vous avez quitté le magasin.\n");
    } else {
        printf("Choix invalide.\n");
    }
}

