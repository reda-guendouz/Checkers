#include "modele.h"


void init_tabDamier ()
{
    int i,j;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if ((i+j)%2==0)
                tableau[i][j].typeP=VIDE;
            else
            {
                tableau[i][j].typeP=VIDE;
                if (i<4)
                {
                    tableau[i][j].typeP=PION;
                    tableau[i][j].coulP=BLANC;
                }
                else if (i>5)
                {
                    tableau[i][j].typeP=PION;
                    tableau[i][j].coulP=NOIR;
                }
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
            printf("ligne : %d, colonne %d, typeP => %d, coulP => %d\n",c,l,tableau[l][c].typeP,tableau[l][c].coulP);
		}		
	}
}


void deplacement(numCase source, numCase destination){ 
    int i;
    if (destination.c - source.c != 1)
    {
        numCase nc;
        nc.c = destination.c - source.c;
        nc.l = destination.l - source.l;
        tableau[nc.c][nc.l].typeP=VIDE;     
    }

    tableau[destination.c][destination.l].typeP = tableau[source.c][source.l].typeP;
    tableau[source.c][source.l].typeP = VIDE;
}
