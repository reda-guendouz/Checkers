#include "graphics.h"
#include "vue.c"
#include "modele.c"
#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h> 

#define LARGEUR_FENETRE 800

#define HAUTEUR_FENETRE 700


/****************************
*            Main           *
****************************/


int main()
{	
	init_graphics(LARGEUR_FENETRE,HAUTEUR_FENETRE);



	wait_escape();
	return 0;
	
}
