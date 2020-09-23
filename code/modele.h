typedef enum{
    VIDE,PION,DAME
}TYPEP;

typedef enum{
    NOIR,BLANC
}COULP;

typedef struct PIECE
{
    TYPEP typeP;
    COULP coulP;
}PIECE;

/*
* tableau global a tout le projet
*/
PIECE tableau[10][10];

typedef struct numCase
{
	int l;
	int c;
}numCase;


void init_tabDamier ();

void test_afficheTab();

numCase clic_to_numCase(POINT p);

void deplacement(numCase source, numCase destination);

int est_dans_la_zone(POINT p);

POINT numCase_to_point(numCase nc);