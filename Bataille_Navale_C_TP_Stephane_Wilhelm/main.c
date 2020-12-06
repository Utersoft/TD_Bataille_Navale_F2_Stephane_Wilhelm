/*ALGORITHME : Bataille Navale
//BUT : Principe de la bataille navale, 2 joueurs qui placent leur bateaux sur une grille et essaye de couler ceux de l'autre joueur
//ENTREE : Les coordonées des bateaux ainsi que les coordonnées à attaquer
//SORTIE : Le plateau du jeu, les emplacements déjà ciblé (juste ou non), si le tir est réussi ou non et les pertes

TYPE ENREGISTREMENT = bateau
    ENTIER <- x
    ENTIER <- y
    ENTIER <- vie
    ENTIER <- taille
    CAR <- signe
FINENREGISTREMENT

TYPE ENREGISTREMENT = flotte
    TABLEAU DE BATEAU <- navire
FINENREGISTREMENT

TYPE ENREGISTREMENT = joueur
    CHAINE <- nom
    ENTIER <- nbBateau
    FLOTTE <- tFlotte
FINENREGISTREMENT

PROCEDURE INITPLATEAU(TABLEAU DE CAR : plateau, ENTIER : taille)
//BUT : Initialiser les cases du plateau avec un tableau
//ENTREE : /
//SORTIE : /
var n_i <- 0, n_j <- 0 : ENTIER

DEBUT
    POUR n_i DE 0 A taille FAIRE
    DEBUT
        POUR n_j DE 0 A taille FAIRE
        DEBUT
            SI (n_i = 0 ET n_j <> 0) ALORS
            DEBUT
                plateau[n_i][n_j] <- "A" + n_j
            SINON SI (n_j = 0 ET n_i <> 0)ALORS
            DEBUT
                plateau[n_i][n_j] <- n_i
            SINON
            DEBUT
                plateau[n_i][n_j] <- "_"
            FINSI
        FINPOUR
    FINPOUR
FINPROCEDURE

PROCEDURE affichPlateau(TABLEAU DE CAR : plateau, ENTIER : taille)
//BUT : Affichage du plateau
//ENTREE : /
//SORTIE : Le plateau du joueur qui n'a pas son tour

var n_i <- 0, n_j <- 0 : ENTIER

DEBUT
    POUR n_i DE 0 A taille FAIRE
    DEBUT
        POUR n_j DE 0 A taille FAIRE
        DEBUT
            ECRIRE plateau[n_i][n_j], "|"
        FINPOUR
        ECRIRE "\n"
    FINPOUR
FINPROCEDURE

FONCTION verifPlace (TABLEAU de BATEAU : bateau, ENTIER : taille) : BOOLEEN
//BUT : Verifier que l'emplacement sélectionné par l'utilisateur est compris dans le plateau
//ENTREE : Emplacement du bateau
//SORTIE : VRAI ou FAUX
DEBUT
    SI(bateau.x < 1 OU bateau.y < 1 OU bateau.x > taille OU bateau.y > taille)ALORS
    DEBUT
        verifPlace <- FAUX
    SINON
    DEBUT
        verifPlace <- VRAI
    FINSI
FINFONCTION


FONCTION verifLettre(CAR : emplacementCar) : BOOLEEN
//BUT : Vérifier que la lettre est comprise entre A et J
//ENTREE : Lettre entrée
//SORTIE : VRAI ou FAUX
DEBUT
    SI ((emplacementCar < "A" && emplacementCar > "J") || (emplacementCar < "a" && emplacementCar > "j") ALORS
    DEBUT
        verifLettre <- FAUX
    SINON
    DEBUT
        verifLettre <- VRAI
    FINSI
FINFONCTION


PROCEDURE changeLettreEntier(CAR : emplacementCar, ENTIER : emplacementEntier)
//BUT : Changer la lettre en coordonnée chiffre
//ENTREE : Lettre entrer par l'utilisateur
//SORTIE : /

DEBUT
    SI (emplacementCar >= "A" && emplacementCar <= "J") ALORS
    DEBUT
        emplacementEntier <- emplacementCar - 16
    FINSI
    SI (emplacementCar >= "a" && emplacementCar <= "j") ALORS
    DEBUT
        emplacementEntier <- emplacementCar - 48
    FINSI
FINPROCEDURE


FONCTION verifCasePose(ENTIER : n_x, ENTIER : n_y, TABLEAU DE CAR : plateau, ENTIER : taille, BOOLEEN : sens) : BOOLEEN
//BUT : Verifié que la coordonnée entrée n'est pas à côté d'un autre bateau ou même dessus
//ENTREE : Les coordonnées
//SORTIE : VRAI ou FAUX
var n_i <- 0 : ENTIER
var statut <- FAUX : BOOLEEN
DEBUT
    POUR i DE 0 A taille FAIRE
    DEBUT
        SI ((sens = 1) && plateau[n_x + n_i][n_y] = "C" || plateau[n_x + n_i + 1][n_y] = "C" || plateau[n_x + n_i][n_y + 1] = "C" || plateau[n_x + n_i][n_y - 1] = "C")
        DEBUT
            statut <- VRAI
        FINSI
        SI ((sens = 0) && plateau[n_x][n_y + n_i] = "C" || plateau[n_x][n_y + n_i + 1] = "C" || plateau[n_x + 1][n_y + n_i] = "C" || plateau[n_x - 1][n_y + n_i] = "C")
        DEBUT
            statut <- FAUX
        FINSI
    FINPOUR
    verifCasePose <- statut
FINPROCEDURE

PROCEDURE initBat(TABLEAU DE BATEAU : bateau, ENTIER : taille)
//BUT : initialisation des bateaux
//ENTREE : //
//SORTIE : //
var n_i <- 0 : ENTIER
DEBUT
    POUR n_i DE 0 A taillebat FAIRE
    DEBUT
        bateau[n_i].x <- 0
        bateau[n_i].y <- 0
        bateau[n_i].vie <- taille
        bateau[n_i].taille <- taille
        bateau[n_i].signe <- "C"
    FINPOUR
FINPROCEDURE

PROCEDURE verifDepassement(ENTIER x, ENTIER y, BOOLEEN : sens, ENTIER : taille, ENTIER : taillebat)
//BUT : Eviter les débordements de plateau
//ENTREE : /
//SORTIE : /
DEBUT
    SI (sens = VRAI) ALORS
    DEBUT
        SI (x + taillebat > taille)ALORS
        DEBUT
            x <- x - ((x + taillebat) - taille)
        FINSI
    SINON
    DEBUT
        SI (y + taillebat > taille)ALORS
        DEBUT
            y <- y - ((y + taillebat) - taille)
        FINSI
    FINSI
FINPROCEDURE


PROCEDURE setBateau(TABLEAU DE BATEAU : bateau, ENTIER : taille, BOOLEEN : sens)
//BUT : mettre les positions des bateaux en place
//ENTREE : Les positions initiales du bateau
//SORTIE : /

ENTIER n_i <- 0

DEBUT
    SI(sens = VRAI) ALORS
    DEBUT
        POUR n_i DE 1 A bateau.taille FAIRE
        DEBUT
            bateau[n_i].x <- bateau[0].x + n_i
        FINPOUR
    SINON
    DEBUT
        POUR n_i DE 1 A bateau.taille FAIRE
        DEBUT
            bateau[n_i].y <- bateau[0].y + n_i
        FINPOUR
    FINSI
FINPROCEDURE


FONCTION verifCaseTouche(TABLEAU D'ENTIER : plateau, ENTIER : x, ENTIER : y)
//BUT : Vérifier que la case sélectionnée touche ou non un bateau
//ENTREE : les coordonnées
//SORTIE : VRAI ou FAUX
DEBUT
    SI(plateau[x][y] = "C")ALORS
    DEBUT
        verifCaseTouche <- VRAI
    SINON
        verifCaseTouche <- FAUX
    FINSI
FINFONCTION

FONCTION verifVie(TABLEAU DE BATEAU : bateau)
//BUT : Vérifier que le bateau est coulé
//ENTREE : /
//SORTIE : /
DEBUT
    SI (bateau.vie <= 0) ALORS
    DEBUT
        verifVie <- VRAI
    SINON
    DEBUT
        verifVie <- FAUX
    FINSI
FINFONCTION

PROCEDURE initJoueur(JOUEUR joueur)
var n_i <- 0, n_j <- 0
DEBUT
    ECRIRE "Entrez votre nom"
    LIRE joueur.nom




CONST TAILLEPLATEAU <- 10
CONST TAILLEBATPA <- 5
CONST TAILLEBATCROISEUR <- 4
CONST TAILLEBATCT <- 3
CONST TAILLEBATTOR <- 2

var plateau : TABLEAU D'ENTIER
var plateauAffiche : TABLEAU D'ENTIER
var joueur1 : JOUEUR
var joueur2 : JOUEUR

DEBUT




*/



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


int main()
{
    tJoueur joueur1;
    tJoueur joueur2;
    char plateauAfficheJ1[TAILLEPLATEAU][TAILLEPLATEAU];
    char plateauAfficheJ2[TAILLEPLATEAU][TAILLEPLATEAU];
    int nbNavire = 0;

    joueur1 = initJoueur(joueur1, 1);
    initPlateau(plateauAfficheJ1);
    printf("%s vous allez pouvoir entrer les coordonnees de vos bateaux.\n", joueur1.nom);
    do{
        placementBateauJoueur(&joueur1, &nbNavire);
        system("pause");
        system("cls");
    }while(nbNavire < 5);
    joueur2 = initJoueur(joueur2, 2);
    initPlateau(plateauAfficheJ2);
    nbNavire = 0;
    printf("%s vous allez pouvoir entrer les coordonnees de vos bateaux.\n", joueur2.nom);
    do{
        placementBateauJoueur(&joueur2, &nbNavire);
        system("pause");
        system("cls");
    }while(nbNavire < 5);
    //la partie s'arrête uniquement si l'un des joueurs à son compteur de bateau à 0
    do{
        tourJoueur(&joueur1, &joueur2, plateauAfficheJ1);
        //On vérifie d'abord que le joueur n'a pas perdu avant de jouer son tour pour éviter qu'il rejoue en cas de défaite
        if(joueur2.cptBateau > 0){
            system("cls");
            printf("Change de joueur, veuillez quitter l'ecran.\n");
            system("pause");

            tourJoueur(&joueur2, &joueur1, plateauAfficheJ2);
            if(joueur1.cptBateau > 0){
                system("cls");
                printf("Change de joueur, veuillez quitter l'ecran.\n");
                system("pause");
            }
        }
    }while(joueur1.cptBateau > 0 && joueur2.cptBateau > 0);
    if(joueur1.cptBateau <= 0){
        printf("Bravo %s, vous avez gagne!", joueur2.nom);
    }else{
        printf("Bravo %s, vous avez gagne!", joueur1.nom);
    }


    return 0;
}
