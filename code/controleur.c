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

int deplacer_piece(numCase source, numCase destination, COULP joueurActuel, INTERFACE_GRAPHIQUE ig, THEME th, int piecePrise);

BOOL est_clic_valide(POINT clicSource, int zone1, int zone2, int zone3, int zone4);

BOOL est_premier_coup_valide(POINT clic, COULP joueur, INTERFACE_GRAPHIQUE ig);

BOOL est_second_coup_valide(numCase* casesPossibles, numCase destination, int taille);

COULP changer_joueur(COULP joueur);

BOOL verifie_partie_finie(COULP joueurSuivant);

numCase clic_to_numCase(POINT p, INTERFACE_GRAPHIQUE ig);

POINT numCase_to_point(numCase nc, INTERFACE_GRAPHIQUE ig);

POINT* numCasesPossibles_to_Point(numCase* numCasesPossibles, INTERFACE_GRAPHIQUE ig, int nbCasesPossibles);

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
	FIN finPartie = VICTOIREJOUEUR1;
	init_graphics(LARGEUR_FENETRE, HAUTEUR_FENETRE);
	init_themes();
	affiche_auto_off();
	BOOL retourMenu, secondClicValide, estValide = false, jeuEnCours = true, partieEnCours = true, pieceEnPrise = false;
	INTERFACE_GRAPHIQUE ig;
	POINT clic1, clic2;

	numCase source, destination;
	numCase *casesPossibles = NULL;

	while (jeuEnCours)
	{
		affiche_menu_principal();
		do
		{
			clic1 = wait_clic();						    // JOUER
			if (est_clic_valide(clic1, 450, 270, 650, 330)) //QUITTER
				exit(0);
		} while (!est_clic_valide(clic1, 475, 365, 625, 425));

		ig = CLASSIQUE;
		affiche_menu_partie_ig();
		do
		{
			clic1 = wait_clic(); // INTERFACE_GRAPHIQUE
			if (est_clic_valide(clic1, 450, 350, 650, 410))
				ig = CLASSIQUE;
			else if (est_clic_valide(clic1, 447, 250, 653, 310))
				ig = ALTERNATIF;
		} while (!est_clic_valide(clic1, 450, 350, 650, 410) && !est_clic_valide(clic1, 447, 250, 653, 310));  //INTERFACE_GRAPHIQUE
		
		th = themes[0];
		affiche_menu_partie_theme(ig);
		do
		{
			affiche_menu_fleche_theme(th, true);
			clic1 = wait_clic();
			affiche_menu_fleche_theme(th, false);
			if (est_clic_valide(clic1, 325, 400, 425, 500))
				th = themes[0];
			else if (est_clic_valide(clic1, 625, 400, 725, 500))
				th = themes[1];
			else if (est_clic_valide(clic1, 325, 200, 425, 300))
				th = themes[2];
			else if (est_clic_valide(clic1, 625, 200, 725, 300))
				th = themes[3];
		} while (!est_clic_valide(clic1, 420, 55, 690, 115));
		
		init_tabDamier();
		joueurActuel = BLANC;
		piecePerdueClaire = 0;
		piecePerdueSombre = 0;
		
		affiche_plateau(ig, th);
		retourMenu = FALSE;
		do
		{
			affiche_joueur(joueurActuel, ig, th);
			do {
				estValide = false;
				clic1 = wait_clic();
				if (est_clic_valide(clic1, 10, 560, 90,HAUTEUR_FENETRE))
					retourMenu = TRUE;
				if (est_premier_coup_valide(clic1, joueurActuel, ig)) {
					estValide = true;
					source = clic_to_numCase(clic1, ig);
					casesPossibles = get_numCases_possibles_avant_prise(source, ptrTaillePossible);
				}
			}while((!estValide || taillePossible == 0) && !retourMenu);
			if (!retourMenu) 
			{
				pieceEnPrise = false;
				do {
					pointsCasesPossibles = numCasesPossibles_to_Point(casesPossibles, ig, taillePossible);
					affiche_efface_cases_possibles(pointsCasesPossibles, taillePossible, ig, th, true); // affiche surbrillance
					clic1 = numCase_to_point(source, ig);
					do
					{
						clic2 = wait_clic();
						destination = clic_to_numCase(clic2, ig);
						secondClicValide = est_second_coup_valide(casesPossibles, destination, taillePossible);
					} while (!secondClicValide && 
							!est_clic_valide(clic2, (clic1.x - TAILLE_CASE / 2), (clic1.y - TAILLE_CASE / 2),
							(clic1.x + TAILLE_CASE / 2),( clic1.y + TAILLE_CASE / 2)));
					affiche_efface_cases_possibles(pointsCasesPossibles,taillePossible,ig,th,false);
					if (secondClicValide){
						if (joueurActuel == BLANC) {
							distance = deplacer_piece(source, destination, joueurActuel, ig, th, piecePerdueSombre);
							if (distance == 2){
								piecePerdueSombre++;
								pieceEnPrise = true;
							}
							else
								pieceEnPrise = false;
						}
						else {
							distance = deplacer_piece(source, destination, joueurActuel, ig, th, piecePerdueClaire);
							if (distance == 2) {
								piecePerdueClaire++;
								pieceEnPrise = true;
							}
							else
								pieceEnPrise = false;
						}
						if (pieceEnPrise) {
							source = destination;
							casesPossibles = get_numCases_possibles_apres_prise(source,ptrTaillePossible);
							pointsCasesPossibles = numCasesPossibles_to_Point(casesPossibles, ig, taillePossible);
							if (taillePossible != 0) {
								affiche_efface_cases_possibles(pointsCasesPossibles,taillePossible,ig,th,true);
								pieceEnPrise = true;
								secondClicValide = false;
							}
						}
						if (taillePossible == 0 || secondClicValide){
							joueurActuel = changer_joueur(joueurActuel);
							partieEnCours = verifie_partie_finie(joueurActuel);
						}
					} else
					{
						secondClicValide = true;
						if (pieceEnPrise)
						{
							joueurActuel = changer_joueur(joueurActuel);
							partieEnCours = verifie_partie_finie(joueurActuel);
						}
					}
					
				}while(!secondClicValide);
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
				if (est_clic_valide(clic1, 455, 145, 610, 215))
					exit(0);
			} while (!est_clic_valide(clic1, 435, 245, 625, 315));
		}
	}
	wait_escape();
	return 0;
}

/****************************
*          Fonctions        *
****************************/

BOOL est_clic_valide(POINT clicSource, int zoneBG1, int zoneBG2, int zoneHD1, int zoneHD2)
{
	if (clicSource.x > zoneBG1 && clicSource.y > zoneBG2 && clicSource.x < zoneHD1 && clicSource.y < zoneHD2)
		return true;
	return false;
}

POINT* numCasesPossibles_to_Point(numCase* numCasesPossibles, INTERFACE_GRAPHIQUE ig, int nbCasesPossibles)
{
	int i;
	POINT p;
	POINT* pointsCasesPossibles = NULL;
	pointsCasesPossibles = (POINT *)malloc(nbCasesPossibles * sizeof(POINT));

	for (i = 0; i < nbCasesPossibles; i++)
	{
		p = numCase_to_point(numCasesPossibles[i], ig);
		pointsCasesPossibles[i] = p;
	}

	return pointsCasesPossibles;
}

BOOL est_second_coup_valide(numCase* casesPossibles, numCase destination, int taille)
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

BOOL est_premier_coup_valide(POINT clicSource, COULP joueurActuel, INTERFACE_GRAPHIQUE ig)
{
	numCase source = clic_to_numCase(clicSource, ig);
	PIECE PSource = tabDamier[source.c][source.l];

	if (source.c >= 0 && source.l >= 0 && source.c < 10 && source.l < 10)
	{
		if (joueurActuel == PSource.coulP && PSource.typeP != VIDE)
			return true;
	}

	return false;
}

BOOL verifie_partie_finie(COULP joueurSuivant)
{
	numCase source;
	int verifTailleCasesPossibles = 0, col, lig;
	int *ptrVerif = &verifTailleCasesPossibles;

	for (col = 0; col < 10; col++)
	{
		for (lig = 0; lig < 10; lig++)
		{
			if (tabDamier[col][lig].typeP != VIDE && tabDamier[col][lig].coulP == joueurSuivant) 
			{
				source.c = col;
				source.l = lig;
				get_numCases_possibles_avant_prise(source, ptrVerif);
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

int deplacer_piece(numCase source, numCase destination, COULP joueurActuel, INTERFACE_GRAPHIQUE ig, THEME th, int piecePrise){
	PIECE P;
	POINT p3, pSource = numCase_to_point(source, ig), pDestination = numCase_to_point(destination, ig);
	
	appliquer_coup(source, destination);
	P = tabDamier[destination.c][destination.l];
	if (absol(destination.c - source.c) == 2)
	{
		numCase entreDeux;
		entreDeux.c = source.c + (destination.c - source.c)/2;
        entreDeux.l = source.l + (destination.l - source.l)/2;
		p3 = numCase_to_point(entreDeux, ig);
		efface_piece(ig, p3, th);
		affiche_pieces_prises(joueurActuel, ig, th, piecePrise);
	}
	
	affiche_deplacement_piece(ig, P, pSource, pDestination, th);
	return absol(destination.c - source.c);
}
