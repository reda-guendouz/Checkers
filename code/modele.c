#include "modele.h"

int absol(int val){
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
                if (i==4 && j==5)
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


void appliqueCoup(numCase source, numCase destination){
    PIECE P = tableau[destination.c][destination.l];
    printf("distance = %d\n",absol(destination.c - source.c));

    if (destination.c==9 || destination.c==0)
    {
        if (tableau[source.c][source.l].coulP==NOIR && destination.c==0)
            tableau[source.c][source.l].typeP=DAME;
        else if (tableau[source.c][source.l].coulP==BLANC && destination.c==9)
            tableau[source.c][source.l].typeP=DAME;
    }

    if (absol(destination.c - source.c) != 1) // dans le cas d'une prise
    {
        numCase nc;
        nc.c = source.c + (destination.c - source.c)/2;
        nc.l = source.l + (destination.l - source.l)/2;
        tableau[nc.c][nc.l] = P; // car la destination est toujours vide    
    }

    tableau[destination.c][destination.l] = tableau[source.c][source.l];
    tableau[source.c][source.l] = P;
}


numCase* numCases_possibles_apres_prise(numCase source,int *tailleCmpt){
    int compteur=0,i;
    int col [4] = {1,1,-1,-1};
    int lig [4] = {1,-1,1,-1};
    numCase possible,prise,retour;
    PIECE P,PDestination;
    COULP joueur;
    numCase *casesPossibles = NULL;
    casesPossibles = (numCase *)malloc(4*sizeof(numCase));

    if (tableau[source.c][source.l].typeP == VIDE)
        return false; 
    joueur = tableau[source.c][source.l].coulP;

    for (i = 0; i != 4; i++)
    {
        possible.c = col[i]; possible.l = lig[i];
        prise.c = col[i]*2;  prise.l = lig[i]*2;
        P = tableau[source.c + possible.c][source.l + possible.l];
        PDestination = tableau[source.c + prise.c][source.l + prise.l];
        if (P.coulP != joueur && PDestination.typeP==VIDE && 
        source.c + prise.c >= 0 && source.l + prise.l >=0 && source.c + prise.c < 10 && source.l + prise.l < 10)
        // meme verification pour les cases a distance de 2 (dans le cas d'une prise)
        {
            retour.c = source.c + prise.c;
            retour.l = source.l + prise.l;
            casesPossibles[compteur] = retour;
            compteur++;
        }
    }

    for (i = 0; i != compteur; i++)
		printf("numero %d : c(%d)\tl(%d)\n",i,casesPossibles[i].c,casesPossibles[i].l);

    *tailleCmpt = compteur;
    return casesPossibles;
}

numCase* numCases_possibles_avant_prise(numCase source,int *tailleCmpt){
    int compteur=0, i, taille;
    int col [4]; int lig [4];
    numCase possible,prise,retour;
    PIECE P,PDestination,PSource;
    numCase *casesPossibles = NULL;
    casesPossibles = (numCase *)malloc(4*sizeof(numCase));

    PSource = tableau[source.c][source.l];
    if (PSource.typeP == VIDE)
        return false; 
    COULP joueur = PSource.coulP;
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
        lig[0] = 1; lig[1] = -1;lig[2] = 1; lig[3] = -1;
    }

    for (i = 0; i != taille; i++)
    {
        possible.c = col[i]; possible.l = lig[i];
        prise.c = col[i]*2;  prise.l = lig[i]*2;
        // verification que les 4 cases de distance 1 sont bien incluses dans le damier (evitons de se deplacer en doehors du damier)
        if (source.c + possible.c >= 0 && source.l + possible.l >=0 && source.c + possible.c < 10 && source.l + possible.l < 10)
        {
            P = tableau[source.c + possible.c][source.l + possible.l];
            PDestination = tableau[source.c + prise.c][source.l + prise.l];
            if (P.typeP==VIDE)
            {
                retour.c = source.c + possible.c;
                retour.l = source.l + possible.l;
                casesPossibles[compteur] = retour;
                compteur++;
            } else if (P.coulP != joueur && PDestination.typeP==VIDE && 
            source.c + prise.c >= 0 && source.l + prise.l >=0 && source.c + prise.c < 10 && source.l + prise.l < 10)
            // meme verification pour les cases a distance de 2 (dans le cas d'une prise)
            {
                retour.c = source.c + prise.c;
                retour.l = source.l + prise.l;
                casesPossibles[compteur] = retour;
                compteur++;
            }
        }
    }

    for (i = 0; i != compteur; i++)
		printf("numero %d : c(%d)\tl(%d)\n",i,casesPossibles[i].c,casesPossibles[i].l);

    *tailleCmpt = compteur;
    return casesPossibles;
}
