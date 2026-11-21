/* Invierte cada linea con reverse(s), conservando su salto final. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char s[]);
int leer_linea(char **linea, size_t *capacidad, size_t *longitud);

int main(void)
{
    char *linea = NULL;
    size_t capacidad = 0, longitud = 0;
    int estado, salto;
    while ((estado = leer_linea(&linea, &capacidad, &longitud)) == 1) {
        salto = linea[longitud - 1] == '\n';
        if (salto) --longitud;
        linea[longitud] = '\0';
        reverse(linea);
        fwrite(linea, 1, longitud, stdout);
        if (salto) putchar('\n');
    }
    free(linea);
    if (estado < 0) fprintf(stderr, "Error de lectura o memoria insuficiente\n");
    return estado < 0 || ferror(stdout) ? 1 : 0;
}

void reverse(char s[])
{
    size_t izquierda = 0, derecha = strlen(s);
    char temporal;
    while (izquierda < derecha) {
        --derecha;
        if (izquierda >= derecha) break;
        temporal = s[izquierda];
        s[izquierda] = s[derecha];
        s[derecha] = temporal;
        ++izquierda;
    }
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
