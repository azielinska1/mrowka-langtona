#include <stdio.h>
#include <stdlib.h>
#include "plansza.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Podaj dwie liczby calkowite jako argumenty programu.\n");
        return 1;
    }

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);

    rysuj(m, n);

    return 0;
}

