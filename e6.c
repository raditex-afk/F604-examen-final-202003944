/* Imprime las lineas con mas de 80 caracteres sin contar el salto.
   Guarda solo los primeros 81 bytes y luego copia directamente hasta EOF. */
#include <stdio.h>

int main(void)
{
    unsigned char inicio[81];
    size_t longitud = 0;
    int c, seleccionada = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            if (seleccionada) putchar(c);
            longitud = 0;
            seleccionada = 0;
        } else if (seleccionada) {
            putchar(c);
        } else {
            inicio[longitud++] = (unsigned char)c;
            if (longitud == 81) {
                fwrite(inicio, 1, longitud, stdout);
                seleccionada = 1;
            }
        }
    }
    return ferror(stdin) || ferror(stdout) ? 1 : 0;
}
