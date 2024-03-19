#include <unistd.h>

int nombreAleatoire(int nombreMax)
{
    return (rand() % nombreMax+1);
}
/**********Give randomly a word from the dictionary of a given length*******/
int piocherMot2(char *motPioche, int longueurDesiree)
{
    FILE *dico = fopen("Dictionnaire.txt", "r");

    if (dico == NULL) {
        printf("\033[31m");
        printf("\n\t\tUnable to load the word dictionary");
        printf("\033[0m");
        return 0;
    }

    // Count the number of words in the file with the desired length
    int nombreMots = 0;
    char motCourant[100]; // Assuming maximum word length of 100 characters
    while (fscanf(dico, "%s", motCourant) == 1) {
        if (strlen(motCourant) == longueurDesiree) {
            nombreMots++;
        }
    }

    if (nombreMots == 0) {
        printf("\033[31m");
        printf("\n\t\tNo words found with the specified length");
        printf("\033[0m");
        fclose(dico);
        return 0;
    }

    // Generate a random number between 0 and (nombreMots - 1)
    srand(time(NULL));
    int numMotChoisi = rand() % nombreMots;

    // Reset the file pointer to the beginning of the file
    rewind(dico);

    // Read the file until the chosen word with the desired length
    nombreMots = 0;
    while (fscanf(dico, "%s", motCourant) == 1) {
        if (strlen(motCourant) == longueurDesiree) {
            if (nombreMots == numMotChoisi) {
                strcpy(motPioche, motCourant);
                fclose(dico);
                return 1;
            }
            nombreMots++;
        }
    }

    printf("\033[31m");
    printf("\t\tError retrieving the secret word.\n");
    printf("\033[0m");
    fclose(dico);
    return 0;
}
/***********Give randomly a word from the dictionary**********/
int piocherMot(char *motPioche)
{
    FILE *dico = fopen("Dictionnaire.txt", "r");

    if (dico == NULL) {
        printf("\033[31m");
        printf("\n\t\tUnable to load the word dictionary");
        printf("\033[0m");

        return 0;
    }

    // Count the number of words in the file
    int nombreMots = 0;
    while (fscanf(dico, "%s", motPioche) == 1) {
        nombreMots++;
    }

    // Generate a random number between 0 and (nombreMots - 1)
    srand(time(NULL));
    int numMotChoisi = rand() % nombreMots;

    // Reset the file pointer to the beginning of the file
    rewind(dico);

    // Read the file until the chosen word
    for (int i = 0; i < numMotChoisi; i++) {
        if (fscanf(dico, "%s", motPioche) != 1) {
            printf("\033[31m");
            printf("\t\tError retrieving the secret word.\n");
            printf("\033[0m");
            fclose(dico);
            return 0;
        }
    }

    fclose(dico);
    return 1;
}

/*************Insert word into tree******************/
void insererMot(char *mot, TArbre *noeud)
{
    if (*noeud != NULL)
    {
        if (mot[0] != '\0') // End of word not reached
        {
            if ((*noeud)->caractere == mot[0])
            {
                mot++; //delete first character
                insererMot(mot, &((*noeud)->filsGauche));//go down left
            }
            else
            {
                if((*noeud)->caractere > mot[0]){ //alphabetical order
                        TArbre n = arbreCons(mot[0], 0, NULL, *noeud);
                        mot++;
                        *noeud = n;
                        insererMot(mot, &((*noeud)->filsGauche));
                }else{
                    if ((*noeud)->filsDroit != NULL)//go down right
                    {
                        insererMot(mot, &((*noeud)->filsDroit));
                  
                    }
                    else //character does not exist
                    {
                        (*noeud)->filsDroit = arbreCons(mot[0], 0, NULL, NULL);
                        insererMot(mot, &(*noeud)->filsDroit);
                    }
                }
            }
        }
        else if (mot[0] == '\0' && (*noeud)->caractere != '\0')//special case"
        {
                    TArbre n = arbreCons('\0', 1, NULL, *noeud); 
                    *noeud = n;
        }
        else if (mot[0] == '\0' && (*noeud)->caractere == '\0') //end of word
        {
            (*noeud)->nbrOccurrence++;
        }
    }
    else
    {
        if (mot[0] != '\0')
        {
            *noeud = arbreCons(mot[0], 0, NULL, NULL);
            mot++;
            insererMot(mot, &((*noeud)->filsGauche));
        }
        else
        {
            *noeud = arbreCons('\0', 1, NULL, NULL);
        }
    }
}

/**********Allows to add a word********/
void dicoInsererMot(char *mot, TArbre*arbre)
{
    if (strlen(mot) > 0)
    {
        if (*arbre == NULL)
            *arbre = arbreConsVide();

        insererMot(mot, arbre);

    }
}

/***********Function to display all words from the dictionary**********/
void afficherMotsDictionnaire() {
	   
    FILE *fichierMots = fopen("Dictionnaire.txt", "r");

    if (fichierMots == NULL) {
        printf("\033[31m");
       fprintf(stderr, "\t\tUnable to open the file Dictionnaire.txt.\n");
       printf("\033[0m");
        return;
    }

    // Dynamic array to store words
    Mot *mots = NULL;
    size_t tailleMots = 0;
    char ligne[TAILLE_MAX];

    // Read each line from the file and store the word in the array
    while (fgets(ligne, TAILLE_MAX, fichierMots) != NULL) {
        size_t len = strlen(ligne);

        //Remove the newline at the end of the word
        if (len > 0 && ligne[len - 1] == '\n') {
            ligne[len - 1] = '\0';
        }

        //Add the word to the dynamic array
        Mot nouveauMot;
        strcpy(nouveauMot.mot, ligne);

        tailleMots++;
        mots = realloc(mots, tailleMots * sizeof(Mot));
        mots[tailleMots - 1] = nouveauMot;
    }

    fclose(fichierMots);
   
    // Display all the words from the array.
            printf("\033[1m"); 
        printf("\033[36m");
            printf("\t__________________________________________________________________________________\n");

            printf("\t__________________________________________________________________________________\n");

    printf("\n                                       DICTIONARY                              \n");
    printf("\t__________________________________________________________________________________\n");
        printf("\t__________________________________________________________________________________\n");

        printf("\033[0m"); 
    printf("\n\tWords in the dictionary:\n");
    for (size_t i = 0; i < tailleMots; i++) {
        printf("\t[%ld] \t %s\n", i + 1, mots[i].mot);
    }
    
    // Free the memory used by the array
    free(mots);
}

int MotExiste(char motRecher[])
{
    FILE *dictionnaire = fopen("Dictionnaire.txt", "r");
    int motTrouve=0;

    char ligne[50];
    while (fgets(ligne, sizeof(ligne), dictionnaire) != NULL)
    {

        //Remove the newline at the end if present
        if (ligne[strlen(ligne) - 1] == '\n') {
            ligne[strlen(ligne) - 1] = '\0';
        }
      
        // To convert the line to lowercase
        for (int i = 0; ligne[i]; i++) {
            ligne[i] = tolower(ligne[i]);
        }

        //To check if the line matches the word to be searched
        if (strcmp(ligne, motRecher) == 0) {
            motTrouve =1;
        }
    }
    fclose(dictionnaire);
    return(motTrouve);
}

/******To add a word to the Dictionary file*******/
void AjouterMot(char mot[])
{   for (int i = 0; mot[i]; i++) {
        mot[i] = tolower(mot[i]);
    }
    if( MotExiste(mot)==0)
    {
        FILE *dictionnaire = fopen("Dictionnaire.txt", "a");

        if (dictionnaire == NULL) {
           printf("\033[31m");
           printf("\t\tError opening the file dictionnaire.txt.\n");
            printf("\t\tFailed to add.\n");
            printf("\033[0m");

        }

        else{
             // To append the word to the end of the file
            fprintf(dictionnaire, "\n%s", mot);
            fclose(dictionnaire);
            printf("\033[33m");
            printf("\t\tWord added successfully. ");
            printf("\033[0m");
        }

    }
    else{
        printf("\033[36m");
        printf("\t\tWord already exists in the Dictionary");
        printf("\033[0m");
    }

}




void effacerDerniereLigneVide(const char *nomFichier) {
    FILE *fichier = fopen("Dictionnaire.txt", "r+"); // Ouverture en mode lecture/écriture

    if (fichier == NULL) {
        printf("\t\tErreur lors de l'ouverture du fichier.\n");
        return;
    }

    fseek(fichier, 0, SEEK_END); // To move the cursor to the end of the file

    long pos = ftell(fichier); // To retrieve the current position of the curso

    // To traverse the file from the end to find the last empty line
    while (pos > 0) {
        pos--; // To decrement the cursor position
        fseek(fichier, pos, SEEK_SET); // To move the cursor to the specified position

        char c = fgetc(fichier); // To read the character at that position

        if (c == '\n') { 
            pos--; 
            fseek(fichier, pos, SEEK_SET); // To move the cursor to the previous position.

            char prevChar = fgetc(fichier); 

            if (prevChar == '\n') { 
                ftruncate(fileno(fichier), pos); 
                break;
            }
        }
    }

    fclose(fichier); 
}


/***********Delete a word from the Dictionary file***************/ 
void SupprimerMot(char motASupprimer[]) 
{
    for (int i = 0; motASupprimer[i]; i++) {
        motASupprimer[i] = tolower(motASupprimer[i]);
    }

    if (MotExiste(motASupprimer)==1)
    {
        FILE *dictionnaire = fopen("Dictionnaire.txt", "r");
        FILE *temp = fopen("temp.txt", "w");
        if (dictionnaire == NULL || temp == NULL) {
        printf("\033[31m");
          printf("\t\tError opening files.\n");
          printf("\033[0m");
            return;
        }

        char ligne[50]; 

         while (fgets(ligne, sizeof(ligne), dictionnaire) != NULL) 
        {
            
            if (ligne[strlen(ligne) - 1] == '\n') 
            {
                ligne[strlen(ligne) - 1] = '\0';
            }
    
           
            for (int i = 0; ligne[i]; i++) 
            {
                ligne[i] = tolower(ligne[i]);
            }
            
            if (strcmp(ligne, motASupprimer) != 0) 
            {
                // Write the line into the temporary file
                fprintf(temp, "%s\n", ligne);
            }
            
        }
        fclose(dictionnaire);
        fclose(temp);
        // Replace the original file with the temporary file
        remove("Dictionnaire.txt");
        rename("temp.txt", "Dictionnaire.txt");
         effacerDerniereLigneVide("Dictionnaire.txt");
         printf("\033[33m");
        printf("\t\tThe word has been successfully deleted.\n");
        printf("\033[0m");

    }
    else
    {
        printf("\033[31m");
       printf("\t\tDeletion error: Word does not exist");
        printf("\033[0m");
    } 
     
}