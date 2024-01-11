#include <stdio.h>
#include <stdlib.h>
#include "plansza.h"
#include "wersja2.h"
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Błąd: Podano zbyt wiele argumentów.\n");
        return 1;
    }

    int wersja;
    int m = 0, n = 0;  // Wymiary planszy
    int itr;            // Liczba iteracji
    int kierunek;       // 0 - góra, 1 - prawo, 2 - dół, 3 - lewo
    int x, y;           // Współrzędne mrówki

    printf("Wersje:\n");
    printf("1 - wczytanie pustej planszy z mrówką na środku\n");
    printf("2 - wczytanie planszy z pliku\n");
    printf("3 - wygenerowanie losowo planszy\n");
    printf("Podaj liczbe:\n");
    scanf("%d", &wersja);

    printf("Podaj wymiary:\n");

    if (scanf("%d %d", &m, &n) != 2 || m <= 0 || n <= 0) {
        fprintf(stderr, "Błąd: Podano nieprawidłowe wymiary planszy.\n");
        return 1;
    }

    printf("Podaj liczbe iteracji:\n");

    if (scanf("%d", &itr) != 1 || itr <= 0) {
        fprintf(stderr, "Błąd: Podano nieprawidłową liczbę iteracji.\n");
        return 1;
    }

    int **tab = (int **)malloc((m + 2) * sizeof(int *)); // Stany planszy
    for (int i = 0; i <= m + 1; i++) {
        tab[i] = (int *)malloc((n + 2) * sizeof(int));
    }


    if (wersja == 1) {
        printf("Podaj kierunek mrówki (0 - góra, 1 - prawo, 2 - dół, 3 - lewo):\n");
        scanf("%d", &kierunek);

        x = (m + 1) / 2;
        y = (n + 1) / 2;
    }
    else if (wersja == 2) {
	if (zczytywanie(m, n, &x, &y, &kierunek, tab) != 0) {
            fprintf(stderr, "Błąd: Wczytywanie pliku nie powiodło się.\n");
            // Zwolnienie zaalokowanej pamięci przed zakończeniem programu
            for (int i = 0; i <= n + 1; i++) {
                free(tab[i]);
            }
            free(tab);
            return 1;
        }
    }

    // 'Ściany' nie pozwalające wyjść mrówce poza planszę
    for (int i = 0; i <= m + 1; i++) {
        for (int j = 0; j <= n + 1; j++) {
            if (i == 0 || j == 0 || i == m + 1 || j == n + 1)
                tab[i][j] = 2;
            else
                tab[i][j] = 0;
        }
    }

    FILE *out = argc > 1 ? fopen(argv[1], "w") : stdout;
    char NazwaPliku[50];
    if (argc == 2) {
        out = fopen(argv[1], "w");
        if (out == NULL) {
        
            fprintf(stderr, "Błąd: nie można otworzyć pliku %s\n", argv[1]);
            // Zwolnienie zaalokowanej pamięci przed zakończeniem programu
            for (int i = 0; i <= n + 1; i++) {
                free(tab[i]);
            }
            free(tab);
            return 1;
        }
    } else {
        out = stdout; // Standardowe wyjście
    }

    rysuj(m, n, x, y, kierunek, tab, out);

    if (argc == 2) {
        fclose(out);
    }

    for (int i = 0; i < itr; i++) {
        if (tab[x][y] == 0) {
            kierunek = (kierunek + 1) % 4;
            tab[x][y] = 1;
        } else {
            kierunek = (kierunek + 3) % 4;
            tab[x][y] = 0;
        }
        if (kierunek == 0)
            y--;
        if (kierunek == 1)
            x++;
        if (kierunek == 2)
            y++;
        if (kierunek == 3)
            x--;

        if (x < 1 || x > m+1 || y < 1 || y > n+1) {
            fprintf(stderr, "Mrowka wyszla poza plansze w iteracji %d\n", i);
            // Zwolnienie zaalokowanej pamięci przed zakończeniem programu
            for (int i = 0; i <= n + 1; i++) {
                free(tab[i]);
            }
            free(tab);
            return 2;
        }
        if (argc == 2) {
            sprintf(NazwaPliku, "%s_%d.txt", argv[1], i + 1);
            out = fopen(NazwaPliku, "w");
            if (out == NULL) {
                fprintf(stderr, "Błąd: nie można otworzyć pliku %s\n", NazwaPliku);
                // Zwolnienie zaalokowanej pamięci przed zakończeniem programu
                for (int i = 0; i <= n + 1; i++) {
                    free(tab[i]);
                }
                free(tab);
                return 1;
            }
        } else {
            out = stdout; // Standardowe wyjście
        }
	rysuj(m, n, x, y, kierunek, tab, out);

        if (argc == 2) {
            fclose(out);
        }
    }

    // Zwolnienie zaalokowanej pamięci przed zakończeniem programu
    for (int i = 0; i <= n + 1; i++) {
        free(tab[i]);
    }
    free(tab);

    return 0;
}

