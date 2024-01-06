#include <stdio.h>
#include <stdlib.h>
#include "plansza.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        return 1;
    }

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);


    int **tab = (int **)malloc((n+1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        tab[i] = (int *)malloc((m+1) * sizeof(int));
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            tab[i][j] = 0; 
        }
    }
	tab[m-2][n-1]=1;
    int itr = atoi(argv[3]);
    int kierunek = atoi(argv[4]);//0 - gora, 1 - prawo, 2 - dol, 3 - lewo
	
    rysuj(m, n, (m+1)/2, (n+1)/2, kierunek, tab);
    for ( int i=0 ; i<itr ; i++ ){


    }
    printf("%d\n",itr);

    for (int i = 0; i <= n; i++) {
        free(tab[i]);
    }
    free(tab);

    return 0;
}

