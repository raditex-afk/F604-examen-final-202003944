/* Lee un entero e imprime el mismo valor, como el programa Python. */
#include <stdio.h>

int main(void)
{
    int valor;
    printf("Ingrese un valor entero\n");
    if (scanf("%d", &valor) != 1) {
        fprintf(stderr, "Entrada no valida\n");
        return 1;
    }
    printf("Salida: %d\n", valor);
    return 0;
}
