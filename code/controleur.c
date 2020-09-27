#include "graphics.h"
#include "modele.c"
#include "vue.c"
#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h> 

#define LARGEUR_FENETRE 1100

#define HAUTEUR_FENETRE 650


/****************************
*            FONCTIONS      *
****************************/

BOOL joueur_peut_jouer(COULP joueur){
	// verification qu'au moins une des cases du joueur peut bouger
	return false;
}
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

/****************************
*            Main           *
****************************/


int main()
{	
	// Variables
	BOOL jeu_fini=false;
	COULP joueur_actuel = NOIR; // le premier joueur est celui possédant les pions noirs

	numCase nc1,nc2;
	nc1.c = 3; nc1.l = 2;
	nc2.c = 4; nc2.l = 1;
	init_graphics(LARGEUR_FENETRE,HAUTEUR_FENETRE);
	affiche_auto_off();
	fill_screen(blanc);
	init_tabDamier();
	//test_afficheTab();
	/*
	affiche_damier_classique();
	//affiche_damier_alternatif();
	wait_clic();
	deplacement(nc1,nc2);
	POINT p2;
	p2 = numCase_to_point_classique(nc2);
	//p2 = numCase_to_point_alternatif(nc2);
	POINT p1;
	p1 = numCase_to_point_classique(nc1);
	//p1 = numCase_to_point_alternatif(nc1);
	printf("point p1 : %d %d\n",p1.x, p1.y);
	printf("point p2 : %d %d\n",p2.x, p2.y);
	//affiche_damier_classique();
	//affiche_damier_alternatif();
	PIECE P = tableau[nc1.l][nc1.c];
	affiche_deplacement_piece_ronde(P,p1,p2);
	//affiche_deplacement_piece_losange(P,p1,p2);
	*/
	while (jeu_fini)
	{
		// jeu
		jeu_fini = joueur_peut_jouer();
	}
	

	wait_escape();
	return 0;
	
}
