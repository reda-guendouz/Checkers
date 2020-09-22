#include "graphics.h" 
 

/*******************************
*          Fonctions           *
*******************************/

void dessiner_case(POINT centre,int taille,COULEUR clr){
    POINT p1,p2;
    p1.x = centre.x - taille;
    p1.y = centre.y - taille;

    p2.x = centre.x + taille;
    p2.y = centre.y + taille;

    draw_fill_rectangle(p1,p2,clr);
}

void reset_screen() {
    affiche_auto_off();
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
    affiche_auto_off();
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
    POINT P2;
    P2.x = 5; P2.y = 580;
    aff_pol("Au tour de :",50,P2,vert);
    P2.x = 505; P2.y = 500;
    aff_pol("Pions restants (noir) :",20,P2,vert);
    P2.x = 505; P2.y = 250;
    aff_pol("Pions restants (blanc) :",20,P2,vert);
    affiche_all();
}

void affiche_parametre() {
    affiche_auto_off();
    POINT P1;
    P1.x = 5;
    P1.y = 580;
    aff_pol("Choisissez vos parametres de jeu :",40,P1, blanc);
    P1.x = 5;
    P1.y = 480;
    aff_pol("Choisissez un theme de couleur :", 30, P1, blanc);
    P1.x = 55;
    P1.y = 400;
    aff_pol("Theme Original :", 30, P1, blanc);
    P1.x = 55;
    P1.y = 280;
    aff_pol("Theme Sombre :", 30, P1, blanc);    
    
    affiche_all();

}

void affiche_menu_principal() {
    affiche_auto_off();
    POINT P1;
    P1.x = 180;
    P1.y = 580;
    aff_pol("CHECKERS",80,P1, blanc);
    P1.x = 220;
    P1.y = 380;
    aff_pol("Jouer (FLECHE HAUT)", 30, P1, blanc);
    P1.x = 190;
    P1.y = 300;
    aff_pol("Parametre (FLECHE BAS)", 30, P1, blanc);
    P1.x = 275;
    P1.y = 80;
    aff_pol("Appuyer sur ECHAP pour quitter la fenetre", 10, P1, blanc);
    P1.x = 250;
    P1.y = 60;
    aff_pol("Realise par Marwane BAHRAOUI & Reda GUENDOUZ", 10, P1, blanc);


    affiche_all();

}
