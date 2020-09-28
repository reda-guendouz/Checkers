#define RAYON 22
#define TAILLE_CASE 50

typedef enum{
    CLASSIQUE,ALTERNATIF
}DAMIER_CHOIX;



/*******************************
*      Affichage de piece      *
*******************************/

void affiche_piece_ronde(PIECE P, POINT p, COULEUR clr_pion_clair, COULEUR clr_pion_sombre);

void affiche_piece_losange(PIECE P, POINT p,COULEUR clr_pion_clair, COULEUR clr_pion_sombre);

/*******************************
*       Affiche case           *
*******************************/

void affiche_case_carre(POINT p1, POINT p2, COULEUR clr);

void affiche_case_ronde(POINT p, COULEUR clr);

/*******************************
*       Effacer une piece      *
*******************************/

void efface_piece_ronde(POINT p,COULEUR clr);

void efface_piece_losange(POINT p, COULEUR clr);

/*******************************
*      Deplacement piece       *
*******************************/

void affiche_deplacement_piece_ronde(PIECE P,POINT p1, POINT p2, COULEUR clr_case_sombre, COULEUR clr_pion_clair, COULEUR clr_pion_sombre);

void affiche_deplacement_piece_losange(PIECE P,POINT p1, POINT p2, COULEUR clr_case_sombre, COULEUR clr_pion_clair, COULEUR clr_pion_sombre);

/*******************************
*        Affiche damier        *
*******************************/

void affiche_damier_classique(COULEUR clr_case_claire, COULEUR clr_case_sombre, COULEUR clr_pion_clair, COULEUR clr_pion_sombre);

void affiche_damier_alternatif(COULEUR clr_case_claire, COULEUR clr_case_sombre, COULEUR clr_pion_clair, COULEUR clr_pion_sombre);

/*******************************
*        Affiche Plateau       *
*******************************/

void affiche_plateau(DAMIER_CHOIX choix, COULEUR clr_case_claire, COULEUR clr_case_sombre, COULEUR clr_pion_clair, COULEUR clr_pion_sombre);
