#define MAX(x, y) (((x) > (y)) ? (x) : (y))

/***********Build Empty Tree*******/
TArbre arbreConsVide()
{
    return NULL;
}

/***********Returns whether the tree is empty*******/
bool arbreEstVide(TArbre a)
{
    if (a == NULL)
    {
        return true;
    }
    return false;
}

/***********Build Node***************/
TArbre arbreCons(char caractere, int entier, TArbre filsGauche, TArbre filsDroit)
{
    TArbre a = (Noeud *)malloc(sizeof(Noeud));
    a->caractere = caractere;
    a->nbrOccurrence = entier;
    a->filsGauche = filsGauche;
    a->filsDroit = filsDroit;
    return a;
}

/***********Return the character of the root*************/
char arbreRacineLettre(TArbre a)
{
    if (!arbreEstVide(a))
    {
        return a->caractere;
    }
    return '\0';
}

/***********Return left child**********/
TArbre noeudFilsGauche(TArbre a)
{
    if (a != NULL)
    {
        return a->filsGauche;
    }
    return NULL;
}

/***********Return right child*************/
TArbre noeudFilsDroit(TArbre a)
{
    if (a != NULL)
    {
        return a->filsDroit;
    }
    return NULL;
}

/***********Allows deleting the tree*************/
void arbreSuppr(TArbre *noeud)
{
    if (*noeud != NULL)
    {
        arbreSuppr(&((*noeud)->filsDroit));
        arbreSuppr(&((*noeud)->filsGauche));
        free(*noeud);
        *noeud = NULL;
    }
}

/***********Returns the height of the tree************/
int hauteurArbre(TArbre a)
{
    if (a != NULL)
    {
        return 1 + MAX(hauteurArbre(a->filsGauche), hauteurArbre(a->filsDroit));
    }
    return -1;
}
/***********DisplayNoeud**********/
void afficherNoeuds(TArbre noeud, int espace)
{
    if (noeud != NULL)
    {
    	int i;
        for (i = 0; i < espace; i++)
            printf(".");

        if (noeud->caractere != '\0')
        {
            
            if(noeud->caractere == ' '){
                printf("NULL\n");
            }else{
                printf("%c\n", noeud->caractere);
            }
        }
        else
        {
            printf("\\0\n");
        }
        if (noeud->filsGauche != NULL)
            printf("(G)"); // Left Child
        afficherNoeuds(noeud->filsGauche, espace + 1);
        if (noeud->filsDroit != NULL)
            printf("(D)"); // Right Child
        afficherNoeuds(noeud->filsDroit, espace + 1);
    }
}



/****************displaying the tree**************/
void afficherArbre(TArbre a)
{
    if (a != NULL)
    {   
        printf("\033[1m");
        printf("\033[36m"); 
            printf("\t__________________________________________________________________________________\n");
    printf("\t__________________________________________________________________________________\n");

        printf("\n                                    TREE                               \n");
            printf("\t__________________________________________________________________________________\n");
    printf("\t__________________________________________________________________________________\n");

                printf("\033[0m");
        printf("\nTree height: %i\n\n",  hauteurArbre(a));
        printf("(R)"); //root
        afficherNoeuds(a, 1);
    }
}


/***********Searching for a character in the Trie***************/
TArbre rechercheCaractereTrie(TArbre a, char caractere) {
    // Base case: empty tree or character found
    if (arbreEstVide(a) || a->caractere == caractere) {
        return a;
    }

    // If the character is smaller than the root character, search in the left subtree
    if (caractere != a->caractere) {
        return rechercheCaractereTrie(a->filsGauche, caractere);
    }
    // Otherwise, search in the right subtree
    return rechercheCaractereTrie(a->filsDroit, caractere);
}

