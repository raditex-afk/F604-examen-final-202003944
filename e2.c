/* Lee un nombre completo y lo saluda con dos espacios despues de Hola. */
#include <stdio.h>
#include <stdlib.h>

int leer_linea(char **linea, size_t *capacidad, size_t *longitud);

int main(void)
{
    char *nombre = NULL;
    size_t capacidad = 0, longitud = 0;
    int estado;
    printf("Ingrese un nombre\n");
    estado = leer_linea(&nombre, &capacidad, &longitud);
    if (estado <= 0) {
        fprintf(stderr, "No se pudo leer el nombre\n");
        free(nombre);
        return 1;
    }
    if (longitud > 0 && nombre[longitud - 1] == '\n') --longitud;
    printf("Hola  ");
    fwrite(nombre, 1, longitud, stdout);
    putchar('\n');
    free(nombre);
    return ferror(stdout) ? 1 : 0;
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
