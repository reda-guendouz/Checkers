#include "modele.h"

int absol(int val){
    if (val<0)
        return -val;
    return val;
}


void init_tabDamier ()
{
    int i, j;

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if ((i+j)%2==0)
                tabDamier[i][j].typeP=VIDE;
            else
            {
                tabDamier[i][j].typeP=VIDE;
                if (i<4)
                {
                    tabDamier[i][j].typeP=PION;
                    tabDamier[i][j].coulP=BLANC;
                }
                else if (i>5)
                {
                    tabDamier[i][j].typeP=PION;
                    tabDamier[i][j].coulP=NOIR;
                }
            }            
        }
    }   
}

void appliquer_coup(numCase source, numCase destination){
    PIECE PDestinationAvecPrise = tabDamier[destination.c][destination.l];

    if (destination.c==9 || destination.c==0)
    {
        if (tabDamier[source.c][source.l].coulP==NOIR && destination.c==0)
            tabDamier[source.c][source.l].typeP=DAME;
        else if (tabDamier[source.c][source.l].coulP==BLANC && destination.c==9)
            tabDamier[source.c][source.l].typeP=DAME;
    }

    if (absol(destination.c - source.c) != 1)
    {
        numCase nc;

        nc.c = source.c + (destination.c - source.c)/2;
        nc.l = source.l + (destination.l - source.l)/2;
        tabDamier[nc.c][nc.l] = PDestinationAvecPrise;     
    }

    tabDamier[destination.c][destination.l] = tabDamier[source.c][source.l];
    tabDamier[source.c][source.l] = PDestinationAvecPrise;
}


numCase* get_numCases_possibles_apres_prise(numCase source,int *tailleCmpt){
    int compteur=0, i;
    int col [4] = {1,1,-1,-1};
    int lig [4] = {1,-1,1,-1};
    numCase destinationSansPrise, destinationAvecPrise, destinationPossible;
    PIECE PDestinationSansPrise, PDestinationAvecPrise;
    COULP joueur;
    numCase *casesPossibles = NULL;
    casesPossibles = (numCase *)malloc(4*sizeof(numCase));

    if (tabDamier[source.c][source.l].typeP == VIDE)
        return false;
    
    joueur = tabDamier[source.c][source.l].coulP;

    if (joueur == NOIR)
	    joueur = BLANC;
    else 
	    joueur = NOIR;

    for (i = 0; i != 4; i++)
    {
        destinationSansPrise.c = col[i]; destinationSansPrise.l = lig[i];
        destinationAvecPrise.c = col[i]*2;  destinationAvecPrise.l = lig[i]*2;

        PDestinationSansPrise = tabDamier[source.c + destinationSansPrise.c][source.l + destinationSansPrise.l];
        PDestinationAvecPrise = tabDamier[source.c + destinationAvecPrise.c][source.l + destinationAvecPrise.l];
        
        if (PDestinationSansPrise.coulP == joueur && PDestinationAvecPrise.typeP == VIDE && PDestinationSansPrise.typeP != VIDE && 
        source.c + destinationAvecPrise.c >= 0 && source.l + destinationAvecPrise.l >=0 && 
        source.c + destinationAvecPrise.c < 10 && source.l + destinationAvecPrise.l < 10)
        {
            destinationPossible.c = source.c + destinationAvecPrise.c;
            destinationPossible.l = source.l + destinationAvecPrise.l;
            casesPossibles[compteur] = destinationPossible;
            compteur++;
        }
    }

    *tailleCmpt = compteur;
    return casesPossibles;
}

numCase* get_numCases_possibles_avant_prise(numCase source,int *tailleCmpt){
    int compteur = 0, i, taille;
    int col [4]; int lig [4];
    numCase destinationSansPrise, destinationAvecPrise, destinationPossible;
    PIECE PDestinationSansPrise,PDestinationAvecPrise, PSource;
    numCase *casesPossibles = NULL;
    casesPossibles = (numCase *)malloc(4*sizeof(numCase));

    PSource = tabDamier[source.c][source.l];
    COULP joueur = PSource.coulP;

    if (PSource.typeP == VIDE)
        return false;
    
    if (PSource.typeP==PION)
    {
        taille=2;
        if (PSource.coulP==BLANC)
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
        col[0] = 1; col[1] = 1; col[2] = -1; col[3] = -1;
        lig[0] = 1; lig[1] = -1;lig[2] = 1;  lig[3] = -1;
    }

    for (i = 0; i != taille; i++)
    {
        destinationSansPrise.c = col[i]; destinationSansPrise.l = lig[i];
        destinationAvecPrise.c = col[i]*2;  destinationAvecPrise.l = lig[i]*2;

        if (source.c + destinationSansPrise.c >= 0 && source.l + destinationSansPrise.l >=0 && 
        source.c + destinationSansPrise.c < 10 && source.l + destinationSansPrise.l < 10)
        {
            PDestinationSansPrise = tabDamier[source.c + destinationSansPrise.c][source.l + destinationSansPrise.l];
            PDestinationAvecPrise = tabDamier[source.c + destinationAvecPrise.c][source.l + destinationAvecPrise.l];

            if (PDestinationSansPrise.typeP==VIDE)
            {
                destinationPossible.c = source.c + destinationSansPrise.c;
                destinationPossible.l = source.l + destinationSansPrise.l;
                casesPossibles[compteur] = destinationPossible;
                compteur++;
            } else if (PDestinationSansPrise.coulP != joueur && PDestinationAvecPrise.typeP==VIDE && PDestinationSansPrise.typeP != VIDE &&
            source.c + destinationAvecPrise.c >= 0 && source.l + destinationAvecPrise.l >=0 && 
            source.c + destinationAvecPrise.c < 10 && source.l + destinationAvecPrise.l < 10)
            {
                destinationPossible.c = source.c + destinationAvecPrise.c;
                destinationPossible.l = source.l + destinationAvecPrise.l;
                casesPossibles[compteur] = destinationPossible;
                compteur++;
            }
        }
    }

    *tailleCmpt = compteur;
    return casesPossibles;
}
