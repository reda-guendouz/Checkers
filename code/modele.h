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


void init_tabDamier ();

void test_afficheTab();

void deplacement_modele(numCase source, numCase destination);

BOOL conditions_deplacement(numCase source,numCase destination);

numCase* deplacement_possible(numCase source);

numCase* numCases_possibles_apres_prise(numCase source);

numCase* numCases_possibles_avant_prise(numCase source, int *compteur);