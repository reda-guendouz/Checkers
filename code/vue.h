#ifndef H_GRAPHICS
#define H_GRAPHICS
	#include "graphics.h"
#endif

#ifndef H_MODELE
#define H_MODELE
	#include "modele.h"
#endif

#define H_VUE

#define RAYON 22
#define TAILLE_CASE 50

#define LARGEUR_FENETRE 1100

#define HAUTEUR_FENETRE 650

typedef enum{
    CLASSIQUE,ALTERNATIF
}INTERFACE_GRAPHIQUE;

typedef struct {
	COULEUR caseClaire;
	COULEUR caseSombre;
	COULEUR pionClair;
	COULEUR pionSombre;
}THEME;

THEME themes[4]; //Madame Pilard a validé cette variable globale


/*******************************
*      Affichage de piece      *
*******************************/

void affiche_piece(INTERFACE_GRAPHIQUE ig, PIECE P, POINT p, THEME theme);

/*******************************
*       Affiche case           *
*******************************/

void affiche_case(INTERFACE_GRAPHIQUE ig,POINT p1,COULEUR clr); 

/*******************************
*       Effacer une piece      *
*******************************/

void efface_piece(INTERFACE_GRAPHIQUE ig,POINT p,THEME theme);

/*******************************
*      Deplacement piece       *
*******************************/

void affiche_deplacement_piece(INTERFACE_GRAPHIQUE ig, PIECE P,POINT p1, POINT p2, THEME theme);

/*******************************
*            THEME             *
*******************************/

void init_themes();

/*******************************
*        Affiche damier        *
*******************************/

void affiche_damier(INTERFACE_GRAPHIQUE ig, THEME theme);

/*******************************
*        Affiche MENU          *
*******************************/

void affiche_menu_retour();

BOOL affiche_menu(); 

void affiche_menu_cadre(POINT p1, POINT p2, COULEUR clr);

void affiche_menu_principal();

void affiche_menu_fleche_theme(THEME th, BOOL afficheEfface);

void affiche_menu_partie_theme(INTERFACE_GRAPHIQUE ig);

void affiche_menu_partie_ig();

void affiche_menu_apres_partie();

/*******************************
*        Affiche Plateau       *
*******************************/

void reset_affichage_screen(COULEUR clr);

void affiche_joueur(COULEUR clr, INTERFACE_GRAPHIQUE ig, THEME theme);

void affiche_plateau(INTERFACE_GRAPHIQUE ig, THEME theme);

void affiche_efface_cases_possibles(POINT* pointsCasesPossibles, int nombreCasesPossibles, INTERFACE_GRAPHIQUE ig,THEME th,BOOL afficheEfface);

void affiche_pieces_prises(COULEUR clr, INTERFACE_GRAPHIQUE ig, THEME th, int nbPiecesPrises);
