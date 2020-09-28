#include "graphics.h"
#include "modele.c"
#include "vue.c"
#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h> 

#define LARGEUR_FENETRE 1100

#define HAUTEUR_FENETRE 650


/****************************
*            Main           *
****************************/

POINT numCase_to_point_classique(numCase nc){
	POINT p;
	p.x = (nc.c*TAILLE_CASE)+ 325;
	p.y = (nc.l*TAILLE_CASE) + 50;
	return p;
}

numCase clic_to_numCase_classique(POINT p){
	numCase nc;
	nc.c = p.x/TAILLE_CASE - 300;
	nc.l = p.y/TAILLE_CASE	- 50;
	return nc;
}

POINT numCase_to_point_alternatif(numCase nc){
	POINT p;
	p.x = (nc.l*TAILLE_CASE) + 300;
	p.y = (nc.c*TAILLE_CASE) + 50;
	return p;
}

numCase clic_to_numCase_alternatif(POINT p){
	numCase nc;
	nc.c = p.x/TAILLE_CASE - 300;
	nc.l = p.y/TAILLE_CASE	- 50;
	return nc;
}

int main()
{	
	numCase nc1,nc2;
	nc1.c = 3;
	nc1.l = 2;
	nc2.c = 4;
	nc2.l = 1;
	init_graphics(LARGEUR_FENETRE,HAUTEUR_FENETRE);
	affiche_auto_off();
	init_tabDamier();
	affiche_plateau(CLASSIQUE,argent,gris,blanc,darkblue);
	wait_clic();
	deplacement(nc1,nc2);
	POINT p2;
	p2 = numCase_to_point_classique(nc2);
	//p2 = numCase_to_point_alternatif(nc2);
	POINT p1;
	p1 = numCase_to_point_classique(nc1);
	//p1 = numCase_to_point_alternatif(nc1);
	PIECE P = tableau[nc1.l][nc1.c];
	affiche_deplacement_piece_ronde(P,p1,p2,gris,blanc,darkblue);
	//affiche_deplacement_piece_losange(P,p1,p2,gris,blanc,noir);
	wait_escape();
	return 0;
	
}
