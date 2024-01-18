#include <stdio.h>
#include <stdlib.h>
#include "plansza.h"
#include "wersja2.h"
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;
    int wersja;
    int m = 0, n = 0;  // Wymiary planszy
    int itr;            // Liczba iteracji
    int kierunek;       // 0 - góra, 1 - prawo, 2 - dół, 3 - lewo
    int x, y;           // Współrzędne mrówki
    char Pliczek[] = NULL;

    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
            case 'f':
                Pliczek = optarg;
                break;
            default:
                fprintf(stderr, "Użycie: %s [-f plik_wyjsciowy]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (argc - optind != 1) {
        fprintf(stderr, "Uzycie: %s [-o plik_wyjsciowy] <wersja>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    wersja = atoi(argv[optind]);

    if (wersja < 1 || wersja > 3) {
        fprintf(stderr, "Błąd: Nieprawidłowa wartość dla wersji.\n");
        exit(EXIT_FAILURE);
    }

    printf("Podaj wymiary:\n");

    if (scanf("%d %d", &m, &n) != 2 || m <= 0 || n <= 0) {
        fprintf(stderr, "Błąd: Podano nieprawidłowe wymiary planszy.\n");
        exit(EXIT_FAILURE);
    }

    printf("Podaj liczbe iteracji:\n");

    if (scanf("%d", &itr) != 1 || itr <= 0) {
        fprintf(stderr, "Błąd: Podano nieprawidłową liczbę iteracji.\n");
        exit(EXIT_FAILURE);
    }

    int **tab = (int **)malloc((m + 2) * sizeof(int *));
    for (int i = 0; i <= m + 1; i++) {
        tab[i] = (int *)malloc((n + 2) * sizeof(int));
    }

    for (int i = 0; i <= m + 1; i++) {
        for (int j = 0; j <= n + 1; j++) {
            if (i == 0 || j == 0 || i == m + 1 || j == n + 1)
                tab[i][j] = 2;
            else
                tab[i][j] = 0;
        }
    }

    if (wersja == 1) {
        printf("Podaj kierunek mrowki (0 - gora, 1 - prawo, 2 - dol, 3 - lewo):\n");
        scanf("%d", &kierunek);

        x = (m + 1) / 2;
        y = (n + 1) / 2;
    } else if (wersja == 2) {
        if (zczytywanie(m, n, &x, &y, &kierunek, tab) != 0) {
            fprintf(stderr, "Blad: Wczytywanie pliku nie powiodlo sie.\n");
            for (int i = 0; i <= m + 1; i++) {
                free(tab[i]);
            }
            free(tab);
            exit(EXIT_FAILURE);
        }
    }

    FILE *out;

    if (Pliczek != NULL) {
        out = fopen(Pliczek, "w");
        if (out == NULL) {
            fprintf(stderr, "Blad: Nie mozna otworzyć pliku %s\n", Pliczek);
            for (int i = 0; i <= m + 1; i++) {
                free(tab[i]);
            }
            free(tab);
            exit(EXIT_FAILURE);
        }
    } else {
        out = stdout; 
    }
    rysuj(m, n, x, y, kierunek, tab, out);

    if (Pliczek != NULL) {
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

        if (x < 1 || x > m + 1 || y < 1 || y > n + 1) {
            fprintf(stderr, "Mrowka wyszla poza plansze w iteracji %d\n", i);
            for (int i = 0; i <= m + 1; i++) {
                free(tab[i]);
            }
            free(tab);
            exit(EXIT_FAILURE);
        }
        if (Pliczek != NULL) {
            char NazwaPliku[50];
            sprintf(NazwaPliku, "%s_%d.txt", Pliczek, i + 1);
            out = fopen(NazwaPliku, "w");
            if (out == NULL) {
                fprintf(stderr, "Blad: Nie mozna otworzyc pliku %s\n", NazwaPliku);
                for (int i = 0; i <= m + 1; i++) {
                    free(tab[i]);
                }
                free(tab);
                exit(EXIT_FAILURE);
            }
        } else {
            out = stdout; 
        }
        rysuj(m, n, x, y, kierunek, tab, out);

        if (Pliczek != NULL) {
            fclose(out);
        }
    }
    for (int i = 0; i <= m + 1; i++) {
        free(tab[i]);
    }
    free(tab);

    return 0;
}
