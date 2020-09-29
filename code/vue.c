#include "vue.h" 


/*******************************
*          Fonctions           *
*******************************/

/*******************************
*      Affichage de piece      *
*******************************/

void affiche_piece_ronde(PIECE P, POINT p, COULEUR clr_pion_clair, COULEUR clr_pion_sombre){
	POINT p1;
	p1.x = p.x-2;
	p1.y = p.y-2;
	draw_fill_circle(p1,RAYON,noir);
	if (P.coulP == NOIR) 
		draw_fill_circle(p,RAYON,clr_pion_sombre);
	else 
		draw_fill_circle(p,RAYON,clr_pion_clair);
}

void affiche_piece_losange(PIECE P, POINT p,COULEUR clr_pion_clair, COULEUR clr_pion_sombre){
	POINT p1,p2,p3;
	p1.x = p.x - 17;
	p1.y = p.y;
	p2.x = p.x;
	p2.y = p.y - 17;
	p3.x = p.x + 17;
	p3.y = p.y;
	if (P.coulP == NOIR) {
		draw_fill_triangle(p1,p2,p3,clr_pion_sombre);
		p2.y = p.y + 17;
		draw_fill_triangle(p1,p2,p3,clr_pion_sombre);
	}
	else {
		draw_fill_triangle(p1,p2,p3,clr_pion_clair);
		p2.y = p.y + 17;
		draw_fill_triangle(p1,p2,p3,clr_pion_clair);
	}
}


/*******************************
*       Affiche case           *
*******************************/


void affiche_case_carre(POINT p1, POINT p2, COULEUR clr) {
	draw_fill_rectangle(p1,p2, clr);
	
}

void affiche_case_ronde(POINT p, COULEUR clr) {
	draw_fill_circle(p,RAYON,clr);
	draw_circle(p,RAYON,noir);
}

/*******************************
*       Effacer une piece      *
*******************************/

void efface_piece_ronde(POINT p,COULEUR clr) {
	POINT p1,p2;
	p1.x = p.x - TAILLE_CASE/2;
	p1.y = p.y - TAILLE_CASE/2;
	p2.x = p.x + TAILLE_CASE/2;
	p2.y = p.y + TAILLE_CASE/2;
	affiche_case_carre(p1,p2, clr);
}

void efface_piece_losange(POINT p, COULEUR clr) {
	affiche_case_ronde(p, clr);
}

/*******************************
*      Deplacement piece       *
*******************************/


void affiche_deplacement_piece_ronde(PIECE P,POINT p1, POINT p2, COULEUR clr_case_sombre, COULEUR clr_pion_clair, COULEUR clr_pion_sombre) {
	efface_piece_ronde(p1, clr_case_sombre);
	affiche_piece_ronde(P, p2, clr_pion_clair,clr_pion_sombre);
}

void affiche_deplacement_piece_losange(PIECE P,POINT p1, POINT p2, COULEUR clr_case_sombre, COULEUR clr_pion_clair, COULEUR clr_pion_sombre){ 
	efface_piece_losange(p1, clr_case_sombre);
	affiche_piece_losange(P,p2,clr_pion_clair,clr_pion_sombre);
}


/*******************************
*        Affiche damier        *
*******************************/

void affiche_damier_classique(COULEUR clr_case_claire, COULEUR clr_case_sombre, COULEUR clr_pion_clair, COULEUR clr_pion_sombre)  {
	int i,j;
	PIECE P;
	POINT p1;
	POINT p2;
	for (i = 0; i<10; i++) {
		for (j = 0; j<10; j++) {
			p1.x =i*TAILLE_CASE +300;
			p1.y =j*TAILLE_CASE + 25;
			p2.x = p1.x + TAILLE_CASE;
			p2.y = p1.y + TAILLE_CASE;
			if ((i+j)%2 == 0)
				affiche_case_carre(p1,p2, clr_case_claire);
			else { 
				affiche_case_carre(p1,p2, clr_case_sombre);
				p1.x += TAILLE_CASE/2;
				p1.y += TAILLE_CASE/2;
				P = tableau[i][j];
				if (P.typeP == PION)
					affiche_piece_ronde(P,p1,clr_pion_clair,clr_pion_sombre);
			
			}
		}
	}
	p2.x = 300;
	p2.y = 25;
	p1.x += TAILLE_CASE;
	p1.y += TAILLE_CASE;
	draw_rectangle(p2,p1,noir);
	affiche_all();
}

void affiche_damier_alternatif(COULEUR clr_case_claire, COULEUR clr_case_sombre, COULEUR clr_pion_clair, COULEUR clr_pion_sombre) {
	int i,j;
	PIECE P;
	POINT p1;
	for (i = 0; i<10; i++) {
		for (j = 0; j<10; j++) {
			p1.x =i*TAILLE_CASE + 300;
			p1.y =j*TAILLE_CASE + 50;
			if ((i+j)%2 == 0)
				affiche_case_ronde(p1, clr_case_claire);
			else { 
				affiche_case_ronde(p1, clr_case_sombre);
				P = tableau[j][i];
				if (P.typeP == PION)
					affiche_piece_losange(P,p1,clr_pion_clair,clr_pion_sombre);
			}
		}
	}
	affiche_all();
}

void affiche_retour_menu() {
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

void affiche_plateau(DAMIER_CHOIX choix, COULEUR clr_case_claire, COULEUR clr_case_sombre, COULEUR clr_pion_clair, COULEUR clr_pion_sombre) {	
	POINT p;
	fill_screen(argent);
	p.x = 5;
	p.y = 500;
	aff_pol("Piece obtenu par Joueur 1 :",15,p,marron);
	p.x = 800;
	p.y = 500;
	aff_pol("Piece obtenu par Joueur 2 :",15,p,marron);
	p.x = 300;
	p.y = 600;
	aff_pol("Tour du joueur :",30,p,marron);
	affiche_retour_menu();
	if (choix == CLASSIQUE) {
		affiche_damier_classique(clr_case_claire,clr_case_sombre,clr_pion_clair,clr_pion_sombre);
	}
	else {
		affiche_damier_alternatif(clr_case_claire,clr_case_sombre,clr_pion_clair,clr_pion_sombre);
	}
}
