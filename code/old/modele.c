#include "modele.h"

void init_tabDamier ()
{
	int l,c;
	
	for (l=0; l!=10; l++)
	{
		for (c=0; c!=10; c++)
		{
            if ((l+c)%2==1)
                tableau[l][c] = -1;
            else
            {
                tableau[l][c] = 0;
                if (c<4)
                    tableau[l][c] = 1;
                else if (c>5)
                    tableau[l][c] = 2;           
            }
		}		
	}
}

void test_afficheTab(){
    int l,c;
	
	for (l=0; l!=10; l++)
	{
		for (c=0; c!=10; c++)
		{
            printf("ligne : %d, colonne %d, valeur => %d\n",l,c,tableau[l][c]);
:	}		
	}
}

numCase clic_to_numCase(POINT p){
	numCase nc;
	nc.c = p.x/50;
	nc.l = p.y/50;
	return nc;
}

void deplacement(numCase source, numCase destination){
	tableau[destination.c][destination.l] = tableau[source.c][source.l];
	tableau[source.c][source.l] = 0;
}

int est_dans_la_zone(POINT p){
	if (p.x < 500 && p.y < 500)
		return 1;
	return 0;
}

POINT numCase_to_point(numCase nc){
	POINT p;
	p.x = (nc.c*50)+25;
	p.y = (nc.l*50)+25;
	return p;
}
