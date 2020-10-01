#ifndef H_GRAPHICS
#define H_GRAPHICS
#include "graphics.h"
#endif

#include "modele.h"

#include "vue.h"

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

/****************************
*          Protoypes        *
****************************/

int deplacement(numCase source,numCase destination,COULP joueurActuel,INTERFACE_GRAPHIQUE ig, THEME th, int ptrPrise);

BOOL clic_zone_valide(POINT clicSource, POINT zone1, POINT zone2);

BOOL premier_clic_valide(POINT clic, COULP joueur, INTERFACE_GRAPHIQUE ig);

BOOL second_clic_valide(numCase *casesPossibles, numCase destination, int taille);

COULP changer_joueur(COULP joueur);

BOOL joueur_suivant_peut_jouer(COULP joueurSuivant);

numCase clic_to_numCase(POINT p, INTERFACE_GRAPHIQUE ig);

POINT numCase_to_point(numCase nc, INTERFACE_GRAPHIQUE ig);

POINT *numCasesPossibles_to_Point(numCase *numCasesPossibles, INTERFACE_GRAPHIQUE ig, int nbCasesPossibles);

/****************************
*            Main           *
****************************/

int main()
{
	int taillePossible = 0, piecePerdueClaire, piecePerdueSombre,distance;
	POINT *pointsCasesPossibles;
	int *ptrTaillePossible = &taillePossible; 
	COULP joueurActuel;
	THEME th;
	FIN finPartie = EGALITE;
	init_graphics(LARGEUR_FENETRE, HAUTEUR_FENETRE);
	init_themes();
	affiche_auto_off();
	BOOL retourMenu, secondClicValide, jeuEnCours = true, partieEnCours = true, pieceEnPrise = false;
	INTERFACE_GRAPHIQUE ig;
	POINT clic1, clic2, zoneJouer1, zoneJouer2, zoneQuitter1, zoneQuitter2,
		zoneValide1, zoneValide2, zoneIg1, zoneIg2, zoneIg3, zoneIg4,
		zoneClic1, zoneClic2, zoneRejouer1, zoneRejouer2,temp;
	zoneJouer1.x = 475;
	zoneJouer1.y = 365;
	zoneJouer2.x = 625;
	zoneJouer2.y = 425;

	zoneQuitter1.x = 450;
	zoneQuitter1.y = 270;
	zoneQuitter2.x = 650;
	zoneQuitter2.y = 330;

	zoneValide1.x = 420;
	zoneValide1.y = 55;
	zoneValide2.x = 690;
	zoneValide2.y = 115;

	zoneIg1.x = 450;
	zoneIg1.y = 350;
	zoneIg2.x = 650;
	zoneIg2.y = 410;

	zoneIg3.x = 447;
	zoneIg3.y = 250;
	zoneIg4.x = 653;
	zoneIg4.y = 310;

	zoneRejouer1.x = 435;
	zoneRejouer1.y = 245;
	zoneRejouer2.x = 625;
	zoneRejouer2.y = 315;

	numCase source, destination;
	numCase *casesPossibles = NULL;

	while (jeuEnCours)
	{
		//affiche_menu();
		affiche_menu_principal();
		do
		{
			clic1 = wait_clic();									 // JOUER
			if (clic_zone_valide(clic1, zoneQuitter1, zoneQuitter2)) //QUITTER
				exit(0);
		} while (!clic_zone_valide(clic1, zoneJouer1, zoneJouer2));

		ig = CLASSIQUE;
		affiche_menu_partie_ig();
		do
		{
			clic1 = wait_clic(); // INTERFACE_GRAPHIQUE
			if (clic1.x > 450 && clic1.x < 650 && clic1.y > 350 && clic1.y < 410)
				ig = CLASSIQUE;
			else if (clic1.x > 447 && clic1.x < 653 && clic1.y > 250 && clic1.y < 310)
				ig = ALTERNATIF;
		} while (!clic_zone_valide(clic1, zoneIg1, zoneIg2) && !clic_zone_valide(clic1, zoneIg3, zoneIg4));
		th = themes[0];
		affiche_menu_partie_theme(ig);
		do
		{
			affiche_menu_fleche_theme(th, true);
			clic1 = wait_clic();
			affiche_menu_fleche_theme(th, false);
			if (clic1.x > 325 && clic1.x < 425 && clic1.y > 400 && clic1.y < 500)
				th = themes[0];
			else if (clic1.x > 625 && clic1.x < 725 && clic1.y > 400 && clic1.y < 500)
				th = themes[1];
			else if (clic1.x > 325 && clic1.x < 425 && clic1.y > 200 && clic1.y < 300)
				th = themes[2];
			else if (clic1.x > 625 && clic1.x < 725 && clic1.y > 200 && clic1.y < 300)
				th = themes[3];
		} while (!clic_zone_valide(clic1, zoneValide1, zoneValide2));
		init_tabDamier();
		joueurActuel = BLANC;
		piecePerdueClaire = 0;
		piecePerdueSombre = 0;
		affiche_plateau(ig, th);
		retourMenu = FALSE;
		do
		{
			affiche_joueur(joueurActuel, ig, th);
			clic1 = wait_clic();
			if (clic1.x > 10 && clic1.x < 90 && clic1.y > 560)
				retourMenu = TRUE;
			else
			{
				do {
					while (!premier_clic_valide(clic1, joueurActuel, ig))
						clic1 = wait_clic();
					source = clic_to_numCase(clic1, ig);
					casesPossibles = numCases_possibles_avant_prise(source, ptrTaillePossible);
					printf("taille : %d\n",taillePossible);
					temp.x = clic1.x;temp.y = clic1.y;
					clic1.x = 0;clic1.y = 0;
				}while (taillePossible == 0);
				clic1.x = temp.x;clic1.y = temp.y;
				pointsCasesPossibles = numCasesPossibles_to_Point(casesPossibles, ig, taillePossible);
				affiche_efface_cases_possibles(pointsCasesPossibles, taillePossible, ig, th, true); // affiche surbrillance
				clic1 = numCase_to_point(source, ig);
				zoneClic1.x = clic1.x - TAILLE_CASE / 2;
				zoneClic1.y = clic1.y - TAILLE_CASE / 2;
				zoneClic2.x = clic1.x + TAILLE_CASE / 2;
				zoneClic2.y = clic1.y + TAILLE_CASE / 2;
				do
				{
					clic2 = wait_clic();
					destination = clic_to_numCase(clic2, ig);
					secondClicValide = second_clic_valide(casesPossibles, destination, taillePossible);
				} while (!secondClicValide && !clic_zone_valide(clic2, zoneClic1, zoneClic2));
				affiche_efface_cases_possibles(pointsCasesPossibles, taillePossible, ig, th, false); // enleve surbrillance
				if (secondClicValide)
				{
					casesPossibles = numCases_possibles_avant_prise(source,ptrTaillePossible);
					pieceEnPrise = false;
					if (joueurActuel == BLANC) {
						distance = deplacement(source,destination,joueurActuel,ig,th,piecePerdueSombre);
						if (distance == 2) {
							piecePerdueSombre++;
							pieceEnPrise = true;
						}
					}
					else {
						distance = deplacement(source,destination,joueurActuel,ig,th,piecePerdueClaire);
						if (distance == 2) {
							piecePerdueClaire++;
							pieceEnPrise = true;
						}
					}
					while(pieceEnPrise) { //prises multiples
						source = destination;
						casesPossibles = numCases_possibles_apres_prise(source, ptrTaillePossible);
						pointsCasesPossibles = numCasesPossibles_to_Point(casesPossibles, ig, taillePossible);
						if (taillePossible > 0) 
						{
							affiche_efface_cases_possibles(pointsCasesPossibles, taillePossible, ig, th, true);
							clic1 = numCase_to_point(source, ig);
							zoneClic1.x = clic1.x - TAILLE_CASE / 2;
							zoneClic1.y = clic1.y - TAILLE_CASE / 2;
							zoneClic2.x = clic1.x + TAILLE_CASE / 2;
							zoneClic2.y = clic1.y + TAILLE_CASE / 2;

							do 
							{
								clic2 = wait_clic();
								destination = clic_to_numCase(clic2, ig);
								secondClicValide = second_clic_valide(casesPossibles, destination, taillePossible);
							} while (!secondClicValide && !clic_zone_valide(clic2, zoneClic1, zoneClic2));
							affiche_efface_cases_possibles(pointsCasesPossibles, taillePossible, ig, th, false); // enleve surbrillance
							if (secondClicValide)
							{
								casesPossibles = numCases_possibles_apres_prise(source,ptrTaillePossible);
								if (joueurActuel == BLANC) {
									distance = deplacement(source,destination,joueurActuel,ig,th,piecePerdueSombre);
									piecePerdueSombre++;
								}
								else {
									distance = deplacement(source,destination,joueurActuel,ig,th,piecePerdueClaire);
									piecePerdueClaire++;
								}
								if (distance == 2) 
									pieceEnPrise = true;
								else
									pieceEnPrise = false;
						 	}
	
						}
						else 
							pieceEnPrise = false;
					}
					joueurActuel = changer_joueur(joueurActuel);
					pieceEnPrise = false;
					partieEnCours = joueur_suivant_peut_jouer(joueurActuel);
				}
			}
		} while (partieEnCours && !retourMenu);
		if (!retourMenu && !partieEnCours)
		{
			if (joueurActuel == NOIR)
				finPartie = VICTOIREJOUEUR1;
			else
				finPartie = VICTOIREJOUEUR2;
			affiche_menu_apres_partie(finPartie, th);

			do
			{
				clic1 = wait_clic();
				if (clic1.x > 455 && clic1.x < 610 && clic1.y > 145 && clic1.y < 215)
					exit(0);
			} while (!clic_zone_valide(clic1, zoneRejouer1, zoneRejouer2));
		}
	}
	wait_escape();
	return 0;
}

/****************************
*          Fonctions        *
****************************/

BOOL clic_zone_valide(POINT clicSource, POINT zone1, POINT zone2)
{
	// zone1 = en bas a gauche, zone2 = en haut a droite
	if (clicSource.x > zone1.x && clicSource.y > zone1.y && clicSource.x < zone2.x && clicSource.y < zone2.y)
		return true;
	return false;
}

POINT *numCasesPossibles_to_Point(numCase * numCasesPossibles, INTERFACE_GRAPHIQUE ig, int nbCasesPossibles)
{
	int i;
	POINT p;
	POINT *pointCasesPossibles = NULL;
	pointCasesPossibles = (POINT *)malloc(nbCasesPossibles * sizeof(POINT));
	for (i = 0; i < nbCasesPossibles; i++)
	{
		p = numCase_to_point(numCasesPossibles[i], ig);
		pointCasesPossibles[i] = p;
	}
	return pointCasesPossibles;
}

BOOL second_clic_valide(numCase * casesPossibles, numCase destination, int taille)
{
	int i;
	for (i = 0; i != taille; i++)
	{
		if (casesPossibles[i].c == destination.c && casesPossibles[i].l == destination.l)
			return true;
	}
	return false;
}

COULP changer_joueur(COULP joueur)
{
	if (joueur == NOIR)
		return BLANC;
	else
		return NOIR;
}

BOOL premier_clic_valide(POINT clicSource, COULP joueurActuel, INTERFACE_GRAPHIQUE ig)
{
	numCase source = clic_to_numCase(clicSource, ig);
	PIECE PSource = tableau[source.c][source.l];
	printf("colonne : %d,\t ligne : %d\n", source.c, source.l);
	if (source.c >= 0 && source.l >= 0 && source.c < 10 && source.l < 10)
	{
		if (joueurActuel == PSource.coulP && PSource.typeP != VIDE)
			return true;
	}
	return false;
}

BOOL joueur_suivant_peut_jouer(COULP joueurSuivant)
{
	numCase source;
	int verifTailleCasesPossibles = 0, col, lig;
	int *ptrVerif = &verifTailleCasesPossibles;

	for (col = 0; col < 10; col++)
	{
		for (lig = 0; lig < 10; lig++)
		{
			if (tableau[col][lig].typeP != VIDE && tableau[col][lig].coulP == joueurSuivant) // si c'est lent c'est a cause de reda
			{
				source.c = col;
				source.l = lig;
				numCases_possibles_avant_prise(source, ptrVerif);
				if (verifTailleCasesPossibles > 0)
					return true;
			}
		}
	}
	return false;
}

numCase clic_to_numCase(POINT p, INTERFACE_GRAPHIQUE ig)
{
	numCase nc;
	if (ig == CLASSIQUE)
	{
		nc.c = (p.x - 275) / TAILLE_CASE;
		nc.l = (p.y - 25) / TAILLE_CASE;
	}
	else
	{
		nc.l = (p.x - 275) / TAILLE_CASE;
		nc.c = (p.y - 25) / TAILLE_CASE;
	}
	return nc;
}

POINT numCase_to_point(numCase nc, INTERFACE_GRAPHIQUE ig)
{
	POINT p;
	if (ig == CLASSIQUE)
	{
		p.x = (nc.c * TAILLE_CASE) + 300;
		p.y = (nc.l * TAILLE_CASE) + 50;
	}
	else
	{
		p.x = (nc.l * TAILLE_CASE) + 300;
		p.y = (nc.c * TAILLE_CASE) + 50;
	}
	return p;
}

int deplacement(numCase source,numCase destination,COULP joueurActuel,INTERFACE_GRAPHIQUE ig, THEME th, int piecePrise){
	PIECE P;
	POINT p1 = numCase_to_point(source,ig), p2 = numCase_to_point(destination,ig),p3;
	appliqueCoup(source,destination);
	P = tableau[destination.c][destination.l]; // car la source et la destination ont ete intervertis
	if (absol(destination.c - source.c) == 2)
	{
		numCase entreDeux;
		entreDeux.c = source.c + (destination.c - source.c)/2;
        entreDeux.l = source.l + (destination.l - source.l)/2;
		p3 = numCase_to_point(entreDeux,ig);
		efface_piece(ig,p3,th);
		affiche_pieces_prises(joueurActuel,ig,th,piecePrise);
	}
	
	affiche_deplacement_piece(ig,P, p1,p2,th);
	return absol(destination.c - source.c);
}
