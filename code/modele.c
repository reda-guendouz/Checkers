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
		}		
	}
}

numCase clic_to_numCase(POINT p){
	numCase nc;
	nc.c = p.x/50;
	nc.l = p.y/50;
	return nc;
}