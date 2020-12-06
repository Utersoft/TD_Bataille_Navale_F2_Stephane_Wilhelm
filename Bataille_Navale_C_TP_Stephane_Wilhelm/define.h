#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED
#define TAILLEPLATEAU 11
#define TAILLEBATPA 5
#define TAILLEBATCROISEUR 4
#define TAILLEBATCT 3
#define TAILLEBATTOR 2
#define NBBATEAU 5

typedef struct tBateau{
    int x;
    int y;
    int vie;
    int taille;
    char signe;
    char statut;
}tBateau;

typedef struct tFlotte{
    tBateau navire[NBBATEAU];
}tFlotte;

typedef struct tJoueur{
    char nom[15];
    int cptBateau;
    tFlotte flotte[NBBATEAU];
    char plateau[TAILLEPLATEAU][TAILLEPLATEAU];
}tJoueur;

typedef enum tsens{horizontal = 1, vertical = 0}tsens;

//proto
void initBat(tBateau bateau[], int taille);
void initPlateau(char plateau[TAILLEPLATEAU][TAILLEPLATEAU]);
void affichPlateau(char plateau[TAILLEPLATEAU][TAILLEPLATEAU]);
tJoueur initJoueur(tJoueur joueur, int nbJ);
int verifPlace(int x, int taille);
int verifLettre(char emplacementCar);
int verifCasePose(int n_x, int n_y, char plateau[TAILLEPLATEAU][TAILLEPLATEAU], int taille, int sens);
void verifDepassement(tBateau bateau[], int sens);
void setBateau(tBateau bateau[], int sens);
int verifCaseTouche(char plateau[TAILLEPLATEAU][TAILLEPLATEAU], int x, int y);
int verifVie(tBateau bateau[]);
int convertirLettre(char lettreCoordonner);
void placeBateau(tBateau bateau[], char plateau[TAILLEPLATEAU][TAILLEPLATEAU], int taille);
void placementBateauJoueur(tJoueur *joueur, int *nbnavire);
void bateauTouche(tFlotte flotte[], int x, int y);
void tourJoueur(tJoueur *joueurJ, tJoueur *joueurR, char plateau[TAILLEPLATEAU][TAILLEPLATEAU]);

#endif // DEFINE_H_INCLUDED
