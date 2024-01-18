#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include "wersja2.h"

int  zczytywanie(int wymiar_m, int wymiar_n, int *x, int *y, int *kierunek, int **t) {
    char buffer[256];
    char *nazwapliku;

    printf("Podaj nazwe pliku: ");
    
    if (scanf("%255s", buffer) != 1) {
        fprintf(stderr, "Błąd podczas wczytywania nazwy pliku.\n");
        return 1; 
    }

    nazwapliku = malloc(strlen(buffer) + 1);
    if (nazwapliku == NULL) {
        fprintf(stderr, "Błąd alokacji pamięci.\n");
        return 1;
    }

    strcpy(nazwapliku, buffer);
    
    FILE *plik = fopen(nazwapliku, "r");
    if (plik == NULL) {
        fprintf(stderr, "Błąd otwarcia pliku.\n");
        free(nazwapliku);
        return 1;
    }
    
    int m = 0, tn = 1, n;
    char znak;

    setlocale(LC_ALL, "C.UTF-8");
    
    
    while ((znak = fgetc(plik)) != EOF) {

		if (znak == '\n') {
		    tn++;
		    m = 1;
		} else if (znak == ' ') {
		    m++;
		} 
		n=tn/3;
		if (znak == "█") {	//
		
		printf("m=%d,n=%d\n",m,n);
		    t[m][n] = 1;
		    m++;
		} else if (znak == 0x25B3) {  // △
		
		    m++;
		    *x = m;
		    *y = n + 1;
		    *kierunek = 0;
		} else if (znak == 0x25B2) {  // ▲
		
		    m++;
		    *x = m;
		    *y = n;
		    *kierunek = 0;
		    t[m][n] = 1;
		} else if (znak == 0x25B7) {  // ▷
		    m++;
		    *x = m;
		    *y = n + 1;
		    *kierunek = 1;
		} else if (znak == 0x25B6) {  // ▶
		    m++;
		    *x = m;
		    *y = n + 1;
		    *kierunek = 1;
		    t[m][n] = 1;
		} else if (znak == 0x25BD) {  // ▽
		printf("m=%d,n=%d\n",m,n);
		    m++;
		    *x = m;
		    *y = n + 1;
		    *kierunek = 2;
		} else if (znak == 0x25BC) {  // ▼
		    m++;
		    *x = m;
		    *y = n + 1;
		    *kierunek = 2;
		    t[m][n] = 1;
		} else if (znak == 0x25C1) {  // ◁
		    m++;
		    *x = m;
		    *y = n + 1;
		    *kierunek = 3;
		} else if (znak == 0x25C0) {  // ◀
		    m++;
		    *x = m;
		    *y = n + 1;
		    *kierunek = 3;
		    t[m][n] = 1;
		}
        
    }

    fclose(plik);
    free(nazwapliku);
    return 0;
}

