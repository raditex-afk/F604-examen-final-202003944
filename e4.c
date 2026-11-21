/* Genera una tabla Celsius-Fahrenheit desde 0 hasta 100 en pasos de 10.
   Estructura inspirada en el ejemplo del profesor:
   https://github.com/ECFM-USAC/led-F604/blob/main/src/ejemplo1.c */
#include <stdio.h>

int main(void)
{
    int celsius = 0;
    double fahrenheit;
    printf("Tabla de conversion: Celsius a Fahrenheit\n");
    printf("%7s %10s\n", "Celsius", "Fahrenheit");
    while (celsius <= 100) {
        fahrenheit = (9.0 / 5.0) * celsius + 32.0;
        printf("%7d %10.1f\n", celsius, fahrenheit);
        celsius += 10;
    }
    return 0;
}
