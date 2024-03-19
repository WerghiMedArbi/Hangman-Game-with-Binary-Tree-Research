#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> // For the sleep() function
char MotSecret2[TAILLE_MAX];
char MotSecret[TAILLE_MAX];
char motActuel[TAILLE_MAX];
TArbre trie;


/*****************Display Hangman*******************/
void afficherPendu(int chances, int coupsRestants) {
    if (coupsRestants == 0) {
        // Show the complete hangman
        printf("\033[1m");
        printf("\033[31m");
        printf("\t\t   ____________\n");
        printf("\t\t   |          |\n");
        printf("\t\t   |          O\n");
        printf("\t\t   |         /|\\\n");
        printf("\t\t   |         / \\\n");
        printf("\t\t   |\n");
        printf("\t\t   |\n");
        printf("\t\t___|___\n");
        printf("\033[0m");
    } else {
        printf("\033[1m");
        printf("\033[31m");
        // Show the hangman according to the number of chances left
            switch (chances) {
            
            case 0:
                printf("\t\t   ____________\n");
                printf("\t\t   |          |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t___|___\n");
                break;
            case 1:
                printf("\t\t   ____________\n");
                printf("\t\t   |          |\n");
                printf("\t\t   |          O\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t___|___\n");
                break;
            case 2:
                printf("\t\t   ____________\n");
                printf("\t\t   |          |\n");
                printf("\t\t   |          O\n");
                printf("\t\t   |          |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t___|___\n");
                break;
            case 3:
                printf("\t\t   ____________\n");
                printf("\t\t   |          |\n");
                printf("\t\t   |          O\n");
                printf("\t\t   |         /|\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t___|___\n");
                break;
            case 4:
                printf("\t\t   ____________\n");
                printf("\t\t   |          |\n");
                printf("\t\t   |          O\n");
                printf("\t\t   |         /|\\\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t___|___\n");
                break;
            case 5:
                printf("\t\t   ____________\n");
                printf("\t\t   |          |\n");
                printf("\t\t   |          O\n");
                printf("\t\t   |         /|\\\n");
                printf("\t\t   |         /\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t___|___\n");
                break;
            case 6:
                printf("\t\t   ____________\n");
                printf("\t\t   |          |\n");
                printf("\t\t   |          O\n");
                printf("\t\t   |         /|\\\n");
                printf("\t\t   |         / \\\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t___|___\n");
                break;
    
            // Add cases for remaining chances if needed
            default:
                // Show the hangman with no additional parts
                printf("\t\t   ____________\n");
                printf("\t\t   |          |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t   |\n");
                printf("\t\t___|___\n");
                break;
            
        }
        printf("\033[0m");
    }
}
// Function to read a character from the user
char lireCaractere() {
    char caractere = 0;
    caractere = getchar();
    // Convert to lowercase
    caractere = tolower(caractere);
    // We read the other characters stored one by one until the \n (to erase them)
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
    //If the user wants to quit, return a special value to indicate the exit
    if (caractere == '0') {
        return -1;  // Return a special value to indicate exit
    }
    return caractere;
}



void lireLigne(char* mot) {
    int i = 0;

    while ((mot[i] = getchar()) != '\n') {
        // Use isdigit to check if the character is a digit.
        if (!isdigit(mot[i])) {
            printf("\033[31m");
            printf("\t \t Please enter a number only!\n");
            printf("\033[0m");
            // Clear the input buffer to prevent issues with subsequent inputs
            while (getchar() != '\n');
            i = 0;  // Reset the index to begin input again
        } else {
            // Convert the character to uppercase
            mot[i] = toupper(mot[i]);
            i++;
        }
    }
    mot[i] = '\0';
}



void genererMotSecret(TArbre *Mdico) {
    int length_word;
    char dif[TAILLE_MAX];
    *Mdico = arbreConsVide();
     printf("\n \t Difficulty Level: Enter the length of the word to guess \n\t\t");
    do {
        fgets(dif, TAILLE_MAX, stdin);
        length_word = atoi(dif); // Convert the string to an integer
        if (length_word < 3 || length_word > 13) {
            printf("\033[34m");
            printf("\n \t Please enter a number between 3 and 13 characters:");
            printf("\033[0m");
        }
    } while (length_word < 3 || length_word > 13);

    // Pick a single random word
    if (piocherMot2(MotSecret,length_word) == 1) {
        // Display the secret word
        printf("\033[36m");
        printf("\n \t \t Secret word:");
        printf("\033[8m");
        printf("%s", MotSecret);
        printf("\033[0m");
        printf("     \n");
        // Insert the secret word into the tree (if necessary)
        dicoInsererMot(MotSecret, Mdico);
    printf("\033[0m");
    } else {
        printf("Error retrieving the secret word.\n");
    }
    
}



int jeuxDePendu(TArbre trie) {
    int i, taille;
    char motCache[TAILLE_MAX];
    int coupsRestants, coups;
    char carLu;

    printf("\033[1m"); // bold text
    printf("\033[36m"); // text color    
    printf("\t__________________________________________________________________________________\n");
    printf("\t__________________________________________________________________________________\n");

    printf("\n \t                           Welcome to the Hangman Game                                   \n");

    printf("\t__________________________________________________________________________________\n");
    printf("\t__________________________________________________________________________________\n");
    printf("\033[0m"); // reset text format
    printf("\033[37m"); // reset text color
    printf(" \t \t If you are ready, type '1' to start  \n\t\t");

    carLu = lireCaractere(); 
    //Convert to lowercase
    carLu = tolower(carLu); 
  
    if (carLu == '1') {
        // The user has chosen to start the game
        printf("\033[1m"); // bold text
        printf("\033[36m"); // text color 
        printf(" \t \t                            The game begins                             \n");
        printf("\033[0m"); // reset text format
    } 
    else 
        {
        while (carLu != '1') {
            printf(" \t \t You must type '1' again (anti-robot verification) \n\t\t");
            carLu = lireCaractere();
        }
        printf("\033[1m"); 
        printf("\033[36m"); 
        printf(" \t \t                     The game begins                            \n");
        printf("\033[0m"); 
    }
    strcpy(motCache,MotSecret);
    taille = strlen(motCache);
    printf("\033[1m"); 
    printf("\n \t \tWord length : %d \n", taille);
    printf("\033[0m"); 

    char motActuel[TAILLE_MAX];
    for (i = 0; i < taille; i++) {
        motActuel[i] = '-';
    }
    motActuel[taille] = '\0';
    coupsRestants = taille+2;
    coups = coupsRestants;
    
    printf("\n \t \tNumber of attempts left: %d \n", coupsRestants);
    printf("\033[1m"); 
    printf("\033[36m"); 
    printf("\t__________________________________________________________________________________\n");
    printf("\033[0m");
    

    while (strncmp(motActuel, motCache, taille) != 0 && coupsRestants > 0) {
        printf("\n \t \tWhat is the secret word? ");
        printf("\033[36m"); 
        printf("%s\n", motActuel);
        printf("\033[0m");  
        printf("\t \tYou have %d attempts left\n", coupsRestants);
        printf("\n \t \tPropose a letter: (or press 0 to quit)\n\t\t");


        carLu = lireCaractere();

        if (carLu == -1) {
            // User entered '0', exit the game
            printf("\033[1m");
            printf("\033[31m");
            printf("\t \t                         Goodbye!!\n");
            exit(0); 
        }

    TArbre result = rechercheCaractereTrie(trie, carLu);
    if (result != NULL) {
        printf("\n \t \t Letter found: %c\n", result->caractere);
        int letterFound = 0;

        for (i = 0; i < strlen(motCache); i++) {
            if (motCache[i] == result->caractere && motActuel[i] == '-' ) {
                motActuel[i] = carLu;
                letterFound = 1;
            }
        }

        if (letterFound) {
            coupsRestants--;
            printf("\033[1m");
            printf("\t__________________________________________________________________________________\n");
            printf("\033[0m"); 
    

            if (strncmp(motActuel, motCache, taille) == 0) {
                printf("\033[33m");
                printf("\n\n \t \tCongratulations!  \t The guessed word is ");
                printf("\033[36m");
                printf("%s", motCache);
                printf("\033[0m");
                printf("\033[33m");
                printf("\n \t \tYou won in %d attempts!\n\n", coups - coupsRestants);
                printf("\033[0m");
                printf("\033[1m");
                printf("\033[36m"); 
                printf("\t__________________________________________________________________________________\n");
                printf("\033[0m"); 
            
                coupsRestants = 0;
            }
        }
        else {
            // The letter has already been guessede
            printf("\n \t \t Letter already guessed. You have %d attempts left.\n", coupsRestants); 
            printf("\033[1m");
            printf("\033[36m"); 
            printf("\t__________________________________________________________________________________\n");
            printf("\033[0m"); 
    
        }
    } 
    else {
        // Handling when result is NULL (letter not found in the tree).
        coupsRestants--;
        printf("\n \t \t Letter not found in the tree. You have %d attempts left.\n", coupsRestants);
        afficherPendu(coups - coupsRestants, coupsRestants);    
        printf("\033[1m"); 
        printf("\033[36m"); 
        printf("\t__________________________________________________________________________________\n");
        printf("\033[0m"); 
    
    }    
    }

if (strncmp(motActuel, motCache, taille) != 0) {
    printf("\n\n \t \t  you lost all your attempts! Now enter your final guess(full word)!\n\t\t");
    char finalguess[100]; // Assuming maximum word length is 100 characters
    printf("\033[36m");
    scanf(" \t \t %s", finalguess);
    printf("\033[0m");
    
    if (strcasecmp(finalguess, motCache) == 0) {// It performs a case-insensitive comparison of strings
        printf("\033[33m");
        printf("\n\t\tBravo! You guessed the word correctly!");
        printf("\033[36m");
        printf("\033[0m");

    }
    else{
        printf("\033[31m");
        printf("\t\tSorry but you lost ! the correct word is %s", motCache);
        printf("\033[0m");

    }
    coupsRestants = 0; 
    
}
    return 0;
}


/*********************checkExistence*****************/
int VerifMotexiste(char motSecret[])
{
    FILE *dictionnaire = fopen("Dictionnaire.txt", "r");
    int motTrouve=0;

    char ligne[50];
    while (fgets(ligne, sizeof(ligne), dictionnaire) != NULL)
    {

        // Remove the newline at the end if present.
        if (ligne[strlen(ligne) - 1] == '\n') {
            ligne[strlen(ligne) - 1] = '\0';
        }
      
       // Convert the line to lowercase
        for (int i = 0; ligne[i]; i++) {
            ligne[i] = tolower(ligne[i]);
        }

        // Check if the line matches the word to search for.
        if (strcmp(ligne, motSecret) == 0) {
            motTrouve =1;
        }
    }
    fclose(dictionnaire);
    return(motTrouve);
}

/******************playWithAFriend*****************/

void jouerAvecUnAmi() {
    char motSecret[50];
    char motActuel[50];
    int taille, coupsRestants, i, coups;
    char carLu;
    int Existe;

    // Player 1 entre le mot
    
    printf("\t\tDear Player 1,\n");
    do {
        
        printf("\033[34m");
        printf("\t\tEnter the secret word: ");
        printf("\033[8m");
        scanf("%s",motSecret);
        printf("\033[0m");
        // Convert the secret word to lowercase
            for (int i = 0; motSecret[i]; i++) {
                motSecret[i] = tolower(motSecret[i]);
            }
            Existe = VerifMotexiste(motSecret);
            if (!Existe) {
                printf("\033[31m");
                printf("\n\t\tThe word you entered does not exist in the dictionary. Please try again.\n");
                printf("\033[0m");
            }
    } while (Existe == 0);

    taille = strlen(motSecret);

   // Player 1 enters the number of attempts for Player 2
    do {
        printf("\033[34m");
        printf("\n\t\tPlease enter the number of attempts for your opponent (at least 1): ");
        printf("\033[0m");
        if (scanf("%d", &coups) != 1 || coups < 1) { 
            printf("\033[31m");
            printf("\t\tInvalid input. Please enter a valid number (at least 1).\n");
            printf("\033[0m");
            while (getchar() != '\n'); // Flush the input buffer
        }
    } while (coups < 1);

    coupsRestants = coups;

    // Initialize currentWord with dashes
    for (i = 0; i < taille; i++) {
        motActuel[i] = '-';
    }
    motActuel[i] = '\0'; //Terminate the string with a null character

   // Clear the input buffer
    while (getchar() != '\n');

    // Player 2 tries to guess the word
    printf("\t\tPlayer 2, it's your turn to guess the word!\n");
   // Main loop of the game
    while (coupsRestants > 0) {
        printf("\n\t\tSecret word: %s\n", motActuel);
        printf("\t\tYou have %d attempts left\n", coupsRestants);
        printf("\033[34m");
        printf("\t\tPropose a letter: (or press 0 to quit)\n\t\t");
        printf("\033[0m");

        // Read input from Player 2
        scanf(" %c", &carLu);
       //Convert the letter to lowercase
        carLu = tolower(carLu);
        if (carLu == '0') {
            // Player 2 chooses to exit the game
            printf("👣 Goodbye!\n");
            exit(0);
        }
        int letterFound = 0; // Move the declaration inside the loop

        // Check if the proposed letter is in the word.
        for (i = 0; i < taille; i++) {
            if (motSecret[i] == carLu && motActuel[i] == '-') {
                motActuel[i] = carLu;
                letterFound = 1; // Set letterFound to 1 if the letter is found
            }
        }

        if (strncmp(motActuel, motSecret, taille) == 0) {
            printf("\033[33m");
            printf("\t\tCongratulations! The guessed word is %s\n", motSecret);
            printf("\t\tYou won in %d attempts!\n", coups - coupsRestants + 1);
            printf("\033[0m");
            exit(0);
        }

        if (letterFound) {
            coupsRestants--;
        } else {
            // The proposed letter is not in the word
            coupsRestants--;
            printf("\t\tLetter not found. You have %d attempts left.\n", coupsRestants);
            afficherPendu(coups - coupsRestants, coupsRestants);
        }
    }
    // Player 2 did not guess the word within the attempts.
    printf("\033[31m");
    printf("\t\tSorry, you ran out of attempts. The word was %s\n", motSecret);
    printf("\033[0m");
}
