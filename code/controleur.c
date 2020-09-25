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

POINT numCase_to_point(numCase nc){
	POINT p;
	p.x = (nc.c*50)+25;
	p.y = (nc.l*50)+25;
	return p;
}

numCase clic_to_numCase(POINT p){
	numCase nc;
	nc.c = p.x/50;
	nc.l = p.y/50;
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
	fill_screen(blanc);
	init_tabDamier();
	//test_afficheTab();

	//affiche_damier_classique();
	affiche_damier_alternatif();
	deplacement(nc1,nc2);
	wait_clic();
	affiche_damier_alternatif();
	wait_escape();
	return 0;
	
}
