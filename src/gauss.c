#include "gauss.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 * Zwraca 0 - eliminacja zakończona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
    int i, j, k;
    int n = mat->r;
    
    // Elimnacja Gaussa
    for (i = 0; i < n; i++) {
        // Szukamy największego elementu w kolumnie i, aby uniknąć dzielenia przez 0
        if (mat->data[i][i] == 0) {
            int swapRow = -1;
            for (j = i + 1; j < n; j++) {
                if (mat->data[j][i] != 0) {
                    swapRow = j;
                    break;
                }
            }
            // Jeżeli nie znaleźliśmy niezerowego elementu, to macierz jest osobliwa
            if (swapRow == -1) {
                return 1;  // Macierz osobliwa
            }
            // Zamieniamy wiersze
            for (j = 0; j < n; j++) {
                double temp = mat->data[i][j];
                mat->data[i][j] = mat->data[swapRow][j];
                mat->data[swapRow][j] = temp;
            }
            // Zamieniamy również wektor b
            double temp = b->data[i][0];
            b->data[i][0] = b->data[swapRow][0];
            b->data[swapRow][0] = temp;
        }

        // Przechodzimy przez wszystkie wiersze poniżej i zerujemy wartości w kolumnie i
        for (j = i + 1; j < n; j++) {
            double factor = mat->data[j][i] / mat->data[i][i];
            for (k = i; k < n; k++) {
                mat->data[j][k] -= mat->data[i][k] * factor;
            }
            b->data[j][0] -= b->data[i][0] * factor;
        }
    }

    // Podstawienie wsteczne (rozwiązanie układu równań)
    for (i = n - 1; i >= 0; i--) {
        for (j = i + 1; j < n; j++) {
            b->data[i][0] -= mat->data[i][j] * b->data[j][0];
        }
        b->data[i][0] /= mat->data[i][i];
    }

    return 0;  // Sukces
}
