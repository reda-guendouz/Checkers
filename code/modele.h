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

PIECE tabDamier[10][10];

typedef struct numCase
{
	int l;
	int c;
}numCase;

int absol(int a);

/*******************************
*        Creation Damier       *
*******************************/

void init_tabDamier();

/*******************************
*       Deplacement Damier     *
*******************************/

void appliquer_coup(numCase source, numCase destination);

/*******************************
*         Prises PIECE         *
*******************************/

numCase* get_numCases_possibles_avant_prise(numCase source,int *tailleCmpt);

numCase* get_numCases_possibles_apres_prise(numCase source,int *tailleCmpt);
