/* Agrega titulo y encabezados a la tabla Fahrenheit-Celsius del profesor.
   Adaptado de https://github.com/ECFM-USAC/led-F604/blob/main/src/ejemplo1.c
   Conserva los limites 0 y 300, el incremento 20 y los datos con un decimal. */
#include <stdio.h>

int main(void)
{
    int lower = 0, upper = 300, step = 20;
    float fahr = lower, celsius;
    printf("Tabla de conversion: Fahrenheit a Celsius\n");
    printf("%4s %6s\n", "F", "C");
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%4.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}
