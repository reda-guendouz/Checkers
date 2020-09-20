int tableau[10][10];
/************************
* Tableau :
* -1 => case claire (impossible de s'y déplacer)
* 0  => case jouable (sombre)
* 1  => case occupée par un pion blanc
* 2  => case occupée par un pion noir
*************************/

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
                else if (c>6)
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