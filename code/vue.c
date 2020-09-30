#include "vue.h" 


/*******************************
*          Fonctions           *
*******************************/

/*******************************
*         Reset screen         *
*******************************/

void reset_affichage_screen(COULEUR clr) {
	POINT p1, p2;
	p1.x = 0; p1.y = 0;
	p2.x = LARGEUR_FENETRE ; p2.y = HAUTEUR_FENETRE;
	draw_fill_rectangle(p1,p2,clr);
}

/*******************************
*      Affichage de piece      *
*******************************/

void affiche_piece_ronde(PIECE P, POINT p, THEME theme){
	POINT p1;
	p1.x = p.x-2;
	p1.y = p.y-2;
	draw_fill_circle(p1,RAYON,noir);
	if (P.coulP == NOIR) 
		draw_fill_circle(p,RAYON,theme.pionSombre);
	else 
		draw_fill_circle(p,RAYON,theme.pionClair);
}

void affiche_piece_losange(PIECE P, POINT p,THEME theme){
	POINT p1,p2,p3;
	p1.x = p.x - 17;
	p1.y = p.y;
	p2.x = p.x;
	p2.y = p.y - 17;
	p3.x = p.x + 17;
	p3.y = p.y;
	if (P.coulP == NOIR) {
		draw_fill_triangle(p1,p2,p3,theme.pionSombre);
		p2.y = p.y + 17;
		draw_fill_triangle(p1,p2,p3,theme.pionSombre);
	}
	else {
		draw_fill_triangle(p1,p2,p3,theme.pionClair);
		p2.y = p.y + 17;
		draw_fill_triangle(p1,p2,p3,theme.pionClair);
	}
}


/*******************************
*       Affiche case           *
*******************************/


void affiche_case_carre(POINT p1, COULEUR clr) {
	POINT p2;
	p2.x = p1.x + TAILLE_CASE;
	p2.y = p1.y + TAILLE_CASE;
	draw_fill_rectangle(p1,p2, clr);
	
}

void affiche_case_ronde(POINT p, COULEUR clr) {
	draw_fill_circle(p,RAYON,clr);
	draw_circle(p,RAYON,noir);
}

/*******************************
*       Effacer une piece      *
*******************************/

void efface_piece_ronde(POINT p, THEME theme) {
	POINT p1;
	p1.x = p.x - TAILLE_CASE/2;
	p1.y = p.y - TAILLE_CASE/2;
	affiche_case_carre(p1, theme.caseSombre);
}

void efface_piece_losange(POINT p, THEME theme) {
	affiche_case_ronde(p, theme.caseSombre);
}

/*******************************
*      Deplacement piece       *
*******************************/

void affiche_deplacement_piece(INTERFACE_GRAPHIQUE ig, PIECE P,POINT p1, POINT p2, THEME theme) {
	if (ig == CLASSIQUE) {
		efface_piece_ronde(p1, theme);
		affiche_piece_ronde(P, p2, theme);
	}
	else {
		efface_piece_losange(p1, theme);
		affiche_piece_losange(P,p2,theme);
	} 
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
	p1.y = 350;
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
					if ((j+k)%2 == 0) {
						affiche_case_carre(p2, th.caseSombre);
						p2.x += TAILLE_CASE/2;
						p2.y += TAILLE_CASE/2;
						if (ig == CLASSIQUE)
							affiche_piece_ronde(P,p2,th);
						else
							affiche_piece_losange(P,p2,th);
						P.coulP = NOIR;
					}
					else
						affiche_case_carre(p2, th.caseClaire);

			}
		}
		if (i == 2) {
			p1.x = 	325 + 300;
			p1.y = 350  - 250;
		}
		else if (i == 1) {
			p1.y =  350 - 250;
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

void affiche_damier_classique(THEME theme)  {
	int i,j;
	PIECE P;
	POINT p1;
	POINT p2;
	for (i = 0; i<10; i++) {
		for (j = 0; j<10; j++) {
			p1.x =i*TAILLE_CASE +275;
			p1.y =j*TAILLE_CASE + 25;
			if ((i+j)%2 == 0)
				affiche_case_carre(p1, theme.caseClaire);
			else { 
				affiche_case_carre(p1, theme.caseSombre);
				p1.x += TAILLE_CASE/2;
				p1.y += TAILLE_CASE/2;
				P = tableau[i][j];
				if (P.typeP == PION)
					affiche_piece_ronde(P,p1,theme);
			}
		}
	}
	p2.x = 275;
	p2.y = 25;
	p1.x += TAILLE_CASE;
	p1.y += TAILLE_CASE;
	draw_rectangle(p2,p1,noir);
	affiche_all();
}

void affiche_damier_alternatif(THEME theme) {
	int i,j;
	PIECE P;
	POINT p1;
	for (i = 0; i<10; i++) {
		for (j = 0; j<10; j++) {
			p1.x =i*TAILLE_CASE + 300;
			p1.y =j*TAILLE_CASE + 50;
			if ((i+j)%2 == 0)
				affiche_case_ronde(p1, theme.caseClaire);
			else { 
				affiche_case_ronde(p1, theme.caseSombre);
				P = tableau[j][i];
				if (P.typeP == PION)
					affiche_piece_losange(P,p1,theme);
			}
		}
	}
	affiche_all();
}

/*******************************
*        Affiche Menu          *
*******************************/

BOOL affiche_menu() {
	POINT p1;
	affiche_menu_principal();
	p1 = wait_clic();
	if(p1.x >= 475 && p1.x <= 625 && p1.y >= 365 && p1.y <= 465) {
		affiche_menu_partie();
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
	reset_affichage_screen(noir);	
	POINT p1,p2;
	p1.x = 425;p1.y = 625;
	aff_pol("CHECKERS",45,p1,blanc);
	p2.x = 675 ; p2.y = 565;
	affiche_menu_cadre (p1,p2,blanc);

	p1.x = 475;p1.y = 425;
	aff_pol("JOUER",45,p1,blanc);
	p2.x = 625 ; p2.y = 365;
	affiche_menu_cadre (p1,p2,rouge);

	p1.x = 375;p1.y = 75;
	aff_pol("Realise par Marwane BAHRAOUI & Reda GUENDOUZ",15,p1,blanc);
	
	affiche_all();
}

void affiche_menu_partie() {
	reset_affichage_screen(noir);
	POINT p1;
	INTERFACE_GRAPHIQUE ig = CLASSIQUE;
	
	p1.x = 350;p1.y = 600;
	aff_pol("CHOISIR UN THEME",35,p1,blanc);
	
	affiche_themes(ig);
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
	if (ig == CLASSIQUE) {
		affiche_damier_classique(theme);
	}
	else {
		affiche_damier_alternatif(theme);
	}
}
