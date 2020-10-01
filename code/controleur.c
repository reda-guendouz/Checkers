#ifndef H_GRAPHICS
#define H_GRAPHICS
#include "graphics.h"
#endif

#include "modele.h"

#include "vue.h"

#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h> 

/****************************
*          Protoypes        *
****************************/

void deplacement(numCase source,numCase destination,INTERFACE_GRAPHIQUE ig,THEME th);

BOOL clic_zone_valide(POINT clic_source, POINT zone1, POINT zone2);

BOOL premier_clic_valide(POINT clic, COULP joueur,INTERFACE_GRAPHIQUE ig);

BOOL second_clic_valide(numCase* cases_possibles,numCase destination,int taille);

COULP changer_joueur(COULP joueur);

BOOL joueur_suivant_peut_jouer(COULP joueur);

numCase clic_to_numCase(POINT p,INTERFACE_GRAPHIQUE ig);

POINT numCase_to_point(numCase nc,INTERFACE_GRAPHIQUE ig);

POINT* numCasesPossibles_to_Point(numCase* numCasesPossibles,INTERFACE_GRAPHIQUE ig, int nbCasesPossibles);

/****************************
*          Fonctions        *
****************************/

BOOL clic_zone_valide(POINT clic_source, POINT zone1, POINT zone2){
	// zone1 = en bas a gauche, zone2 = en haut a droite
	if (clic_source.x > zone1.x && clic_source.y > zone1.y && clic_source.x < zone2.x && clic_source.y < zone2.y)
		return true;	
	return false;
}

POINT* numCasesPossibles_to_Point(numCase* numCasesPossibles,INTERFACE_GRAPHIQUE ig,int nbCasesPossibles){
	int i;
	POINT p;
	POINT * pointCasesPossibles = NULL;
	pointCasesPossibles = (POINT *)malloc(nbCasesPossibles*sizeof(POINT));
	for (i = 0;i<nbCasesPossibles;i++) {
		p = numCase_to_point(numCasesPossibles[i],ig);
		pointCasesPossibles[i] = p;
	}
	return pointCasesPossibles;
}

void deplacement(numCase source,numCase destination,INTERFACE_GRAPHIQUE ig, THEME th){
	printf("deplacement de c1(%d) l1(%d) -> c2(%d) l2(%d)\n",source.c,source.l,destination.c,destination.l);
	PIECE P;
	POINT p1 = numCase_to_point(source,ig), p2 = numCase_to_point(destination,ig),p3;
	printf("p1 %d %d  p2  %d %d\n", p1.x, p1.y,p2.x, p2.y);
	appliqueCoup(source,destination);
	P = tableau[destination.c][destination.l]; // car la source et la destination ont ete intervertis
	if (absol(destination.c - source.c) == 2)
	{
		numCase entreDeux;
		entreDeux.c = source.c + (destination.c - source.c)/2;
        	entreDeux.l = source.l + (destination.l - source.l)/2;
		p3 = numCase_to_point(entreDeux,ig);
		efface_piece(ig,p3,th);
	}
	
	affiche_deplacement_piece(ig,P, p1,p2,th);
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

BOOL premier_clic_valide(POINT clic_source, COULP joueur_actuel,INTERFACE_GRAPHIQUE ig){
	numCase source = clic_to_numCase(clic_source,ig);
	PIECE pi_source = tableau[source.c][source.l];
	printf("colonne : %d,\t ligne : %d\n",source.c,source.l);
	if(source.c >= 0 && source.l >= 0 && source.c < 10 && source.l < 10){
		if (joueur_actuel == pi_source.coulP && pi_source.typeP!=VIDE)
			return true;
	}
	return false; 	
}

BOOL joueur_suivant_peut_jouer(COULP joueur){
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
			if (tableau[col][lig].coulP == joueur_suivant && tableau[col][lig].typeP!=VIDE)
			{
				source.c = col; source.l = lig;
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
		nc.c = (p.x - 275)/TAILLE_CASE;
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
		p.x = (nc.c*TAILLE_CASE)+ 300;
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
	int taille_possible = 0, piecePerdueClaire,piecePerdueSombre;
	POINT* pointsCasesPossibles;
	int* ptr_taille_possible = &taille_possible;
	COULP joueur_actuel;
	THEME th;
	BOOL jeu_en_cours=true,partie_en_cours=true;
	init_graphics(LARGEUR_FENETRE,HAUTEUR_FENETRE);
	init_themes();
	affiche_auto_off();
	BOOL retourMenu, secondClicValide;
	INTERFACE_GRAPHIQUE ig;
	POINT clic1,clic2,zoneJouer1,zoneJouer2,zoneQuitter1,zoneQuitter2,
	zoneValide1, zoneValide2, zoneIg1, zoneIg2, zoneIg3, zoneIg4,
	zoneClic1, zoneClic2;
	
	zoneJouer1.x = 475;zoneJouer1.y = 365;
	zoneJouer2.x = 625;zoneJouer2.y = 425;
	
	zoneQuitter1.x = 450;zoneQuitter1.y = 270;
	zoneQuitter2.x = 650;zoneQuitter2.y = 330;
	
	zoneValide1.x = 420;zoneValide1.y =55;
	zoneValide2.x = 690;zoneValide2.y = 115;

	zoneIg1.x = 450; zoneIg1.y =350;
	zoneIg2.x = 650; zoneIg2.y =410;
	
	zoneIg3.x = 447; zoneIg3.y =250;
	zoneIg4.x = 653; zoneIg4.y =310;

	numCase source,destination;
	numCase *cases_possibles = NULL;

	while (jeu_en_cours)
	{
		//affiche_menu();
		affiche_menu_principal();
		do
		{
			clic1 = wait_clic(); // JOUER
			if (clic_zone_valide(clic1,zoneQuitter1,zoneQuitter2)) //QUITTER
				exit(0);
		} while (!clic_zone_valide(clic1,zoneJouer1,zoneJouer2));
		
		ig = CLASSIQUE;
		affiche_menu_partie_ig();
		do
		{
			clic1 = wait_clic(); // INTERFACE_GRAPHIQUE
			if (clic1.x > 450 && clic1.x < 650 && clic1.y > 350 && clic1.y < 410) 
				ig = CLASSIQUE;
			else if (clic1.x > 447 && clic1.x < 653 && clic1.y > 250 && clic1.y < 310) 
				ig = ALTERNATIF;
		} while (!clic_zone_valide(clic1,zoneIg1,zoneIg2) && !clic_zone_valide(clic1,zoneIg3,zoneIg4));
		th = themes[0];
		affiche_menu_partie_theme(ig);
		do
		{

			affiche_menu_fleche_theme(th,true);
			clic1 = wait_clic();
			affiche_menu_fleche_theme(th,false);
			if (clic1.x > 325 && clic1.x < 425 && clic1.y > 400 && clic1.y < 500) 
				th = themes[0];
			else if  (clic1.x > 625 && clic1.x < 725 && clic1.y > 400 && clic1.y < 500)
				th = themes[1];
			else if  (clic1.x > 325 && clic1.x < 425 && clic1.y > 200 && clic1.y < 300)
				th = themes[2];				
			else if  (clic1.x > 625 && clic1.x < 725 && clic1.y > 200 && clic1.y < 300)
				th = themes[3];
		} while (!clic_zone_valide(clic1,zoneValide1,zoneValide2));
		
		init_tabDamier();
		joueur_actuel = BLANC;
		piecePerdueClaire = 0;
		piecePerdueSombre = 0;
		affiche_plateau(ig,th);
		retourMenu = FALSE;

		do
		{
			// jeu ici ?
			affiche_joueur(joueur_actuel,ig,th);
			clic1 = wait_clic();
			if (clic1.x > 10 && clic1.x < 90 && clic1.y > 560) {
					printf("dedans sortir\n");
					retourMenu = TRUE;
				}
			else {
				while (!premier_clic_valide(clic1, joueur_actuel,ig)){
					clic1 = wait_clic();
				} 
				printf("clic1 fait !\n");
				printf("joueur : %d, \t clic valide\n",joueur_actuel);
				source = clic_to_numCase(clic1,ig);
				cases_possibles = numCases_possibles_avant_prise(source,ptr_taille_possible);
				pointsCasesPossibles = numCasesPossibles_to_Point(cases_possibles,ig,taille_possible);
				affiche_efface_cases_possibles(pointsCasesPossibles,taille_possible,ig,th,true);
				clic1 = numCase_to_point(source,ig);
				zoneClic1.x =clic1.x - TAILLE_CASE/2;zoneClic1.y = clic1.y - TAILLE_CASE/2;
				zoneClic2.x =clic1.x + TAILLE_CASE/2;zoneClic2.y = clic1.y + TAILLE_CASE/2;
				do {
					clic2 = wait_clic();
					printf("clic2 fait !\n");
					destination = clic_to_numCase(clic2,ig);
					secondClicValide = second_clic_valide(cases_possibles,destination,taille_possible);
				}while (!secondClicValide && !clic_zone_valide(clic2,zoneClic1,zoneClic2));
				affiche_efface_cases_possibles(pointsCasesPossibles,taille_possible,ig,th,false);
				if (secondClicValide)
				{
					printf("clic2 validé !\n");
					deplacement(source,destination,ig,th);
					printf("j(%d)\n",joueur_actuel);
					joueur_actuel = changer_joueur(joueur_actuel);
					partie_en_cours = joueur_suivant_peut_jouer(joueur_actuel);
				} else
				{
					// afficher animation second clic invalide (faire clignoter la mauvaise case cliqué en rouge par exemple)
					printf("c2(%d) l2(%d)\n",destination.c,destination.l);
					printf("foo\n");
				}
			}
		} while (partie_en_cours && !retourMenu);
	}
	
	wait_escape();
	return 0;
	
}
