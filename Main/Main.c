#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "arbre.h"
#include "arbre.c"
#include "dico.h"
#include "dico.c"
#include "pendu.c"
#include "pendu.h"
#include "welcome.c"
#include "Menu.c"
#include <time.h>


int main() {

/***************Last execution Time ***************/

    // Declaration of variables to store the hour, minute, second, day, month, and year
    int h, min, s, day, mois, an;
    // Open the file in write mode
    FILE *fichierTime = fopen("Time.txt", "w");
    // Get the current time.
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    // Extracting the hour, minute, second, day, month, and year.
    h = local->tm_hour;
    min = local->tm_min;
    s = local->tm_sec;
    day = local->tm_mday;
    mois = local->tm_mon + 1;  // Months start from 0, so we add 1.
    an = local->tm_year + 1900;  // tm_year represents the number of years since 1900.
    // Writing the date to the file
    fprintf(fichierTime, "Last Execution\n");
    fprintf(fichierTime, "Date : %02d/%02d/%d\n", day, mois, an);
    fprintf(fichierTime, "Time : %02d:%02d:%d\n", h, min, s);
    fclose(fichierTime);
/****************************************************/
    char role;
    char motRech[50];
    char motAajouter[50];
    char motAsupprimer[50];
    int choix;
    TArbre arbre;
/*******************Display Welcome***************/
    afficherBienvenue();
/********************Traiter Role****************/
    role = obtenirRole();
    do {
/*******************afficher Menu ****************/
        choix = afficherMenu(role);
        arbre = arbreConsVide();
        FILE *fichierMots = fopen("Dictionnaire.txt", "r");
        if (fichierMots == NULL) {
             printf("\033[31m");
             fprintf(stderr, "Unable to open the file Dictionnaire.txt.\n");
             printf("\033[0m");
            return 1;
        }

        char ligne[TAILLE_MAX];

        while (fgets(ligne, TAILLE_MAX, fichierMots) != NULL) {
            size_t len = strlen(ligne);
            if (len > 0 && ligne[len - 1] == '\n') {
                ligne[len - 1] = '\0';
            }

            dicoInsererMot(ligne, &arbre);
        }
        fclose(fichierMots);

/*************Dictionary operation***************/
        if (choix == 1) {
            if(role=='A'||role=='a')
            {
                afficherMotsDictionnaire();
            }
            else 
            {
            genererMotSecret(&arbre);
            jeuxDePendu(arbre);
            arbreSuppr(&arbre);
            }
        }
        else if (choix == 2) {
            if(role=='A'||role=='a'){
             printf("\033[34m");
             printf("\t\tEnter the word to search for: ");
             printf("\033[0m");
           
            scanf("%s", motRech);
            for (int i = 0; motRech[i]; i++) {
                motRech[i] = tolower(motRech[i]);
            }
            if (MotExiste(motRech) == 1) {
                 printf("\033[33m");
                 printf("\t\tWord exists in the dictionary\n");
                printf("\033[0m");
               
            }
            else {
                 printf("\033[31m");
                printf("\t\tWord does not exist in the dictionary\n");
                 printf("\033[0m");
               
            }
            }
            else {
                jouerAvecUnAmi(); 
            }
        }
        else if (choix == 3) {
            printf("\033[34m");
            printf("\t\tEnter the word to add to the dictionary: ");
            printf("\033[0m");
            scanf("%s", motAajouter);
            AjouterMot(motAajouter);
        }
        else if (choix == 4) {
            printf("\033[34m");
           printf("\t\tEnter the word to delete from the dictionary: ");
           printf("\033[0m");
            scanf("%s", motAsupprimer);
            SupprimerMot(motAsupprimer);
        }
        else if (choix == 5) {
            afficherArbre(arbre);
        }
        else if (choix == 6) {
            genererMotSecret(&arbre);
            jeuxDePendu(arbre);
            arbreSuppr(&arbre);
        }
        else if (choix == 7) {
           jouerAvecUnAmi();
        }
        
    } while (choix != 0);

    return 0;  
}