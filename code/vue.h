#define RAYON 25
#define TAILLE_CASE 50

void affiche_piece_ronde(PIECE P, POINT p);
void affiche_piece_losange(PIECE P, POINT p);

void affiche_case_carre(POINT p1,POINT p2, COULEUR clr);
void affiche_case_rond(POINT p, COULEUR clr);

void efface_piece_ronde(POINT p);
void efface_piece_losange(POINT p);

void affiche_deplacement_piece_ronde(PIECE P,POINT p1, POINT p2);
void affiche_deplacement_piece_losange(PIECE P,POINT p1, POINT p2);

void affiche_damier_classique();
void affiche_damier_alternatif();
