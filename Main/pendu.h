#ifndef DEF_PENDU
#define DEF_PENDU
#define TAILLE_MAX 255   
char lireCaractere();
int VerifMotexiste(char motSecret[]);
void lireLigne(char* mot);
void jouerAvecUnAmi();     
void genererMotSecret(TArbre *Mdico);
int jeuxDePendu(TArbre trie);
void afficherPendu();
#endif
