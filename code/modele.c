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
            printf("ligne : %d, colonne %d, typeP => %d, coulP => %d\n",c,l,tableau[l][c].typeP,tableau[l][c].coulP);
	}
}


void deplacement_modele(numCase source, numCase destination){
    PIECE pi;
    printf("distance = %d",abs(destination.c - source.c));
    if (abs(destination.c - source.c) != 1) // dans le cas d'une prise
    {
        numCase nc;
        nc.c = source.c + (destination.c - source.c)/2;
        nc.l = source.l + (destination.l - source.l)/2;
        tableau[nc.c][nc.l] = tableau[destination.c][destination.l]; // car la destination est toujours vide    
    }

    pi = tableau[destination.c][destination.l];
    tableau[destination.c][destination.l] = tableau[source.c][source.l];
    tableau[source.c][source.l] = pi;
}


numCase* numCases_possibles_apres_prise(numCase source){
    int compteur = 0,i;
    int col [4] = {1,1,-1,-1};
    int lig [4] = {1,-1,1,-1};
    numCase possible,prise,retour;
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
            retour.c = source.c + prise.c;
            retour.l = source.l + prise.l;
            temp[compteur] = retour;
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
    int *col = NULL; int *lig = NULL;
    numCase possible,prise,retour;
    PIECE pi,pi_destination,pi_source;
    numCase *cases_possibles = NULL;
    numCase temp [5];

    pi_source = tableau[source.c][source.l];
    COULP joueur = pi_source.coulP;
    if (pi_source.typeP==PION)
    {
        taille=2;
        col = (int *)malloc(taille*sizeof(int));
        lig = (int *)malloc(taille*sizeof(int));
        if (pi_source.coulP==BLANC)
        {
            col[0] = 1; col[1] = 1;
        } else
        {
            col[0] = -1; col[1] = -1;
        }
        lig[0] = 1; lig[1] = -1;
    } else
    {
        taille=4;
        col = (int *)malloc(taille*sizeof(int));
        lig = (int *)malloc(taille*sizeof(int));
        col[0] = 1; col[1] = 1; col[2] = -1; col[3] = -1;
        lig[0] = 1; lig[1] = -1;lig[2] = 1; lig[3] = -1;
    }

    for (i = 0; i != taille; i++)
    {
        possible.c = col[i]; possible.l = lig[i];
        prise.c = col[i]*2;  prise.l = lig[i]*2;
        if (source.c + possible.c >= 0 && source.l + possible.l >=0 && source.c + possible.c < 10 && source.l + possible.l < 10)
        {
            pi = tableau[source.c + possible.c][source.l + possible.l];
            pi_destination = tableau[source.c + prise.c][source.l + prise.l];
            if (pi.typeP==VIDE)
            {
                retour.c = source.c + possible.c;
                retour.l = source.l + possible.l;
                temp[compteur] = retour;
                compteur++;
            } else if (pi.coulP != joueur && pi_destination.typeP==VIDE)
            {
                retour.c = source.c + prise.c;
                retour.l = source.l + prise.l;
                temp[compteur] = retour;
                compteur++;
            }
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