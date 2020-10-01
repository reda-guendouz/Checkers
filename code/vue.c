#include "vue.h" 


/*******************************
*          Fonctions           *
*******************************/



/*******************************
*      Affichage de piece      *
*******************************/

void affiche_piece(INTERFACE_GRAPHIQUE ig,PIECE P, POINT p, THEME theme) {
	POINT p1,p2,p3;
	if (ig == CLASSIQUE) {
		p1.x = p.x-2;
		p1.y = p.y-2;
		draw_fill_circle(p1,RAYON,noir);
		if (P.coulP == NOIR) 
			draw_fill_circle(p,RAYON,theme.pionSombre);
		else 
			draw_fill_circle(p,RAYON,theme.pionClair);
		p1.x -= 5;
		p1.y += 17;
		if (P.typeP == DAME)
			aff_pol("D",22,p1,noir);
	}
	else {
		p1.x = p.x - 17;
		p1.y = p.y;
		p2.x = p.x;
		p2.y = p.y - 17;
		p3.x = p.x + 17;
		p3.y = p.y;
		if (P.coulP == NOIR) {
			draw_fill_triangle(p1,p2,p3,theme.pionSombre);
			draw_triangle(p1,p2,p3,noir);
			p2.y = p.y + 17;
			draw_fill_triangle(p1,p2,p3,theme.pionSombre);	
		}
		else {
			draw_fill_triangle(p1,p2,p3,theme.pionClair);
			draw_triangle(p1,p2,p3,noir);
			p2.y = p.y + 17;
			draw_fill_triangle(p1,p2,p3,theme.pionClair);
		}
		p1.x += 9;
		p1.y += 16;
		if (P.typeP == DAME)
			aff_pol("D",22,p1,noir);
	}	
}

/*******************************
*       Affiche case           *
*******************************/


void affiche_case(INTERFACE_GRAPHIQUE ig, POINT p1, COULEUR clr) {
	POINT p2;
	if (ig == CLASSIQUE) {
		p2.x = p1.x + TAILLE_CASE;
		p2.y = p1.y + TAILLE_CASE;
		draw_fill_rectangle(p1,p2, clr);
	}
	else {
		draw_fill_circle(p1,RAYON,clr);
		draw_circle(p1,RAYON,noir);
	}
}

/*******************************
*       Effacer une piece      *
*******************************/

void efface_piece(INTERFACE_GRAPHIQUE ig, POINT p1, THEME theme) {
	if (ig == CLASSIQUE) {
		p1.x = p1.x - TAILLE_CASE/2;
		p1.y = p1.y - TAILLE_CASE/2;
	}
	affiche_case(ig,p1, theme.caseSombre);
}

/*******************************
*      Deplacement piece       *
*******************************/

void affiche_deplacement_piece(INTERFACE_GRAPHIQUE ig, PIECE P,POINT p1, POINT p2, THEME theme) {
	efface_piece(ig,p1, theme);
	affiche_piece(ig,P, p2, theme);
	affiche_all();
}

/*******************************
*             THEMES           *
*******************************/

void init_themes() {
	THEME th;
	th.caseClaire = beige;
	th.caseSombre = brown;
	th.pionClair  = blanc;
	th.pionSombre = darkgray;
	themes[0] = th;
	th.caseClaire = darkgray;
	th.caseSombre = gray;
	th.pionClair  = darksalmon;
	th.pionSombre = darkred;
	themes[1] = th;
	th.caseClaire = beige;
	th.caseSombre = lightblue;
	th.pionClair  = darkcyan;
	th.pionSombre = darkblue;
	themes[2] = th;
	th.caseClaire = beige;
	th.caseSombre = darkmagenta;
	th.pionClair  = darkorange;
	th.pionSombre = darkred;
	themes[3] = th;
}

void affiche_themes(INTERFACE_GRAPHIQUE ig) {	
	int i,j,k;
	POINT p1,p2;
	PIECE P;
	P.typeP = PION;
	THEME th;
	p1.x = 325;
	p1.y = 400;
	for (i = 0; i!= 4;i++) {
		th = themes[i];
		P.coulP = BLANC;
		p2.x = p1.x;
		p2.y = p1.y;
		for (j = 0; j <2; j++)
		{
			for (k = 0; k<2; k++) {
				p2.x = p1.x + k*TAILLE_CASE;
				p2.y = p1.y + j*TAILLE_CASE;
				if (ig == ALTERNATIF) {
					p2.x += TAILLE_CASE/2;
					p2.y += TAILLE_CASE/2;
				}
				if ((j+k)%2 == 0) {
					affiche_case(ig,p2,th.caseSombre);
					if (ig == CLASSIQUE) {
						p2.x += TAILLE_CASE/2;
						p2.y += TAILLE_CASE/2;
					}
					affiche_piece(ig,P,p2,th);
					P.coulP = NOIR;
				}
				else
					affiche_case(ig,p2, th.caseClaire);
			}
		}
		if (i == 2) {
			p1.x = 325 + 300;
			p1.y = 400  - 200;
		}
		else if (i == 1) {
			p1.y = 400 - 200;
			p1.x = 325; 
		}
		else if (i == 0)
			p1.x = 325 + 300;
	}
	affiche_all();	
}

/*******************************
*        Affiche damier        *
*******************************/

void affiche_damier(INTERFACE_GRAPHIQUE ig, THEME theme) {
	int i,j,ecartX =300, ecartY =50;
	PIECE P;
	POINT p1;
	POINT p2;
	if(ig == CLASSIQUE){
		ecartX = 275;
		ecartY = 25;
	}
	for (i = 0; i<10; i++) {
		for (j = 0; j<10; j++) {
			p1.x =i*TAILLE_CASE + ecartX;
			p1.y =j*TAILLE_CASE + ecartY;
			if ((i+j)%2 == 0)
				affiche_case(ig,p1, theme.caseClaire);
			else { 
				affiche_case(ig,p1,theme.caseSombre);
				if (ig == CLASSIQUE) {
					p1.x += TAILLE_CASE/2;
					p1.y += TAILLE_CASE/2;
				}
				if (ig == CLASSIQUE)
					P = tableau[i][j];
				else 
					P = tableau[j][i];
				if (P.typeP != VIDE)
					affiche_piece(ig,P,p1,theme);
			}
		}
	}
	if (ig == CLASSIQUE) {
		p2.x = 275;
		p2.y = 25;
		p1.x += TAILLE_CASE;
		p1.y += TAILLE_CASE;
		draw_rectangle(p2,p1,noir);
	}
	affiche_all();
}


/*******************************
*        Affiche Menu          *
*******************************/

BOOL affiche_menu() {
	POINT p1;
	INTERFACE_GRAPHIQUE ig = CLASSIQUE;
	affiche_menu_principal();
	p1 = wait_clic();
	if(p1.x >= 475 && p1.x <= 625 && p1.y >= 365 && p1.y <= 465) {
		affiche_menu_partie_ig();
		affiche_menu_partie_theme(ig);
		wait_clic();
		return true;
	}
	else 
		return false;
}

void affiche_menu_cadre(POINT p1, POINT p2, COULEUR clr) {
	int i;
	for (i = 1; i<4;i+=2) {
		p1.x -= i ;p1.y -= i;
		p2.x += i ;p2.y += i;
		draw_rectangle(p1,p2,clr);
	}	
}

void affiche_menu_principal() {
	POINT p1,p2;
	reset_affichage_screen(noir);	
	p1.x = 425;p1.y = 625;
	aff_pol("CHECKERS",45,p1,blanc);
	p2.x = 675 ; p2.y = 565;
	affiche_menu_cadre (p1,p2,blanc);

	p1.x = 475;p1.y = 425;
	aff_pol("JOUER",45,p1,blanc);
	p2.x = 625 ; p2.y = 365;
	affiche_menu_cadre (p1,p2,vert);

	p1.x = 450;p1.y = 330;
	aff_pol("QUITTER",45,p1,blanc);
	p2.x = 650 ; p2.y = 270;
	affiche_menu_cadre (p1,p2,rouge);

	p1.x = 375;p1.y = 100;
	aff_pol("Realise par Marwane BAHRAOUI & Reda GUENDOUZ",15,p1,blanc);
	
	affiche_all();
}

void affiche_menu_fleche_theme(THEME th, BOOL afficheEfface) {
	POINT p1,p2,p3;
	COULEUR clr = noir;
	COULEUR thActuel = th.caseSombre;
	if (afficheEfface)
		clr = vert;
	
	if (thActuel == themes[0].caseSombre) {
		p1.x = 475;p1.y = 450;
		p2.x = 525;p2.y = 460;
	}
	else if (thActuel == themes[1].caseSombre) {
		p1.x = 775;p1.y = 450;
		p2.x = 825;p2.y = 460;
	}
	else if (thActuel == themes[2].caseSombre) {
		p1.x = 475;p1.y = 245;
		p2.x = 525;p2.y = 255;
	}
	else { 	
		p1.x = 775;p1.y = 245;
		p2.x = 825;p2.y = 255;
	}
	draw_fill_rectangle(p1,p2,clr);
	p3.x = p1.x; p3.y = p1.y - 10;
	p2.x = p1.x; p2.y = p1.y + 20;
	p1.x -= 15; p1.y += 5;
	draw_fill_triangle(p1,p2,p3,clr);
	affiche_all();
}

void affiche_menu_partie_theme(INTERFACE_GRAPHIQUE ig) {
	POINT p1,p2;
	reset_affichage_screen(noir);
	
	p1.x = 350;p1.y = 600;
	aff_pol("CHOISIR UN THEME",35,p1,blanc);	
	affiche_themes(ig);

	p1.x = 430;p1.y = 100;
	aff_pol("LANCER LA PARTIE",25,p1,blanc);
	p1.x = 420;p1.y = 60;
	p2.x = 685; p2.y = 110;
	affiche_menu_cadre(p1,p2,vert);
	affiche_all();
}

void affiche_menu_partie_ig() {
	POINT p1,p2;
	reset_affichage_screen(noir);

	p1.x =330;p1.y =600;
	aff_pol("CHOISIR UNE INTERFACE",35,p1,blanc);
	p1.x = 320; p1.y = 550;
	p2.x = 790; p2.y = 610;
	affiche_menu_cadre(p1,p2,blanc);

	p1.x = 460; p1.y = 400;
	aff_pol("CLASSIQUE",30,p1,blanc);
	p1.x = 450; p1.y = 350;
	p2.x = 650; p2.y = 410;
	affiche_menu_cadre(p1,p2,bleu);
	
	p1.x = 457; p1.y = 300;
	aff_pol("ALTERNATIF",30,p1,blanc);
	p1.x = 447; p1.y = 250;
	p2.x = 653; p2.y = 310;
	affiche_menu_cadre(p1,p2,jaune);
	affiche_all();
}

void affiche_menu_retour() {
	POINT p1,p2,p3;
	p1.x = 30 ;
	p1.y = 565;
	p2.x = 80 ;
	p2.y = 610;
	draw_fill_rectangle(p1,p2,darkgreen);
	p1.x = 38;
	p1.y = 573;
	p2.x = 73;
	draw_fill_rectangle(p1,p2,argent);
	p1.x = 20;
	p1.y = 600;
	p2.x = 90;
	p2.y = 600;
	p3.x = 55;
	p3.y = 640;
	draw_fill_triangle(p1,p3,p2,darkblue);
	p1.x = 30;
	p2.x = 80;
	p3.y = 630;
	draw_fill_triangle(p1,p3,p2,argent);
	p1.x = 45;
	p1.y = 615;
	aff_pol("H",30,p1,brown);
}

void affiche_menu_apres_partie(FIN fin, THEME th) {
	POINT p1,p2;
	reset_affichage_screen(noir);
	if (fin == VICTOIREJOUEUR1) {
		p1.x =350;p1.y =600;
		aff_pol("VICTOIRE JOUEUR 1 !",35,p1,th.pionClair);
	}
	else if (fin == VICTOIREJOUEUR2) {
		p1.x =350;p1.y =600;
		aff_pol("VICTOIRE JOUEUR 2 !",35,p1,th.pionSombre);
	}
	else {
		p1.x =450;p1.y =600;
		aff_pol("EGALITE !",35,p1,blanc);
	}
	
	p1.x = 325;p1.y = 450;
	aff_pol("QUE VOULEZ-VOUS FAIRE ?",30,p1,blanc);
	p1.x = 450; p1.y = 300;
	aff_pol("RELANCER",30,p1,blanc);
	p1.x = 440; p1.y = 250;
	p2.x = 620; p2.y = 310;
	affiche_menu_cadre(p1,p2,vert);

	p1.x = 465; p1.y = 200;
	aff_pol("QUITTER",30,p1,blanc);
	p1.x = 455; p1.y = 150;
	p2.x = 610; p2.y = 210;
	affiche_menu_cadre(p1,p2,rouge);
	affiche_all();
}

/*******************************
*        Affiche  Plateau      *
*******************************/

void reset_affichage_screen(COULEUR clr) {
	POINT p1, p2;
	p1.x = 0; p1.y = 0;
	p2.x = LARGEUR_FENETRE ; p2.y = HAUTEUR_FENETRE;
	draw_fill_rectangle(p1,p2,clr);
}

void affiche_joueur(COULEUR joueurActuel,INTERFACE_GRAPHIQUE ig, THEME th) {
	PIECE P;
	POINT p1,p2;
	P.typeP = PION;
	P.coulP = joueurActuel;
	p1.x = 575;p1.y = 550;
	p2.x = 625;p2.y = 600;
	draw_fill_rectangle(p1,p2,lavender);
	p1.x = 600;p1.y = 575;
	affiche_piece(ig,P,p1,th);
	affiche_all();	
}

void affiche_plateau(INTERFACE_GRAPHIQUE ig, THEME theme) {	
	POINT p;
	reset_affichage_screen(lavender);
	p.x = 5;
	p.y = 500;
	aff_pol("Piece obtenu par Joueur 1 :",15,p,marron);
	p.x = 800;
	p.y = 500;
	aff_pol("Piece obtenu par Joueur 2 :",15,p,marron);
	p.x = 300;
	p.y = 600;
	aff_pol("Tour du joueur :",30,p,marron);
	affiche_menu_retour();
	affiche_damier(ig,theme);
}


void affiche_efface_cases_possibles(POINT* pointsCasesPossibles, int nombreCasesPossibles, INTERFACE_GRAPHIQUE ig,THEME th,BOOL afficheEfface) {
	POINT p1;
	int i;
	for (i = 0; i <nombreCasesPossibles; i++) {
		p1 = pointsCasesPossibles[i];
		if (ig == CLASSIQUE) {
			p1.x -= TAILLE_CASE/2;
			p1.y -= TAILLE_CASE/2;
		}
		if (afficheEfface)
			affiche_case(ig,p1,rouge);
		else 
			affiche_case(ig,p1,th.caseSombre);
	}
	affiche_all();	
}

void affiche_pieces_prises(COULEUR clr, INTERFACE_GRAPHIQUE ig, THEME th, int nbPiecesPrises) {
	PIECE P;
	POINT p1;
	P.typeP = PION;
	if (clr == BLANC) {
		p1.x = 50 + (TAILLE_CASE*(nbPiecesPrises/6));p1.y =  400 - (TAILLE_CASE * (nbPiecesPrises%6));
		P.coulP = NOIR;
	}
	else {
		p1.x = 1000 - (TAILLE_CASE*(nbPiecesPrises/6));p1.y = 400 -(TAILLE_CASE * (nbPiecesPrises%6));
		P.coulP = BLANC;
	}
	printf("Affiche piece prises : %d  %d %d\n",p1.x,p1.y,nbPiecesPrises);
	affiche_piece(ig,P,p1,th);
	affiche_all();
}
