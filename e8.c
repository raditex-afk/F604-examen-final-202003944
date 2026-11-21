/* Reduce cada secuencia de espacios normales a uno, preservando tabs. */
#include <stdio.h>

int main(void)
{
    int c, espacio_anterior = 0;
    while ((c = getchar()) != EOF) {
        if (c != ' ' || !espacio_anterior) putchar(c);
        espacio_anterior = c == ' ';
    }
    return ferror(stdin) || ferror(stdout) ? 1 : 0;
}
