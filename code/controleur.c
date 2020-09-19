#include <stdio.h>
#include "vue.c"


/****************************
*            Main           *
****************************/


int main()
{
	init_graphics(800,600); /* (largeur, hauteur) */
	creation_damier();
	wait_escape();
	return(0);
}
