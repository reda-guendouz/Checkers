#include "vue.c"
#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h> 



/****************************
*            Main           *
****************************/


int main()
{
<<<<<<< HEAD
	init_graphics(800,600); /* (largeur, hauteur) */
	affiche_auto_off(); // desactivation de la mise a jour automatique des dessins/objets graphiques
	creation_damier(); // Mise à disposition graphique du damier sur une plage de 500 par 500 (10x10 cases)
	affiche_all(); // affichage du damier
	wait_escape(); // attente de la touche "Echap afin de quitter l'application"
=======

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
						creation_damier();
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
>>>>>>> 781ae4bedec6d316aa4544b0cb02eecc09708bff
	return(0);
}
