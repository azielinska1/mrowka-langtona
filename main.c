#include <stdio.h>
#include <stdlib.h>
#include "plansza.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        return 1;
    }

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);

    int itr = atoi(argv[3]);
    int kierunek = atoi(argv[4]);//0 - gora, 1 - prawo, 2 - dol, 3 - lewo
	
    rysuj(m, n, (m+1)/2, (n+1)/2, kierunek);
    for ( int i=0 ; i<itr ; i++ ){


    }
    printf("%d\n",itr);

    return 0;
}

