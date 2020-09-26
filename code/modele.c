#include "modele.h"

int abs(int val){
    if (val<0)
        return -val;
    return val;
}

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
    if (abs(destination.c - source.c) != 1) // dans le cas d'une prise
    {
        numCase nc;
        nc.c = abs((destination.c - source.c)/2);
        nc.l = abs((destination.l - source.l)/2);
        tableau[nc.c][nc.l] = tableau[destination.c][destination.l]; // car la destination est toujours vide    
    }

    pi = tableau[destination.c][destination.l];
    tableau[destination.c][destination.l] = tableau[source.c][source.l];
    tableau[source.c][source.l] = pi;
}



BOOL deplacement_possible(numCase source,numCase destination){
    if (tableau[destination.c][destination.l].typeP==VIDE)
    {
        if (abs(destination.c-source.c) == 1 && abs(destination.l-source.l == 1) && tableau[destination.c][destination.l].typeP==VIDE) // case adjacente a distance de 1 case
            return true;
        else
            return prise_possible(source,destination);
    }

    return false;
}

BOOL prise_possible(numCase source, numCase destination){
    COULP joueur = tableau[source.c][source.l].coulP;
    PIECE pi1,pi2,pi_pion_pris;
    int dist1, dist2;
    dist1 = destination.c - source.c;
    dist2 = destination.l - source.l;
    pi1 = tableau[source.c][source.l];
    pi2 = tableau[destination.c][destination.l];
    pi_pion_pris = tableau[source.c + (dist1/2)][source.l + (dist2/2)];
    if ( abs(dist1)==2 && abs(dist2)==2 && pi2.typeP==VIDE && pi_pion_pris.typeP != VIDE && pi_pion_pris.coulP != joueur )
        return true;
    return false;
}

numCase* numCases_possibles_apres_prise(numCase source){
    int compteur = 0,i;
    int col [4] = {1,1,-1,-1};
    int lig [4] = {1,-1,1,-1};
    numCase possible,prise;
    PIECE pi,pi_destination,pi_source;
    numCase *cases_possibles = NULL;
    numCase temp [5];
    
    pi_source = tableau[source.c][source.l];
    COULP joueur = pi_source.coulP;
    for (i = 0; i != 4; i++)
    {
        possible.c = col[i]; possible.l = lig[i];
        prise.c = col[i]*2;  prise.l = lig[i]*2;
        pi = tableau[possible.c][possible.l];
        pi_destination = tableau[prise.c][prise.l];
        if (pi.coulP != joueur && pi_destination.typeP==VIDE)
        {
            temp[compteur] = prise;
            compteur++;
        }
    }

    if (compteur != 0)
    {
        cases_possibles = (numCase *)malloc(compteur*sizeof(numCase));
        for (i = 0; i != compteur; i++)
            cases_possibles[i] = temp[i];
    }

    return cases_possibles;
}

numCase* numCases_possibles_avant_prise(numCase source){
    int compteur = 0,i,taille;
    numCase possible,prise;
    PIECE pi,pi_destination,pi_source;
    numCase *cases_possibles = NULL;
    numCase temp [5];

    pi_source = tableau[source.c][source.l];
    COULP joueur = pi_source.coulP;
    if (pi_source.typeP==PION)
    {
        taille=2;
        int col [2] = {1,1};
        int lig [2] = {1,-1};
    } else
    {
        taille=4;
        int col [4] = {1,1,-1,-1};
        int lig [4] = {1,-1,1,-1};
    }

    for (i = 0; i != taille; i++)
    {
        possible.c = col[i]; possible.l = lig[i];
        prise.c = col[i]*2;  prise.l = lig[i]*2;
        pi = tableau[possible.c][possible.l];
        pi_destination = tableau[prise.c][prise.l];
        if (pi.typeP==VIDE)
        {
            temp[compteur] = possible;
            compteur++;
        } else if (pi.coulP != joueur && pi_destination.typeP==VIDE)
        {
            temp[compteur] = prise;
            compteur++;
        }
    }

    if (compteur != 0)
    {
        cases_possibles = (numCase *)malloc(compteur*sizeof(numCase));
        for (i = 0; i != compteur; i++)
            cases_possibles[i] = temp[i];
    }
    
    return cases_possibles;
}