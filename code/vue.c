#include "vue.h" 
 

/*******************************
*          Fonctions           *
*******************************/

/*******************************
*      Affichage de piece      *
*******************************/

void affiche_piece_ronde(PIECE P, POINT p){
	if (P.coulP == NOIR) 
		draw_fill_circle(p,RAYON,noir);
	else 
		draw_fill_circle(p,RAYON,blanc);	
	
}

void affiche_piece_losange(PIECE P, POINT p) {
	POINT p1,p2,p3;
	p1.x = p.x - 17;
	p1.y = p.y;
	p2.x = p.x;
	p2.y = p.y - 17;
	p3.x = p.x + 17;
	p3.y = p.y;
	if (P.coulP == NOIR) {
		draw_fill_triangle(p1,p2,p3,noir);
		p2.y = p.y + 17;
		draw_fill_triangle(p1,p2,p3,noir);
	}
	else {
		draw_fill_triangle(p1,p2,p3,blanc);
		p2.y = p.y + 17;
		draw_fill_triangle(p1,p2,p3,blanc);
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

void efface_piece_ronde(POINT p) {
	POINT p1,p2;
	p1.x = p.x - TAILLE_CASE/2;
	p1.y = p.y - TAILLE_CASE/2;
	p2.x = p.x + TAILLE_CASE/2;
	p2.y = p.y + TAILLE_CASE/2;
	printf("p1: %d %d\n",p1.x,p1.y);
	printf("p2: %d %d\n",p2.x,p2.y);
	affiche_case_carre(p1,p2, marron);
}

void efface_piece_losange(POINT p) {
	affiche_case_ronde(p, marron);
}

/*******************************
*      Deplacement piece       *
*******************************/


void affiche_deplacement_piece_ronde(PIECE P,POINT p1, POINT p2) {
	efface_piece_ronde(p1);
	affiche_piece_ronde(P, p2);
}

void affiche_deplacement_piece_losange(PIECE P,POINT p1, POINT p2) {
	efface_piece_losange(p1);
	affiche_piece_losange(P,p2);
}


/*******************************
*        Affiche damier        *
*******************************/

void affiche_damier_classique() {
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
				affiche_case_carre(p1,p2, argent);
			else { 
				affiche_case_carre(p1,p2, marron);
				p1.x += TAILLE_CASE/2;
				p1.y += TAILLE_CASE/2;
				P = tableau[i][j];
				if (P.typeP == PION)
					affiche_piece_ronde(P,p1);
			
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

void affiche_damier_alternatif() {
	int i,j;
	PIECE P;
	POINT p1;
	for (i = 0; i<10; i++) {
		for (j = 0; j<10; j++) {
			p1.x =i*TAILLE_CASE + 300;
			p1.y =j*TAILLE_CASE + 50;
			if ((i+j)%2 == 0)
				affiche_case_ronde(p1, argent);
			else { 
				affiche_case_ronde(p1, marron);
				P = tableau[j][i];
				if (P.typeP == PION)
					affiche_piece_losange(P,p1);
			
			}
		}
	}
	affiche_all();
}
