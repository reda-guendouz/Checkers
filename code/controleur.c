#include "vue.c"


/****************************
*            Main           *
****************************/


int main()
{
	init_graphics(800,600); /* (largeur, hauteur) */
	affiche_auto_off(); // desactivation de la mise a jour automatique des dessins/objets graphiques
	creation_damier(); // Mise à disposition graphique du damier sur une plage de 500 par 500 (10x10 cases)
	affiche_all(); // affichage du damier
	wait_escape(); // attente de la touche "Echap afin de quitter l'application"
	return(0);
}
