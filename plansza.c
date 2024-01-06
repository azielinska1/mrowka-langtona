#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "plansza.h"

void rysuj (int m, int n, int mrowka_m, int mrowka_n, int kierunek){

	for ( int j=1; j<=n; j++)
	{
		for ( int i=1; i<=m; i++)
        	{
			printf("┌─┐");
	        }
		printf("\n");
		for ( int i=1; i<=m; i++)
                {
			if (i == mrowka_m && j == mrowka_n)
			{
				if ( kierunek == 0 ) printf("│△│");
				if ( kierunek == 1 ) printf("│▷│");
				if ( kierunek == 2 ) printf("│▽│");
				if ( kierunek == 3 ) printf("│◁│");
			
			}
			else printf("│ │");
                }
		printf("\n");
		for ( int i=1; i<=m; i++)
                {
                        printf("└─┘");

                }
		printf("\n");


	}
// SQUARE_WHITE: 
// SQUARE_BLACK:█
}

