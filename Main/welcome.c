#include <stdio.h>
#include <unistd.h>
void afficherBienvenue() {
    printf("\033[1m"); // bold text
    printf("\033[36m");
    printf("\t__________________________________________________________________________________\n");
    printf("\t__________________________________________________________________________________\n"); 
    printf("\n\t                  Algorithm Project Hangman Game 1 ING02 IDL 2024                                           \n");
    printf("\t__________________________________________________________________________________\n");
    printf("\t__________________________________________________________________________________\n\n");
    printf("\033[31m");
    printf("  \t\t\t _    _                                          \n");
    fflush(stdout);
    sleep(1);  // Wait for 1 second
    printf("  \t\t\t| |  | |                                         \n");
    fflush(stdout);
    sleep(1);
    printf(" \t\t\t| |__| | __ _ _ __   __ _ _ __ ___   __ _ _ __  \n");
    fflush(stdout);
    sleep(1);
    printf(" \t\t\t|  __  |/ _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\ \n");
    fflush(stdout);
    sleep(1);
    printf(" \t\t\t| |  | | (_| | | | | (_| | | | | | | (_| | | | |\n");
    fflush(stdout);
    sleep(1);
    printf(" \t\t\t|_|  |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n");
    fflush(stdout);
    sleep(1);
    printf("  \t\t\t                     __/ |                      \n");
    fflush(stdout);
    sleep(1);
    printf("  \t\t\t                    |___/                       \n");
    fflush(stdout);
    sleep(1);
    printf("\033[0m"); // reset text format 
    printf("\033[37m");
    printf("\n\t\t Welcome to our Hangman Game!\n\n");
    printf("\t\t Are you the daring administrator creating complex words (type A)\n");
    printf("\t\t or the impatient player ready to unravel the mystery (type J)?\n");
    printf("\t\t Let the word game begin!\n");
}
char obtenirRole() {
    char choix;
    int c;
    do {
        printf("\033[94m"); 
        printf("\t\t Please choose your role (A/J): ");
        scanf(" %c", &choix);
        printf("\033[0m");
        // Flush the input buffer
        while ((c = getchar()) != '\n' && c != EOF);
        // Check if the user input is a single character and matches 'A', 'a', 'J', or 'j'
        if (choix != 'A' && choix != 'a' && choix != 'J' && choix != 'j') {
            printf("\033[31m");
            printf("\t\t Invalid input. "); 
            printf("Please enter either 'A' or 'J'.\n");
            printf("\033[0m");
        }
    } while (choix != 'A' && choix != 'a' && choix != 'J' && choix != 'j');
    //Convert the choice to uppercase before returning it
    choix = toupper(choix);
    return choix;
}

