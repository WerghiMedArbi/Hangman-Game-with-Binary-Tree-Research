#include <stdio.h>

int afficherMenu(char role) {
    int choixMenu;
    int lu;
    printf("\033[1m"); // bold text
    printf("\033[36m"); // text color

    printf("\n\t__________________________________________________________________________________\n");
    printf("\t__________________________________________________________________________________\n");

    printf("\n\t                                  Menu                                          \n");

    printf("\t__________________________________________________________________________________\n");
    printf("\t__________________________________________________________________________________\n");
    printf("\033[0m"); // reset text format

    if (role == 'A' || role == 'a') {
        printf("\033[1m"); 
        printf("\n\t\t\t  | Dictionary Management :\n");
        printf("\033[0m"); 
        printf("\n\t\t\t\t\t 1. Display content");
        printf("\n\t\t\t\t\t 2. Search for a word");
        printf("\n\t\t\t\t\t 3. Add a word");
        printf("\n\t\t\t\t\t 4. Delete a word");
        printf("\n\t\t\t\t\t 5. Display tree \n");

        printf("\033[1m"); 
        printf("\n\t\t\t  | Play :\n");
        printf("\033[0m"); 
        printf("\n\t\t\t\t 6. Start a new game as a solo player\n");
        printf("\n\t\t\t\t 7. Start a new game with two players\n");

        printf("\033[1m");
        printf("\033[36m");
        printf("\n\t\t\t  | Exit(0)\n\n");
        printf("\033[0m");
    } else if (role == 'J' || role == 'j') {
        printf("\033[1m");
        printf("\n\t\t\t  | Play :\n");
        printf("\033[0m");
        printf("\n\t\t\t\t 1. Start a new game as a solo player\n");
        printf("\n\t\t\t\t 2. Start a new game with two players\n");

        printf("\033[1m"); 
        printf("\033[36m");
        printf("\n\t\t\t  | Exit(0)\n\n");
        printf("\033[0m"); 
    }

    do {
        printf("\033[1m"); 
        printf("\t\t->");
        printf("\033[0m"); 
        printf("Your choice:");
        lu = scanf("%d", &choixMenu);
        // Check if scanf succeeded in reading an integer
        if (lu != 1) {
            printf("\033[31m");
            printf("\t\tPlease enter a valid number.\n");
            printf("\033[0m");
            // Clears the input buffer
            while (getchar() != '\n');
        } else if ((role == 'A' || role == 'a') && (choixMenu < 0 || choixMenu > 7)) {
            printf("\033[31m");
            printf("\t\tPlease choose a number from 0 to 7.\n");
            printf("\033[0m");
        } else if ((role == 'J' || role == 'j') && (choixMenu < 0 || choixMenu > 2)) {
            printf("\033[31m");
            printf("\t\tPlease choose either 0, 1 or 2.\n");
            printf("\033[0m");
        }
    } while (lu != 1 || ((role == 'A' || role == 'a') && (choixMenu < 0 || choixMenu > 7)) || ((role == 'J' || role == 'j') && (choixMenu < 0 || choixMenu > 2)));

    return choixMenu;
}
