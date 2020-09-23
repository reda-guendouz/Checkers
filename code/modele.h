int tableau[10][10];
/************************
* Tableau :
* -1 => case claire (impossible de s'y déplacer)
* 0  => case jouable (sombre)
* 1  => case occupée par un pion blanc
* 2  => case occupée par un pion noir
*************************/

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