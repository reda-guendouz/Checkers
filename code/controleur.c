#ifndef H_GRAPHICS
#define H_GRAPHICS
#include "graphics.h"
#endif

#include "modele.h"

#include "vue.h"

#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h> 

#define LARGEUR_FENETRE 1100

#define HAUTEUR_FENETRE 650

/****************************
*          Protoypes        *
****************************/

void deplacement(numCase source,numCase destination,DAMIER_CHOIX dc,COULEUR clr_case_sombre, COULEUR clr_pion_clair, COULEUR clr_pion_sombre);

BOOL second_clic_valide(numCase* cases_possibles,numCase ncClic2,int taille);

COULP changer_joueur(COULP joueur);

BOOL clic_valide(POINT clic, COULP joueur,DAMIER_CHOIX dc);

BOOL peut_jouer(COULP joueur);

POINT numCase_to_point_classique(numCase nc);

numCase clic_to_numCase_classique(POINT p);

POINT numCase_to_point_alternatif(numCase nc);

numCase clic_to_numCase_alternatif(POINT p);

numCase clic_to_numCase(POINT p,DAMIER_CHOIX dc);

POINT numCase_to_point(numCase nc,DAMIER_CHOIX dc);

/****************************
*          Fonctions        *
****************************/

void deplacement(numCase source,numCase destination,DAMIER_CHOIX dc, COULEUR clr_case_sombre, COULEUR clr_pion_clair, COULEUR clr_pion_sombre){
	printf("deplacement de c1(%d) l1(%d) -> c2(%d) l2(%d)\n",source.c,source.l,destination.c,destination.l);
	PIECE P = tableau[source.c][source.l];
	POINT p1 = numCase_to_point(source,dc), p2 = numCase_to_point(destination,dc);
	if (dc == CLASSIQUE) {
		printf("p1 %d %d  p2  %d %d\n", p1.x, p1.y,p2.x, p2.y);
		appliqueCoup(source,destination);
		affiche_deplacement_piece_ronde(P, p1,p2,clr_case_sombre, clr_pion_clair, clr_pion_sombre);
	}
	//else
		//affiche_deplacement_piece_losange();
}

BOOL second_clic_valide(numCase* cases_possibles,numCase ncClic2,int taille){
	int i;
	for (i = 0; i != taille; i++)
	{
		if (cases_possibles[i].c == ncClic2.c && cases_possibles[i].l == ncClic2.l)
			return true;
	}
	return false;
}

COULP changer_joueur(COULP joueur){
	if (joueur==NOIR)
		return BLANC;
	else
		return NOIR;
}

BOOL clic_valide(POINT clic, COULP joueur,DAMIER_CHOIX dc){
	numCase clicNc = clic_to_numCase(clic,dc);
	COULP testCouleurJoueur;
	printf("colonne : %d,\t ligne : %d\n",clicNc.c,clicNc.l);
	if(clicNc.c >= 0 && clicNc.l >= 0 && clicNc.c < 10 && clicNc.l < 10){
		testCouleurJoueur = tableau[clicNc.c][clicNc.l].coulP;
		if (joueur == testCouleurJoueur)
			return true;
	}

	return false; 	
}

BOOL peut_jouer(COULP joueur){
	// verif
	return true;
}

POINT numCase_to_point_classique(numCase nc){
	POINT p;
	p.x = (nc.c*TAILLE_CASE)+ 325;
	p.y = (nc.l*TAILLE_CASE) + 50;
	return p;
}

numCase clic_to_numCase_classique(POINT p){
	numCase nc;
	nc.c = (p.x - 300)/TAILLE_CASE;
	nc.l = (p.y - 25)/TAILLE_CASE;
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

numCase clic_to_numCase(POINT p,DAMIER_CHOIX dc){
	numCase nc;
	if (dc == CLASSIQUE)
		nc = clic_to_numCase_classique(p);
	else
		nc = clic_to_numCase_alternatif(p);
	return nc;
}

POINT numCase_to_point(numCase nc,DAMIER_CHOIX dc){
	POINT p;
	if (dc == CLASSIQUE)
		p = numCase_to_point_classique(nc);
	else
		p = numCase_to_point_alternatif(nc);
	return p;
}



/****************************
*            Main           *
****************************/


int main()
{	
	int taille_possible = 0;
	int* ptr_taille_possible = &taille_possible;
	COULP joueur_actuel = NOIR;
	BOOL jeu_en_cours=true,partie_en_cours=true;
	init_graphics(LARGEUR_FENETRE,HAUTEUR_FENETRE);
	affiche_auto_off();
	init_tabDamier();
	DAMIER_CHOIX dc = CLASSIQUE;
	POINT clic1,clic2;
	numCase ncClic1,ncClic2;
	numCase *cases_possibles = NULL;
	affiche_plateau(dc,argent,gris,blanc,darkblue);

	while (jeu_en_cours)
	{
		while (partie_en_cours)
		{
			do {
				clic1 = wait_clic();
			} while (!clic_valide(clic1, joueur_actuel,dc));
			printf("clic1 fait !\n");
			printf("joueur : %d, \t clic valide\n",joueur_actuel);
			ncClic1 = clic_to_numCase(clic1,dc);
			cases_possibles = numCases_possibles_avant_prise(ncClic1,ptr_taille_possible);

			clic2 = wait_clic();
			printf("clic2 fait !\n");
			ncClic2 = clic_to_numCase(clic2,dc);
			if (second_clic_valide(cases_possibles,ncClic2,taille_possible))
			{
				deplacement(ncClic1,ncClic2,dc,gris,blanc,darkblue);
				printf("j(%d)\n",joueur_actuel);
				joueur_actuel = changer_joueur(joueur_actuel);
				partie_en_cours = peut_jouer(joueur_actuel);
			} else
			{
				// afficher animation second clic invalide (faire clignoter la mauvaise case cliqué en rouge par exemple)
				printf("c2(%d) l2(%d)\n",ncClic2.c,ncClic2.l);
				printf("foo\n");
			}
			affiche_damier_classique(argent,gris,blanc,darkblue);
		}
		// jeu_en_cours = "Voulez-vous continuer ?"
	}
	
	wait_escape();
	return 0;
	
}
