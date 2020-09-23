#include "graphics.h"
#include "vue.c"
#include "modele.c"
#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h> 

#define LARGEUR_FENETRE 900

#define HAUTEUR_FENETRE 600


/****************************
*            Main           *
****************************/


int main()
{	
	init_graphics(LARGEUR_FENETRE,HAUTEUR_FENETRE);

    init_tabDamier();
    test_afficheTab();

	wait_escape();
	return 0;
	
}
