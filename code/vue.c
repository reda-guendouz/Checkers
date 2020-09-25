#include "vue.h" 
 

/*******************************
*          Fonctions           *
*******************************/

void affiche_piece_ronde(PIECE P, POINT p){
	if (P.coulP == NOIR) 
		draw_fill_circle(p,25,noir);
	else 
		draw_fill_circle(p,25,blanc);	
	
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

void affiche_case_carre(POINT p1, POINT p2, COULEUR clr) {
	draw_fill_rectangle(p1,p2, clr);
	
}

void affiche_case_ronde(POINT p,int rayon, COULEUR clr) {
	draw_fill_circle(p,rayon,clr);
}

void affiche_damier_classique() {
	int i,j;
	PIECE P;
	POINT p1;
	POINT p2;
	for (i = 0; i<10; i++) {
		for (j = 0; j<10; j++) {
			p1.x =i*50;
			p1.y =j*50;
			p2.x = p1.x + 50;
			p2.y = p1.y + 50;
			if ((i+j)%2 == 0)
				affiche_case_carre(p1,p2, argent);
			else { 
				affiche_case_carre(p1,p2, gris);
				p1.x += 25;
				p1.y += 25;
				P = tableau[i][j];
				if (P.typeP == PION)
					affiche_piece_ronde(P,p1);
			
			}
		}
	}
	affiche_all();
}

void affiche_damier_alternatif() {
	int i,j;
	PIECE P;
	POINT p1;
	for (i = 0; i<10; i++) {
		for (j = 0; j<10; j++) {
			p1.x =i*50 + 22;
			p1.y =j*50 + 22;
			if ((i+j)%2 == 0)
				affiche_case_ronde(p1,20, argent);
			else { 
				affiche_case_ronde(p1,20, gris);
				P = tableau[j][i];
				if (P.typeP == PION)
					affiche_piece_losange(P,p1);
			
			}
		}
	}
	affiche_all();
}

/*
void dessiner_case(POINT centre,int taille,COULEUR clr){
    POINT p1,p2;
    p1.x = centre.x - taille;
    p1.y = centre.y - taille;

    p2.x = centre.x + taille;
    p2.y = centre.y + taille;

    draw_fill_rectangle(p1,p2,clr);
}

void reset_screen() {
    POINT p1,p2;
    p1.x = 0;
    p1.y = 0;

    p2.x = 800;
    p2.y = 800;

    draw_fill_rectangle(p1,p2,noir);
    affiche_all();
}

void creation_damier(){
    POINT P1;
    P1.x=25;
    P1.y=25;
    for(P1.x=25;P1.x!=525;P1.x+=50){
        for (P1.y = 25;P1.y!=525;P1.y+=50)
        {
            if ((P1.x+P1.y)%100==0)
                dessiner_case(P1,25,argent); // dessiner case claire
            else
            {
                dessiner_case(P1,25,gris); // dessiner case foncee
                if (P1.x<200)
                    draw_fill_circle(P1,23,blanc); // dessiner pion blanc
                else if (P1.x>300)
                    draw_fill_circle(P1,23,noir); // dessiner pion noir               
            }
        }
        
    }

 */
