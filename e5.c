/* Quita espacios y tabulaciones finales y suprime las lineas vacias.
   Lectura hasta EOF inspirada en:
   https://github.com/ECFM-USAC/led-F604/blob/main/src/character_counting.c */
#include <stdio.h>
#include <stdlib.h>

int leer_linea(char **linea, size_t *capacidad, size_t *longitud);

int main(void)
{
    char *linea = NULL;
    size_t capacidad = 0, longitud = 0;
    int estado, salto;
    while ((estado = leer_linea(&linea, &capacidad, &longitud)) == 1) {
        salto = linea[longitud - 1] == '\n';
        if (salto) --longitud;
        while (longitud > 0 &&
               (linea[longitud - 1] == ' ' || linea[longitud - 1] == '\t'))
            --longitud;
        if (longitud > 0) {
            fwrite(linea, 1, longitud, stdout);
            if (salto) putchar('\n');
        }
    }
    free(linea);
    if (estado < 0) fprintf(stderr, "Error de lectura o memoria insuficiente\n");
    return estado < 0 || ferror(stdout) ? 1 : 0;
}

/* Lee una linea completa sin truncarla; conserva el salto si existe.
   Devuelve 1 al leer, 0 al llegar a EOF y -1 ante un error. */
int leer_linea(char **linea, size_t *capacidad, size_t *longitud)
{
    int c;
    *longitud = 0;
    while ((c = getchar()) != EOF) {
        if (*longitud + 1 >= *capacidad) {
            size_t nueva;
            char *temporal;
            if (*capacidad > (size_t)-1 / 2) return -1;
            nueva = *capacidad == 0 ? 128 : *capacidad * 2;
            temporal = realloc(*linea, nueva);
            if (temporal == NULL) return -1;
            *linea = temporal;
            *capacidad = nueva;
        }
        (*linea)[(*longitud)++] = (char)c;
        if (c == '\n') break;
    }
    if (ferror(stdin)) return -1;
    if (*longitud == 0) return 0;
    (*linea)[*longitud] = '\0';
    return 1;
}
