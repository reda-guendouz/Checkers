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

void deplacement(numCase source,numCase destination,INTERFACE_GRAPHIQUE ig,THEME th);

BOOL second_clic_valide(numCase* cases_possibles,numCase destination,int taille);

COULP changer_joueur(COULP joueur);

BOOL clic_valide(POINT clic, COULP joueur,INTERFACE_GRAPHIQUE ig);

BOOL peut_jouer(COULP joueur);

numCase clic_to_numCase(POINT p,INTERFACE_GRAPHIQUE ig);

POINT numCase_to_point(numCase nc,INTERFACE_GRAPHIQUE ig);

/****************************
*          Fonctions        *
****************************/

void deplacement(numCase source,numCase destination,INTERFACE_GRAPHIQUE ig, THEME th){
	printf("deplacement de c1(%d) l1(%d) -> c2(%d) l2(%d)\n",source.c,source.l,destination.c,destination.l);
	PIECE P = tableau[source.c][source.l];
	POINT p1 = numCase_to_point(source,ig), p2 = numCase_to_point(destination,ig);
	printf("p1 %d %d  p2  %d %d\n", p1.x, p1.y,p2.x, p2.y);
	appliqueCoup(source,destination);
	affiche_deplacement_piece(ig,P, p1,p2,th);
	
	//else
		//affiche_deplacement_piece_losange();
}

BOOL second_clic_valide(numCase* cases_possibles,numCase destination,int taille){
	int i;
	for (i = 0; i != taille; i++)
	{
		if (cases_possibles[i].c == destination.c && cases_possibles[i].l == destination.l)
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

BOOL clic_valide(POINT clic_source, COULP joueur_actuel,INTERFACE_GRAPHIQUE ig){
	numCase source = clic_to_numCase(clic_source,ig);
	PIECE pi_source = tableau[source.c][source.l];
	printf("colonne : %d,\t ligne : %d\n",source.c,source.l);
	if(source.c >= 0 && source.l >= 0 && source.c < 10 && source.l < 10){
		if (joueur_actuel == pi_source.coulP && pi_source.typeP!=VIDE)
			return true;
	}
	return false; 	
}

BOOL peut_jouer(COULP joueur){
	COULP joueur_suivant;
	numCase source;
	int verif_taille_cases_possibles = 0,col,lig;
	int *ptr_verif = &verif_taille_cases_possibles;

	if (joueur==NOIR)
		joueur_suivant = BLANC;
	else
		joueur_suivant = NOIR;

	for (col = 0; col < 10; col++)
	{
		for (lig = 0; lig < 10; lig++)
		{
			source.c = col; source.l = lig;
			if (tableau[col][lig].coulP == joueur_suivant)
			{
				numCases_possibles_avant_prise(source,ptr_verif);
				if (verif_taille_cases_possibles > 0)
					return true;
			}
		}
	}
	return false;
}


numCase clic_to_numCase(POINT p,INTERFACE_GRAPHIQUE ig){
	numCase nc;
	if (ig == CLASSIQUE) {
		nc.c = (p.x - 300)/TAILLE_CASE;
		nc.l = (p.y - 25)/TAILLE_CASE;
	}
	else {
		nc.l = (p.x - 275)/TAILLE_CASE;
		nc.c = (p.y - 25)/TAILLE_CASE;
	}
	return nc;
}

POINT numCase_to_point(numCase nc,INTERFACE_GRAPHIQUE ig){
	POINT p;
	if (ig == CLASSIQUE) {
		p.x = (nc.c*TAILLE_CASE)+ 325;
		p.y = (nc.l*TAILLE_CASE) + 50;
	}
	else {
		p.x = (nc.l*TAILLE_CASE) + 300;
		p.y = (nc.c*TAILLE_CASE) + 50;
	}
	return p;
}



/****************************
*            Main           *
****************************/


int main()
{	
	int taille_possible = 0;
	int* ptr_taille_possible = &taille_possible;
	COULP joueur_actuel = BLANC;
	THEME th;
	th.caseClaire = argent;
	th.caseSombre = marron;
	th.pionClair = blanc;
	th.pionSombre = noir;
	BOOL jeu_en_cours=true,partie_en_cours=true;
	init_graphics(LARGEUR_FENETRE,HAUTEUR_FENETRE);
	affiche_auto_off();
	init_tabDamier();
	INTERFACE_GRAPHIQUE ig = CLASSIQUE;
	POINT clic1,clic2;
	numCase source,destination;
	numCase *cases_possibles = NULL;
	affiche_plateau(ig,th);

	while (jeu_en_cours)
	{
		while (partie_en_cours)
		{
			do {
				clic1 = wait_clic();
			} while (!clic_valide(clic1, joueur_actuel,ig));
			/*
			printf("clic1 fait !\n");
			printf("joueur : %d, \t clic valide\n",joueur_actuel);
			*/
			source = clic_to_numCase(clic1,ig);
			cases_possibles = numCases_possibles_avant_prise(source,ptr_taille_possible);
			// todo : si taille 0 source devient rouge
			clic2 = wait_clic();
			printf("clic2 fait !\n");
			destination = clic_to_numCase(clic2,ig);
			if (second_clic_valide(cases_possibles,destination,taille_possible))
			{
				printf("clic2 validé !\n");
				deplacement(source,destination,ig,th);
				printf("j(%d)\n",joueur_actuel);
				joueur_actuel = changer_joueur(joueur_actuel);
				partie_en_cours = peut_jouer(joueur_actuel);
			} else
			{
				// afficher animation second clic invalide (faire clignoter la mauvaise case cliqué en rouge par exemple)
				printf("c2(%d) l2(%d)\n",destination.c,destination.l);
				printf("foo\n");
			}
			affiche_damier_classique(th);
		}
		wait_escape();
		// jeu_en_cours = "Voulez-vous continuer ?"
	}
	
	wait_escape();
	return 0;
	
}
