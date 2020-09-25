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

void deplacement(numCase source, numCase destination);

BOOL conditions_deplacement(numCase source,numCase destination);

numCase* deplacement_possible(numCase nc);