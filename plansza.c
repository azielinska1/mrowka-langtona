#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "plansza.h"

void rysuj (int m, int n){
	for ( int j=0; j<n; j++)
	{
		for ( int i=0; i<m; i++)
        	{
			printf("┌─┐");
	        }
		printf("\n");
		for ( int i=0; i<m; i++)
                {
                        printf("│ │");
                }
		printf("\n");
		for ( int i=0; i<m; i++)
                {
                        printf("└─┘");

                }
		printf("\n");


	}
// SQUARE_WHITE: 
// SQUARE_BLACK:█
}

