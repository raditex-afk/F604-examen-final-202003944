/* Sustituye TAB por >, retroceso, -; y retroceso por <, retroceso, -.
   Los reemplazos contienen el byte 0x08 real, no la cadena literal \\b. */
#include <stdio.h>

int main(void)
{
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            putchar('>');
            putchar('\b');
            putchar('-');
        } else if (c == '\b') {
            putchar('<');
            putchar('\b');
            putchar('-');
        } else {
            putchar(c);
        }
    }
    return ferror(stdin) || ferror(stdout) ? 1 : 0;
}
