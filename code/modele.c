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
    PIECE pi;
    if (destination.c - source.c != 1) // dans le cas d'une prise
    {
        numCase nc;
        nc.c = destination.c - source.c;
        nc.l = destination.l - source.l;
        tableau[nc.c][nc.l] = tableau[destination.c][destination.l]; // car la destination est toujours vide    
    }

    pi = tableau[destination.c][destination.l];
    tableau[destination.c][destination.l] = tableau[source.c][source.l];
    tableau[source.c][source.l] = pi;
}



BOOL conditions_deplacement(numCase source,numCase destination){
    COULP joueur = tableau[source.c][source.l].coulP;
    if (tableau[destination.c][destination.l].typeP==VIDE)
    {
        if (destination.c-source.c == 1 && destination.l-source.l == 1) // case adjacente a distance de 1 case
            return true;
        if ( destination.c-source.c == 2 && destination.l-source.l == 2) // prise case adjacente a distance de 2 cases
        {
            if (tableau[source.c+1][source.l+1].coulP != joueur) // verification de la couleur du pion pris
                return true;
        }
    }

    return false;
}

numCase* deplacement_possible(numCase source){
    int compteur = 0;
    numCase temp [15];
    for (i = 1; i != 3; i++)
    {
        if (source.c-1)
    }    
}