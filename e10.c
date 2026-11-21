/* Cuenta palabras por longitud y dibuja un histograma horizontal.
   Separadores tomados del ejemplo (el histograma es una implementacion propia):
   https://github.com/ECFM-USAC/led-F604/blob/main/src/word_counting.c */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t *frecuencia = NULL, *temporal;
    size_t capacidad = 0, longitud = 0, maxima = 0, nueva, i, j;
    int c;
    do {
        c = getchar();
        if (c == EOF || c == ' ' || c == '\t' || c == '\n') {
            if (longitud > 0) {
                ++frecuencia[longitud];
                if (longitud > maxima) maxima = longitud;
                longitud = 0;
            }
        } else {
            if (longitud == (size_t)-1) goto error;
            ++longitud;
            if (longitud >= capacidad) {
                if (capacidad > (size_t)-1 / 2) goto error;
                nueva = capacidad == 0 ? 16 : capacidad * 2;
                if (nueva > (size_t)-1 / sizeof(*frecuencia)) goto error;
                temporal = realloc(frecuencia, nueva * sizeof(*frecuencia));
                if (temporal == NULL) goto error;
                frecuencia = temporal;
                for (i = capacidad; i < nueva; ++i) frecuencia[i] = 0;
                capacidad = nueva;
            }
        }
    } while (c != EOF);
    if (ferror(stdin)) goto error;
    printf("Longitud | Cantidad de palabras | Histograma\n");
    if (maxima == 0) printf("Sin palabras\n");
    for (i = 1; i <= maxima; ++i) {
        if (frecuencia[i] > 0) {
            printf("%8zu | %20zu | ", i, frecuencia[i]);
            for (j = 0; j < frecuencia[i]; ++j) putchar('*');
            putchar('\n');
        }
    }
    free(frecuencia);
    return ferror(stdout) ? 1 : 0;

error:
    fprintf(stderr, "Error de lectura o memoria insuficiente\n");
    free(frecuencia);
    return 1;
}
