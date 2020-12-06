#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#define TAILLEPLATEAU 11
#define TAILLEBATPA 5
#define TAILLEBATCROISEUR 4
#define TAILLEBATCT 3
#define TAILLEBATTOR 2
#define NBBATEAU 5


void initPlateau(char plateau[TAILLEPLATEAU][TAILLEPLATEAU]){
//BUT : Initialiser les cases du plateau avec un tableau
//ENTREE : /
//SORTIE : /
int n_i = 0, n_j = 0;

    for (n_i = 0;n_i < TAILLEPLATEAU; n_i++){
        for(n_j = 0; n_j < TAILLEPLATEAU; n_j++){
            if((n_i == 0 )&& (n_j != 0)){
                plateau[n_i][n_j] = 'A' + (n_j -1);
            }else if((n_j == 0) && (n_i != 0) && n_i != TAILLEPLATEAU - 1){
                plateau[n_i][n_j] = '0' + n_i;
            }else if (n_i == 0 && n_j == 0){
                plateau[n_i][n_j] = '\\';
            }else if(n_i == TAILLEPLATEAU - 1 && n_j == 0){
                plateau[n_i][n_j] = '0';
            }else{
                plateau[n_i][n_j] = '_';
            }
        }
    }
}

void affichPlateau(char plateau[TAILLEPLATEAU][TAILLEPLATEAU]){
//BUT : Affichage du plateau
//ENTREE : /
//SORTIE : Le plateau du joueur qui n'a pas son tour

int n_i = 0, n_j = 0;

    for(n_i = 0; n_i <= TAILLEPLATEAU - 1; n_i++){
        if(n_i == 10){
            printf("1");
        }else{
            printf(" ");
        }
        for(n_j = 0; n_j <= TAILLEPLATEAU - 1; n_j++){
            printf("%c|", plateau[n_i][n_j]);
        }
        printf("\n");
    }
}

int verifPlace(int x, int taille){
//BUT : Verifier que l'emplacement sélectionné par l'utilisateur est compris dans le plateau
//ENTREE : Emplacement du bateau
//SORTIE : VRAI ou FAUX
    if(x < 1 || x > taille){
        return 0;
    }else{
        return 1;
    }
}


int verifLettre(char emplacementCar){
//BUT : Vérifier que la lettre est comprise entre A et J
//ENTREE : Lettre entrée
//SORTIE : VRAI ou FAUX

    if((emplacementCar < 'A' || emplacementCar > 'J') && (emplacementCar < 'a' || emplacementCar > 'j')){
        return 0;
    }else{
        return 1;
    }
}

int convertirLettre(char lettreCoordonner){
//BUT : convertir la lettre en entier
//ENTREE : une lettre
//SORTIE : un entier
    switch(lettreCoordonner){
        case 'A' : return 1; break;
        case 'a' : return 1; break;
        case 'B' : return 2; break;
        case 'b' : return 2; break;
        case 'C' : return 3; break;
        case 'c' : return 3; break;
        case 'D' : return 4; break;
        case 'd' : return 4; break;
        case 'E' : return 5; break;
        case 'e' : return 5; break;
        case 'F' : return 6; break;
        case 'f' : return 6; break;
        case 'G' : return 7; break;
        case 'g' : return 7; break;
        case 'H' : return 8; break;
        case 'h' : return 8; break;
        case 'I' : return 9; break;
        case 'i' : return 9; break;
        case 'J' : return 10; break;
        case 'j' : return 10; break;
    }
    return 0;
}


int verifCasePose(int n_x, int n_y, char plateau[TAILLEPLATEAU][TAILLEPLATEAU], int taille, int sens){
//BUT : Verifié que la coordonnée entrée n'est pas à côté d'un autre bateau ou même dessus
//ENTREE : Les coordonnées
//SORTIE : VRAI ou FAUX
int n_i = 0;
int statut = 1;
    for(n_i = 0; n_i < taille; n_i++){
        //On vérifie les coordonnées horizontales et on renvoi faux (0) si dans une case adjacente de chacune des cases du bateau il y a déjà bateau
        if((sens == 1) && (plateau[n_x + n_i][n_y] == 'O' || plateau[n_x + n_i + 1][n_y] == 'O' || plateau[n_x + n_i][n_y + 1] == 'O' || plateau[n_x + n_i][n_y - 1] == 'O' || plateau[n_x + n_i - 1][n_y] == 'O')){
            statut = 0;
        }
        //Même chose pour la verticale
        if((sens == 0) && (plateau[n_x][n_y + n_i] == 'O' || plateau[n_x][n_y + n_i + 1] == 'O' || plateau[n_x + 1][n_y + n_i] == 'O' || plateau[n_x - 1][n_y + n_i] == 'O' || plateau[n_x][n_y + n_i - 1] == 'O')){
            statut = 0;
        }
    }
    return statut;
}

void initBat(tBateau bateau[], int taille){
//BUT : initialisation des valeurs des bateaux
//ENTREE : //
//SORTIE : //
int n_i = 0;
    for(n_i = 0; n_i < taille; n_i++){
        bateau[n_i].x = 0;
        bateau[n_i].y = 0;
        bateau[n_i].vie = 1;
        bateau[n_i].taille = taille;
        bateau[n_i].signe = 'O';
        bateau[n_i].statut = 'A';
    }
}

void verifDepassement(tBateau bateau[], int sens){
//BUT : Eviter les débordements de plateau
//ENTREE : /
//SORTIE : /

    if(sens == 1){
        //Si la taille du bateau dépasse la taille plateau, on réduit la distance de l'origine d'autant de case que la coordonnée dépassait le plateau horizontal
        if(bateau[0].x + bateau[0].taille > TAILLEPLATEAU - 1){
            bateau[0].x = bateau[0].x - ((bateau[0].x + bateau[0].taille) - TAILLEPLATEAU);
        }
    }else{
        //même chose pour la verticale
        if(bateau[0].y + bateau[0].taille > TAILLEPLATEAU - 1){
            bateau[0].y = bateau[0].y - ((bateau[0].y + bateau[0].taille) - TAILLEPLATEAU);
        }
    }
}


void setBateau(tBateau bateau[], int sens){
//BUT : mettre les positions des bateaux en place dans les cases bateaux
//ENTREE : Les positions initiales du bateau
//SORTIE : /

int n_i = 0;

    if(sens == 1){
        //On set les coordonnées horizontales
        for(n_i = 0; n_i <= bateau[0].taille; n_i++){
            bateau[n_i].x = bateau[0].x + n_i;
            bateau[n_i].y = bateau[0].y;
        }
    }else{
        //Ici les verticales
        for(n_i = 0; n_i <= bateau[0].taille; n_i++){
            bateau[n_i].y = bateau[0].y + n_i;
            bateau[n_i].x = bateau[0].x;
        }
    }
}


int verifCaseTouche(char plateau[TAILLEPLATEAU][TAILLEPLATEAU], int x, int y){
//BUT : Vérifier que la case sélectionnée touche ou non un bateau
//ENTREE : les coordonnées
//SORTIE : VRAI ou FAUX
    if(plateau[x][y] == 'O'){
        return 1;
    }else{
        return 0;
    }
}

int verifVie(tBateau bateau[]){
//BUT : Vérifier que le bateau est coulé
//ENTREE : /
//SORTIE : /
    int n_i = 0;
    int statut = 1;
    int cpt = 0;
    for(n_i = 0; n_i < bateau[0].taille; n_i++){
        //On vérifie que le bateau n'a plus de vie et qu'il est en "A" (alive)
        if(bateau[n_i].vie <= 0 && bateau[0].statut == 'A'){
            cpt++;
        }
    }
    //Si le compteur est égale à la taille du bateau, ça veut dire que toutes les case du bateau ont été touché et que le bateau est coulé, donc on renvoi 0
    if (cpt == bateau[0].taille){
        bateau[0].statut = 'C';
        statut = 0;
    }
    return statut;
}

tJoueur initJoueur(tJoueur joueur, int nbJ){
//BUT : initialiser chaque joueur sur leur nom, bateau, compteur de bateau et leur plateau
int n_i = 0;
int taille = 0;
    printf("Entrez votre nom joueur %d.\n", nbJ);
    fflush(stdin);
    gets(joueur.nom);
    joueur.cptBateau = NBBATEAU;
    //joueur.flotte[n_i].navire = (tBateau*)malloc(TAILLEBATPA*sizeof(tBateau));
    for(n_i = 0; n_i < NBBATEAU; n_i++){
        switch(n_i){
            case 0 : taille = TAILLEBATTOR; break;
            case 1 : taille = TAILLEBATCT; break;
            case 2 : taille = TAILLEBATCT; break;
            case 3 : taille = TAILLEBATCROISEUR; break;
            case 4 : taille = TAILLEBATPA; break;
        }
        initBat(joueur.flotte[n_i].navire, taille);
    }
    initPlateau(joueur.plateau);
    return joueur;
}


void placeBateau(tBateau bateau[], char plateau[TAILLEPLATEAU][TAILLEPLATEAU], int taille){
//BUT : cette fonction place les bateaux sur les plateaux des joueurs
//ENTREE : /
//SORTIE: /
    int n_i = 0;
    for(n_i = 0; n_i < taille; n_i++){
        plateau[bateau[n_i].x][bateau[n_i].y] = bateau[n_i].signe;
    }
}


void placementBateauJoueur(tJoueur *joueur, int *nbnavire){
//BUT : permet au joueur d'entrer les coordonnées des bateaux dans le plateau du jeu
//ENTREE : Les coordonnées x et y
//SORTIE : le bateau placé
    int tailleNavire = 0;
    char coordonneeLettre = ' ';
    tsens sens = 2;
    affichPlateau(joueur->plateau);
    sens = 2;
    printf("Veuillez entrer des coordonnees valides. \n");
    switch(*nbnavire){
        case 0 : printf("C'est le torpilleur.\nIl a 2 cases.\n"); tailleNavire = TAILLEBATTOR; break;
        case 1 : printf("C'est le contre-torpilleur.\nIl a 3 cases\n"); tailleNavire = TAILLEBATCT; break;
        case 2 : printf("C'est le contre-torpilleur.\nIl a 3 cases\n"); tailleNavire = TAILLEBATCT; break;
        case 3 : printf("C'est le croiseur.\nIl a 4 cases\n"); tailleNavire = TAILLEBATCROISEUR; break;
        case 4 : printf("C'est le porte-avions.\nIl a 5 cases\n"); tailleNavire = TAILLEBATPA; break;
    }
    //On demande a l'utilisateur de rentrer 0 ou 1 sinon on redemande tant que ce n'est pas le cas
    while(sens != horizontal && sens != vertical){
        printf("Mettre le bateau en horizontal ou vertical?\n0 : Horizontal\n1 : Vertical\n");
        fflush(stdin);
        scanf("%u", &sens);
    }
    //On demande à l'utilisateur une lettre comprise entre A et J, sinon on redemande jusqu'à ce que soit le cas
    do{
        printf("Commencez par entrer la lettre (valide).\n");
        fflush(stdin);
        scanf("%c", &coordonneeLettre);
    }while(verifLettre(coordonneeLettre) == 0);
    joueur->flotte[*nbnavire].navire[0].y = convertirLettre(coordonneeLettre);
    joueur->flotte[*nbnavire].navire[0].x = 0;
    //On vérifie que la coordonnée x est correcte (entre 1 et 10 inclus, sinon on ne laisse pas sortir de la boucle
    while(verifPlace(joueur->flotte[*nbnavire].navire[0].x, TAILLEPLATEAU - 1) == 0){
        printf("Maintenant le nombre (valide).\n");
        fflush(stdin);
        scanf("%d", &joueur->flotte[*nbnavire].navire[0].x);
    }
    verifDepassement(joueur->flotte[*nbnavire].navire, sens);
    //On vérifie qu'aucun bateau n'est sur le chemin ou à côté et si ce n'est pas le cas on peut initialiser les valeurs des bateaux puis les placer sur le plateau
    if (verifCasePose(joueur->flotte[*nbnavire].navire[0].x, joueur->flotte[*nbnavire].navire[0].y, joueur->plateau, tailleNavire, sens) == 1){
        setBateau(joueur->flotte[*nbnavire].navire, sens);
        placeBateau(joueur->flotte[*nbnavire].navire, joueur->plateau, tailleNavire);
        *nbnavire = *nbnavire + 1;
    }
}

void bateauTouche(tFlotte flotte[], int x, int y){
//BUT : enlever la vie de la partie du bateau touché
//ENTREE : /
//SORTIE : /
    int n_i = 0, n_j = 0;

    for(n_i = 0; n_i < NBBATEAU; n_i++){
        for(n_j = 0; n_j < flotte[n_i].navire[n_i].taille; n_j++){
            if(flotte[n_i].navire[n_j].x == x && flotte[n_i].navire[n_j].y == y){
                flotte[n_i].navire[n_j].vie = 0;
            }
        }
    }
}


void tourJoueur(tJoueur *joueurJ, tJoueur *joueurR, char plateau[TAILLEPLATEAU][TAILLEPLATEAU]){
//BUT : Le tour d'un joueur de la bataille navale
//ENTREE : les coordonnées a attaquées
//SORTIE : touché/coulé
    char coordonneeLettre = ' ';
    int coordonneX = 0, coordonneY = 0;
    int n_i = 0;
    int vieBateau = 1;
    printf("%s c'est votre tour.\n", joueurJ->nom);
    printf("Votre plateau.\n");
    affichPlateau(joueurJ->plateau);
    printf("Celui de votre adversaire.\n");
    affichPlateau(plateau);
    printf("Veuillez entrer les coordonnees a attaquer.\nD'abord la lettre.\n");
    //Comme avant, on vérifie que la lettre soit comprise entre A et J
    do{
        printf("Entrez une lettre (valide).\n");
        fflush(stdin);
        scanf("%c", &coordonneeLettre);
    }while(verifLettre(coordonneeLettre) == 0);
    coordonneY = convertirLettre(coordonneeLettre);
    //On vérifie que la coordonnée x est comprise entre 1 et 10 inclus
    while(verifPlace(coordonneX, TAILLEPLATEAU - 1) == 0){
        printf("Maintenant le nombre (valide).\n");
        fflush(stdin);
        scanf("%d", &coordonneX);
    }
    //Si la case comprend un bateau on enlève la vie de l'emplacement touché, on affiche un X à la place du bateau chez le joueur touché et sur le plateau
    //d'affichage du joueur attaquant puis on vérifie la vie du bateau et on lui applique le statut C (coulé) s'il n'a plus aucune vie sur aucune case
    //Sinon on affiche un V chez les deux joueurs pour signifier qu'il n'est pas touché ou si cette case a déjà été entrée
    if(verifCaseTouche(joueurR->plateau, coordonneX, coordonneY) == 1){
        bateauTouche(joueurR->flotte, coordonneX, coordonneY);
        joueurR->plateau[coordonneX][coordonneY] = 'X';
        plateau[coordonneX][coordonneY] = 'X';
        printf("Touche!\n");
        for(n_i = 0; n_i < NBBATEAU; n_i++){
            if(verifVie(joueurR->flotte[n_i].navire) == 0){
                vieBateau = 0;
            }
        }
    }else if(joueurR->plateau[coordonneX][coordonneY] != 'X' && joueurR->plateau[coordonneX][coordonneY] != 'V'){
        printf("Rate...\n");
        joueurR->plateau[coordonneX][coordonneY] = 'V';
        plateau[coordonneX][coordonneY] = 'V';
    }else{
        printf("Deja essaye...\n");
    }
    //Si un bateau a coulé, on diminue le compteur de bateau du joueur de 1
    if(vieBateau == 0){
        printf("Coule!\n");
        joueurR->cptBateau = joueurR->cptBateau - 1;
    }
    system("pause");
}
