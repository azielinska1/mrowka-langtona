#include <stdio.h>
#include <stdlib.h>
#include "plansza.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        return 1;
    }

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);


    int **tab = (int **)malloc((n+2) * sizeof(int *));
    for (int i = 0; i <= n+1; i++) {
        tab[i] = (int *)malloc((m+2) * sizeof(int));
    }

    for (int i = 0; i <= m+1; i++) {
        for (int j = 0; j <= n+1; j++) {
		if (i==0 || j==0 || i==m+1 || j==n+1) tab[i][j]=2;//sciany
		else tab[i][j] = 0; 
        }
    }
    int itr = atoi(argv[3]);
    int kierunek = atoi(argv[4]);//0 - gora, 1 - prawo, 2 - dol, 3 - lewo
    //wspolrzedne mrowki
    int x=(m+1)/2;
    int y=(n+1)/2;
    for (int i = 0; i <= m+1; i++) {
        for (int j = 0; j <= n+1; j++) {
                printf ("%d",tab[i][j]);
        }
	printf("\n");
    }
    rysuj(m, n, x, y, kierunek, tab);
    for ( int i=0 ; i<itr ; i++ ){
	if ( tab[x][y]==0 ) //komorka jest biala
	{
		kierunek=(kierunek+1)%4;//przekrecenie w prawo
		tab[x][y]=1;
	}
	else //komorka jest czarna
	{
		kierunek=(kierunek+3)%4;//przekrecenie w lewo
		tab[x][y]=0;
	}
	if (kierunek==0) y--;
        if (kierunek==1) x++;
        if (kierunek==2) y++;
        if (kierunek==3) x--;
	if (tab[x][y]==2) { printf("Mrowka wyszla poza plansze\n"); return 2; }
	rysuj (m, n, x, y, kierunek, tab);
    }
    printf("%d\n",itr);

    for (int i = 0; i <= n+1; i++) {
        free(tab[i]);
    }
    free(tab);

    return 0;
}

