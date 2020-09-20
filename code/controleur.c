#include "vue.c"
#include "modele.c"
#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h> 


/****************************
*            Main           *
****************************/


int main()
{
	init_graphics(799,600); /* (largeur, hauteur) */
	int fin = 1;
	SDL_Event event;    // Creation d une entree clavier a recuperer
	while (fin) {
		//printf("dedans\n");
		SDL_WaitEvent(&event);  //Attend pendant 10 ms pour recuperer une entree
		switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
					case SDLK_UP:    // Si touche du haut => Damier
						creation_damier(); // Mise à disposition graphique du damier sur une plage de 500 par 500 (10x10 cases)
						init_tabDamier();
						test_afficheTab();
						break;
					case SDLK_DOWN:  // Si touche du bas => Parametre
						printf("Parametre\n");
						break;
					case SDLK_ESCAPE:// Si echap => QUIT
						fin = 0;
						break;
					default :
						break;
				}
				break;
			default :
				break;
		}
	}
	SDL_Quit();
	return(0);
}
