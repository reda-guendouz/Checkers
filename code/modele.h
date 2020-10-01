#ifndef H_GRAPHICS
#define H_GRAPHICS
    #include "graphics.h"
#endif

#define H_MODELE

#include<stdlib.h>
#include<stdio.h>

typedef enum{
    VIDE,PION,DAME
}TYPEP;

typedef enum{
    NOIR,BLANC
}COULP;

typedef struct PIECE
{
    TYPEP typeP;
    COULP coulP;
}PIECE;

/*
* tableau global a tout le projet
*/
PIECE tableau[10][10];

typedef struct numCase
{
	int l;
	int c;
}numCase;

/*
* Renvoie la valeur absolue de la valeur donnée en paramètre
*/
int absol(int a);

/*
* initialise le damier une premiere fois avec les pions noirs et blancs
* damier de 10x10 cases avec 40 pions (20 blancs et 20 noirs)
*/
void init_tabDamier ();

void test_afficheTab();

/*
* Effectue le deplacement des pions dans le tableau global du damier
* , effectue aussi la prise => supression de la piece "prise"
*/
void appliqueCoup(numCase source, numCase destination);

/*
* Indique les mouvements possibles d'une piece selon son emplacement dans le cas où le jouer a déjà effectué une prise.
* Utilise une numCase "source" afin de renvoyer la liste de numCases 
* correspondant aux deplacements possibles de la piece liée à la "source".
* Modifie la variable donnée en paramètre pour lui attribuer la taille de la liste.
*/
numCase* numCases_possibles_apres_prise(numCase source,int *tailleCmpt);

/*
* Indique les mouvements possibles d'une piece selon son emplacement dans le cas où le jouer n'a pas effectué une prise.
* Utilise une numCase "source" afin de renvoyer la liste de numCases 
* correspondant aux deplacements possibles de la piece liée à la "source".
* Modifie la variable donnée en paramètre pour lui attribuer la taille de la liste.
*/
numCase* numCases_possibles_avant_prise(numCase source,int *tailleCmpt);
