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


int main()
{	
	init_graphics(LARGEUR_FENETRE,HAUTEUR_FENETRE);
	affiche_auto_off();
	fill_screen(blanc);
	init_tabDamier();
	//test_afficheTab();

	affiche_damier_classique();
	wait_escape();
	return 0;
	
}
