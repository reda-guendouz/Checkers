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
                if (P1.y<200)
                    draw_fill_circle(P1,23,blanc);
                else if (P1.y>300)
                    draw_fill_circle(P1,23,noir);                
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
}
